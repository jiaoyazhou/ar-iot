/*
 * mctrtabchart1.h
 *
 *  Created on: 2017年4月27日
 *      Author: root
 */

#ifndef DEBUG_MCTRTABCHART1_H_
#define DEBUG_MCTRTABCHART1_H_

#define TEXT_BOX_SPACE 5
#define X_INCREMENT 5
#define POINT_RADIUS 3

#include <QWidget>
#include <QtGui>
#include "global.h"

class mctrtabchart1 : public QWidget
{
    Q_OBJECT
public:
    explicit mctrtabchart1(QWidget *parent = 0);
    virtual ~mctrtabchart1();

public slots:
    void addData(qreal data);

    void setUseAntialiasing(bool use)
    {
        m_bUseAntialiasing=use;
        update();
    }

    bool getUseAntialiasing() const
    {
        return m_bUseAntialiasing;
    }

    void setHorizontalLineColor(const QColor& clr)
    {
        m_hLineClr=clr;
        update();
    }

    void setShowPoint(bool show)
    {
        m_bShowPoint=show;
        update();
    }

    void setTitle(const QString& str)
    {
        m_strTitle=str;
        update();
    }

    void setLine(int iline)
    {
    	m_iLine = iline;
    	update();
    }

    void setMax(int iMax)
    {
    	m_iMax = iMax;
    	update();

    }

    void setDecValue(int iValue)
    {
    	m_iDecValue = iValue;
    	update();
    }

protected:
    void paintEvent(QPaintEvent *);

    void resizeEvent(QResizeEvent *)
    {
        updateVector();
    }

    QSize sizeHint() const
    {
        return QSize(350,350);
    }

    QSize minimumSizeHint() const
    {
        return QSize(280,280);
    }

private:
    void resetVariables(QPainter* painter);
    void drawBackground(QPainter* painter);
    void drawBox(QPainter* painter);
    void drawText1(QPainter* painter);
    void drawText2(QPainter* painter);
    void drawGraph(QPainter* painter);
    void drawTitle(QPainter* painter);

private:
    qreal            m_leftSpace;
    qreal            m_topSpace;
    QVector<qreal>   m_dataVec;
    QVector<QPointF> m_potVec;
    bool             m_bUseAntialiasing;
    bool             m_bShowHLine;
    bool             m_bShowPoint;
    QRectF           m_topRect;
    QRectF           m_bottomRect;
    QRectF           m_boxRect;
    QColor           m_hLineClr;
    QString          m_strTitle;
    QPalette 		 m_Palette;

    int m_iLine;
    int m_iMax;
    int m_iDecValue;

    void initVariables();
    void updateVector();

};

#endif /* DEBUG_MCTRTABCHART1_H_ */
