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
	QString fileName; //文件名
	QString fileSize;  //文件大小
	QString lastModify; //最后修改时间
	QString fileType;    //文件类型
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
	/*初始化对话框*/
	void Init();

	//对密码进行加密，发送post请求
	void postSignIn(QUrl &u);

	//根据rsauthtoken，发送第二次请求，得到userkey
	void userLogin(QUrl &u,QString rsauthtoken);

	//根据userkey，发送第三次请求，得到文件列表
	void getUserDirFile(QUrl &u, QString userkey, QString treePath = "");

	//根据获得的数据初始化tablewidget
	void showTable(QList<FileData> &datalist);

	//调用websocket接口，连接服务端
	void connectToServer();

	void removeItem(QTreeWidgetItem * item);

	//通过路径下载文件
	void downLoadByPath(QList<QString> filepath);

	//判断复选框有多少个被勾选,返回被勾选的文件名,并记录最后一次选中的文件名
	QList<QString> getCheckedData(QString &filename);
public slots:
    //登录 
    void on_pushButton_3_clicked();

	//文件上传
	void on_pushButton_clicked();

	void on_finished(QNetworkReply *reply);
	 //下载
	void on_pushButton_2_clicked();

	//第一次得到响应，解析json，获得token，根据token再次发送请求获得userKey
	void readyRead();

	//第二次得到响应，解析json，获得userkey，根据userkey第三次发送请求获得文件列表
	void readyReadTwo();

	//第三次得到响应，解析json，获得文件列表，根据文件列表初始化tablewidget，并把文件列表存进成员变量
	void readyReadThree();

	//响应报错
	void slotError(QNetworkReply::NetworkError);
	void slotSslErrors(const QList<QSslError> &);

	//websocket部分
	//客户端连接服务器成功后会触发槽函数
	void onConnected();

	//客户端断开服务器后会触发槽函数
	void onDisconnected();

	//服务端给客户端发送消息的槽函数（QByteArray）
	void onTextReceived(const QByteArray &data);

	//服务端给客户端发送消息的槽函数（QString）
	void onTextMessageReceived(const QString& data);
 
	// 响应报错
	void slotError(QAbstractSocket::SocketError error); 

	//tablewidget部分
	//绑定双击tablewidget的信号，会在treewidget生成相应的节点，并保存当前的节点为成员变量，为后期下载路径做准备
	void clickedchange(int row, int col);

	//绑定表头的全选复选框，槽函数（全选/全不选tablewidget的复选框）
	void setAlarmListCheckState(bool ischeck);

	//绑定checkbox的信号，从而判断是否激活/置灰下载按钮
	void on_activebutton(int row, int col);

	//treewidget部分
	//绑定treewidget的信号，根据treewidget选择的节点组装相应的路径，根据路径，userkey获得相应的文件列表并在tablewidget展示
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
	QTreeWidgetItem * m_item; //跟节点
	QTreeWidgetItem * m_currentitem; //当前节点
	QString m_treepath = "";//点击tablewidget的path
	QCheckBox * m_checkbox;
	int m_function;//功能
};
