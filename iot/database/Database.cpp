/*
 * Database.cpp
 *
 *  Created on: 2017年4月28日
 *      Author: root
 */

#include "Database.h"
#include "sqlite3.h"
#include <pthread.h>
#include <sys/file.h>


//#define PRINTLOG
#define PRINTLOGLEGTH 1024

sqlite3 *g_XCME_DB = NULL;


//查询多笔记录用的结果集
char **mutilresult=NULL;

pthread_mutex_t mutex_x= PTHREAD_MUTEX_INITIALIZER;

Database::Database()
{

}

Database::~Database()
{

}

int Database::printflog (__const char *__format, ...)
{
#ifdef PRINTLOG
	char strprintf[PRINTLOGLEGTH] = {0};
	va_list args;
	va_start(args, __format);
	vsnprintf(strprintf,PRINTLOGLEGTH-1,__format,args);
	return printf(strprintf);
#endif
	return 0;
}

int Database::db_open(char *strDbLocation)
{
    if(strlen(strDbLocation) < 5)
        return -2;
    pthread_mutex_lock(&mutex_x);
    int rc = 1;
    while(rc){
        rc = sqlite3_open(strDbLocation, &g_XCME_DB);   //打开指定的数据库文件,如果不存在将创建一个同名的数据库文件

        if(rc)
        {
        	printflog("Can't open database: %s\n", sqlite3_errmsg(g_XCME_DB));
        	 db_close();
            continue;
        }
        else
        {
        	printflog("open %s successfully!\n",strDbLocation);
        	 break;
        }
    }
    //flock(g_XCME_DB->nDb,LOCK_EX);
    return 0;
}

int Database::db_close(void)
{
	pthread_mutex_unlock(&mutex_x);
	if(g_XCME_DB != NULL)
	{
		sqlite3_close(g_XCME_DB);
		//flock(g_XCME_DB->nDb,LICK_UN);
		g_XCME_DB = NULL;
		return 0;
	}
	return -1;
}

int Database::db_exec_cmd(char *dbcmd)
{
    char *pErrMsg  = 0;
    int result=SQLITE_ERROR;

    //防止数据库锁死
    while(true)
    {
    	result=sqlite3_exec(g_XCME_DB,dbcmd,0,0,&pErrMsg);
    	if(result == SQLITE_LOCKED )
        {
    		printf("\n------执行数据库操作:-----\n%s\n=======失败result:%s======\n",dbcmd , pErrMsg);
    		sqlite3_free(pErrMsg);
    		continue;
        }
    	else
    	{
    		break;
    	}
    }
    db_close();
    printflog("执行数据库操作 %s 成功\n",dbcmd);
    return 0;
}

int Database::get_count_table(char *datacmd)
{
    char *pErrMsg  = 0;
    char **result=NULL;
    int nrow=0;
    int ncolumn=0;
    int rst=0;

    rst=sqlite3_get_table(g_XCME_DB,datacmd,&result,&nrow,&ncolumn,&pErrMsg);
    if(rst==SQLITE_OK)
    {
    	printflog("nrow=%d,ncolumn=%d,result=%s\n",nrow,ncolumn,result[1]);
        rst=atoi(result[1]);
        sqlite3_free_table(result);
        return rst;
    }
    else
    {
    	 printf("\n---SQL:%s---\nerror:%s---\n",datacmd, pErrMsg);
        sqlite3_free(pErrMsg);
        sqlite3_free_table(result);
        return 0;
    }
}

int Database::insertIntoCollectInfo(ST_CollectInfo &collectinfo)
{
	char tablename[100] = {0};
	char valuename[100] = {0};

	int ret = db_open();
	if(ret != 0)
		return ret;
	else
	{
		switch (collectinfo.flag)
		{
		case airtemper:
			strcpy(tablename, "airtemper");
			strcpy(valuename, "airtemper");
			break;

		case airhumid:
			strcpy(tablename, "airhumid");
			strcpy(valuename, "airhumid");
			break;

		case soiltemper:
			strcpy(tablename, "soiltemper");
			strcpy(valuename, "soiltemper");
			break;

		case soilhumid:
			strcpy(tablename, "soilhumid");
			strcpy(valuename, "soilhumid");
			break;

		case co2:
			strcpy(tablename, "co2");
			strcpy(valuename, "co2");
			break;
		}

		char datacmd[1024]={0};
		sprintf(datacmd,"insert into %s(time,id,variety,%s) "
				"values(\"%s\",%d,\"%s\",%d);"
				,tablename
				,valuename
				,collectinfo.time.toLatin1().data()
				,collectinfo.id
				,collectinfo.variety.c_str()
				,collectinfo.value);
		printflog("insert:%s\n",datacmd);
		return db_exec_cmd(datacmd);
	}
	return 0;
}

