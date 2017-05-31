#ifndef EXPERTINFO_OPERATION_WINDOW_H
#define EXPERTINFO_OPERATION_WINDOW_H

#include <QtGui/QWidget>
#include "userdef.h"
#include "QGridLayout"
#include "QLabel"
#include "QLineEdit"
#include "QPushButton"
#include "global.h"
#include "QString"
#include <QMessageBox>

class expertinfo_operation_window : public QDialog
{
    Q_OBJECT

public:
    expertinfo_operation_window(QWidget *parent = NULL, int flag = 0);
    ~expertinfo_operation_window();

private:
    QGridLayout        *m_MainLayout;//最底层布局

    QLabel			   *label_title;
    QLabel			   *label_Expertid;
    QLabel			   *label_Expertvariety;
    QLabel			   *label_Expertairtemper;
    QLabel			   *label_Expertairhumid;
    QLabel			   *label_Expertsoiltemper;
    QLabel			   *label_Expertsoilhumid;
    QLabel			   *label_Expertco2;
    QLabel			   *label_delete;

    QLineEdit		   *text_Expertid;
    QLineEdit		   *text_Expertvariety;
    QLineEdit		   *text_Expertairtemper;
    QLineEdit		   *text_Expertairhumid;
    QLineEdit		   *text_Expertsoiltemper;
    QLineEdit		   *text_Expertsoilhumid;
    QLineEdit		   *text_Expertco2;

    QPushButton        *button_sure;
    QPushButton        *button_cancel;

    QRect			   m_Rcwindow;

    int				   m_flag;//区分不同的窗口

	void set_sizeof_window(int button_flag);

signals:
	void sendData(ST_ExpertInfo  InputExpertInfo);

private slots:
	void  ReturnInputInfo();

};

#endif // EXPERTINFO_OPERATION_WINDOW_H
