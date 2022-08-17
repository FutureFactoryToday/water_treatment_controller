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
#define SPI_H_FIFO_SIZE 2
typedef struct {
	unsigned cnt: 8;
	unsigned ERR: 1;
	unsigned FREE: 1;
	unsigned DMA: 1;
	unsigned INT: 1;
} handlerStatus_t;

typedef struct {
	unsigned BUSY: 1;
} spi_handler_status_t;

typedef struct {
	SPI_TypeDef *SPI;
	fifo_t* handlerFifo;
	handlerStatus_t (*curHandler)(void);
	void* next;
	spi_handler_status_t status;
	handlerStatus_t lastResult;
} spi_handler_t;

/*Global params*/

/*Prototypes */

uint8_t registerHandler(SPI_TypeDef *SPI, handlerStatus_t (*handlerFunc)(void));

/*DO NOT USE */
uint8_t spiInterruptHandler (SPI_TypeDef *SPI);

/*Tests*/
void testSPIHandler (void);
/*************/
#endif /* __SPI_Handler_H__ */

