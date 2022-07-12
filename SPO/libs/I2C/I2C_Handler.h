#ifndef _I2C_HANDLER_H_
#define _I2C_HANDLER_H_

	#include "main.h"
	
	#define DEFAULT_QUEUE_SIZE 1
	#define BORDER_DATA_SIZE 0
	

	
	typedef struct {
		unsigned INITED:1;
		unsigned WAITING:1;
		unsigned SEND_IN_PROCESS:1;
		unsigned RCV_IN_PROCESS:1;
		unsigned TRANS_TYPE:2;

		unsigned ERROR:1;
} i2cHandlerStatusBits_t;
	
	union i2cHandlerStatusSRK {
		i2cHandlerStatusBits_t bits;
		uint16_t all;
	};
	
	//Состояние handler	
	#define NOT_INITED 0x00
	#define DMA 0x01
	#define INTERRUPT 0x02
	
  typedef struct {
		unsigned newData:1;
		unsigned inProcess:1;
		unsigned error:2;
	} i2c_buf_status_bits_t;
	
	//Типы ошибок примо-передачи
	#define NO_SLAVE 0x01
	#define NORM 0x00
	#define NACK 0x02
	
	typedef union {
		i2c_buf_status_bits_t bits;
		uint8_t all;
	} i2c_buf_status_t;
	
	typedef struct {
		uint8_t* buf;
		uint16_t bufSize;
		uint16_t dataSize;
		uint8_t adr;
		i2c_buf_status_t status;
		void (*callBack)(void);
	} i2c_buf_t;
	
		

	
	void I2C_Handler(void);
	void I2C_Send(i2c_buf_t* buf);
	void I2C_Read(i2c_buf_t* buf);
	//i2c_buf_t* I2C_RegisterBuf(uint8_t size);
	uint8_t I2C_Manual_Send(uint8_t adr, uint8_t* data, uint8_t bufSize);
	uint8_t I2C_Manual_Read (uint8_t adr, uint8_t* destination, uint8_t msgSize);
	uint8_t I2C_Find_Slave (uint8_t adr);
	
#endif
