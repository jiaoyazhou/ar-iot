/*
 * getdata.cpp
 *
 *  Created on: 2017年6月6日
 *      Author: root
 */

#include "getdata.h"
#include "string.h"
#include "memory.h"


//用来存储序列号及品种的相关信息
ST_IDInfo  idinfo[10] = {{1,0,"玉米",0}, {2,0,"水稻",0}, {3,0,"小麦",0}, {4,0,"苹果",0}, {5,0,"香蕉",0},
						 {6,0,"白菜",0}, {7,0,"萝卜",0}, {8,0,"茄子",0}, {9,0,"桃子",0}, {10,0,"梨",0},};

static int parase_data(uint8_t *_protocol, int _len);

getdata::getdata()
{
	// TODO Auto-generated constructor stub
	m_comcontrol = new comcontrol("/dev/ttySAC1", 115200);
	int ret = m_comcontrol->Com_Init();
	if(ret < 0)
	{
		printf("com init error\n");
		return;
	}
	else
	{
		connect(m_comcontrol,SIGNAL(OnComRead()),this,SLOT(OnComRead()));
	}
    this->start();
}

void getdata::run()
{
    list = new protocol_list_t();
    protocol_list_init(list, m_buf, sizeof(m_buf));

    while(1)
    {
    	int ret = parase_protocol(list, parase_data);
    	printf("data lenth is %d \n",ret);
    }
}


static int parase_data(uint8_t *_protocol, int _len)
{

    int tmp = 0;   //标志是否在结构体数组中查到对应的序列号
	ST_CollectInfo  m_collectinfo;
	protocol_stable_t* stable =(protocol_stable_t*)_protocol;
	//获取序列号，时间
	int serial = *(int *)stable->from_serial;
	printf("id is %d\n",serial);
	for(int i = 0; i < 10; i++)
	{
		if(idinfo[i].serialnum == serial)
		{
			m_collectinfo.id = idinfo[i].id;
			m_collectinfo.variety = idinfo[i].variety;
			tmp = 1;
			break;
		}

	}
	if(tmp == 0)
	{
		for(int i = 0; i < 10; i++)
		{
			if(idinfo[i].flag == 0)
			{
				idinfo[i].serialnum = serial;
				m_collectinfo.id = idinfo[i].id;
				m_collectinfo.variety = idinfo[i].variety;
				idinfo[i].flag =1;
				break;
			}

		}
	}

	QDateTime current_date_time = QDateTime::currentDateTime();     //获取当前时间
	QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm");
	m_collectinfo.time = current_date;

	int value = 0;
	if(stable->command != CMD_REPORTER)  //根据命令情况，转换为不同的数据结构
	{
		protocol_reporter_status* report_data = (protocol_reporter_status*)stable;
		value = big_to_uint32(&report_data->value);
	}

	switch(stable->flag)
	{
		case FLAG_TEMPERATURE:
			m_collectinfo.flag = airtemper;
			m_collectinfo.value = value;
			printf("====温度： %d==== \n", value);
			//m_temperature.push_back(int_temp);
			break;

		case FLAG_HUMIDITY:
			m_collectinfo.flag = airhumid;
			m_collectinfo.value = value;
			printf("====湿度： %d====\n", value);
		//	m_humidity.push_back(int_humid);
			break;

		case FLAG_CO2:
			m_collectinfo.flag = co2;
			m_collectinfo.value = value;
			printf("====CO2： %d====\n", value);
		//	m_humidity.push_back(int_humid);
			break;
	}
	g_database->insertIntoCollectInfo(m_collectinfo);
	return 0;
}


void getdata::OnComRead()
{
	uint8_t com_initdata[100];
	int ret = 0;

	ret = m_comcontrol->ComRecv((char *)com_initdata, sizeof(com_initdata));
	printf("read : %d  \n",ret);

	ret = put_data_to_list(list, (uint8_t *)com_initdata, sizeof(com_initdata));
	printf("put_data_to_list %d \n",ret);
}

void getdata::Close()
{
	while(this->isRunning())
	{
		this->terminate();
	}
}

getdata::~getdata() {
	// TODO Auto-generated destructor stub
}

