#ifndef LOGIN_H
#define LOGIN_H

#include <QtGui/QWidget>
#include "ui_login.h"
#include "widget/qpushbutton_new.h"

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = 0);
    ~login();

private:
    Ui::loginClass *ui;
    QRect m_rcMain;
    QRect m_rcTitle;
    QRect m_rcUserNameL;
    QRect m_rcUserNameE;
    QRect m_rcPassWordL;
    QRect m_rcPassWordE;
    QRect m_rcLogin;

    QPushButton_new *pushButton_Login;

private slots:
	void CheckloginSuc();
};

#endif // LOGIN_H
