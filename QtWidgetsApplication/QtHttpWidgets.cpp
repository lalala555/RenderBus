#include "QtHttpWidgets.h"
#include<QDir>
#include<QUrl>

QtHttpWidgets::QtHttpWidgets(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QtHttpWidgets::~QtHttpWidgets()
{
}

void QtHttpWidgets::on_finished()
{
	QFileInfo fileInfo;
	fileInfo.setFile(downloadedFile->fileName());
	downloadedFile->close();
	delete downloadedFile;
	downloadedFile = Q_NULLPTR;
	reply->deleteLater();
	reply = Q_NULLPTR;
}

void QtHttpWidgets::on_readyRead()
{
	downloadedFile->write(reply->readAll());
}

void QtHttpWidgets::on_downloadProgress(qint64 bytesRead, qint64 totalBytes)
{

}

void QtHttpWidgets::on_pushButton_clicked()
{
	QString path = ui.lineEdit->text().trimmed();
	   if (path == "")
	   {
		   return;
	   }
	   QUrl newUrl = QUrl::fromUserInput(path);
	   if (!newUrl.isValid())
	   {
		   return;
	   }
	   QString tempDir = ui.lineEdit_2->text().trimmed();
	   if (tempDir.isEmpty())
	   {
		   return;
	   }
	   QString fullFileName = tempDir + newUrl.fileName();
	   if (QFile::exists(fullFileName))
		   QFile::remove(fullFileName);
	   downloadedFile = new QFile(fullFileName);
	   if (!downloadedFile->open(QIODevice::WriteOnly))
	   {
		   return;
	   }
	   ui.pushButton->setEnabled(false);
	   reply = networkManger.get(QNetworkRequest(newUrl));
	   connect(reply, SIGNAL(finished()), this, SLOT(on_finished()));
	   connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
	   connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(on_downloadProgress(qint64,qint64)));

}

void QtHttpWidgets::on_pushButton_2_clicked()
{
	QString curpath = QDir::currentPath();
	QDir dir(curpath);
	QString sub = "temp";
	dir.mkdir(sub);
	ui.lineEdit_2->setText(curpath + "/" + sub + "/");
}
