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


/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
	
/* Private function prototypes -----------------------------------------------*/
void	interruptSend (spi_handler_t *handler);
void dmaSend(spi_handler_t *handler);

/* Private user code ---------------------------------------------------------*/

void initHandler(spi_handler_t *handler){
	
}
void sendMsg (spi_handler_t *handler, spi_msg_t *msg);
void receiveMsg (spi_handler_t *handler, spi_msg_t *msg);