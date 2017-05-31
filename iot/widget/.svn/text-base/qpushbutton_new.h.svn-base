#ifndef QPUSHBUTTON_NEW_H
#define QPUSHBUTTON_NEW_H

#include <QWidget>
#include "qpushbutton.h"
#include <QPalette>
#include <QPixmap>
#include "global.h"

class QPushButton_new : public QPushButton
{
    Q_OBJECT
public:
    explicit QPushButton_new(QWidget *parent = 0);
    explicit QPushButton_new(QString text,QString strNor = ":iot/png/button/normal.png",QString strPre = ":iot/png/button/press.png",QString strDi = ":iot/png/button/disable.png",QWidget *parent=0);

    void setText(const QString &text);
    void setColor(const QColor &color);
    void setPixmap(QPixmap PixNor, QPixmap PixPre = QPixmap( ":iot/png/button/press.png"),QPixmap PixUn = QPixmap( ":iot/png/button/disable.png"));
    void setState(int istate);
signals:

public slots:

private:
    void setBkPalette(int transparency);//设置透明度

    QPixmap m_PixNor;
    QPixmap m_PixPre;
    QPixmap m_PixUn;

    QString m_Text;
    QColor m_Color;

    int m_iState;//按钮状态 0:正常 1:按下

protected:
    void mousePressEvent(QMouseEvent *e);//点击
    void mouseReleaseEvent(QMouseEvent *e);//释放
    void paintEvent(QPaintEvent *event);
};

#endif // QPUSHBUTTON_NEW_H
