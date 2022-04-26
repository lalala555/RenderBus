#pragma once

#include <QWidget>
#include "ui_QtWidgetsClass.h"
#include <QtNetwork\QNetworkAccessManager>
#include <QtNetwork\QNetworkReply>
#include <QtNetwork\QNetworkRequest>
#include <QtWebSockets\QWebSocket>
#include <QtWebSockets\QWebSocketServer>  
#include <QtNetWork/QAbstractSocket>
#include "CheckBoxHeaderView.h"

typedef struct FileData
{
	QString fileName; //�ļ���
	QString fileSize;  //�ļ���С
	QString lastModify; //����޸�ʱ��
	QString fileType;    //�ļ�����
};
enum function
{
	upload,
    download
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

	//��������м��ܣ�����post����
	void postSignIn(QUrl &u);

	//����rsauthtoken�����͵ڶ������󣬵õ�userkey
	void userLogin(QUrl &u,QString rsauthtoken);

	//����userkey�����͵��������󣬵õ��ļ��б�
	void getUserDirFile(QUrl &u, QString userkey, QString treePath = "");

	//���ݻ�õ����ݳ�ʼ��tablewidget
	void showTable(QList<FileData> &datalist);

	//����websocket�ӿڣ����ӷ����
	void connectToServer();

	void removeItem(QTreeWidgetItem * item);

	//ͨ��·�������ļ�
	void downLoadByPath(QList<QString> filepath);

	//�жϸ�ѡ���ж��ٸ�����ѡ,���ر���ѡ���ļ���,����¼���һ��ѡ�е��ļ���
	QList<QString> getCheckedData(QString &filename);
public slots:
    //��¼ 
    void on_pushButton_3_clicked();

	//�ļ��ϴ�
	void on_pushButton_clicked();

	void on_finished(QNetworkReply *reply);
	 //����
	void on_pushButton_2_clicked();

	//��һ�εõ���Ӧ������json�����token������token�ٴη���������userKey
	void readyRead();

	//�ڶ��εõ���Ӧ������json�����userkey������userkey�����η����������ļ��б�
	void readyReadTwo();

	//�����εõ���Ӧ������json������ļ��б������ļ��б��ʼ��tablewidget�������ļ��б�����Ա����
	void readyReadThree();

	//��Ӧ����
	void slotError(QNetworkReply::NetworkError);
	void slotSslErrors(const QList<QSslError> &);

	//websocket����
	//�ͻ������ӷ������ɹ���ᴥ���ۺ���
	void onConnected();

	//�ͻ��˶Ͽ���������ᴥ���ۺ���
	void onDisconnected();

	//����˸��ͻ��˷�����Ϣ�Ĳۺ�����QByteArray��
	void onTextReceived(const QByteArray &data);

	//����˸��ͻ��˷�����Ϣ�Ĳۺ�����QString��
	void onTextMessageReceived(const QString& data);
 
	// ��Ӧ����
	void slotError(QAbstractSocket::SocketError error); 

	//tablewidget����
	//��˫��tablewidget���źţ�����treewidget������Ӧ�Ľڵ㣬�����浱ǰ�Ľڵ�Ϊ��Ա������Ϊ��������·����׼��
	void clickedchange(int row, int col);

	//�󶨱�ͷ��ȫѡ��ѡ�򣬲ۺ�����ȫѡ/ȫ��ѡtablewidget�ĸ�ѡ��
	void setAlarmListCheckState(bool ischeck);

	//��checkbox���źţ��Ӷ��ж��Ƿ񼤻�/�û����ذ�ť
	void on_activebutton(int row, int col);

	//treewidget����
	//��treewidget���źţ�����treewidgetѡ��Ľڵ���װ��Ӧ��·��������·����userkey�����Ӧ���ļ��б���tablewidgetչʾ
	void on_itemClicked(QTreeWidgetItem * item, int index);



private:
	QUrl url;
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
	QString m_userkey;
	CheckBoxHeaderView *m_checkheaderview;
	
	QList<FileData> m_alldata;
	QTreeWidgetItem * m_item; //���ڵ�
	QTreeWidgetItem * m_currentitem; //��ǰ�ڵ�
	QString m_treepath = "";//���tablewidget��path
	QCheckBox * m_checkbox;
	int m_function;//����
};
