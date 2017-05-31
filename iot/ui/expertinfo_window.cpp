#include "expertinfo_window.h"

expertinfo_window::expertinfo_window(QWidget *parent)
    : QWidget(parent)
{
	button_flag = 0;
	this->setGeometry(QRect(0,g_RcStatusbar.bottom(),g_RcMain.width(),g_RcMain.height()));
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);

	m_MainLayout = new QGridLayout(this);
	m_MainLayout->setGeometry(QRect(0,g_ScreenSize.height()*1/10,g_ScreenSize.width(),g_ScreenSize.height()*8/10));
	datatableview = new QTableView(this);
	datatableview->setGeometry(QRect(0,g_ScreenSize.height()*2/10,g_ScreenSize.width(),g_ScreenSize.height()*6/10));
	m_ButtonLayout = new QHBoxLayout();
	m_ButtonLayout->setGeometry(QRect(0,g_ScreenSize.height()*8/10,g_ScreenSize.width(),g_ScreenSize.height()*1/10));

	button_search = new QPushButton(tr("Search"), this);
	button_increate = new QPushButton(tr("Increase"), this);
	button_update = new QPushButton(tr("Update"), this);
	button_delete = new QPushButton(tr("Delete"), this);

	m_MainLayout->addWidget(datatableview,1,0);
	m_MainLayout->addLayout(m_ButtonLayout,8,0);
	m_ButtonLayout->addWidget(button_search);
	m_ButtonLayout->addWidget(button_increate);
	m_ButtonLayout->addWidget(button_update);
	m_ButtonLayout->addWidget(button_delete);

	datatableview->verticalHeader()->setVisible(false);
	datatableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
	datatableview->setSelectionMode(QAbstractItemView::SingleSelection);
	datatableview->setSelectionBehavior(QAbstractItemView::SelectRows);
	datatableview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //关闭滚动条
	datatableview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	datatableview->setStyleSheet("QTableView{background-color: rgb(86, 86, 86);color: white}");

	m_model = new QStandardItemModel(6, 7,this);
	m_model->setHeaderData(0, Qt::Horizontal, tr("序号"));
	m_model->setHeaderData(1, Qt::Horizontal, tr("品种"));
	m_model->setHeaderData(2, Qt::Horizontal, tr("空气温度"));
	m_model->setHeaderData(3, Qt::Horizontal, tr("空气湿度"));
	m_model->setHeaderData(4, Qt::Horizontal, tr("土壤温度"));
	m_model->setHeaderData(5, Qt::Horizontal, tr("土壤湿度"));
	m_model->setHeaderData(6, Qt::Horizontal, tr("CO2浓度"));
	datatableview->setModel(m_model);
	datatableview->resizeColumnsToContents(); //根据内容调整所有列的列宽

	m_rowcount = 0;
	m_currentrow = 0;

	v_expertinfo.clear();
	expertdata.getExpertInfo(v_expertinfo);
	datatableview_update(v_expertinfo);

	connect(button_delete, SIGNAL(clicked()), this, SLOT(button_delete_clicked()));
	connect(button_update, SIGNAL(clicked()), this, SLOT(button_update_clicked()));
	connect(button_increate, SIGNAL(clicked()), this, SLOT(button_increate_clicked()));
	connect(button_search, SIGNAL(clicked()), this, SLOT(button_search_clicked()));
}

expertinfo_window::~expertinfo_window()
{

}

/**
 * 置按钮标志位，弹出输入框
 *
 */
void expertinfo_window::button_search_clicked()
{
	button_flag = 1;
	m_operation_window = new expertinfo_operation_window(this,button_flag);
	connect(m_operation_window, SIGNAL(sendData(ST_ExpertInfo)), this, SLOT(receiveData(ST_ExpertInfo)));
	m_operation_window->exec();
}

void expertinfo_window::button_increate_clicked()
{
	button_flag = 2;
	m_operation_window = new expertinfo_operation_window(this,button_flag);
	connect(m_operation_window, SIGNAL(sendData(ST_ExpertInfo)), this, SLOT(receiveData(ST_ExpertInfo)));
	m_operation_window->exec();
}

