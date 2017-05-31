#include "login.h"
#include "maincontrol.h"
#include<qthread.h>
#include<qmessagebox.h>

login::login(QWidget *parent)
    : QWidget(parent),
	  m_rcMain(g_RcMain),
	  m_rcTitle(QRect(parent->width()*0.33,parent->height ()/12,parent->width()*0.5,parent->height ()*0.125)),
	  m_rcUserNameL(QRect( parent->width()*0.25, parent->height ()*0.3 , parent->width()*0.25, parent->height ()*0.1)),
	  m_rcUserNameE(QRect(parent->width()*0.4375 , parent->height ()*0.3 , parent->width()*0.33,parent->height ()*0.1)),
	  m_rcPassWordL(QRect( parent->width()*0.25, parent->height ()*0.5, parent->width()*0.25, parent->height ()*0.1)),
	  m_rcPassWordE(QRect(parent->width()*0.4375 ,parent->height ()*0.5, parent->width()*0.33,parent->height ()*0.1)),
	  m_rcLogin(QRect(parent->width()*0.375,parent->height ()*0.7, parent->width()*0.25,parent->height ()*0.1)),
	  pushButton_Login(0),
	  ui(new Ui::loginClass)
{
	ui->setupUi(this);

	this->setGeometry(m_rcMain);
	this->setAttribute(Qt::WA_DeleteOnClose);

	ui->label_Title->setGeometry(m_rcTitle);
	//ui->label_Title->setFont(Statusbar::GetFont(parent->width()*0.05));
	ui->label_UsrName->setGeometry(m_rcUserNameL);
	//ui->label_UsrName->setFont(Statusbar::GetFont(parent->width()*0.04));
	ui->lineEdit_UsrName->setGeometry(m_rcUserNameE);
	ui->lineEdit_UsrName->setEnabled(true);
	//ui->lineEdit_UsrName->setFont(Statusbar::GetFont(parent->width()*0.04));
	ui->label_PassWord->setGeometry(m_rcPassWordL);
	//ui->label_PassWord>setFont(Statusbar::GetFont(parent->width()*0.04));
	ui->lineEdit_PassWord->setGeometry(m_rcPassWordE);
	//ui->lineEdit_PassWord->setFont(Statusbar::GetFont(parent->width()*0.04));

	pushButton_Login = new QPushButton_new(this);
	pushButton_Login->setText("LOGIN");
	pushButton_Login->setGeometry(m_rcLogin);
	//ui->pushButton_Login->setFont(Statusbar::GetFont(parent->width()*0.04));


	connect(pushButton_Login,SIGNAL(clicked()),this,SLOT(CheckloginSuc()));

	 /*UI SETTING*/
	 //ui->label_logo->setGeometry(QRect((m_rcMain.width()-m_rcMain.height()*2/14)/2,m_rcMain.height()/14,m_rcMain.height()*2/14,m_rcMain.height()*2/14));
}

login::~login()
{
	if(pushButton_Login != 0)
	{
		delete pushButton_Login;
		pushButton_Login = 0;
	}
}

void login::CheckloginSuc()
{
	if(ui->lineEdit_UsrName->text().length() < 1)
	    	{
	    		QMessageBox::warning(this,tr("警告"),QString("用户名为空！"));
	    	}
	else if(ui->lineEdit_PassWord->text().length() < 1)
	    	{
				QMessageBox::warning(this,tr("警告"),QString("密码为空！"));
	    	}
	    	//QByteArray userName = ui->lineEdit_UserName->text().toLatin1();
	    	//QByteArray passWd = ui->lineEdit_PassWord->text().toLatin1();
	    	//int ret =  getUserInfo(g_userInfo,userName.data(),passWd.data());
	else if(ui->lineEdit_UsrName->text()=="aaa" & ui->lineEdit_PassWord->text()=="666")
	    	{
		        maincontrol *maincontrolwin = new maincontrol(this->parentWidget ());
	    		maincontrolwin->show();
	    		this->close();
	    	}
	else
	    	{
				QMessageBox::warning(this,tr("警告"),QString("用户名或密码错误！"),QMessageBox::Yes);
	    	}
}
