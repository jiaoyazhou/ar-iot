#include "iot.h"

iot::iot(QWidget *parent)
    : QWidget(parent),
	  qwLogin(0),
	  vdshow(0)
{

	qDebug()<<g_RcMain.left()<<g_RcMain.width()<<g_RcMain.top()<<g_RcMain.height();
	this->setGeometry(QRect(0,g_RcStatusbar.bottom(),g_RcMain.width(),g_RcMain.height()));
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setFont(g_Font[2]);
    //w.setPalette(g_Palette);
	this->setWindowOpacity(1);
	this->setWindowFlags(Qt::FramelessWindowHint);

	this->setMouseTracking(true);

	//设置背景
    this->setAutoFillBackground(true);
    QPalette palette = g_Palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/iot/png/background.jpg").scaled (this->width (),this->height ())));
    this->setPalette(palette);


	login *qwLogin = new login(this);

	//vdshow = new video_show(this);

}

iot::~iot()
{
	if(qwLogin != 0)
	{
		delete qwLogin;
		qwLogin = 0;
	}

	if(vdshow != 0)
	{
		delete vdshow;
		vdshow = 0;
	}
}
