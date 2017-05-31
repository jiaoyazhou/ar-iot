/*
 * comcontrol.h
 *
 *  Created on: 2014-11-27
 *      Author: searchmybaby
 */

#ifndef COMCONTROL_H_
#define COMCONTROL_H_
#include "qthread.h"
#include "qmutex.h"

class comcontrol : public QThread
{
	Q_OBJECT
public:
	comcontrol(char *strCom,int speed = 115200,bool bWaitRead = false,int databits = 8, int stopbits = 1, int parity = 'N');
	~comcontrol();

	int SetParam(char *strCom,int speed = 115200,bool bWaitRead = false,int databits = 8, int stopbits = 1, int parity = 'N');

	/*
	 * 初始化串口 开始读取串口信息
	 * 成功:返回串口文件标记
	 * 失败:-1:串口名称为空
	 * 		-2:打开串口失败
	 * 		-3:波特率错误
	 * 		-4:设置波特率失败
	 * 		-5:设置串口参数失败
	 */
	int Com_Init();

	int Com_Close();

	int Com_Clear();

	int GetComFd();

	/*
	 * 串口发送数据
	 * data:发送数据内容
	 * datalen:发送数据长度
	 * 返回:-1:串口还未初始化
	 * 		-2:写入长度错误
	 * 		其他:写入长度
	 */
	int ComSend(char *data, int datalen);

	/*
	 * 串口读取数据
	 * data:读取数据内容
	 * datalen:读取数据长度
	 * timeout:读取超时
	 * 返回:-1:串口还未初始化
	 * 		-2:未有数据待读取
	 * 		其他:读取长度
	 */
	int ComRecv(char *data, int datalen);

Q_SIGNALS:
	void OnComRead();

protected:
    virtual void run();

protected:
	int lcom_setbaut(int speed);
	int lcom_setpara(int databits, int stopbits, int parity);

private:
	char *m_strCom;
	volatile int m_comfd;
	int m_speed,m_databits,m_stopbits,m_parity;

	QMutex m_mutex;
	bool m_bRead;
	bool m_bRun;
	bool m_bWaitRead;
};

#endif /* COMCONTROL_H_ */
