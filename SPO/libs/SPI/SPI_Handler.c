/**
  ******************************************************************************
  * @file           : SPI_Handler.c
  * @brief          : 
  ******************************************************************************
  * @attention
  *
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

typedef struct spi_perif_node_t{
	SPI_TypeDef *SPIx;
	fifo_t* msgBuf;
	struct spi_perif_node_t* next;
} spi_perif_node_t;
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
	
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
