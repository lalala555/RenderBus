/********************************************************************************
** Form generated from reading UI file 'QtWidgetsClass.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSCLASS_H
#define UI_QTWIDGETSCLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsClass
{
public:
    QLineEdit *lineEdit_user;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_3;
    QTableWidget *tableWidget;

    void setupUi(QWidget *QtWidgetsClass)
    {
        if (QtWidgetsClass->objectName().isEmpty())
            QtWidgetsClass->setObjectName(QStringLiteral("QtWidgetsClass"));
        QtWidgetsClass->resize(468, 401);
        lineEdit_user = new QLineEdit(QtWidgetsClass);
        lineEdit_user->setObjectName(QStringLiteral("lineEdit_user"));
        lineEdit_user->setGeometry(QRect(10, 20, 81, 31));
        lineEdit_2 = new QLineEdit(QtWidgetsClass);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(10, 60, 81, 31));
        pushButton_3 = new QPushButton(QtWidgetsClass);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(20, 110, 61, 23));
        tableWidget = new QTableWidget(QtWidgetsClass);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(100, 20, 331, 261));

        retranslateUi(QtWidgetsClass);

        QMetaObject::connectSlotsByName(QtWidgetsClass);
    } // setupUi

    void retranslateUi(QWidget *QtWidgetsClass)
    {
        QtWidgetsClass->setWindowTitle(QApplication::translate("QtWidgetsClass", "QtWidgetsClass", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("QtWidgetsClass", "\347\231\273\345\275\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsClass: public Ui_QtWidgetsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSCLASS_H
