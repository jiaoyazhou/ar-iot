#include "statusbar.h"
#include "global.h"
extern "C"{
#include "systat/sysstat.h"
#include "inifile.h"
}

statusbar::statusbar(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);

	//this->setFont(g_Font[2]);
	this->setGeometry(g_RcStatusbar);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowFlags(Qt::FramelessWindowHint);

    this->setAutoFillBackground(true);
    QPalette palette = g_Palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/iot/png/statuabar.png").scaled (this->width (),this->height ())));
    this->setPalette(palette);
}

statusbar::~statusbar()
{

}
