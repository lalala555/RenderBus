#pragma once

#include <QWidget>
#include "ui_QtWidgetsClass.h"

class QtWidgetsClass : public QWidget
{
	Q_OBJECT

public:

	QtWidgetsClass(QWidget *parent = Q_NULLPTR);
	

	~QtWidgetsClass();
public:
	/*��ʼ���Ի���*/
	void Init();
public slots:
    //��¼
    
    void on_pushButton_3_clicked();

private:
	Ui::QtWidgetsClass ui;
};
