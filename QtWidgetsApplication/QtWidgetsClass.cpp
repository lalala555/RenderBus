#include "QtWidgetsClass.h"
#include "QtNetwork\qhostinfo.h"
#include <qdebug.h>


QtWidgetsClass::QtWidgetsClass(QWidget *parent)
	: QWidget(parent)
{
   
	ui.setupUi(this);
	m_Request = new QNetworkRequest;	
	m_Manager = new QNetworkAccessManager;
	m_Reply = Q_NULLPTR;
	Init();
}
QtWidgetsClass::~QtWidgetsClass()
{
}

void QtWidgetsClass::Init()
{
	
}

void QtWidgetsClass::Get(QUrl u)
{
	//QNetworkRequest request;
	url = u;
	m_Request->setUrl(url);
	m_Request->setRawHeader("userkey", "rsat:K11wcPCkY517BQEB7jKNqN8SJwN");
	m_Request->setRawHeader("languageflag", "0");
	m_Request->setRawHeader("platform", "2");
	m_Request->setRawHeader("signature", "rayvision2017");
	m_Request->setRawHeader("version", "1.0.0");
	m_Request->setRawHeader("channel", "2");
	m_Request->setRawHeader("Content-Type", "application/json");
	if (m_Reply != Q_NULLPTR)
	{
		//更改m_Reply指向位置钱一定要保证之前的定义了自动delete
		m_Reply->deleteLater();
	}
	m_Reply = m_Manager->get(*m_Request);
	qDebug() << "start get";
	connect(m_Reply, &QNetworkReply::finished, this, &QtWidgetsClass::finished);

}

void QtWidgetsClass::on_pushButton_3_clicked()
{
	QUrl u = QUrl("https://task.renderbus.com/api/rendering/user/queryUser");
	Get(u);
	
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

void QtWidgetsClass::finished()
{
	QByteArray bytes = m_Reply->readAll();
	const QVariant redirectionTarget = m_Reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
	m_Reply->deleteLater();
	m_Reply = Q_NULLPTR;
	if (!redirectionTarget.isNull())
	{//如果网址跳转重新请求
		const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
		qDebug() << "redirectedUrl:" << redirectedUrl.url();
		Get(redirectedUrl);
		return;

	}
	qDebug() << "finished";
	html_text = bytes;
	qDebug() << "get ready,read size:" << html_text.size();
}


