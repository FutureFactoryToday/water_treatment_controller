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
/*Global params*/

/*Prototypes */


#endif /* __SPI_Handler_H__ */

