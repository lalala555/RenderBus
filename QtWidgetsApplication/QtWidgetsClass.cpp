#include "QtWidgetsClass.h"
#include "QtNetwork\qhostinfo.h"
#include <QCryptographicHash>
#include <qdebug.h>
#include <qjsonarray.h>
#include <QJsonParseError>
#include <QJsonObject>
#include <QEventLoop>
#include <qurlquery.h>
#include "QtTipsDialog.h"
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QHBoxLayout>
#include <QStyleFactory>
#include <QMessageBox>

QtWidgetsClass::QtWidgetsClass(QWidget *parent)	: QWidget(parent)
{
	ui.setupUi(this);

	ui.lineEdit_user->setText("TD_MAX");
	ui.lineEdit_2->setText("Abc123456");
	m_alldata.clear();
	m_Request = new QNetworkRequest;
	m_Manager = new QNetworkAccessManager;
	m_websocket = new QWebSocket;
	m_userkey = "";

	//初始化树
	m_item = new QTreeWidgetItem;
	m_item->setText(0, "genmulu");
	ui.treeWidget->addTopLevelItem(m_item);
	m_checkbox = new QCheckBox();
	//m_serversocket = new QWebSocketServer("server", QWebSocketServer::NonSecureMode);
	//m_serversocket->listen(QHostAddress::Any, 2121);
	//connect(m_serversocket, SIGNAL(newConnection()), this, SLOT(slotNewConnect()));

	connect(m_Manager, SIGNAL(finished(QNetworkReply *reply)), this, SLOT(on_finished(QNetworkReply *reply)));

	connect(m_websocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::AutoConnection);

	connect(m_websocket, SIGNAL(connected()), this, SLOT(onConnected()), Qt::AutoConnection);

	connect(m_websocket, SIGNAL(sslErrors(const QList<QSslError> &)), this, SLOT(slotSslErrors(const QList<QSslError> &)), Qt::AutoConnection);

	connect(m_websocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

	connect(m_websocket, SIGNAL(binaryMessageReceived(const QByteArray&)), this, SLOT(onTextReceived(const QByteArray&)));

	connect(m_websocket, SIGNAL(textMessageReceived(const QString&)), this, SLOT(onTextMessageReceived(const QString&)));

	//tablewidget连接
	connect(ui.tableWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(clickedchange(int, int)));

	//treewidget连接
	m_checkheaderview = new CheckBoxHeaderView(0, QPoint(26, 13), QSize(20, 20), Qt::Horizontal, this);
	m_checkheaderview->setObjectName(QStringLiteral("m_checkHeaderView"));
	m_checkheaderview->setStretchLastSection(true);
	connect(m_checkheaderview, SIGNAL(checkStatusChange(bool)), this, SLOT(SetAlarmListCheckState(bool)));
	connect(m_checkheaderview, &CheckBoxHeaderView::checkStatusChange, this, &QtWidgetsClass::SetAlarmListCheckState);
	
	connect(ui.tableWidget, SIGNAL(cellClicked(int, int)), m_checkheaderview, SLOT(checkstate(int, int)));
	connect(m_checkbox, SIGNAL(stateChanged(int)), m_checkheaderview, SLOT(checkstate(int)));

	m_Reply = Q_NULLPTR;
	Init();
	//connectToServer();

}

QtWidgetsClass::~QtWidgetsClass()
{
}

void QtWidgetsClass::Init()
{

}

void QtWidgetsClass::postSignIn(QUrl &u)
{
	//QNetworkRequest request;
	url = u;
	m_Request->setUrl(url);

	QString username = ui.lineEdit_user->text();
	QString password = ui.lineEdit_2->text();
	m_username = username;
	//对密码进行加密
	int size = password.size();
	//等分为三份后每一块的大小
	int split = size / 3.0;
	//等分
	QString str1 = password.mid(0, split);
	QString str2 = password.mid(split, split);
	QString str3 = password.mid(split + split);
	QString newpass = QString("%1vaBci%2l6AF8%3vM9vH").arg(str1).arg(str2).arg(str3);
	//md5加密
	QCryptographicHash hash(QCryptographicHash::Sha1);
	hash.addData(newpass.toLatin1());
	QByteArray finalpass = hash.result().toHex();
	QString finalword = finalpass;

	m_password = finalword;

	/*QUrlQuery query;
	query.addQueryItem("loginName", username);
	query.addQueryItem("password", finalpass);
	url.setQuery(query);
	QString aa = url.toString();*/
	qDebug() << url;

	//m_Request->setRawHeader("userkey", "rsat:L4lkPYwkpJLAhIxHGhxm1Tnaq4g");
	//m_Request->setRawHeader("languageflag", "0");
	//m_Request->setRawHeader("platform", "2");
	m_Request->setRawHeader("signature", "rayvision2017");
	m_Request->setRawHeader("version", "1.0.0");
	//m_Request->setRawHeader("channel", "2");
	m_Request->setRawHeader("Content-Type", "application/json");

	QJsonDocument doc;
	QJsonObject jsonData;
	jsonData.insert("loginName", username);     // 设置用户名密码
	jsonData.insert("password", finalword);
	jsonData.insert("redirect", url.toString()); // 设置内容字段
	doc.setObject(jsonData);

	if (m_Reply != Q_NULLPTR)
	{
		//更改m_Reply指向位置前一定要保证之前的定义了自动delete
		// m_Reply->deleteLater();
	}
	QByteArray data;
	data = doc.toJson();
	m_Reply = m_Manager->post(*m_Request, data);

	//添加事件循环机制
	//QEventLoop eventLoop;
   // connect(m_Reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
   // eventLoop.exec();

	//qDebug() << replyData;

	qDebug() << "start get";

	//userLogin();

	connect(m_Reply, SIGNAL(readyRead()), this, SLOT(readyRead()));
	connect(m_Reply, SIGNAL(error(QNetworkReply::NetworkError)),
		this, SLOT(slotError(QNetworkReply::NetworkError)));
	connect(m_Reply, SIGNAL(sslErrors(QList<QSslError>)),
		this, SLOT(slotSslErrors(QList<QSslError>)));


}

void QtWidgetsClass::userLogin(QUrl &u, QString rsauthtoken)
{
	QNetworkRequest * req = new QNetworkRequest(u);
	QNetworkAccessManager *man = new QNetworkAccessManager;
	req->setRawHeader("signature", "rayvision2017");
	req->setRawHeader("version", "1.0.0");
	req->setRawHeader("Content-Type", "application/json");
	req->setRawHeader("platform", "2");
	req->setRawHeader("channel", "2");

	QJsonDocument doc;
	QJsonObject jsonData;
	jsonData.insert("userName", m_username);     // 设置用户名密码
	jsonData.insert("password", m_password);
	jsonData.insert("version","1.0.0"); 
	jsonData.insert("rsAuthToken", rsauthtoken);
	jsonData.insert("loginType", "");
	doc.setObject(jsonData);

	QByteArray data;
	data = doc.toJson();
	m_Reply1 = man->post(*req, data);
	connect(m_Reply1, SIGNAL(readyRead()), this, SLOT(readyReadTwo()));

}

void QtWidgetsClass::getUserDirFile(QUrl & u, QString userkey,QString treePath)
{
	QNetworkRequest * req = new QNetworkRequest(u);
	QNetworkAccessManager *man = new QNetworkAccessManager;
	req->setRawHeader("signature", "rayvision2017");
	req->setRawHeader("version", "1.0.0");
	req->setRawHeader("Content-Type", "application/json");
	req->setRawHeader("platform", "2");
	req->setRawHeader("channel", "2");
	req->setRawHeader("languageflag", "0");
	req->setRawHeader("userkey", userkey.toLatin1());

	QJsonDocument doc;
	QJsonObject jsonData;
	if (treePath == "")
	{
		treePath = "/";
	}
	jsonData.insert("treePath", treePath);     // 设置用户名密码
	doc.setObject(jsonData);

	QByteArray data;
	data = doc.toJson();
	m_Reply2 = man->post(*req, data);
	connect(m_Reply2, SIGNAL(readyRead()), this, SLOT(readyReadThree()));

}

void QtWidgetsClass::showTable(QList<FileData>& datalist)
{
	m_checkheaderview->setStyleSheet("alignment: left;");
	ui.tableWidget->setHorizontalHeader(m_checkheaderview);
	ui.tableWidget->horizontalHeader()->setVisible(true);
	
	


	ui.tableWidget->setRowCount(datalist.size());
	ui.tableWidget->setColumnCount(5);
	/*QList<QString> collist;
	collist.append("");
	collist.append("filename");
	collist.append("filesize");
	collist.append("updatedate");
	collist.append("filetype");

	ui.tableWidget->setHorizontalHeaderLabels(collist);*/
//	QTableWidgetItem *item = new QTableWidgetItem(QString(""));
	//ui.tableWidget->item(row, col)->setCheckState(Qt::Unchecked);
//	ui.tableWidget->setItem(0, 0, new QTableWidgetItem(""));
	//ui.tableWidget->item(0, 0)->setCheckState(Qt::Unchecked);
	for (int i = 0; i < datalist.size(); i++)
	{
		//QWidget *pWidget = new QWidget();
		//QHBoxLayout *hLayout = new QHBoxLayout();
		//m_checkbox = new QCheckBox();
		//m_checkbox->setCheckState(Qt::CheckState::Unchecked);
		//m_checkbox->setStyle(QStyleFactory::create("fusion"));
		//m_checkbox->setStyleSheet(QString("QCheckBox {margin:3px;border:0px;}QCheckBox::indicator {width: %1px; height: %1px; }").arg(20));
		//hLayout->addWidget(m_checkbox);
		//hLayout->setMargin(1); //设置边缘距离
		//hLayout->setAlignment(m_checkbox, Qt::AlignCenter); //居中
		//pWidget->setLayout(hLayout);
	
		QString fileName = datalist.at(i).fileName;
		QString fileSize = datalist.at(i).fileSize;
		QString lastModify = datalist.at(i).lastModify;
		QString fileType = datalist.at(i).fileType;
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(""));
		ui.tableWidget->setItem(i, 1,  new QTableWidgetItem(fileName));
		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(fileSize));
		ui.tableWidget->setItem(i, 3, new QTableWidgetItem(lastModify));
		ui.tableWidget->setItem(i, 4, new QTableWidgetItem(fileType));
		
		
		ui.tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
		//ui.tableWidget->setCellWidget(i, 0, pWidget);

	}
	
	//ui.tableWidget->setCellWidget(1, 0, pWidget);
	//ui.tableWidget->setHorizontalHeader(m_checkheaderview);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void QtWidgetsClass::connectToServer()
{
	QString path = "wss://local.raysync.cn:9527/"; 
	//QString path = "wss://127.0.0.1:2121";
	QUrl url = QUrl(path);
	m_websocket->open(url);
}

