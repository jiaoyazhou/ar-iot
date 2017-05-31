/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginClass
{
public:
    QLabel *label_Title;
    QLabel *label_UsrName;
    QLabel *label_PassWord;
    QLineEdit *lineEdit_UsrName;
    QLineEdit *lineEdit_PassWord;

    void setupUi(QWidget *loginClass)
    {
        if (loginClass->objectName().isEmpty())
            loginClass->setObjectName(QString::fromUtf8("loginClass"));
        loginClass->resize(1024, 600);
        label_Title = new QLabel(loginClass);
        label_Title->setObjectName(QString::fromUtf8("label_Title"));
        label_Title->setGeometry(QRect(330, 70, 431, 71));
        QFont font;
        font.setPointSize(36);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        label_Title->setFont(font);
        label_UsrName = new QLabel(loginClass);
        label_UsrName->setObjectName(QString::fromUtf8("label_UsrName"));
        label_UsrName->setGeometry(QRect(340, 190, 121, 40));
        QFont font1;
        font1.setPointSize(24);
        font1.setBold(true);
        font1.setWeight(75);
        label_UsrName->setFont(font1);
        label_PassWord = new QLabel(loginClass);
        label_PassWord->setObjectName(QString::fromUtf8("label_PassWord"));
        label_PassWord->setGeometry(QRect(340, 270, 101, 40));
        label_PassWord->setFont(font1);
        label_PassWord->setLayoutDirection(Qt::LeftToRight);
        lineEdit_UsrName = new QLineEdit(loginClass);
        lineEdit_UsrName->setObjectName(QString::fromUtf8("lineEdit_UsrName"));
        lineEdit_UsrName->setGeometry(QRect(510, 190, 151, 40));
        QFont font2;
        font2.setPointSize(20);
        lineEdit_UsrName->setFont(font2);
        lineEdit_PassWord = new QLineEdit(loginClass);
        lineEdit_PassWord->setObjectName(QString::fromUtf8("lineEdit_PassWord"));
        lineEdit_PassWord->setGeometry(QRect(510, 270, 150, 40));
        lineEdit_PassWord->setFont(font2);

        retranslateUi(loginClass);

        QMetaObject::connectSlotsByName(loginClass);
    } // setupUi

    void retranslateUi(QWidget *loginClass)
    {
        loginClass->setWindowTitle(QApplication::translate("loginClass", "login", 0, QApplication::UnicodeUTF8));
        label_Title->setText(QApplication::translate("loginClass", "\345\206\234\344\270\232\344\277\241\346\201\257\351\207\207\351\233\206\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        label_UsrName->setText(QApplication::translate("loginClass", "\347\224\250\346\210\267\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_PassWord->setText(QApplication::translate("loginClass", "\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class loginClass: public Ui_loginClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
