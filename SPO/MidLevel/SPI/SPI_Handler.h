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
	void* buf;
	int dataSize;
	int msgSize;
} spi_msg_t;

typedef struct spi_perif_node_t{
	SPI_TypeDef *SPIx;
	fifo_t* msgBuf;
} spi_handler_t;

/*Global params*/

/*Prototypes */
void initHandler(spi_handler_t *handler);
void sendMsg (spi_handler_t *handler, spi_msg_t *msg);
void receiveMsg (spi_handler_t *handler, spi_msg_t *msg);

/*DO NOT USE */
void handler (spi_handler_t *handler);
/*************/
#endif /* __SPI_Handler_H__ */

