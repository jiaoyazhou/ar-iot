/*
 * sysstat.c
 *
 *  Created on: 2014-8-27
 *      Author: searchmybaby
 */
#include "sysstat.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int if_a_string_is_a_valid_ipv4_address(const char *str)
{
    struct in_addr addr;
    int ret;
    volatile int local_errno;

    errno = 0;
    ret = inet_pton(AF_INET, str, &addr);
    local_errno = errno;
//    if (ret > 0)
//        fprintf(stderr, "\"%s\" is a valid IPv4 address\n", str);
//    else if (ret < 0)
//        fprintf(stderr, "EAFNOSUPPORT: %s\n", strerror(local_errno));
//    else
//        fprintf(stderr, "\"%s\" is not a valid IPv4 address\n", str);

    return ret;
}

int GetWlan0Stat(char *ssid,char *HWaddr,char *ip,char *Bcast,char *Mask)
{
    if(GetPrivateProfileInt("SysSetting","bWifiEquiped",0,LOCALINIFILE) != 1)
    {
    	return -1;
    }

    if(GetPrivateProfileInt("NetSetting","iNetMode",0,LOCALINIFILE) != 1 )
    {
    	return 0;
    }

    memset(ssid,0,sizeof(ssid));
    memset(HWaddr,0,sizeof(HWaddr));
    memset(ip,0,sizeof(ip));
    memset(Bcast,0,sizeof(Bcast));
    memset(Mask,0,sizeof(Mask));

	char buffer[BUFSIZ];
	FILE *read_fp;
	int chars_read;
	int ret = 0;

	//获取硬件地址
	read_fp = popen("ifconfig wlan0|grep \"HWaddr\"|awk '{print $5}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			if(HWaddr != 0)
			{
				sprintf(HWaddr,"%s",buffer);
			}
		}
		else
		{
			ret = 0;
		}
		pclose(read_fp);
	}
	else
	{
		ret = -2;
	}
	if(ret < 0)
		return ret;

	//获取是否链接
	read_fp = popen("ifconfig wlan0| grep RUNNING", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			ret = 1;
		}
		else
		{
			ret = 0;
		}
		pclose(read_fp);
	}
	else
	{
		ret = -1;
	}
	if(ret <= 0)
		return ret;


	//获取IP地址
	read_fp = popen("ifconfig wlan0|grep \"inet addr:\"|cut -d: -f2|awk '{print $1}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			if(ip != 0)
			{
				sprintf(ip,"%s",buffer);
			}
		}
		pclose(read_fp);
	}
	else
	{
		ret = -3;
	}
	if(ret < 0)
		return ret;


	//获取网关
	read_fp = popen(" ifconfig wlan0|grep \"inet addr:\"|cut -d: -f3|awk '{print $1}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			if(Bcast != 0)
			{
				sprintf(Bcast,"%s",buffer);
			}
		}
		pclose(read_fp);
	}
	else
	{
		ret = -4;
	}
	if(ret < 0)
		return ret;

	//获取子网掩码
	read_fp = popen(" ifconfig wlan0|grep \"inet addr:\"|cut -d: -f4|awk '{print $1}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			if(Mask != 0)
			{
				sprintf(Mask,"%s",buffer);
			}
		}
		pclose(read_fp);
	}
	else
	{
		ret = -5;
	}
	if(ret < 0)
		return ret;

	read_fp = popen("iwconfig wlan0|grep \"ESSID\" |awk '{print $4}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			if(ssid!=0)
				strncpy(ssid,buffer+7,strlen(buffer)-9);
		}
		else
		{
			ret = 0;
		}
		pclose(read_fp);
	}
	else
	{
		ret = -6;
	}
	if(ret <= 0)
		return ret;

	read_fp = popen("iwconfig wlan0|grep \"Signal level=\" |awk '{print $4}'", "r");
	if (read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			char signal[10] = {0};
			strncpy(signal,buffer+6,strlen(buffer)-7);
			double dsignal = atof(signal);
			//printf("signal:%s\ndsignal:%0.2f\n",signal,dsignal);
			if(dsignal <= 20)
			{
				ret = 0;
			}
			else if(dsignal > 20 && dsignal <= 40)
			{
				ret = 1;
			}
			else if(dsignal > 40 && dsignal <= 60)
			{
				ret = 2;
			}
			else if(dsignal > 60 && dsignal <= 80)
			{
				ret = 3;
			}
			else if(dsignal > 80)
			{
				ret = 4;
			}
		}
		else
		{
			ret = 0;
		}
		pclose(read_fp);
	}
	else
	{
		ret = -6;
	}
	if(ret <= 0)
		return ret;

	return ret;
}

