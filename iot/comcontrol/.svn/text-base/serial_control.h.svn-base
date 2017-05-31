/*
 * serial_control.h
 *
 *  Created on: May 3, 2017
 *      Author: ken
 */

#ifndef SRC_SERIAL_CONTROL_H_
#define SRC_SERIAL_CONTROL_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
	B_0 = 0, B_50, B_75,	B_110,	B_134,	B_150,	B_200,	B_300,	B_600,	B_1200,
	B_1800,	B_2400,	B_4800,	B_9600,	B_19200, B_38400, B_57600, B_115200, B_230400
}SPEED;

/**
 * @brief use demo *serial_init("/dev/ttyS0", B_115200, 8, 1, 'N', 'N')
 * @_dev the serial device point
 * @_speed serial speed
 * @_size
 */
int serial_init(const char *_dev, SPEED _speed, int _size, int _stop,
		int _parity, int _cflow);

/**
 * @brief read data from serial
 * @return the number of data which get from serial
 */
int serial_read(uint8_t *_msg, int _len);

/**
 * @brief
 */
int serial_write(const uint8_t *_msg, int _len);

void serial_close(void);

#ifdef __cplusplus
}
#endif

#endif /* SRC_SERIAL_CONTROL_H_ */
