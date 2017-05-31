#ifndef VIDEO_SHOW_H
#define VIDEO_SHOW_H

#include <QtGui/QWidget>
#include "ui_video_show.h"
#include "video/videodevice.h"
#include "qlabel.h"
#include "qtimer.h"
#include "widget/qpushbutton_new.h"

class DecodeThread :public QThread
{
	Q_OBJECT
public:
	explicit DecodeThread(QObject *parent = 0)
		:QThread(parent)
	{
		m_mutex.tryLock();
		connect(g_qrcode,SIGNAL(DecodeStr(QString ,int )),this,SLOT(Decode(QString ,int )));
	}

	void setImage(QImage image)
	{
		m_DecodeImage = image;
		m_mutex.unlock();
	}

protected:
	void run()
	{
		while(1)
		{
			if(g_qrcode != 0)
			{
				g_qrcode->decodeImage(m_DecodeImage);
			}
			else
			{
				sleep(1);
			}
		}
	}

private slots:
	void Decode(QString tag,int itime)
	{
		m_mutex.tryLock(10);
		emit DecodeStr(tag,itime);
	}

signals:
	void DecodeStr(QString tag,int itime);

private:
	QImage m_DecodeImage;
	QMutex m_mutex;
};

class video_show : public QWidget
{
    Q_OBJECT

public:
    video_show(QWidget *parent = 0);
    ~video_show();

private:
    Ui::video_showClass ui;
    QRect m_rcMain;

    QLabel *m_qlabel;
    QPushButton_new *m_btPic;
    QLabel *m_qlabel_qr;
    QLabel *m_qlabel_pic;

    QImage *m_frame;

    QTimer *m_timer;

    DecodeThread *m_Dt;

    VideoDevice *m_vd;

    uchar *pp;
    uchar * p;

 private slots:
    void display_error(QString err);
    void updateVideo();
    void btPicClick();
    void DecodeStr(QString tag,int itime);
};

#endif // VIDEO_SHOW_H
