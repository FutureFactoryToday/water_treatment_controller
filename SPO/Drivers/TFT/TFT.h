/**
  ******************************************************************************
  * @file    TFT.h
  * @brief   This file contains all the function prototypes for
  *          the TFT.c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TFT_H_
#define _TFT_H_

/*Includes */
#include "main.h"
#include "SPI/SPI_Handler.h"
#include "TFT/TFT_LL.h"
/*Public defines */

/*Структура пикселя*/
typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} pixel_t;

/*Global params*/
extern uint32_t TFT_ID;

/*Prototypes */
uint8_t initTFT(void);
uint8_t readID(readResult_t *result);
uint8_t placePic(uint32_t coordX, uint32_t coordY, uint32_t hight, uint32_t width, uint8_t* pic); 
uint8_t drawPixel(uint32_t coordX, uint32_t coordY, pixel_t* pix);
uint8_t drawLine (uint32_t coordX1, uint32_t coordY1, uint32_t coordX2, uint32_t coordY2, pixel_t pix);
#endif /* __TFT_H__ */

