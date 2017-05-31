#ifndef IOT_H
#define IOT_H

#include <QtGui/QMainWindow>
#include "ui/login.h"
#include "ui/video_show.h"

class iot : public QWidget
{
    Q_OBJECT

public:
    iot(QWidget *parent = 0);
    ~iot();

private:
    login *qwLogin;
    video_show *vdshow;
};

#endif // IOT_H