void QtWidgetsClass::removeItem(QTreeWidgetItem * item)
{
	if (!item)
		return;
	int count = item->childCount();
	if (count == 0)
		return;
	for (int i = 0; i < count; i++)
	{
		QTreeWidgetItem *childItem = item->child(0);
		delete childItem;
		//removeItem(childItem);
	}
	
}

void QtWidgetsClass::downLoadByPath(QList<QString> filepath)
{
	QString left = "";
	QString right = "";
	

	QByteArray data1;
	QByteArray data2;
	QByteArray data3;
	QByteArray data4;
	QByteArray data5;
	//QJsonArray array;
//	array.append("0");
     
	
	

	QJsonDocument doc4;
	QJsonObject jsonData2;
	
	for (int i = 0; i < filepath.size(); i++)
	{
		QString path = filepath.at(i);
		//分隔路径
		int index = path.lastIndexOf("/");
		if (index >= 0)
		{
			left = path.left(index);
		    right = path.right(path.size() - index - 1);
		}
		else
		{
			left = "";
			right = path;
		}
		

		QString dex = QString("%1").arg(i);
		jsonData2.insert(dex, right);
	}
	QJsonArray array1;
	array1.append(right);
	QJsonObject jsonData3;
	jsonData3.insert("names", array1);
	QString leftpath = QString("/input/100000849/%1").arg(left);
	jsonData3.insert("path", leftpath);
	jsonData3.insert("to", "");
	QJsonArray array2;
	array2.append(jsonData3);
	QJsonObject jsonData4;
	jsonData4.insert("action", "download");
	jsonData4.insert("src", array2);
	doc4.setObject(jsonData4);
	data4 = doc4.toJson(QJsonDocument::Compact);

	m_websocket->sendBinaryMessage(data4);
}

