#pragma once

#include <QWidget>
#include "ui_QtWidgetsClass.h"
#include <QtNetwork\QNetworkAccessManager>
#include <QtNetwork\QNetworkReply>
#include <QtNetwork\QNetworkRequest>

typedef struct FileData
{
	QString fileName; //�ļ���
	QString fileSize;  //�ļ���С
	QString lastModify; //����޸�ʱ��
	QString fileType;    //�ļ�����
};
class QtWidgetsClass : public QWidget
{
	Q_OBJECT

public:

	QtWidgetsClass(QWidget *parent = Q_NULLPTR);
	

	~QtWidgetsClass();
public:
	/*��ʼ���Ի���*/
	void Init();

	void postSignIn(QUrl &u);

	void userLogin(QUrl &u,QString rsauthtoken);

	void getUserDirFile(QUrl &u, QString userkey);

	void showTable(QList<FileData> &datalist);

	
public slots:
    //��¼
    
    void on_pushButton_3_clicked();

	void on_finished(QNetworkReply *reply);

	//����json
	void readyRead();

	void readyReadTwo();

	void readyReadThree();

	void slotError(QNetworkReply::NetworkError);
	void slotSslErrors(QList<QSslError>);

private:
	Ui::QtWidgetsClass ui;
	QNetworkAccessManager *m_Manager;
	QNetworkReply *m_Reply;
	QNetworkReply *m_Reply1;
	QNetworkReply *m_Reply2;
	QNetworkRequest *m_Request;
	QString m_username;
	QString m_password;
	QUrl url;
	QString html_text;
};