int Database::insertIntoCollectInfo(vector<ST_CollectInfo> &v_collectinfo)
{
	int ret = -1;
	int count = 0;
	for(unsigned i=0;i<v_collectinfo.size();i++)
	{
		ret = insertIntoCollectInfo(v_collectinfo[i]);
		if(ret != 0)
		{
	    	count++;
		}
		else
		{
			v_collectinfo.erase(v_collectinfo.begin()+count);
		}
	}
	return count;
}

int Database::insertIntoExpertInfo(ST_ExpertInfo &expertinfo)
{
	int ret = db_open();
	if(ret != 0)
		return ret;
	else
	{
		char datacmd[1024]={0};
		sprintf(datacmd,"insert into expertinfo(iExpertid,strExpertvariety,iExpertairtemper,iExpertairhumid,iExpertsoiltemper,iExpertsoilhumid,iExpertco2) "
				"values(%d, \"%s\", %d, %d, %d, %d, %d);"
				,expertinfo.iExpertid
				,expertinfo.strExpertvariety.c_str()
				,expertinfo.iExpertairtemper
				,expertinfo.iExpertairhumid
				,expertinfo.iExpertsoiltemper
				,expertinfo.iExpertsoilhumid
				,expertinfo.iExpertco2);
		printflog("insert:%s\n",datacmd);
		return db_exec_cmd(datacmd);
	}
	return 0;
}

int Database::insertIntoExpertInfo(vector<ST_ExpertInfo> &v_expertinfo)
{
	int ret = -1;
	int count = 0;
	for(unsigned i=0;i<v_expertinfo.size();i++)
	{
		ret = insertIntoExpertInfo(v_expertinfo[i]);
		if(ret != 0)
		{
	    	count++;
		}
		else
		{
			v_expertinfo.erase(v_expertinfo.begin()+count);
		}
	}
	return count;
}

int Database::updateExpertInfo(ST_ExpertInfo &expertinfo)
{
	int ret = db_open();
	if(ret != 0)
		return ret;
	else
	{
		char datacmd[1024]={0};
		sprintf(datacmd,"update expertinfo set strExpertvariety = \"%s\", iExpertairtemper = %d, iExpertairhumid = %d, iExpertsoiltemper = %d, iExpertsoilhumid = %d, iExpertco2 = %d  where iExpertid = %d;"
				,expertinfo.strExpertvariety.c_str()
				,expertinfo.iExpertairtemper
				,expertinfo.iExpertairhumid
				,expertinfo.iExpertsoiltemper
				,expertinfo.iExpertsoilhumid
				,expertinfo.iExpertco2
				,expertinfo.iExpertid);
		printflog("updateExpertInfo:%s\n",datacmd);
		return db_exec_cmd(datacmd);
	}
}

int Database::updateExpertInfo(vector<ST_ExpertInfo> &v_expertinfo)
{
	for(unsigned i=0;i<v_expertinfo.size();i++)
	{
		int ret = updateExpertInfo(v_expertinfo[i]);
		if(ret < 0)
			return ret;
	}
	return 0;
}

int Database::getCollectInfo(vector<ST_CollectInfo> &v_collectinfo, ValueFlag flag)
{
	v_collectinfo.clear();
	int ret = db_open();
	if(ret != 0)
		return ret;
	else
	{
		char **result=NULL;
		char *errormsg=NULL;
		int nrow=0;
		int ncolumn=0;
		int rst=0;
		char datacmd[1024]={0};
		char valuename[100] = {0};

		switch (flag)
		{
		case airtemper:
			strcpy(valuename, "airtemper");
			break;

		case airhumid:
			strcpy(valuename, "airhumid");
			break;

		case soiltemper:
			strcpy(valuename, "soiltemper");
			break;

		case soilhumid:
			strcpy(valuename, "soilhumid");
			break;

		case co2:
			strcpy(valuename, "co2");
			break;
		}

		sprintf(datacmd,"select * from %s;",valuename);
		rst=sqlite3_get_table(g_XCME_DB,datacmd,&result,&nrow,&ncolumn,&errormsg);
		db_close();
		printflog("nrow=%d,ncolumn=%d result = %d\n",nrow,ncolumn,result);

		if(rst==SQLITE_OK)
		{
			if(nrow<1)
			{
				sqlite3_free_table(result);
				return -1;
			}
			else
			{
				DbdataToCollectInfo(nrow,ncolumn,result,v_collectinfo,valuename);
				sqlite3_free_table(result);
				return 0;
			}
		}
		else
		{
			printf("\n---SQL:%s---\nerror:%s---\n",datacmd, errormsg);
			sqlite3_free(errormsg);
			sqlite3_free_table(result);
			return -2;
		}
	}
	return 0;
}