void QtWidgetsClass::on_pushButton_3_clicked()
{
	QUrl u = QUrl("https://task.renderbus.com/api/sso/sign/signIn");
	postSignIn(u);

}

void QtWidgetsClass::on_pushButton_clicked()
{
	connectToServer();
	function = 0;
	/*QJsonDocument doc1;
	QJsonObject jsonData1;
	jsonData1.insert("action", "list");
	jsonData1.insert("path", "/input/100000849/");
	doc1.setObject(jsonData1);
	QByteArray newdata1;
	newdata1 = doc1.toJson(QJsonDocument::Compact);

	QJsonDocument doc2;
	QJsonObject jsonData2;
	jsonData2.insert("action", "upload");
	jsonData2.insert("full_path", false);
	jsonData2.insert("path", "/input/100000849/");
	jsonData2.insert("type", 0);
	doc2.setObject(jsonData2);
	QByteArray newdata2;
	newdata2 = doc2.toJson(QJsonDocument::Compact);

	m_websocket->sendBinaryMessage(newdata1);
	m_websocket->sendBinaryMessage(newdata2);
*/
	/*ui.tableWidget->clear();
	QUrl u = QUrl("https://task.renderbus.com/api/rendering/file/operate/getUserDirFile");
	getUserDirFile(u, m_userkey);*/
    //上传后刷新界面
	//ui.tableWidget->clear();
	//QUrl u = QUrl("https://task.renderbus.com/api/sso/sign/signIn");
	//postSignIn(u);
	//QUrl u = QUrl("https://task.renderbus.com/api/rendering/file/operate/getUserDirFile");
	//getUserDirFile(u, m_userkey);

}