int GetGPRSStat(char *HWaddr,char *ip,char *Bcast,char *Mask)
{
    if(GetPrivateProfileInt("SysSetting","bGprsEquiped",0,LOCALINIFILE) != 1)
    {
    	return -1;
    }

    if(GetPrivateProfileInt("NetSetting","iNetMode",0,LOCALINIFILE) != 3 )
    {
    	return 0;
    }

    memset(HWaddr,0,sizeof(HWaddr));
    memset(ip,0,sizeof(ip));
    memset(Bcast,0,sizeof(Bcast));
    memset(Mask,0,sizeof(Mask));

    if(HWaddr != 0)
    {
    	memset(HWaddr,0,sizeof(HWaddr));
    }

	char buffer[BUFSIZ];
	FILE *read_fp;
	int chars_read;
	int ret = 0;

	//获取是否链接
	read_fp = popen("ifconfig ppp0 | grep RUNNING", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, sizeof(buffer) );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			ret = 1;
		}
		else
		{
			ret = 0;
		}
		pclose(read_fp);
	}
	else
	{
		ret = -1;
	}
	if(ret <= 0)
		return ret;

	//获取IP地址
	read_fp = popen(" ifconfig ppp0|grep \"inet addr:\"|cut -d: -f2|awk '{print $1}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			if(ip != 0)
			{
				sprintf(ip,"%s",buffer);
			}
		}
		else
		{
			ret = 0;
		}
		pclose(read_fp);
	}
	else
	{
		ret = -3;
	}
	if(ret < 0)
		return ret;


	//获取网关
	read_fp = popen(" ifconfig ppp0|grep \"inet addr:\"|cut -d: -f3|awk '{print $1}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			if(Bcast != 0)
			{
				sprintf(Bcast,"%s",buffer);
			}
		}
		else
		{
			ret = 0;
		}
		pclose(read_fp);
	}
	else
	{
		ret = -4;
	}
	if(ret < 0)
		return ret;

	//获取子网掩码
	read_fp = popen(" ifconfig ppp0|grep \"inet addr:\"|cut -d: -f4|awk '{print $1}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			if(Mask != 0)
			{
				sprintf(Mask,"%s",buffer);
			}
		}
		else
		{
			ret = 0;
		}
		pclose(read_fp);
	}
	else
	{
		ret = -5;
	}
	if(ret < 0)
		return ret;

	return ret;
}

