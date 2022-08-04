/**
  ******************************************************************************
  * @file    SPI_Handler.h
  * @brief   This file contains all the function prototypes for
  *          the SPI_Handler.c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SPI_Handler_H_
#define _SPI_Handler_H_

/*Includes */
#include "main.h"
#include "FIFO.h"
/*Public defines */

typedef struct {
	uint8_t* data;
	uint32_t dataSize;
	uint32_t cnt;
} spi_data_t;

typedef struct {
	unsigned BUSY:1;
	unsigned DMA:1;
	unsigned INT:1;
	unsigned SEND:1;
	unsigned RCV:1;
} spi_handler_status_bits_t;

typedef union {
	spi_handler_status_bits_t bits;
	uint8_t all;
} spi_handler_status_t;

typedef enum {
	ERR = 0,
	OK = 1,
	RETRY, 
	NO_DATA,
	COMPLETE
} result_t;

typedef enum {
	SEND,
	RCV
} dir_t;

typedef struct {
	spi_data_t* data;
	dir_t dir;
} spi_msg_t;

typedef struct {
	SPI_TypeDef *SPI;
	spi_handler_status_t status;
	fifo_t* msgFifo;
	spi_msg_t* curMsg;
	void* next;
	void (*interruptSend) (uint8_t data);
	void (*dmaSend) (uint8_t *data, uint32_t dataSize);
	uint8_t (*interruptReceive) (void);
	uint8_t (*dmaReceive) (uint8_t *inputBuffer, uint32_t dataSize);
	void (*startTransmision) (void);
	void (*finishTransmision) (void);
} spi_handler_t;

/*Global params*/

/*Prototypes */
result_t registerHandler(spi_handler_t handler);
result_t sendMsg (SPI_TypeDef *SPI, spi_data_t *data);
result_t receiveMsg (SPI_TypeDef *SPI, spi_data_t *data);

/*DO NOT USE */
result_t handler (SPI_TypeDef *SPI);

/*Tests*/
void testSPIHandler (void);
/*************/
#endif /* __SPI_Handler_H__ */