void QtWidgetsClass::on_finished(QNetworkReply *reply)
{
	//解析返回的Json结果
	QByteArray replyData = m_Reply->readAll();
	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData, &json_error));
	if (json_error.error != QJsonParseError::NoError)
	{
		return;
	}
	QJsonObject rootObj = jsonDoc.object();
	QString codeStr = rootObj.value("username").toString();

	QByteArray bytes = m_Reply->readAll();
	const QVariant redirectionTarget = m_Reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
	m_Reply->deleteLater();
	m_Reply = Q_NULLPTR;
	if (!redirectionTarget.isNull())
	{//如果网址跳转重新请求
		const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
		qDebug() << "redirectedUrl:" << redirectedUrl.url();
		//postSignIn(redirectedUrl);
		return;

	}
	qDebug() << "finished";
}

void QtWidgetsClass::on_pushButton_2_clicked()
{
	connectToServer();
	function = 1;
	//QList<QString> valuelist;
	//QList<QString> filepath;
	//QString treepath = "";
	//QString filename = "";
	//for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	//{
	//	bool aa = ui.tableWidget->item(i, 0)->checkState(); //->setCheckState(Qt::Unchecked);
	//	if (aa)
	//	{
	//		
	//		filename = ui.tableWidget->item(i, 1)->text();
	//		valuelist.append(filename);
	//	}
	//		
	//	qDebug() << aa;
	//}
	////如果没有选择文件
	//if (valuelist.size() == 0)
	//{
	//	QMessageBox::warning(this, QStringLiteral("Error!"), QStringLiteral("Please select file"), QMessageBox::Ok);
	//	return;
	//}
	////选择了一个文件
	//else if (valuelist.size() == 1) {
	//	//判断是否有成员变量路径
	//	if (m_treepath == NULL)
	//	{
	//		treepath = QString("%1").arg(filename);
	//	}
	//	else
	//	{
	//		treepath = QString("%1/%2").arg(m_treepath).arg(filename);
	//		treepath.remove(0, 1);
	//	}
	//	filepath.append(treepath);
	//}
	////选择了多个文件
	//else {
	//	if (m_treepath == "/")
	//	{
	//		//说明此时在根目录
	//		for (int i = 0; i < filepath.size(); i++)
	//		{
	//			treepath = QString("%1").arg(filepath.at(i));
	//			filepath.append(treepath);
	//		}
	//		
	//	}
	//	else {
	//		//按实际选择的路径
	//		for (int i = 0; i < filepath.size(); i++)
	//		{
	//			treepath = QString("%1/%2").arg(m_treepath).append(filepath.at(i));
	//			treepath.remove(0,1);
	//			filepath.append(treepath);
	//		}
	//	}
	//}
	//downLoadByPath(filepath);
}