int Database::getCollectInfoByDate(vector<ST_CollectInfo> &v_collectinfo,char * strDateBegin,char *strDateEnd,ValueFlag flag)
{
	if(CheckDateStr(strDateBegin) < 0 || CheckDateStr(strDateEnd) < 0)
		return -1;
	v_collectinfo.clear();
	int ret = db_open();
	if(ret != 0)
		return ret;
	else
	{
		char **result=NULL;
		char *errormsg=NULL;
		int nrow=0;
		int ncolumn=0;
		int rst=0;
		char datacmd[1024]={0};
		char valuename[100] = {0};

		switch (flag)
		{
		case airtemper:
			strcpy(valuename, "airtemper");
			break;

		case airhumid:
			strcpy(valuename, "airhumid");
			break;

		case soiltemper:
			strcpy(valuename, "soiltemper");
			break;

		case soilhumid:
			strcpy(valuename, "soilhumid");
			break;

		case co2:
			strcpy(valuename, "co2");
			break;
		}

		sprintf(datacmd,"select * from %s where time >= \"%s\" and time <= \"%s\"",valuename,strDateBegin,strDateEnd);
		strcat(datacmd,"order by time desc;");

		rst=sqlite3_get_table(g_XCME_DB,datacmd,&result,&nrow,&ncolumn,&errormsg);
		db_close();
		printflog("nrow=%d,ncolumn=%d result = %d\n",nrow,ncolumn,result);

		if(rst==SQLITE_OK)
		{
			if(nrow<1)
			{
				sqlite3_free_table(result);
				return -1;
			}
			else
			{
				DbdataToCollectInfo(nrow,ncolumn,result,v_collectinfo,valuename);
				sqlite3_free_table(result);
				return 0;
			}
		}
		else
		{
			printf("\n---SQL:%s---\nerror:%s---\n",datacmd, errormsg);
			sqlite3_free(errormsg);
			sqlite3_free_table(result);
			return -2;
		}
	}
	return 0;
}

void Database::DbdataToCollectInfo(int nrow, int ncolumn,char** result,vector<ST_CollectInfo> &v_collectinfo,char* valuename)
{
	int j = ncolumn;
	for(int k=0;k<nrow;k++)
	{
		ST_CollectInfo tmp;
		for(int i=0;i<ncolumn;i++)
		{
				if(result[i]==NULL)
				{
					j++;
					continue;
				}

				if(strcmp("time",result[i])==0)
				{
					tmp.time = result[j];
				}
				else if(strcmp("variety",result[i])==0)
				{
					tmp.variety = result[j];
				}
				else if(strcmp("id",result[i])==0)
				{
					tmp.id = atoi(result[j]);
				}
				else if(strcmp(valuename,result[i])==0)
				{
					tmp.value = atoi(result[j]);
				}
				j++;
		}
		v_collectinfo.push_back(tmp);
	}
}

int Database::getExpertInfo(vector<ST_ExpertInfo> &v_expertinfo)
{
	v_expertinfo.clear();
	int ret = db_open();
	if(ret != 0)
		return ret;
	else
	{
		char **result=NULL;
		char *errormsg=NULL;
		int nrow=0;
		int ncolumn=0;
		int rst=0;
		char datacmd[1024]={0};

		sprintf(datacmd,"select * from expertinfo;");

		rst=sqlite3_get_table(g_XCME_DB,datacmd,&result,&nrow,&ncolumn,&errormsg);
		db_close();
		printflog("nrow=%d,ncolumn=%d result = %d\n",nrow,ncolumn,result);

		if(rst==SQLITE_OK)
		{
			if(nrow<1)
			{
				sqlite3_free_table(result);
				return -1;
			}
			else
			{
				DbdataToExpertInfo(nrow,ncolumn,result,v_expertinfo);
				sqlite3_free_table(result);
				return 0;
			}
		}
		else
		{
			printf("\n---SQL:%s---\nerror:%s---\n",datacmd, errormsg);
			sqlite3_free(errormsg);
			sqlite3_free_table(result);
			return -2;
		}
	}
	return 0;
}

