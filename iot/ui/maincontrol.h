#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include <QtGui/QWidget>
#include "ui_maincontrol.h"
#include "global.h"
#include"mctrtabchart1.h"
#include"comcontrol/serial_control.h"
#include"comcontrol/protocol.h"
#include "comcontrol/comcontrol.h"

class maincontrol : public QWidget
{
    Q_OBJECT

public:
    maincontrol(QWidget *parent = 0);
    ~maincontrol();

protected:
    int addlabel(int i,QString str = "");
    int updateUI();

protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);

protected:

private slots:
	void btnClick();
    void UpdateData();
    void OnComRead();
    int get_realdata();

private:
    Ui::maincontrolClass ui;
    QVBoxLayout *mainLayout1;
    QHBoxLayout *layout1;
    QScrollArea *m_ScrollArea;
    QWidget *m_ScrollWidget;
    QFrame *fm1;
    QLabel *label1;

    QRect m_rcMain;
    QRect m_rcTab;
    QRect m_rcSan;
    QRect m_rcSaWidgetn;
    QRect m_rcBt;

    vector<QLabel *> m_vlabeln;
    vector<QRect > m_vRcn;
    vector<QLabel *> m_vlabelh;
    vector<QRect > m_vRch;

    QPoint m_Point;
    QTimer *updateTimer1;
    QTimer *updateTimer2;

    mctrtabchart1 *tabchart1;
    mctrtabchart1 *tabchart2;


    uint8_t m_buf[1024];
    protocol_list_t *list;

    comcontrol *m_comcontrol;
};

#endif // MAINCONTROL_H
