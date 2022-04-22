#pragma once

#include <QWidget>
#include "ui_QtWidgetsClass.h"
#include <QtNetwork\QNetworkAccessManager>
#include <QtNetwork\QNetworkReply>
#include <QtNetwork\QNetworkRequest>
#include <QtWebSockets\QWebSocket>
#include <QtWebSockets\QWebSocketServer>
#include "QServer.h"
#include <QtNetWork/QAbstractSocket>

typedef struct FileData
{
	QString fileName; //文件名
	QString fileSize;  //文件大小
	QString lastModify; //最后修改时间
	QString fileType;    //文件类型
};
class QtWidgetsClass : public QWidget
{
	Q_OBJECT

public:

	QtWidgetsClass(QWidget *parent = Q_NULLPTR);
	

	~QtWidgetsClass();
public:
	/*初始化对话框*/
	void Init();

	void postSignIn(QUrl &u);

	void userLogin(QUrl &u,QString rsauthtoken);

	void getUserDirFile(QUrl &u, QString userkey);

	void showTable(QList<FileData> &datalist);

	void connectToServer();



	
public slots:
    //登录
    
    void on_pushButton_3_clicked();

	void on_pushButton_clicked();

	void on_finished(QNetworkReply *reply);

	//解析json
	void readyRead();

	void readyReadTwo();

	void readyReadThree();

	void slotError(QNetworkReply::NetworkError);
	void slotSslErrors(const QList<QSslError> &);

	//websocket部分
	void onConnected();

	void onDisconnected();

	void onTextReceived(const QByteArray &data);

	void onTextMessageReceived(const QString& data);
 
	void slotError(QAbstractSocket::SocketError error); // 响应报错


private:
	Ui::QtWidgetsClass ui;
	QNetworkAccessManager *m_Manager;
	QNetworkReply *m_Reply;
	QNetworkReply *m_Reply1;
	QNetworkReply *m_Reply2;
	QNetworkRequest *m_Request;
	QWebSocket  *m_websocket;
	QWebSocketServer * m_serversocket;
	QString m_username;
	QString m_password;
	QString m_raySyncUserKey;
	QUrl url;
};
