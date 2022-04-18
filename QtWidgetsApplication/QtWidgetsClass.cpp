#include "QtWidgetsClass.h"
#include "QtNetwork\qhostinfo.h"

QtWidgetsClass::QtWidgetsClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	Init();
}
QtWidgetsClass::~QtWidgetsClass()
{
}

void QtWidgetsClass::Init()
{

	
}

void QtWidgetsClass::on_pushButton_3_clicked()
{
	QString hostName = QHostInfo::localHostName();
	QHostInfo hostInfo = QHostInfo::fromName(hostName);
	QList<QHostAddress> addList = hostInfo.addresses();
	for (int i = 0; i < addList.size(); i++)
	{
		QHostAddress aHost = addList.at(i);
		QString aa = aHost.toString();
	}
}