int Database::getExpertInfoById(vector<ST_ExpertInfo> &v_expertinfo,int iExpertid)
{
	v_expertinfo.clear();
	int ret = db_open();
	if(ret != 0)
		return ret;
	else
	{
		char **result=NULL;
		char *errormsg=NULL;
		int nrow=0;
		int ncolumn=0;
		int rst=0;
		char datacmd[1024]={0};

		sprintf(datacmd,"select * from expertinfo where iExpertid = %d ;",iExpertid);

		rst=sqlite3_get_table(g_XCME_DB,datacmd,&result,&nrow,&ncolumn,&errormsg);
		db_close();
		printflog("nrow=%d,ncolumn=%d result = %d\n",nrow,ncolumn,result);

		if(rst==SQLITE_OK)
		{
			if(nrow<1)
			{
				sqlite3_free_table(result);
				return -1;
			}
			else
			{
				DbdataToExpertInfo(nrow,ncolumn,result,v_expertinfo);
				sqlite3_free_table(result);
				return 0;
			}
		}
		else
		{
			printf("\n---SQL:%s---\nerror:%s---\n",datacmd, errormsg);
			sqlite3_free(errormsg);
			sqlite3_free_table(result);
			return -2;
		}
	}
	return 0;
}

int Database::getExpertInfoByVariety(vector<ST_ExpertInfo> &v_expertinfo,char * strExpertvariety)
{
	v_expertinfo.clear();
	int ret = db_open();
	if(ret != 0)
		return ret;
	else
	{
		char **result=NULL;
		char *errormsg=NULL;
		int nrow=0;
		int ncolumn=0;
		int rst=0;
		char datacmd[1024]={0};

		sprintf(datacmd,"select * from expertinfo where strExpertvariety = \"%s\"",strExpertvariety);
		strcat(datacmd,"order by iExpertid desc;");

		rst=sqlite3_get_table(g_XCME_DB,datacmd,&result,&nrow,&ncolumn,&errormsg);
		db_close();
		printflog("nrow=%d,ncolumn=%d result = %d\n",nrow,ncolumn,result);

		if(rst==SQLITE_OK)
		{
			if(nrow<1)
			{
				sqlite3_free_table(result);
				return -1;
			}
			else
			{
				DbdataToExpertInfo(nrow,ncolumn,result,v_expertinfo);
				sqlite3_free_table(result);
				return 0;
			}
		}
		else
		{
			printf("\n---SQL:%s---\nerror:%s---\n",datacmd, errormsg);
			sqlite3_free(errormsg);
			sqlite3_free_table(result);
			return -2;
		}
	}
	return 0;
}

int Database:: getExpertInfoByInput(vector<ST_ExpertInfo> &v_expertinfo,char * strExpertvariety,int iExpertid)
{
	v_expertinfo.clear();
	int ret = db_open();
	if(ret != 0)
	{
		printf("open error\n");
		return ret;
	}
	else
	{
		char **result=NULL;
		char *errormsg=NULL;
		int nrow=0;
		int ncolumn=0;
		int rst=0;
		char datacmd[1024]={0};

		printf("databases  id = %d\n", iExpertid);

		sprintf(datacmd,"select * from expertinfo where strExpertvariety = \"%s\" and iExpertid = %d;",strExpertvariety,iExpertid);
//		strcat(datacmd,"order by iExpertid desc;");
		rst=sqlite3_get_table(g_XCME_DB,datacmd,&result,&nrow,&ncolumn,&errormsg);
		db_close();

		printf("rst = %d\n",rst);
		printflog("nrow=%d,ncolumn=%d result = %d\n",nrow,ncolumn,result);
		printf("nrow=%d,ncolumn=%d \n",nrow,ncolumn);
		if(rst==SQLITE_OK)
		{
			if(nrow<1)
			{
				sqlite3_free_table(result);
				return -1;
			}
			else
			{
				printf("start change\n");
				DbdataToExpertInfo(nrow,ncolumn,result,v_expertinfo);
				sqlite3_free_table(result);
				return 0;
			}
		}
		else
		{
			printf("\n---SQL:%s---\nerror:%s---\n",datacmd, errormsg);
			sqlite3_free(errormsg);
			sqlite3_free_table(result);
			return -2;
		}
	}
	return 0;
}

