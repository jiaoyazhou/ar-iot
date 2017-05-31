/*
 * sysstat.h
 *
 *  Created on: 2014-8-27
 *      Author: searchmybaby
 */

#ifndef NETSTAT_H_
#define NETSTAT_H_

#include <stdlib.h>
#include <stdio.h>
#include "inifile.h"
#include "get_cpu.h"

#define A8BOARD

/*******************************************************
* Function Name:if_a_string_is_a_valid_ipv4_address
* Purpose：判断字符串是否为有效的IPV4地址
* Params :
*   const char *str:输入的字符串
* Return：
* Limitation:大于0为有效IP地址
*******************************************************/
int if_a_string_is_a_valid_ipv4_address(const char *str);

/*******************************************************
* Function Name:GetWlan0Stat
* Purpose：获取无线网卡信息
* Params :
*   char ssid*：无线网络名
*   char *HWaddr：返回MAC地址
*   char *ip:返回IP
*   char *Bcast：返回网关
*   char *Mask：返回子网掩码
* Return：
* Limitation:返回1：网卡已连接；
* 			 返回0：网卡未连接；
* 			 返回-1:网卡未启动；
* 			 返回-2：获取有线网卡MAC地址错误；
* 			 返回-3：获取IP地址错误;
* 			 返回-4：获取网关错误；
* 			 返回-5：获取子网掩码错误；
* 			 返回-6：获取SSID错误；
*******************************************************/
int GetWlan0Stat(char *ssid,char *HWaddr,char *ip,char *Bcast,char *Mask);

/*******************************************************
* Function Name:GetGPRSStat
* Purpose：获取GPRS信息
* Params :
*		char *HWaddr：返回MAC地址
*		char *ip:返回IP
*		char *Bcast：返回网关
*		char *Mask：返回子网掩码
* Return：
* Limitation: 返回1：网卡已连接；
* 				返回0：网卡未连接；
* 				返回-1:网卡未启动；
* 				返回-2：获取有线网卡MAC地址错误；
* 				返回-3：获取IP地址错误;
* 				返回-4：获取网关错误；
* 				返回-5：获取子网掩码错误；
*******************************************************/
int GetGPRSStat(char *HWaddr,char *ip,char *Bcast,char *Mask);

/*******************************************************
* Function Name:GetEth0Stat
* Purpose：获取有线网卡信息
* Params :
*   char *HWaddr：返回MAC地址
*   char *ip:返回IP
*   char *Bcast：返回网关
*   char *Mask：返回子网掩码
* Return：
* Limitation: 返回1：网卡已连接；
* 			 	返回0：网卡未连接；
* 			 	返回-1:网卡未启动；
* 			  	返回-2：获取网卡MAC地址错误；
* 			  	返回-3：获取IP地址错误;
* 			  	返回-4：获取网关错误；
* 			  	返回-5：获取子网掩码错误；
*******************************************************/
int GetEth0Stat(char *HWaddr,char *ip,char *Bcast,char *Mask);

/*******************************************************
* Function Name:freemem
* Purpose：获取系统程序运行剩余内存
* Params :
* 		int *strMemTotal:总RAM的值
* 		int *strFree:空闲RAM的值
* Return：double
* Limitation:剩余百分比
*******************************************************/
double RAMFree(int *iMemTotal,int *iMemFree);

/*******************************************************
* Function Name:freemem
* Purpose：获取系统存储剩余内存
* Params :
* 		int *strMemTotal:总ROM的值
* 		int *strFree:空闲ROM的值
* Return：double
* Limitation:剩余百分比
*******************************************************/
double ROMFree(int *iMemTotal,int *iMemFree);

/*******************************************************
* Function Name:CPUInfo
* Purpose：获取CPU信息
* Params :
* 		char *strProcessor:CPU的指令集
* 		char *strHardware:CPU硬件平台
* Return：double
* Limitation:剩余百分比
*******************************************************/
double CPUInfo(char *strProcessor,char *strHardware);

#endif /* NETSTAT_H_ */
