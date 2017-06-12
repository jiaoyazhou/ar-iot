/*
 * getdata.h
 *
 *  Created on: 2017年6月6日
 *      Author: root
 */

#ifndef COMCONTROL_GETDATA_H_
#define COMCONTROL_GETDATA_H_

#include <qthread.h>
#include <QDateTime>
#include "comcontrol.h"
#include "protocol.h"
#include "stdio.h"
#include "userdef.h"
#include "string.h"
#include "global.h"

struct ST_IDInfo{
	int 	id;
	int 	serialnum;
	string  variety;
	int	    flag;
};

class getdata: public QThread {
public:
	getdata();
	virtual ~getdata();

	void OnComRead();
	void Close();
	void DataInit();

protected:
    virtual void run();

private:
    uint8_t m_buf[1024];
    protocol_list_t *list;

	comcontrol *m_comcontrol;
};

#endif /* COMCONTROL_GETDATA_H_ */