/*
 * 获取数据库全部数据，并刷新界面
 */
void expertinfo_window::button_update_clicked()
{
	expertdata.getExpertInfo(v_expertinfo);
	datatableview_update(v_expertinfo);
}

/*
 *获取到当前的选中行，并从数据库删除选中数据，刷新界面
 */
void expertinfo_window::button_delete_clicked()
{
	m_currentrow = datatableview->currentIndex().row();
	QModelIndex indextmp = m_model->index(m_currentrow, 0);
	QVariant datatmp = m_model->data(indextmp);
	int deleteid = datatmp.toInt();

	if(m_currentrow < 0)
	{
		QMessageBox::warning(this, tr("警告"), tr("没有选中数据！"));
	}
	else
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::information(this, tr("删除"), tr("确认删除？"), QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
			if(reply == QMessageBox::Yes)
			{
				expertdata.deleteExpertInfo(deleteid);
				expertdata.getExpertInfo(v_expertinfo);
				datatableview_update(v_expertinfo);
			}
	}
}

/*
 * 弹窗信号的槽函数，用于接收输入数据
 */
void expertinfo_window::receiveData(ST_ExpertInfo InputInfo)
{
	vector<ST_ExpertInfo>  v_expertinfo;
	//收到的数据如何处理
	switch(button_flag)
	{
		//查找按钮按下，用户可输入ID或者品种查找;调数据库命令，更新界面
		case 1:
		{
			v_expertinfo.clear();
			printf("start size is %d\n", v_expertinfo.size());
			if(InputInfo.strExpertvariety.size() == 0)
			{
				expertdata.getExpertInfoById(v_expertinfo,InputInfo.iExpertid);
			}
			else
			{
				char * strExpertvariety = const_cast<char *>(InputInfo.strExpertvariety.c_str());
				expertdata.getExpertInfoByVariety(v_expertinfo,strExpertvariety);
			}

			datatableview_update(v_expertinfo);
			break;
		}
		//添加按钮按下，用户可输入新的记录;
		case 2:
		{
			expertdata.insertIntoExpertInfo(InputInfo);
			expertdata.getExpertInfo(v_expertinfo);
			datatableview_update(v_expertinfo);
			break;
		}
	}
}

/*
 * 根据结果数据，修改model,刷新界面
 */
void expertinfo_window::datatableview_update(vector<ST_ExpertInfo>  v_expertinfo)
{
	m_model->removeRows(0,m_rowcount);
	m_rowcount = v_expertinfo.size();
	m_model->setRowCount(m_rowcount);
	QString tmp;
	for(uint8_t i=0; i<v_expertinfo.size(); i++)
	{
		QModelIndex index1 = m_model->index(i, 0, QModelIndex());
		m_model->setData(index1, QVariant(v_expertinfo[i].iExpertid));
		QModelIndex index2 = m_model->index(i, 1, QModelIndex());
		tmp = QString::fromStdString(v_expertinfo[i].strExpertvariety);
		m_model->setData(index2, QVariant(tmp));
		QModelIndex index3 = m_model->index(i, 2, QModelIndex());
		m_model->setData(index3, QVariant(v_expertinfo[i].iExpertairtemper));
		QModelIndex index4 = m_model->index(i, 3, QModelIndex());
		m_model->setData(index4, QVariant(v_expertinfo[i].iExpertairhumid));
		QModelIndex index5 = m_model->index(i, 4, QModelIndex());
		m_model->setData(index5, QVariant(v_expertinfo[i].iExpertsoiltemper));
		QModelIndex index6 = m_model->index(i, 5, QModelIndex());
		m_model->setData(index6, QVariant(v_expertinfo[i].iExpertsoilhumid));
		QModelIndex index7 = m_model->index(i, 6, QModelIndex());
		m_model->setData(index7, QVariant(v_expertinfo[i].iExpertco2));
	}
	datatableview->resizeColumnsToContents();
	datatableview->setModel(m_model);
}


