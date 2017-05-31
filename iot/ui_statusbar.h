/********************************************************************************
** Form generated from reading UI file 'statusbar.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSBAR_H
#define UI_STATUSBAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QHeaderView>
#include <QtGui/QTimeEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_statusbarClass
{
public:
    QTimeEdit *timeEdit;
    QDateEdit *dateEdit;

    void setupUi(QWidget *statusbarClass)
    {
        if (statusbarClass->objectName().isEmpty())
            statusbarClass->setObjectName(QString::fromUtf8("statusbarClass"));
        statusbarClass->resize(900, 50);
        timeEdit = new QTimeEdit(statusbarClass);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(300, 10, 118, 27));
        dateEdit = new QDateEdit(statusbarClass);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setGeometry(QRect(150, 10, 110, 27));

        retranslateUi(statusbarClass);

        QMetaObject::connectSlotsByName(statusbarClass);
    } // setupUi

    void retranslateUi(QWidget *statusbarClass)
    {
        statusbarClass->setWindowTitle(QApplication::translate("statusbarClass", "statusbar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class statusbarClass: public Ui_statusbarClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSBAR_H
