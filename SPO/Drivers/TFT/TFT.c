/**
  ******************************************************************************
  * @file           : TFT.c
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
#include "Settings.h"
/* Private typedef -----------------------------------------------------------*/
#ifndef TFT_SPI 
#error "SPI for TFT Display not specified"
#endif
#ifndef TOUCH_SPI 
#error "SPI for Touch controller not specified"
#endif
#ifdef ALLOW_TFT_DMA
	#ifndef TFT_DMA 
	#error "DMA for TFT Display not specified"
	#endif
#endif
#ifdef ALLOW_TOUCH_DMA
	#ifndef TOUCH_DMA 
	#error "DMA for Touch controller not specified"
	#endif
#endif
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
uint32_t spiManualSend (uint32_t size, uint32_t *data);
uint32_t dmaSend (uint32_t size, uint32_t *data);
uint32_t itSend (uint32_t size, uint32_t *data);
uint16_t* manualReceive (uint32_t size, uint16_t *data);
uint16_t* dmaReceive (uint32_t size, uint16_t *data);
uint16_t* itReceive (uint32_t size, uint16_t *data);
/* Private user code ---------------------------------------------------------*/

uint32_t spiManualSend (uint32_t size, uint32_t *data){
	
	return 0;
}

uint32_t dmaSend (uint32_t size, uint32_t *data){
	
	return 0;
}
uint32_t itSend (uint32_t size, uint32_t *data){
	
	return 0;
}
uint16_t* manualReceive (uint32_t size, uint16_t *data){
	
	
	return NULL;
}
uint16_t* dmaReceive (uint32_t size, uint16_t *data){
	
	return NULL;
}
uint16_t* itReceive (uint32_t size, uint16_t *data){
	
	return NULL;
}