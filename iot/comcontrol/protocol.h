/*
 * protocol.h
 *
 *  Created on: May 4, 2017
 *      Author: ken
 */

#ifndef SRC_PROTOCOL_H_
#define SRC_PROTOCOL_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_RECEIVE_BUF_LEN 36

typedef struct
{
	uint8_t *ring_buf;
	uint16_t head; //用于指定可读位置
	uint16_t tail; //write point
	uint16_t max_len;
	uint16_t count;
}__attribute__((packed)) protocol_list_t;

typedef struct
{
	uint8_t to_serial[4];
	uint8_t from_serial[4];
	uint8_t sn;
	uint8_t command;
	uint8_t flag;

}__attribute__((packed)) protocol_stable_t;

typedef struct
{
	protocol_stable_t stable;
	uint32_t value;
	uint8_t bcc;
}__attribute__((packed)) protocol_reporter_status;



typedef enum
{
	CMD_REPORTER = 0x01,

}command_t;

typedef enum
{
	FLAG_TEMPERATURE = 0x01,
	FLAG_HUMIDITY = 0x02,
	FLAG_CO2 = 0x03,
}flag_t;


//--------   API---------------------
//-----------------------------------
//------------------------------------

/**
 *
 */
void protocol_list_init(protocol_list_t *_list, uint8_t *_buf, int _buf_len);

/**
 *
 */
uint8_t calc_bcc(uint8_t *_buf, int _len);

/**
 *
 */
int put_data_to_list(protocol_list_t *_list, const uint8_t *_data, int _len);

/**
 *
 */
int get_one_package(protocol_list_t *_list, uint8_t *_package, int _len);

/**
 *
 */
int parase_protocol(protocol_list_t *_list, int (*do_cmd)(uint8_t *_protocol, int _len));

int protocol_send(uint8_t *_protocol, int _len);

uint32_t uint32_to_big(uint32_t value);
uint16_t uint16_to_big(uint16_t value);
uint32_t big_to_uint32(uint32_t *value);
uint16_t big_to_uint16(uint16_t *value);


//----------------------------------------------------------------------
#define SLIP_END             0xC0    /* indicates end of packet */
#define SLIP_ESC             0xDB    /* indicates byte stuffing */
#define SLIP_ESC_END         0XDC    /* ESC ESC_END means END data byte */
#define SLIP_ESC_ESC         0XDD    /* ESC ESC_ESC means ESC data byte */

#ifdef __cplusplus
}
#endif

#endif /* SRC_PROTOCOL_H_ */


