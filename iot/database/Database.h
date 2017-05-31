/*
 * Database.h
 *
 *  Created on: 2017年4月28日
 *      Author: root
 */

#ifndef DATABASE_DATABASE_H_
#define DATABASE_DATABASE_H_
#include "userdef.h"
#include <string>
#include <vector>


static char LOCALDB_PATH[100] = "/ufs/lib/ar_iot.db";

class Database
{
public:
	Database();
	~Database();

/*******************************************************
* Function Name:printflog
* Purpose：打印LOG 记录日志
* Params :
*   __const char *__restrict __format:打印LOG格式
* Return：
* Limitation: 0:打开数据库成功 -1：打开数据库失败 -2:数据库路径错误
*******************************************************/
int printflog (__const char *__restrict __format, ...);

/*******************************************************
* Function Name:db_open
* Purpose：打开数据库
* Params :
*   char *strDbLocation  数据库路径
* Return：打开数据库结果
* Limitation: 0:打开数据库成功 -1：打开数据库失败 -2:数据库路径错误
*******************************************************/
int db_open(char *strDbLocation= LOCALDB_PATH);

/*******************************************************
* Function Name:db_close
* Purpose：关闭数据库
* Params :
* Return：关闭数据库结果
* Limitation: 0:关闭数据库成功 -1：关闭数据库失败
*******************************************************/
int db_close();

/*******************************************************
* Function Name:db_exec_cmd
* Purpose：执行SQL语句
* Params :
*   char *dbcmd  SQL语句
* Return：执行SQL语句结果
* Limitation: 0:执行SQL语句成功 -1：执行SQL语句失败
*******************************************************/
int db_exec_cmd(char *dbcmd);

/*******************************************************
* Function Name:get_count_table
* Purpose：执行SQL语句 获取查询语句的结果数
* Params :
*   char *dbcmd  SQL语句
* Return：打开数据库结果
* Limitation: 0:打开数据库成功 -1：打开数据库失败
*******************************************************/
int get_count_table(char *datacmd);

/*******************************************************
* Function Name: InsertIntoCollectAirTemper
* Purpose：插入采集的空气温度信息
* Params :
*	ST_CollectAirTemper &CollectAirTemper:空气温度信息
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int insertIntoCollectInfo(ST_CollectInfo &collectinfo);

/*******************************************************
* Function Name: InsertIntoCollectAirTemper
* Purpose：插入多条采集的空气温度信息
* Params :
*	vector<ST_ArcollectInfo> &v_CollectAirTemper:空气温度信息集
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int insertIntoCollectInfo(vector<ST_CollectInfo> &v_collectinfo);

/*******************************************************
* Function Name: insertIntoExpertInfo
* Purpose：插入单条专家知识信息
* Params :
*	ST_ExpertInfo &expertinfo:专家知识信息
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int insertIntoExpertInfo(ST_ExpertInfo &expertinfo);

/*******************************************************
* Function Name:insertIntoUserInfo
* Purpose：插入多条专家知识信息
* Params :
*	vector<ST_UserInfo> &v_userInfo:专家知识信息集
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int insertIntoExpertInfo(vector<ST_ExpertInfo> &v_expertinfo);

/*******************************************************
* Function Name: updateExpertInfo
* Purpose： 根据专家id修改专家知识信息
* Params :
*	ST_ExpertInfo &expertinfo:专家知识信息
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int updateExpertInfo(ST_ExpertInfo &expertinfo);

/*******************************************************
* Function Name:updateUserInfo
* Purpose：修改多条专家信息记录
* Params :
*	vector<ST_ExpertInfo> &v_expertinfo:专家知识信息集
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int updateExpertInfo(vector<ST_ExpertInfo> &v_expertinfo);

/*******************************************************
* Function Name: getCollectInfoByDate
* Purpose：根据日期范围，获取采集数据
* Params :
* 	vector<ST_CollectInfo> &v_collectinfo:返回的采集数据
* 	char *strDateBegin:起始日期
* 	char *strDateEnd:结束日期
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int getCollectInfo(vector<ST_CollectInfo> &v_collectinfo,ValueFlag flag);

/*******************************************************
* Function Name: getCollectInfoByDate
* Purpose：根据日期范围，获取采集数据
* Params :
* 	vector<ST_CollectInfo> &v_collectinfo:返回的采集数据
* 	char *strDateBegin:起始日期
* 	char *strDateEnd:结束日期
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int getCollectInfoByDate(vector<ST_CollectInfo> &v_collectinfo,char * strDateBegin,char *strDateEnd,ValueFlag flag);

/*******************************************************
* Function Name: DbdataToArcollectInfo
* Purpose：将获取到的记录信息，存入结构体中
* Params :
* 	vector<ST_ArcollectInfo> &v_arcollectinfo:返回的采集数据
* 	int nrow： 记录行数
* 	int ncolumn:列数即字段数
* 	char** result:select返回的结果
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
void DbdataToCollectInfo(int nrow, int ncolumn,char** result,vector<ST_CollectInfo> &v_collectinfo,char* valuename);

/*******************************************************
* Function Name: getExpertInfoById
* Purpose：获取知识数据所有数据
* Params :
* 	vector<ST_ArcollectInfo> &v_expertinfo:返回的专家数据
* 	char *iExpertid： 专家ID
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int getExpertInfo(vector<ST_ExpertInfo> &v_expertinfo);

/*******************************************************
* Function Name: getExpertInfoById
* Purpose：根据专家的编号，获取知识数据
* Params :
* 	vector<ST_ArcollectInfo> &v_expertinfo:返回的专家数据
* 	char *iExpertid： 专家ID
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/

int getExpertInfoById(vector<ST_ExpertInfo> &v_expertinfo,int iExpertid);
/*******************************************************
* Function Name: getExpertInfoByVariety
* Purpose：根据农作物的品种，获取知识数据
* Params :
* 	vector<ST_ArcollectInfo> &v_expertinfo:返回的专家数据
* 	char *iExpertid： 专家ID
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int getExpertInfoByVariety(vector<ST_ExpertInfo> &v_expertinfo,char * strExpertvariety);

/*******************************************************
* Function Name: getExpertInfoByVariety
* Purpose：根据农作物的品种，获取知识数据
* Params :
* 	vector<ST_ArcollectInfo> &v_expertinfo:返回的专家数据
* 	char *iExpertid： 专家ID
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int getExpertInfoByInput(vector<ST_ExpertInfo> &v_expertinfo,char * strExpertvariety,int iExpertid);


/*******************************************************
* Function Name: DbdataToExpertInfo
* Purpose：将获取到的专家信息，存入结构体中
* Params :
* 	vector<ST_ArcollectInfo> &v_expertinfo:返回的专家数据
* 	int nrow： 记录行数
* 	int ncolumn:列数即字段数
* 	char** result:select返回的结果
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
void DbdataToExpertInfo(int nrow, int ncolumn,char** result,vector<ST_ExpertInfo> &v_expertinfo);

/*******************************************************
* Function Name: deleteArcollectInfo
* Purpose：删除指定日期前指定采集节点的记录
* Params :
*	char *strtime:指定的日期
*	char *iArid:指定的采集ID
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int deleteCollectInfo(char *time,ValueFlag flag);

/*******************************************************
* Function Name: deleteArcollectInfo
* Purpose：删除指定采集节点的记录
* Params :
*	char *iArid:指定的采集ID
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int deleteCollectInfo(int id,ValueFlag flag);

/*******************************************************
* Function Name: deleteExpertInfo
* Purpose：删除指定专家的记录
* Params :
*	char *iExpertid:指定的专家ID
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int deleteExpertInfo(int iExpertid);

/*******************************************************
* Function Name: deleteExpertInfo
* Purpose：删除指定品种的专家记录
* Params :
*	char *strExpertvariety:指定的品种
* Return：执行结果
* Limitation: 0:执行成功 -1：执行失败
*******************************************************/
int deleteExpertInfo(char *strExpertvariety);

private:
	int CheckTimeStr(char *time);
	int DateTime2Date(char *datetime , char *date);
	int CheckDateTimeStr(char *datetime);
	int CheckDateStr(char *date);
};
#endif /* DATABASE_DATABASE_H_ */