void QtWidgetsClass::readyRead()
{
	//获得响应的结果
	QByteArray replyData = m_Reply->readAll();
	//解析json
	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData, &json_error));
	if (json_error.error != QJsonParseError::NoError)
	{
		return;
	}
	QJsonObject rootObj = jsonDoc.object();
	QString codeStr = rootObj.value("message").toString();
	//如果登录成功
	if (codeStr == "Success")
	{
		QJsonObject arrObj = rootObj.value("data").toObject();
		//获得token，根据token再次发送请求获得userKey
		QString rsauthtoken = arrObj.value("rsAuthToken").toString();
		QUrl u = QUrl("https://task.renderbus.com/api/rendering/user/userLogin");
		userLogin(u, rsauthtoken);
	}
	////获得响应的结果
	//QByteArray replyData = m_Reply->readAll();
	//QJsonParseError json_error;
	//QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData, &json_error));
	//if (json_error.error != QJsonParseError::NoError)
	//{
	//	return;
	//}
	//QJsonObject rootObj = jsonDoc.object();
	//QStringList list = rootObj.keys();
	////循环json格式
	//foreach(QString key, list)
	//{
	//	if (rootObj[key].isString())
	//	{
	//		qDebug() << "key:" << key << "value:" << rootObj[key].toString();
	//	}
	//	else if (rootObj[key].isArray() || key == "data")
	//	{
	//		//QJsonArray arr = rootObj[key].toString();

	//		QJsonObject arrObj = rootObj.value("data").toObject();
	//		QStringList list = arrObj.keys();
	//		for (int i = 0; i < list.size(); i++)
	//		{
	//			qDebug() << "key:" << list.at(i) << "value:" << arrObj.value(list.at(i)).toString();
	//		}
	//	}

	//}
}

void QtWidgetsClass::readyReadTwo()
{
	//获得响应的结果
	QByteArray data = m_Reply1->readAll();
	//解析json
	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(data, &json_error));
	if (json_error.error != QJsonParseError::NoError)
	{
		return;
	}
	QJsonObject rootObj = jsonDoc.object();
	QString codeStr = rootObj.value("message").toString();
	//如果登录成功
	if (codeStr == "Success" || codeStr == "success")
	{
		QJsonObject arrObj = rootObj.value("data").toObject();
		//获得userkey
		QString userkey = arrObj.value("userKey").toString();
		m_raySyncUserKey = arrObj.value("raySyncUserKey").toString();
		m_userkey = userkey;
		QUrl u = QUrl("https://task.renderbus.com/api/rendering/file/operate/getUserDirFile");
		getUserDirFile(u, userkey);
	}

}

