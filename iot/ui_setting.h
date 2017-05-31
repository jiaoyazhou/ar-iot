/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingClass
{
public:

    void setupUi(QWidget *SettingClass)
    {
        if (SettingClass->objectName().isEmpty())
            SettingClass->setObjectName(QString::fromUtf8("SettingClass"));
        SettingClass->resize(400, 300);

        retranslateUi(SettingClass);

        QMetaObject::connectSlotsByName(SettingClass);
    } // setupUi

    void retranslateUi(QWidget *SettingClass)
    {
        SettingClass->setWindowTitle(QApplication::translate("SettingClass", "Setting", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingClass: public Ui_SettingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
