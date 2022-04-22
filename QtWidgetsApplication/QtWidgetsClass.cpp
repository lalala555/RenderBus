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
#include "QServer.h"



QtWidgetsClass::QtWidgetsClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.lineEdit_user->setText("TD_MAX");
	ui.lineEdit_2->setText("Abc123456");

	m_Request = new QNetworkRequest;
	m_Manager = new QNetworkAccessManager;
	m_websocket = new QWebSocket;
	//m_serversocket = new QWebSocketServer("server", QWebSocketServer::NonSecureMode);
	//m_serversocket->listen(QHostAddress::Any, 2121);
	connect(m_serversocket, SIGNAL(newConnection()), this, SLOT(slotNewConnect()));

	connect(m_Manager, SIGNAL(finished(QNetworkReply *reply)), this, SLOT(on_finished(QNetworkReply *reply)));

	connect(m_websocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::AutoConnection);

	connect(m_websocket, SIGNAL(connected()), this, SLOT(onConnected()), Qt::AutoConnection);

	connect(m_websocket, SIGNAL(sslErrors(const QList<QSslError> &)), this, SLOT(slotSslErrors(const QList<QSslError> &)), Qt::AutoConnection);

	connect(m_websocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

	connect(m_websocket, SIGNAL(binaryMessageReceived(const QByteArray&)), this, SLOT(onTextReceived(const QByteArray&)));

	connect(m_websocket, SIGNAL(textMessageReceived(const QString&)), this, SLOT(onTextMessageReceived(const QString&)));

	m_Reply = Q_NULLPTR;
	Init();

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

void QtWidgetsClass::getUserDirFile(QUrl & u, QString userkey)
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
	jsonData.insert("treePath", "/");     // 设置用户名密码
	doc.setObject(jsonData);

	QByteArray data;
	data = doc.toJson();
	m_Reply2 = man->post(*req, data);
	connect(m_Reply2, SIGNAL(readyRead()), this, SLOT(readyReadThree()));

}

void QtWidgetsClass::showTable(QList<FileData>& datalist)
{
	ui.tableWidget->setRowCount(datalist.size());
	ui.tableWidget->setColumnCount(5);
	/*QList<QString> collist;
	collist.append("文件名");
	collist.append("文件大小");
	collist.append("最后修改时间");
	collist.append("文件类型");
	ui.tableWidget->setHorizontalHeaderLabels(collist);*/
//	QTableWidgetItem *item = new QTableWidgetItem(QString(""));
	//ui.tableWidget->item(row, col)->setCheckState(Qt::Unchecked);

	for (int i = 0; i < datalist.size(); i++)
	{
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
		

	}
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void QtWidgetsClass::connectToServer()
{
	QString path = "wss://local.raysync.cn:9527/"; 
	//QString path = "wss://127.0.0.1:2121";
	QUrl url = QUrl(path);
	m_websocket->open(url);
}

void QtWidgetsClass::on_pushButton_3_clicked()
{
	//QUrl u = QUrl("https://account.dayancloud.com/api/rendering/user/queryUser");
	QUrl u = QUrl("https://task.renderbus.com/api/sso/sign/signIn");
	postSignIn(u);

	/*QNetworkAccessManager manager;

	QString hostName = QHostInfo::localHostName();
	QHostInfo hostInfo = QHostInfo::fromName(hostName);
	QList<QHostAddress> addList = hostInfo.addresses();
	for (int i = 0; i < addList.size(); i++)
	{
		QHostAddress aHost = addList.at(i);
		QString aa = aHost.toString();
	}*/
}

void QtWidgetsClass::on_pushButton_clicked()
{
	//QtTipsDialog *dialog = new QtTipsDialog;
	//dialog->show();
	//QString filepath = QFileDialog::getExistingDirectory();
	//	if (filepath == NULL)
	//		return;
	//开启服务端连接
	//	QServer server(this);
	//	server.startListen();
	connectToServer();


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
	if (codeStr != NULL)
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

		m_websocket->sendBinaryMessage(newdata1);
		m_websocket->sendBinaryMessage(newdata2);
	}
}

void QtWidgetsClass::onTextMessageReceived(const QString& data)
{
	qDebug() << "success";
	qDebug() << data;
}