void Database::DbdataToExpertInfo(int nrow, int ncolumn,char** result,vector<ST_ExpertInfo> &v_expertinfo)
{
	int j = ncolumn;

	for(int k=0;k<nrow;k++)
	{
		ST_ExpertInfo tmp;
		for(int i=0;i<ncolumn;i++)
		{
				if(result[i]==NULL)
				{
					j++;
					continue;
				}

				if(strcmp("iExpertid",result[i])==0)
				{
					tmp.iExpertid = atoi(result[j]);
				}
				else if(strcmp("strExpertvariety",result[i])==0)
				{
					tmp.strExpertvariety = result[j];
				}
				else if(strcmp("iExpertairtemper",result[i])==0)
				{
					tmp.iExpertairtemper =  atoi(result[j]);
				}
				else if(strcmp("iExpertairhumid",result[i])==0)
				{
					tmp.iExpertairhumid =  atoi(result[j]);
				}
				else if(strcmp("iExpertsoiltemper",result[i])==0)
				{
					tmp.iExpertsoiltemper =  atoi(result[j]);
				}
				else if(strcmp("iExpertsoilhumid",result[i])==0)
				{
					tmp.iExpertsoilhumid =  atoi(result[j]);
				}
				else if(strcmp("iExpertco2",result[i])==0)
				{
					tmp.iExpertco2 =  atoi(result[j]);
				}
				j++;
		}
		v_expertinfo.push_back(tmp);
	}
}

int Database::deleteCollectInfo(char *strtime,ValueFlag flag)
{
	char tablename[100] = {0};

		switch (flag)
		{
		case airtemper:
			strcpy(tablename, "airtemper");
			break;

		case airhumid:
			strcpy(tablename, "airhumid");
			break;

		case soiltemper:
			strcpy(tablename, "soiltemper");
			break;

		case soilhumid:
			strcpy(tablename, "soilhumid");
			break;

		case co2:
			strcpy(tablename, "co2");
			break;
		}
	int ret = db_open();
	if(ret != 0)
		return ret;
	char datacmd[1024]={0};
	sprintf(datacmd,"delete from %s where time < \"%s\";",tablename,strtime);
	printflog("delete %s:%s\n",tablename,datacmd);
	return db_exec_cmd(datacmd);
}

int Database::deleteCollectInfo(int id,ValueFlag flag)
{
	char tablename[100] = {0};

	switch (flag)
	{
	case airtemper:
		strcpy(tablename, "airtemper");
		break;

	case airhumid:
		strcpy(tablename, "airhumid");
		break;

	case soiltemper:
		strcpy(tablename, "soiltemper");
		break;

	case soilhumid:
		strcpy(tablename, "soilhumid");
		break;

	case co2:
		strcpy(tablename, "co2");
		break;
	}
	int ret = db_open();
	if(ret != 0)
		return ret;
	char datacmd[1024]={0};
	sprintf(datacmd,"delete from %s where id = %d;",tablename,id);
	printflog("delete %s:%s\n",tablename,datacmd);
	return db_exec_cmd(datacmd);
}

int Database::deleteExpertInfo(int iExpertid)
{
	int ret = db_open();
	if(ret != 0)
		return ret;
	char datacmd[1024]={0};
	sprintf(datacmd,"delete from expertinfo where iExpertid = %d;",iExpertid);
	printflog("deleteExpertInfo:%s\n",datacmd);
	return db_exec_cmd(datacmd);
}

int Database::deleteExpertInfo(char *strExpertvariety)
{
	int ret = db_open();
	if(ret != 0)
		return ret;
	char datacmd[1024]={0};
	sprintf(datacmd,"delete from expertinfo where strExpertvariety = \"%s\";",strExpertvariety);
	printflog("deleteExpertInfo:%s\n",datacmd);
	return db_exec_cmd(datacmd);
}


