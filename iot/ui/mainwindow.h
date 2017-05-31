#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QWidget>
#include "ui_mainwindow.h"
#include "global.h"
#include "ui/iot.h"
#include "expertinfo_window.h"

class mainwindow : public QWidget
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = 0);
    ~mainwindow();

private:
    Ui::mainwindowClass ui;

    iot *m_iot;

    expertinfo_window *m_expert;

};

#endif // MAINWINDOW_H
