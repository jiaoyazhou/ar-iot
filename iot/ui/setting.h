#ifndef SETTING_H
#define SETTING_H

#include <QtGui/QWidget>
#include "ui_setting.h"

class Setting : public QWidget
{
    Q_OBJECT

public:
    Setting(QWidget *parent = 0);
    ~Setting();

private:
    Ui::SettingClass ui;
};

#endif // SETTING_H