int Database::CheckTimeStr(char *time)
{
	char *tmp = time;
	if(tmp == 0)
		return -1;
	int len = strlen(tmp);
	if(len < 5)
		return -2;
	int icount = 0;
	int ipos = 0;
	int icp = 0;
	char strhour[10] = {0};
	char strmin[10] = {0};
	char strsec[10] = {0};
	do
	{
		ipos++;
		if(*tmp == ':')
		{
			switch(icount)
			{
			case 0:
			{
				if(strlen(strhour) > 2)
					return -3;
				else if(atoi(strhour) < 0 || atoi(strhour) > 23)
					return -4;
				break;
			}
			case 1:
			{
				if(strlen(strmin) > 2)
					return -5;
				else if(atoi(strmin) < 0 || atoi(strmin) > 60)
					return -6;
				break;
			}
			case 2:
			{
				if(strlen(strsec) > 2)
					return -7;
				else if(atoi(strsec) < 0 || atoi(strsec) > 60)
					return -8;
				break;
			}
			}
			icp = 0;
			icount++;
			continue;
		}
		else
		{
			if(icp > 4)
				return -9;
			switch(icount)
			{
			case 0:
			{
				strhour[icp++] = *tmp;
				break;
			}
			case 1:
			{
				strmin[icp++] = *tmp;
				break;
			}
			case 2:
			{
				strsec[icp++] = *tmp;
				break;
			}
			default:
				return -10;
			}
		}
	}while(ipos<len && tmp++);
	return 0;
}

int Database::DateTime2Date(char *datetime , char *date)
{
	printflog("datetime:%s\n",datetime);
	char *tmp = datetime;
	if(tmp == 0)
		return -1;
	int len = strlen(tmp);
	if(len < 13)
		return -2;
	if(date == 0)
		return -3;
	int ipos = 0;
	int icp = 0;

	do
	{
		ipos++;
		if(*tmp == ' ')
		{
			break;
		}
		else
		{
			date[icp++] = *tmp;
		}
	}while(ipos<len && tmp++);

	printflog("date:%s\n",date);
	int ret = CheckDateStr(date);
	if(ret < 0)
		return -4;

	return 0;
}

int Database::CheckDateTimeStr(char *datetime)
{
	char *tmp = datetime;
	if(tmp == 0)
		return -1;
	int len = strlen(tmp);
	if(len < 13)
		return -2;
	int icount = 0;
	int ipos = 0;
	int icp = 0;

	char Date[20] = {0};
	char Time[20] = {0};
	do
	{
		ipos++;
		if(*tmp == ' ')
		{
			icp = 0;
			icount++;
			continue;
		}
		else
		{
			if(icp > 10)
				return -3;
			switch(icount)
			{
			case 0:
			{
				Date[icp++] = *tmp;
				break;
			}
			case 1:
			{
				Time[icp++] = *tmp;
				break;
			}
			default:
				return -6;
			}
		}
	}while(ipos<len && tmp++);

	int ret = CheckDateStr(Date);
	if(ret < 0)
		return -4;

	ret = CheckDateStr(Time);
	if(ret < 0)
		return -5;

	return 0;
}

//检查日期字符串是否符合规则
int Database::CheckDateStr(char *date)
{
	char *tmp = date;
	if(tmp == 0)
		return -1;
	int len = strlen(tmp);
	if(len < 8)
		return -2;
	int icount = 0;
	int ipos = 0;
	int icp = 0;
	char stryear[10] = {0};
	char strmonth[10] = {0};
	char strday[10] = {0};
	do
	{
		ipos++;
		if(*tmp == '-')
		{
			switch(icount)
			{
			case 0:
			{
				if(strlen(stryear) > 4)
					return -3;
				else if(atoi(stryear) < 1970)
					return -4;
				break;
			}
			case 1:
			{
				if(strlen(strmonth) > 2)
					return -5;
				else if(atoi(strmonth) < 0 || atoi(strmonth) > 12)
					return -6;
				break;
			}
			case 2:
			{
				if(strlen(strday) > 2)
					return -7;
				else if(atoi(strday) < 0 || atoi(strday) > 31)
					return -8;
				break;
			}
			}
			icp = 0;
			icount++;
			continue;
		}
		else
		{
			if(icp > 4)
				return -9;
			switch(icount)
			{
			case 0:
			{
				stryear[icp++] = *tmp;
				break;
			}
			case 1:
			{
				strmonth[icp++] = *tmp;
				break;
			}
			case 2:
			{
				strday[icp++] = *tmp;
				break;
			}
			default:
				return -10;
			}
		}
	}while(ipos<len && tmp++);

	printflog("year:%s month:%s day:%s\n",stryear,strmonth,strday);
	return 0;
}

