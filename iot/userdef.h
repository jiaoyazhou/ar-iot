#ifndef __USERDEF_H__
#define __USERDEF_H__

#include <vector>
using std::vector;

extern "C" {
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
}

#include <QString>
using namespace std;

/****************************************************数据库结构******************************************************/
//用户登录记录
struct AR_LoginInfo{
    char strUserId[50];                  //用户ID
    char strPassWord[50];                //登录密码
};

enum ValueFlag
{
	airtemper = 0,
	airhumid,
	soiltemper,
	soilhumid,
	co2
};

//采集器采集到的数据
struct ST_CollectInfo{
	QString        time;                  //时间
	int            id;                   //节点编号
	string         variety;             //品种
	int            value;              //采集到的数据
	ValueFlag      flag;              //判断获取的数据是温度或湿度
};

//专家知识库的信息
struct ST_ExpertInfo{
	int     iExpertid;                 //序号
	string  strExpertvariety;          //品种
	int     iExpertairtemper;        //适宜空气温度
	int     iExpertairhumid;         //适宜空气湿度
	int     iExpertsoiltemper;       //适宜土壤温度
	int     iExpertsoilhumid;        //适宜土壤湿度
	int     iExpertco2;              //适宜二氧化碳浓度
};
#endif // __USERDEF_H__
