#pragma once

#include <QDialog>
#include "ui_QtTipsDialog.h"

class QtTipsDialog : public QDialog

{
	Q_OBJECT

public:
	QtTipsDialog(QDialog *parent = Q_NULLPTR);
	~QtTipsDialog();

public slots:
    void on_pushButton_clicked();

	void on_pushButton_2_clicked();

private:
	Ui::QtTipsDialog ui;
};