void QtWidgetsClass::readyReadThree()
{
	FileData  jsondata;
	QList<FileData> datalist;
	//获得响应的结果
	QByteArray data = m_Reply2->readAll();
	//解析json
	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(data, &json_error));
	if (json_error.error != QJsonParseError::NoError)
	{
		return;
	}
	QJsonObject rootObj = jsonDoc.object();
	QString codeStr = rootObj.value("message").toString();
	//如果登录成功
	if (codeStr == "Success" || codeStr == "success")
	{
		QJsonArray arrObj = rootObj.value("data").toArray();
		int aa = arrObj.size();
		//循环文件
		for (int i = 0; i < aa; i++)
		{
			QJsonObject oneObj = arrObj.at(i).toObject();
			jsondata.fileName = oneObj.value("fileName").toString();
			double size = oneObj.value("fileSize").toDouble();
			jsondata.fileSize = QString::number(size, 'f', 0);
			if (jsondata.fileSize.size() <= 3) {
				jsondata.fileSize = QString("%1B").arg(jsondata.fileSize);
			}
			else if (jsondata.fileSize.size() > 3 && jsondata.fileSize.size() <= 6) {
				jsondata.fileSize = QString("%1K").arg(size / 1024.0);
			}
			else if (jsondata.fileSize.size() > 6) {
				jsondata.fileSize = QString("%1M").arg(size / 1024.0 / 1024.0);
			}
			jsondata.lastModify = oneObj.value("lastModify").toString();
			jsondata.fileType = oneObj.value("fileType").toString();
			datalist.append(jsondata);
		}
		m_alldata = datalist;
		showTable(datalist);
		////获得userkey
		//QString userkey = arrObj.value("userkey").toString();
		//QUrl u = QUrl("https://task.renderbus.com/api/rendering/file/operate/getUserDirFile");
		//getUserDirFile(u, userkey);
	}

}

void QtWidgetsClass::slotError(QNetworkReply::NetworkError err)
{
	qDebug() << "get ready,read size:";
}

void QtWidgetsClass::slotError(QAbstractSocket::SocketError error)
{
	qDebug() << __FILE__ << __LINE__ << (int)error << m_websocket->errorString();
}


void QtWidgetsClass::clickedchange(int row, int col)
{
	qDebug() << row << col;
	
	QUrl u = QUrl("https://task.renderbus.com/api/rendering/file/operate/getUserDirFile");
	QString currentvalue = ui.tableWidget->item(row, col)->text();
	

	//创建按钮
	QStringList list;
	list << currentvalue;
	//在跟节点下面创建子节点
	QTreeWidgetItem * childitem = new QTreeWidgetItem(list);
	
	if (!m_item->child(0))
	{
		m_item->addChild(childitem);
		m_treepath = QString("/%1").arg(currentvalue);
	}
	else
	{
		m_currentitem->addChild(childitem);
		m_treepath = QString("%1/%2").arg(m_treepath).arg(currentvalue);
	}
	m_currentitem = childitem;
	ui.treeWidget->expandAll();
	

	
	getUserDirFile(u, m_userkey,m_treepath);
}

void QtWidgetsClass::SetAlarmListCheckState(bool ischeck)
{
	if (ischeck)
	{
		for (int i = 0; i < ui.tableWidget->rowCount(); i++)
		{
			
			ui.tableWidget->item(i, 0)->setCheckState(Qt::Checked);
		}
	}
	else
	{
		for (int i = 0; i < ui.tableWidget->rowCount(); i++)
		{
			ui.tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
		}
	}
}

void QtWidgetsClass::on_itemClicked(QTreeWidgetItem * item, int index)
{
	
	QString treepath = "";
	removeItem(item);
	m_currentitem = item;
	QString name = item->text(index);
	if (item->parent())
	{
		while (item->parent())
		{
			item = item->parent();
			QString text = item->text(index);
			if (text != "genmulu")
			{
				name = QString("%1/%2").arg(text).arg(name);
			}
		}
		name = QString("/%1").arg(name);
	}
	else
	{
		name = "/";
	}
	m_treepath = name;
	
	QUrl u = QUrl("https://task.renderbus.com/api/rendering/file/operate/getUserDirFile");
	
	getUserDirFile(u, m_userkey, name);

}

void QtWidgetsClass::slotSslErrors( const QList<QSslError> &errs)
{
	qDebug() << "get ready,read size:";
}