int GetEth0Stat(char *HWaddr,char *ip,char *Bcast,char *Mask)
{
    if(GetPrivateProfileInt("SysSetting","bEthEquiped",0,LOCALINIFILE) != 1)
    {
    	return -1;
    }

    if(GetPrivateProfileInt("NetSetting","iNetMode",0,LOCALINIFILE) != 2 )
    {
    	return 0;
    }

    memset(HWaddr,0,sizeof(HWaddr));
    memset(ip,0,sizeof(ip));
    memset(Bcast,0,sizeof(Bcast));
    memset(Mask,0,sizeof(Mask));

	char buffer[BUFSIZ];
	FILE *read_fp;
	int chars_read;
	int ret = 0;

	//获取硬件地址
	read_fp = popen("ifconfig eth0|grep \"HWaddr\"|awk '{print $5}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			if(HWaddr != 0)
			{
				sprintf(HWaddr,"%s",buffer);
			}
		}
		else
		{
			ret = 0;
		}
		pclose(read_fp);
	}
	else
	{
		ret = -3;
	}
	if(ret < 0)
		return ret;

	//获取有线是否链接
	read_fp = popen("ifconfig eth0 | grep RUNNING", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			ret = 1;
		}
		else
		{
			ret = 0;
		}
		pclose(read_fp);
	}
	else
	{
		ret = -4;
	}
	if(ret <= 0)
		return ret;

	//获取IP地址
	read_fp = popen(" ifconfig eth0|grep \"inet addr:\"|cut -d: -f2|awk '{print $1}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			if(ip != 0)
			{
				sprintf(ip,"%s",buffer);
			}
		}
		else
		{
			ret = 0;
		}
		pclose(read_fp);
	}
	else
	{
		ret = -5;
	}
	if(ret < 0)
		return ret;


	//获取网关
	read_fp = popen(" ifconfig eth0|grep \"inet addr:\"|cut -d: -f3|awk '{print $1}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			if(Bcast != 0)
			{
				sprintf(Bcast,"%s",buffer);
			}
		}
		else
		{
			ret = 0;
		}
		pclose(read_fp);
	}
	else
	{
		ret = -6;
	}
	if(ret < 0)
		return ret;

	//获取子网掩码
	read_fp = popen(" ifconfig eth0|grep \"inet addr:\"|cut -d: -f4|awk '{print $1}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			if(Mask != 0)
			{
				sprintf(Mask,"%s",buffer);
			}
		}
		else
		{
			ret = 0;
		}
		pclose(read_fp);
	}
	else
	{
		ret = -7;
	}
	if(ret < 0)
		return ret;


	return ret;
}

double RAMFree(int *iMemTotal,int *iMemFree)
{
	char buffer[BUFSIZ];
	FILE *read_fp;
	int chars_read;
	int ret = 0;

	read_fp = popen("free |grep \"Mem:\"|awk '{print $2}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			*iMemTotal = atoi(buffer);
		}
		pclose(read_fp);
	}

	read_fp = popen("free |grep \"Mem:\"|awk '{print $4}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			*iMemFree = atoi(buffer);
		}
		pclose(read_fp);
	}
	if(iMemTotal == 0)
		return 0.00;
	else
		return (double)*iMemFree/(double)*iMemTotal*100;
}

double ROMFree(int *iMemTotal,int *iMemFree)
{
	char buffer[BUFSIZ];
	FILE *read_fp;
	int chars_read;
	int ret = 0;
#ifndef A8BOARD
	read_fp = popen("df |grep \"/dev/mmcblk0p1\"|awk '{print $2}'", "r");
#else
	read_fp = popen("df |grep \"/dev/root\"|awk '{print $2}'", "r");
#endif
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			*iMemTotal = atoi(buffer);
		}
		pclose(read_fp);
	}

#ifndef A8BOARD
	read_fp = popen("df |grep \"/dev/mmcblk0p1\"|awk '{print $4}'", "r");
#else
	read_fp = popen("df |grep \"/dev/root\"|awk '{print $4}'", "r");
#endif
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			*iMemFree = atoi(buffer);
		}
		pclose(read_fp);
	}
	if(iMemTotal == 0)
		return 0.00;
	else
		return (double)*iMemFree/(double)*iMemTotal*100;
}

double CPUInfo(char *strProcessor,char *strHardware)
{
	char buffer[BUFSIZ];
	FILE *read_fp;
	int chars_read;
	int ret = 0;

	read_fp = popen("cat /proc/cpuinfo | grep \"Processor\" | awk '{print $3}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			strncpy(strProcessor,buffer,chars_read);
		}
		pclose(read_fp);
	}

	read_fp = popen("cat /proc/cpuinfo | grep \"Hardware\" | awk '{print $3}'", "r");
	if ( read_fp != 0 )
	{
		memset( buffer, 0, BUFSIZ );
		chars_read = fread(buffer, sizeof(char), BUFSIZ-1, read_fp);
		if (chars_read > 0)
		{
			strncpy(strHardware,buffer,chars_read);
		}
		pclose(read_fp);
	}
	return 0.00;
}


