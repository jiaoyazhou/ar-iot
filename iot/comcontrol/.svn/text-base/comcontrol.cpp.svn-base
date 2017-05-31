/*
 * comcontrol.cpp
 *
 *  Created on: 2014-11-27
 *      Author: searchmybaby
 */

#include "comcontrol.h"
extern"C" {
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
}

comcontrol::comcontrol(char *strCom,int speed,bool bWaitRead,int databits, int stopbits, int parity)
	:m_strCom(0),
	 m_comfd(0),
	 m_speed(speed),
	 m_bWaitRead(bWaitRead),
	 m_databits(databits),
	 m_stopbits(stopbits),
	 m_parity(parity)
{
	// TODO Auto-generated constructor stub
	int iLen = strlen(strCom);
	while(m_strCom == 0 && iLen)
	{
		m_strCom = (char*)malloc(sizeof(char)*(iLen+1));
	};

	if(m_strCom != 0)
	{
		memset(m_strCom,0,iLen+1);
		memcpy(m_strCom,strCom,iLen);
	}
}

comcontrol::~comcontrol()
{
	// TODO Auto-generated destructor stub
	if(m_strCom != 0)
	{
		delete m_strCom;
		m_strCom = 0;
	}
}

int comcontrol::SetParam(char *strCom,int speed,bool bWaitRead,int databits, int stopbits, int parity)
{
	if(m_strCom != 0)
	{
		delete m_strCom;
		m_strCom = 0;
	}

	int iLen = sizeof(strCom);

	while(m_strCom == 0 && iLen)
	{
		m_strCom = (char*)malloc(sizeof(char)*iLen);
	};

	if(m_strCom != 0)
	{
		memcpy(m_strCom,strCom,iLen);
	}


	m_speed = speed;
	m_bWaitRead = bWaitRead;
	m_databits = databits;
	m_stopbits = stopbits;
	m_parity = parity;

	Com_Close();
	Com_Init();

	return 0;
}

int comcontrol::Com_Init()
{
	if(m_strCom == 0)
		return -1;
	else
	{
		m_comfd = open(m_strCom, O_RDWR | O_NOCTTY);
		if (m_comfd <= 0)
		{
			char strError[256] = {0};
			sprintf(strError,"Print Com_Init open %s fail:%d",m_strCom,m_comfd);
			perror(strError);
			return -2;
		}
		else
		{
			int status = -1;
			switch(m_speed)
			{
			case 2400:
			case 4800:
			case 9600:
			case 19200:
			case 38400:
			case 57600:
			case 115200:
				status = lcom_setbaut(m_speed);
				break;
			default:
			{
				printf("Print Com speed(%d) error\n",m_speed);
				return -3;
			}
			}

			if(status != 1)
			{
				printf("Print Com Set speed(%d) error\n",m_speed);
				return -4;
			}

		    if(lcom_setpara(m_databits, m_stopbits,m_parity) != 1 )
			{
		    	printf("Print Com Set Param(%d,%d,%d) error\n",m_databits, m_stopbits,m_parity);
		    	return -5;
			}
		    m_bRun = true;
		    m_bRead = true;
		    this->start();
			return m_comfd;
		}
	}
}

int comcontrol::Com_Close()
{
	m_bRun = false;
	while(this->isRunning())
	{
		this->terminate();
	}
	return close(m_comfd);
}

int comcontrol::Com_Clear()
{
	if(m_comfd <= 0)
		return -1;
	else
		return tcflush(m_comfd, TCIOFLUSH);
}

int comcontrol::GetComFd()
{
	return m_comfd;
}

int comcontrol::ComSend(char *data, int datalen)
{
	if(m_comfd <= 0)
		return -1;


	if(m_bWaitRead){
		int iTime = 0;
		while(!m_bRead){
			usleep(10000);
			if(iTime++ > 1000){
				m_bRead = true;
				printf("打印回复超时！:%d\n",m_bRead);
				return -2;
			}
		}
	}

	m_mutex.lock();
	m_bRead = false;
	int len = 0;
	len = write(m_comfd, data, datalen);//实际写入的长度
	m_mutex.unlock();
	if(len == datalen)
    {
		return len;
    }
	else
    {
		printf("TCOFLUSH刷新写入的数据但不传送\n");
		tcflush(m_comfd, TCOFLUSH);//TCOFLUSH刷新写入的数据但不传送
		return -2;
    }
}

int comcontrol::ComRecv(char *data, int datalen)
{
	if(m_comfd <= 0)
		return -1;

    int len=0,ret = 0;

    len = read(m_comfd, data, datalen);
    //tcflush(m_comfd, TCIFLUSH);
    return len;
}

