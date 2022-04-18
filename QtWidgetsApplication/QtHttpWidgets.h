#pragma once
#include <QWidget>
#include "ui_QtHttpWidgets.h"
#include <QtNetwork/qnetworkreply.h>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QFile>

class QtHttpWidgets : public QWidget
{
	Q_OBJECT

public:
	QtHttpWidgets(QWidget *parent = Q_NULLPTR);
	~QtHttpWidgets();
public slots:
void on_finished();
void on_readyRead();
void on_downloadProgress(qint64 bytesRead, qint64 totalBytes);

void on_pushButton_clicked();

void on_pushButton_2_clicked();



private:
	Ui::QtHttpWidgets ui;
	QNetworkAccessManager networkManger;//网络管理
	QNetworkReply *reply;//网络响应
	QFile *downloadedFile;//下载保存的零食文件
};
