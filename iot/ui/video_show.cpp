#include "video_show.h"
#include "qmessagebox.h"
#include "qdebug.h"
#include "QZXing.h"

video_show::video_show(QWidget *parent)
    : QWidget(parent),
	  m_rcMain(QRect(0,parent->height ()/12,parent->width (),parent->height () - parent->height ()/12)),
	  m_qlabel(0),
	  m_btPic(0),
	  m_qlabel_qr(0),
	  m_qlabel_pic(0),
	  m_frame(0),
	  m_timer(0),
	  m_Dt(0),
	  m_vd(0),
	  pp(0),
	  p(0)
{
	ui.setupUi(this);
	this->setGeometry(m_rcMain);
	this->setAttribute(Qt::WA_DeleteOnClose);

	int iWid = 640;
	int iHei = 480;
	m_qlabel = new QLabel(this);
	m_qlabel->setGeometry(QRect(0,(m_rcMain.height()-iHei)/2,iWid,iHei));

	m_btPic = new QPushButton_new(this);
	m_btPic->setText(tr("拍照"));
	int iWidth = (m_rcMain.width()-iWid)/2;
	int iHeight = m_rcMain.height()/12;
	m_btPic->setGeometry(QRect(iWid+iWidth/2,m_rcMain.height()/12,iWidth,iHeight));
	connect(m_btPic, SIGNAL(clicked()), this,SLOT(btPicClick()));

	iWidth = (m_rcMain.width()-iWid);
	m_qlabel_qr = new QLabel(this);
	m_qlabel_qr->setGeometry(QRect(iWid,m_rcMain.height()/6,iWidth,iHeight));

	iHeight = iWidth*480/640;
	m_qlabel_pic = new QLabel(this);
	m_qlabel_pic->setGeometry(QRect(iWid,m_rcMain.height()/4,iWidth,iHeight));

    pp = (unsigned char *)malloc(WIDTH * HEIGHT * 3 * sizeof(char));

	m_frame = new QImage(pp,WIDTH,HEIGHT,QImage::Format_RGB888);

	m_vd = new VideoDevice(tr("/dev/video0"));

	connect(m_vd, SIGNAL(display_error(QString)), this,SLOT(display_error(QString)));

    int iret = m_vd->open_device();
    if(-1==iret)
    {
        QMessageBox::warning(this,tr("error"),tr("open /dev/video0 error"),QMessageBox::Yes);
        m_vd->close_device();
    }

    iret = m_vd->init_device();
    if(-1==iret)
    {
        QMessageBox::warning(this,tr("error"),tr("init failed"),QMessageBox::Yes);
        m_vd->close_device();
    }

    iret = m_vd->start_capturing();
    if(-1==iret)
    {
        QMessageBox::warning(this,tr("error"),tr("start capture failed"),QMessageBox::Yes);
        m_vd->close_device();
    }

    if(-1==iret)
    {
        QMessageBox::warning(this,tr("error"),tr("get frame failed"),QMessageBox::Yes);
        m_vd->stop_capturing();
    }

    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(updateVideo()));
    m_timer->start(20);

    m_Dt = new DecodeThread(this);
    m_Dt->start();
    connect(m_Dt,SIGNAL(DecodeStr(QString ,int )),this,SLOT(DecodeStr(QString ,int )));
}

video_show::~video_show()
{
    int iret = m_vd->stop_capturing();
    iret = m_vd->uninit_device();
    iret = m_vd->close_device();

	if(m_qlabel != 0)
	{
		delete m_qlabel;
		m_qlabel = 0;
	}

	if(m_btPic != 0)
	{
		delete m_btPic;
		m_btPic = 0;
	}

	if(m_qlabel_qr != 0)
	{
		delete m_qlabel_qr;
		m_qlabel_qr =0;
	}

	if(m_qlabel_pic != 0)
	{
		delete m_qlabel_pic;
		m_qlabel_pic = 0;
	}

	if(m_frame != 0)
	{
		delete m_frame;
		m_frame = 0;
	}

	if(m_timer != 0)
	{
		delete m_timer;
		m_timer = 0;
	}

	if(m_vd != 0)
	{
		delete m_vd;
		m_vd = 0;
	}

	if(pp != 0)
	{
		delete pp;
		pp = 0;
	}
}

void video_show::display_error(QString err)
{
    QMessageBox::warning(this,tr("error"), err,QMessageBox::Yes);
}


void video_show::updateVideo()
{
	//qDebug()<<"===updateVideo===";
	int iret;
	size_t len;
	//qDebug()<<"---get_frame---";
	iret = m_vd->get_frame((void **)&p,&len);
	//qDebug()<<"+++get_frame+++";
	m_vd->convert_yuv_to_rgb_buffer(p,pp,WIDTH,HEIGHT);
    m_frame->loadFromData((uchar *)pp,WIDTH * HEIGHT * 3 * sizeof(char));
    m_Dt->setImage(*m_frame);
    //m_frame->save("/tmp/pic.png");
    //g_qrcode->decodeImage(*m_frame);
    m_qlabel->setPixmap(QPixmap::fromImage(*m_frame,Qt::AutoColor));
    m_qlabel->show();
    iret = m_vd->unget_frame();

	//qDebug()<<"+++updateVideo+++";
}


void video_show::btPicClick()
{
	m_qlabel_pic->setPixmap(QPixmap::fromImage(*m_frame,Qt::AutoColor));
	m_qlabel_pic->show();
}


void video_show::DecodeStr(QString tag,int itime)
{
	m_qlabel_qr->setText(tag);
}
