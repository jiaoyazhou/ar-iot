/********************************************************************************
** Form generated from reading UI file 'video_show.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEO_SHOW_H
#define UI_VIDEO_SHOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_video_showClass
{
public:

    void setupUi(QWidget *video_showClass)
    {
        if (video_showClass->objectName().isEmpty())
            video_showClass->setObjectName(QString::fromUtf8("video_showClass"));
        video_showClass->resize(400, 300);

        retranslateUi(video_showClass);

        QMetaObject::connectSlotsByName(video_showClass);
    } // setupUi

    void retranslateUi(QWidget *video_showClass)
    {
        video_showClass->setWindowTitle(QApplication::translate("video_showClass", "video_show", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class video_showClass: public Ui_video_showClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEO_SHOW_H
