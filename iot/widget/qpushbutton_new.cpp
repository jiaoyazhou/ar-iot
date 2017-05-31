#include "qpushbutton_new.h"
#include "qpainter.h"
#include "qapplication.h"

QPushButton_new::QPushButton_new(QWidget *parent) :
    QPushButton(parent),
    m_iState(0),
    m_Text(""),
    m_Color(QColor(255,0,0)),
    m_PixNor(QPixmap(":iot/png/button/normal.png")),
    m_PixPre(QPixmap(":iot/png/button/press.png")),
    m_PixUn(QPixmap(":iot/png/button/disable.png"))
{
    setBkPalette(0);
    setFlat(true);
    setAutoFillBackground(true);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

QPushButton_new::QPushButton_new(QString text,QString strNor, QString strPre, QString strDi, QWidget *parent):
    QPushButton(parent),
    m_Text(text),
    m_Color(QColor(255,0,0)),
    m_PixNor(QPixmap(strNor)),
    m_PixPre(QPixmap(strPre)),
    m_PixUn(QPixmap(strDi))
{
    setBkPalette(0);
    setFlat(true);
    setAutoFillBackground(true);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void QPushButton_new::setText(const QString &text)
{
    m_Text = text;
    this->update();
}

void QPushButton_new::setColor(const QColor &color)
{
    m_Color = color;
    this->update();
}

void QPushButton_new::setPixmap(QPixmap PixNor, QPixmap PixPre, QPixmap PixUn)
{
    m_PixNor = PixNor;
    m_PixPre = PixPre;
    m_PixUn = PixUn;
    this->update();
}

void QPushButton_new::setState(int istate)
{
    m_iState = istate;
    this->update();
}

void QPushButton_new::setBkPalette(int transparency)//设置背景透明度
{
   QPalette palette;
   palette.setBrush(QPalette::Button,QBrush(QColor(255,255,255,transparency)));
   setPalette(palette);
   this->update();
}

void QPushButton_new::mousePressEvent(QMouseEvent *e)
{
    m_iState = 1;
    this->update();
}
void QPushButton_new::mouseReleaseEvent(QMouseEvent *e)
{
    m_iState = 0;
    emit clicked();//必须写上，否则不会发出clicked信号
    this->update();
}

void QPushButton_new::paintEvent(QPaintEvent *event)
{
    QPainter painter(this) ;
    if(this->isEnabled())
    {
        if(m_iState == 0)
        {
            m_PixNor.scaled(rect().width(),rect().height());
            painter.drawPixmap(rect(),m_PixNor);
            painter.setPen(QPen(QColor(127,0,0)));
        }
        else
        {
            m_PixPre.scaled(rect().width(),rect().height());
            painter.drawPixmap(rect(),m_PixPre);
            painter.setPen(QPen(m_Color));
        }
    }
    else
    {
        m_PixUn.scaled(rect().width(),rect().height());
        painter.drawPixmap(rect(),m_PixUn);
        painter.setPen(QPen(QColor(255,255,255)));
    }
    painter.drawText(rect(),Qt::AlignCenter,m_Text);
    return ;
}
