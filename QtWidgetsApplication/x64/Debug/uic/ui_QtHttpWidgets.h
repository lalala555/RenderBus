/********************************************************************************
** Form generated from reading UI file 'QtHttpWidgets.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTHTTPWIDGETS_H
#define UI_QTHTTPWIDGETS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtHttpWidgets
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QLabel *label_3;

    void setupUi(QWidget *QtHttpWidgets)
    {
        if (QtHttpWidgets->objectName().isEmpty())
            QtHttpWidgets->setObjectName(QStringLiteral("QtHttpWidgets"));
        QtHttpWidgets->resize(400, 300);
        label = new QLabel(QtHttpWidgets);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 31, 16));
        lineEdit = new QLineEdit(QtHttpWidgets);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(50, 20, 201, 20));
        pushButton = new QPushButton(QtHttpWidgets);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(270, 20, 51, 23));
        label_2 = new QLabel(QtHttpWidgets);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 80, 111, 16));
        lineEdit_2 = new QLineEdit(QtHttpWidgets);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(130, 80, 171, 20));
        pushButton_2 = new QPushButton(QtHttpWidgets);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(310, 80, 61, 23));
        label_3 = new QLabel(QtHttpWidgets);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 160, 91, 16));

        retranslateUi(QtHttpWidgets);

        QMetaObject::connectSlotsByName(QtHttpWidgets);
    } // setupUi

    void retranslateUi(QWidget *QtHttpWidgets)
    {
        QtHttpWidgets->setWindowTitle(QApplication::translate("QtHttpWidgets", "QtHttpWidgets", Q_NULLPTR));
        label->setText(QApplication::translate("QtHttpWidgets", "URL\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("QtHttpWidgets", "\344\270\213\350\275\275", Q_NULLPTR));
        label_2->setText(QApplication::translate("QtHttpWidgets", "\344\270\213\350\275\275\346\226\207\344\273\266\344\277\235\345\255\230\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("QtHttpWidgets", "\347\274\272\347\234\201\350\267\257\345\276\204", Q_NULLPTR));
        label_3->setText(QApplication::translate("QtHttpWidgets", "\346\226\207\344\273\266\344\270\213\350\275\275\350\277\233\345\272\246\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtHttpWidgets: public Ui_QtHttpWidgets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTHTTPWIDGETS_H
