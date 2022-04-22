/********************************************************************************
** Form generated from reading UI file 'QtTipsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTIPSDIALOG_H
#define UI_QTTIPSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtTipsDialog
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *pushButton_2;

    void setupUi(QWidget *QtTipsDialog)
    {
        if (QtTipsDialog->objectName().isEmpty())
            QtTipsDialog->setObjectName(QStringLiteral("QtTipsDialog"));
        QtTipsDialog->resize(400, 300);
        pushButton = new QPushButton(QtTipsDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 150, 121, 41));
        label = new QLabel(QtTipsDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 50, 281, 41));
        pushButton_2 = new QPushButton(QtTipsDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(140, 90, 121, 31));

        retranslateUi(QtTipsDialog);

        QMetaObject::connectSlotsByName(QtTipsDialog);
    } // setupUi

    void retranslateUi(QWidget *QtTipsDialog)
    {
        QtTipsDialog->setWindowTitle(QApplication::translate("QtTipsDialog", "QtTipsDialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("QtTipsDialog", "\344\270\213\350\275\275\346\234\200\346\226\260\347\211\210\344\274\240\350\276\223\346\217\222\344\273\266", Q_NULLPTR));
        label->setText(QApplication::translate("QtTipsDialog", "\351\234\200\350\246\201\345\256\211\350\243\205\346\217\222\344\273\266\346\211\215\350\203\275\350\277\233\350\241\214\346\226\207\344\273\266\344\274\240\350\276\223\357\274\214\350\213\245\345\267\262\345\256\211\350\243\205\346\217\222\344\273\266\357\274\214\350\257\267", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("QtTipsDialog", "\347\202\271\345\207\273\345\220\257\347\224\250\346\217\222\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtTipsDialog: public Ui_QtTipsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTIPSDIALOG_H
