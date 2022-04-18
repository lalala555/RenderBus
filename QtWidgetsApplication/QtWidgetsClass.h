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
	/*初始化对话框*/
	void Init();
public slots:
    //登录
    
    void on_pushButton_3_clicked();

private:
	Ui::QtWidgetsClass ui;
};
