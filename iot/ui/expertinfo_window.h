#ifndef EXPERTINFO_WINDOW_H
#define EXPERTINFO_WINDOW_H

#include <QtGui/QWidget>
#include "expertinfo_operation_window.h"
#include "qstandarditemmodel.h"
#include "userdef.h"
#include "global.h"
#include <vector>
#include <stdint.h>

#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableView>
#include <QMessageBox>

#include "../database/Database.h"
#include <vector>

class expertinfo_window : public QWidget
{
    Q_OBJECT

public:
    expertinfo_window(QWidget *parent = 0);
    ~expertinfo_window();

    Database expertdata;

private:
    QGridLayout        *m_MainLayout;//最底层布局
    QTableView         *datatableview;//表格布局的数据显示

    QHBoxLayout        *m_ButtonLayout;//按钮布局
    QPushButton        *button_search;
    QPushButton        *button_increate;
    QPushButton        *button_update;
    QPushButton        *button_delete;

    QRect               m_Rctitle;
    QStandardItemModel *m_model;

    int   m_rowcount;
    int   m_currentrow;

    expertinfo_operation_window  *m_operation_window;

	vector<ST_ExpertInfo>  v_expertinfo;

    void datatableview_update(vector<ST_ExpertInfo>  v_expertinfo);//根据数据库结果，刷新表格
    int button_flag;// 按钮标志位，根据不同的按钮，显示不同的界面
protected slots:
	void button_search_clicked();
	void button_increate_clicked();
	void button_update_clicked();
	void button_delete_clicked();
	void receiveData(ST_ExpertInfo InputInfo);

};

#endif // EXPERTINFO_WINDOW_H