void QtWidgetsClass::onConnected()
{
	QString aa = "success";
	qDebug() << aa;
	QString password = QString("%1&2&2&12345678").arg(m_raySyncUserKey);
	QJsonDocument doc;
	QJsonObject jsonData;
	jsonData.insert("action", "login");     
	jsonData.insert("language", "zh-CN");
	jsonData.insert("pass_word", password);
	jsonData.insert("proxy_ip", "render.raysync.cn");
	jsonData.insert("proxy_port", 32001);
	jsonData.insert("server5_port", 2442);
	jsonData.insert("server5_ssl_port",2443);
	jsonData.insert("server_ip", "127.0.0.1");
	jsonData.insert("server_port", 2121);
	jsonData.insert("user_name", "TD_MAX");
	
	doc.setObject(jsonData);
	QByteArray data;
	data = doc.toJson(QJsonDocument::Compact);
	m_websocket->sendBinaryMessage(data);
}

void QtWidgetsClass::onDisconnected()
{
	qDebug() << "disconnect";
}

void QtWidgetsClass::onTextReceived(const QByteArray &data)
{
	qDebug() << "success";
	qDebug() << data;

	//解析json
	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(data, &json_error));
	if (json_error.error != QJsonParseError::NoError)
	{
		return;
	}
	QJsonObject rootObj = jsonDoc.object();
	QString codeStr = rootObj.value("id").toString();

	QString path = rootObj.value("path").toString();
	if (function == 0)
	{
		QJsonDocument doc1;
		QJsonObject jsonData1;
		jsonData1.insert("action", "list");
		jsonData1.insert("path", "/input/100000849/");
		doc1.setObject(jsonData1);
		QByteArray newdata1;
		newdata1 = doc1.toJson(QJsonDocument::Compact);

		QJsonDocument doc2;
		QJsonObject jsonData2;
		jsonData2.insert("action", "upload");
		jsonData2.insert("full_path", false);
		jsonData2.insert("path", "/input/100000849/");
		jsonData2.insert("type", 0);
		doc2.setObject(jsonData2);
		QByteArray newdata2;
		newdata2 = doc2.toJson(QJsonDocument::Compact);

		function = 3;
		m_websocket->sendBinaryMessage(newdata1);
		m_websocket->sendBinaryMessage(newdata2);
		
	}
	if (path != NULL)
	{
		ui.tableWidget->clear();
		QUrl u = QUrl("https://task.renderbus.com/api/rendering/file/operate/getUserDirFile");
		getUserDirFile(u, m_userkey);
	}
	if (function == 1)
	{
		QList<QString> valuelist;
		QList<QString> filepath;
		QString treepath = "";
		QString filename = "";
		for (int i = 0; i < ui.tableWidget->rowCount(); i++)
		{
			bool aa = ui.tableWidget->item(i, 0)->checkState(); //->setCheckState(Qt::Unchecked);
			if (aa)
			{

				filename = ui.tableWidget->item(i, 1)->text();
				valuelist.append(filename);
			}

			qDebug() << aa;
		}
		//如果没有选择文件
		if (valuelist.size() == 0)
		{
			QMessageBox::warning(this, QStringLiteral("Error!"), QStringLiteral("Please select file"), QMessageBox::Ok);
			return;
		}
		//选择了一个文件
		else if (valuelist.size() == 1) {
			//判断是否有成员变量路径
			if (m_treepath == NULL)
			{
				treepath = QString("%1").arg(filename);
			}
			else
			{
				treepath = QString("%1/%2").arg(m_treepath).arg(filename);
				treepath.remove(0, 1);
			}
			filepath.append(treepath);
		}
		//选择了多个文件
		else {
			if (m_treepath == "/")
			{
				//说明此时在根目录
				for (int i = 0; i < filepath.size(); i++)
				{
					treepath = QString("%1").arg(filepath.at(i));
					filepath.append(treepath);
				}

			}
			else {
				//按实际选择的路径
				for (int i = 0; i < filepath.size(); i++)
				{
					treepath = QString("%1/%2").arg(m_treepath).append(filepath.at(i));
					treepath.remove(0, 1);
					filepath.append(treepath);
				}
			}
		}
		function = 3;
		downLoadByPath(filepath);
		
	}
}

void QtWidgetsClass::onTextMessageReceived(const QString& data)
{
	qDebug() << "success";
	qDebug() << data;
}
