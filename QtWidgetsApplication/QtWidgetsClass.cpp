#include "QtWidgetsClass.h"
#include "QtNetwork\qhostinfo.h"
#include <QCryptographicHash>
#include <qdebug.h>
#include <qjsonarray.h>
#include <QJsonParseError>
#include <QJsonObject>
#include <QEventLoop>
#include <qurlquery.h>


QtWidgetsClass::QtWidgetsClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);



	m_Request = new QNetworkRequest;
	m_Manager = new QNetworkAccessManager;
	connect(m_Manager, SIGNAL(finished(QNetworkReply *reply)), this, SLOT(on_finished(QNetworkReply *reply)));

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
	//��������м���
	int size = password.size();
	//�ȷ�Ϊ���ݺ�ÿһ��Ĵ�С
	int split = size / 3.0;
	//�ȷ�
	QString str1 = password.mid(0, split);
	QString str2 = password.mid(split, split);
	QString str3 = password.mid(split + split);
	QString newpass = QString("%1vaBci%2l6AF8%3vM9vH").arg(str1).arg(str2).arg(str3);
	//md5����
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
	jsonData.insert("loginName", username);     // �����û�������
	jsonData.insert("password", finalword);
	jsonData.insert("redirect", url.toString()); // ���������ֶ�
	doc.setObject(jsonData);

	if (m_Reply != Q_NULLPTR)
	{
		//����m_Replyָ��λ��ǰһ��Ҫ��֤֮ǰ�Ķ������Զ�delete
		// m_Reply->deleteLater();
	}
	QByteArray data;
	data = doc.toJson();
	m_Reply = m_Manager->post(*m_Request, data);

	//����¼�ѭ������
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
	jsonData.insert("userName", m_username);     // �����û�������
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
	jsonData.insert("treePath", "/");     // �����û�������
	doc.setObject(jsonData);

	QByteArray data;
	data = doc.toJson();
	m_Reply2 = man->post(*req, data);
	connect(m_Reply2, SIGNAL(readyRead()), this, SLOT(readyReadThree()));

}

void QtWidgetsClass::showTable(QList<FileData>& datalist)
{
	ui.tableWidget->setRowCount(datalist.size());
	ui.tableWidget->setColumnCount(4);
	QList<QString> collist;
	collist.append("�ļ���");
	collist.append("�ļ���С");
	collist.append("����޸�ʱ��");
	collist.append("�ļ�����");
	ui.tableWidget->setHorizontalHeaderLabels(collist);
	for (int i = 0; i < datalist.size(); i++)
	{
		QString fileName = datalist.at(i).fileName;
		QString fileSize = datalist.at(i).fileSize;
		QString lastModify = datalist.at(i).lastModify;
		QString fileType = datalist.at(i).fileType;
		ui.tableWidget->setItem(i, 0,  new QTableWidgetItem(fileName));
		ui.tableWidget->setItem(i, 1, new QTableWidgetItem(fileSize));
		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(lastModify));
		ui.tableWidget->setItem(i, 3, new QTableWidgetItem(fileType));

	}
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

void QtWidgetsClass::on_finished(QNetworkReply *reply)
{
	//�������ص�Json���
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
	{//�����ַ��ת��������
		const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
		qDebug() << "redirectedUrl:" << redirectedUrl.url();
		//postSignIn(redirectedUrl);
		return;

	}
	qDebug() << "finished";
	html_text = bytes;
	qDebug() << "get ready,read size:" << html_text.size();
}

void QtWidgetsClass::readyRead()
{
	//�����Ӧ�Ľ��
	QByteArray replyData = m_Reply->readAll();
	//����json
	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData, &json_error));
	if (json_error.error != QJsonParseError::NoError)
	{
		return;
	}
	QJsonObject rootObj = jsonDoc.object();
	QString codeStr = rootObj.value("message").toString();
	//�����¼�ɹ�
	if (codeStr == "Success")
	{
		QJsonObject arrObj = rootObj.value("data").toObject();
		//���token������token�ٴη���������userKey
		QString rsauthtoken = arrObj.value("rsAuthToken").toString();
		QUrl u = QUrl("https://task.renderbus.com/api/rendering/user/userLogin");
		userLogin(u, rsauthtoken);
	}
	////�����Ӧ�Ľ��
	//QByteArray replyData = m_Reply->readAll();
	//QJsonParseError json_error;
	//QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData, &json_error));
	//if (json_error.error != QJsonParseError::NoError)
	//{
	//	return;
	//}
	//QJsonObject rootObj = jsonDoc.object();
	//QStringList list = rootObj.keys();
	////ѭ��json��ʽ
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
	//�����Ӧ�Ľ��
	QByteArray data = m_Reply1->readAll();
	//����json
	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(data, &json_error));
	if (json_error.error != QJsonParseError::NoError)
	{
		return;
	}
	QJsonObject rootObj = jsonDoc.object();
	QString codeStr = rootObj.value("message").toString();
	//�����¼�ɹ�
	if (codeStr == "Success" || codeStr == "success")
	{
		QJsonObject arrObj = rootObj.value("data").toObject();
		//���userkey
		QString userkey = arrObj.value("userKey").toString();
		QUrl u = QUrl("https://task.renderbus.com/api/rendering/file/operate/getUserDirFile");
		getUserDirFile(u, userkey);
	}

}

void QtWidgetsClass::readyReadThree()
{
	FileData  jsondata;
	QList<FileData> datalist;
	//�����Ӧ�Ľ��
	QByteArray data = m_Reply2->readAll();
	//����json
	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(data, &json_error));
	if (json_error.error != QJsonParseError::NoError)
	{
		return;
	}
	QJsonObject rootObj = jsonDoc.object();
	QString codeStr = rootObj.value("message").toString();
	//�����¼�ɹ�
	if (codeStr == "Success" || codeStr == "success")
	{
		QJsonArray arrObj = rootObj.value("data").toArray();
		int aa = arrObj.size();
		//ѭ���ļ�
		for (int i = 0; i < aa; i++)
		{
			QJsonObject oneObj = arrObj.at(i).toObject();
			jsondata.fileName = oneObj.value("fileName").toString();
			jsondata.fileSize = oneObj.value("fileSize").toString();
			jsondata.lastModify = oneObj.value("lastModify").toString();
			jsondata.fileType = oneObj.value("fileType").toString();
			datalist.append(jsondata);
		}
		showTable(datalist);
		////���userkey
		//QString userkey = arrObj.value("userkey").toString();
		//QUrl u = QUrl("https://task.renderbus.com/api/rendering/file/operate/getUserDirFile");
		//getUserDirFile(u, userkey);
	}

}

void QtWidgetsClass::slotError(QNetworkReply::NetworkError err)
{
	qDebug() << "get ready,read size:";
}

void QtWidgetsClass::slotSslErrors(QList<QSslError> errs)
{
	qDebug() << "get ready,read size:";
}
