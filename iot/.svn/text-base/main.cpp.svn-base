#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>
#include <signal.h>
#include "myinputpanelcontext.h"
#include "global.h"
#include "ui/mainwindow.h"


void Catcher(int sig)
{
	printf("Caught sig %d it!\n",sig);
	switch(sig)
	{
	case SIGTERM:
	{
		printf("请求中止进程，kill命令缺省发送\n");
		exit(-1);
		break;
	}
	case SIGFPE:
	{
		printf("数学相关的异常，如被0除，浮点溢出，等等\n");
		exit(-2);
		break;
	}
	case SIGSEGV:
	{
		printf("非法内存访问\n");
		exit(-3);
		break;
	}
	case SIGCONT:
	{
		printf("进程继续（曾被停止的进程）\n");
		break;
	}
	case SIGSTOP:
	{
		printf("终止进程 \n");
		break;
	}
	}
}


int main(int argc, char *argv[])
{
	signal(SIGTERM, Catcher);
	signal(SIGFPE, Catcher);
	signal(SIGSEGV, Catcher);
	signal(SIGCONT, Catcher);
	signal(SIGSTOP, Catcher);

	/**********************************程序样式设置**********************************/
	QApplication::setStyle("cleanlooks");
	QApplication a(argc, argv);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));       //支持Tr中文
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));//支持中文文件名显示


	/**********************************获取桌面大小**********************************/
    QDesktopWidget *desktop=QApplication::desktop();
    g_ScreenSize = QSize(desktop->width(),desktop->height());

    g_RcStatusbar = QRect(0,0,g_ScreenSize.width(),g_ScreenSize.height()/12);
    g_RcMain = QRect(0,0,g_ScreenSize.width(),g_ScreenSize.height()*11/12);

	/**********************************自定义字体**********************************/
	int fontId = QFontDatabase::addApplicationFont("/ufs/lib/fonts/msyh.ttf");
	QString msyh = QFontDatabase::applicationFontFamilies ( fontId ).at(0);

	fontId = QFontDatabase::addApplicationFont("/ufs/lib/fonts/dianzhen.ttf");
	QString dianzhen = QFontDatabase::applicationFontFamilies ( fontId ).at(0);

	fontId = QFontDatabase::addApplicationFont("/ufs/lib/fonts/simhei.ttf");
	QString simhei = QFontDatabase::applicationFontFamilies ( fontId ).at(0);

	g_Font[0].setFamily(msyh);
	g_Font[1].setFamily(dianzhen);
	g_Font[2].setFamily(simhei);

	g_Font[0].setPixelSize(16);
	g_Font[1].setPixelSize(16);
	g_Font[2].setPixelSize(16);

	a.setFont(g_Font[0]);

	qDebug()<<"Start Iot........";
	MyInputPanelContext *ic = new MyInputPanelContext;
	a.setInputContext(ic);//将输入上下文与应用程序关联

	/**********************************初始化UI颜色样式**********************************/
	//switch(read_profile_int("UserSettings","iUIType",0,LOCALINIFILE))
	{
	//default:
	{
		g_Palette.setColor(QPalette::Active,QPalette::WindowText,QColor(qRgba(250,170,0,255)));
		g_Palette.setColor(QPalette::Active,QPalette::Text,QColor(qRgba (191,0,0,255)));
		g_Palette.setColor(QPalette::Active,QPalette::Light,QColor(qRgba(170,170,127,255)));
		g_Palette.setColor(QPalette::Inactive,QPalette::WindowText,QColor(qRgba(250,170,0,255)));
		g_Palette.setColor(QPalette::Inactive,QPalette::Text,QColor(qRgba (191,0,0,255)));
		g_Palette.setColor(QPalette::Inactive,QPalette::Light,QColor(qRgba(170,170,127,255)));
		g_Palette.setColor(QPalette::Disabled,QPalette::WindowText,QColor(qRgba(153,153,153,255)));
		g_Palette.setColor(QPalette::Disabled,QPalette::Text,QColor(qRgba(153,153,153,255)));
		//break;
	}
	}

	mainwindow g_mainWin;
	g_mainWin.setWindowOpacity(1);
	g_mainWin.setWindowFlags(Qt::FramelessWindowHint);
	g_mainWin.show();

    return a.exec();
}