void comcontrol::run()
{
    int ret = 0;
    fd_set fs_read;
    struct timeval tv_timeout;
	do
	{
		usleep(10000);
		if(m_comfd == 0)
		{
			continue;
		}
		else
		{
		    FD_ZERO(&fs_read);
		    FD_SET(m_comfd, &fs_read);
		    tv_timeout.tv_sec  = (10*20/115200);
		    tv_timeout.tv_usec = 0;

		    ret = select(m_comfd+1, &fs_read, NULL, NULL, &tv_timeout);
		    //printf("ret = %d\n", ret);
		    //如果返回0，代表在描述符状态改变前已超过timeout时间,错误返回-1

		    if (FD_ISSET(m_comfd, &fs_read))
		    {
		    	m_mutex.lock();
		    	//printf("Com Read Begin\n");
		       emit OnComRead();
		    	//printf("====Com Read End=====\n");
		       m_bRead = true;
		       m_mutex.unlock();
		    }
		    else
		    {
		        continue;
		    }
		}
	}while(m_bRun);
}

int comcontrol::lcom_setbaut(int speed)
{
	int	i, status;
	struct termios Opt;

	int speed_arr[] = {B115200, B57600,B38400, B19200, B9600, B4800, B2400, B1200, B300,};
	int name_arr[] = {115200, 57600,38400,  19200,  9600,  4800,  2400,  1200,  300,};

	tcgetattr(m_comfd, &Opt);
	for ( i=0;  i<sizeof(speed_arr)/sizeof(int); i++)
	{
		if(speed == name_arr[i])
		{
			tcflush(m_comfd, TCIOFLUSH);
			cfsetispeed(&Opt, speed_arr[i]);
			cfsetospeed(&Opt, speed_arr[i]);
			status = tcsetattr(m_comfd, TCSANOW, &Opt);
			if(status != 0)
			{
				perror("tcsetattr fd1");
				return 0;
			}
			tcflush(m_comfd, TCIOFLUSH);
			break;
		}
	}
	return 1;
}

int comcontrol::lcom_setpara(int databits, int stopbits, int parity)
{
	struct termios options;

	//第一步：获得串口指向termios结构的指针
	if(tcgetattr(m_comfd, &options) != 0)
	{
		perror("SetupSerial 1");
		return(0);
	}

	//先屏蔽其他标志
	options.c_cflag &= ~CSIZE;

	//设置数据位
	switch (databits)
	{
		case 5: options.c_cflag |= CS5; break;
		case 6: options.c_cflag |= CS6; break;
		case 7: options.c_cflag |= CS7; break;
		case 8: options.c_cflag |= CS8; break;
		default: return (0);
	}

	//设置校验位
	switch (parity)
	{
		case 'n': case 'N':
			options.c_cflag &= ~PARENB;
			options.c_iflag &= ~INPCK;
			break;

		case 'o': case 'O':
			options.c_cflag |= PARENB;
			options.c_cflag |= PARODD;
			options.c_iflag |= (INPCK | ISTRIP);
			break;

		case 'e': case 'E':
			options.c_iflag |= (INPCK | ISTRIP);
			options.c_cflag |= PARENB;
			options.c_cflag &= ~PARODD;
			break;

		case 'S': case 's':
			options.c_cflag &= ~PARENB;
			options.c_cflag &= ~CSTOPB;
			break;

		default: printf("parity err"); return (0);
	}

	//设置停止位
	switch (stopbits)
	{
		case 1:	options.c_cflag &= ~CSTOPB; break;
		case 2: options.c_cflag |= CSTOPB;  break;
		default: printf("stopbits err"); return (0);
	}

	if (parity != 'n' && parity != 'N')
	{
		options.c_iflag |= INPCK;
	}

	options.c_lflag &= ~( ICANON | ECHO | ECHOE | ISIG );
	options.c_iflag &= ~( IXON | IXOFF | IXANY  );
	options.c_oflag &= ~( INLCR|IGNCR|ICRNL );
	options.c_oflag &= ~( ONLCR|OCRNL );
	options.c_iflag &= ~( ICRNL | IXON );

	//设置超时
	tcflush(m_comfd, TCIFLUSH);
	options.c_cc[VTIME] = 0;
	options.c_cc[VMIN] = 0;

	//将修改后的termios数据设置到串口中
	if (tcsetattr(m_comfd, TCSANOW, &options) != 0)
	{
		perror("SetupSerial 3");
		return (0);
	}
	return (1);
}


