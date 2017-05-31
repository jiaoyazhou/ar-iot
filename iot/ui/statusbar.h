#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QtGui/QWidget>
#include "ui_statusbar.h"


class statusbar : public QWidget
{
    Q_OBJECT

public:
    statusbar(QWidget *parent = 0);
    ~statusbar();

private:
    Ui::statusbarClass ui;
};

#endif // STATUSBAR_H
