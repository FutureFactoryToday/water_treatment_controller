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

/*Public defines */

/* Настройки */
//Порт для параллельного дисплея
	#define TFT_PATAL_PORT GPIOB

//Каналы SPI для дисплея и контроллера сенсорного дисплея
	#define TFT_SPI SPI2
	#define TOUCH_SPI SPI1
//Разрешение применения DMA
	#define ALLOW_TFT_DMA
	
//Настройки DMA
#ifdef ALLOW_TFT_DMA
//Минимальный объем данных для отправки и приема через DMA
	#define DMA_MIN_SIZE 3
	#define TFT_DMA DMA1
	#define TOUCH_DMA DMA2
#endif

#define ALLOW_TOUCH_DMA
#ifdef ALLOW_TOUCH_DMA
//Минимальный объем данных для отправки и приема через DMA
	#define DMA_MIN_SIZE 3
	#define TFT_DMA DMA1
	#define TOUCH_DMA DMA2
#endif

/* Настройки дисплея */
#define RESET_DELAY_MS 10
/*
Структура состояния дисплея:
1. Статус иниацилизации;
2. Тип интерфейса дисплея:
	0 - дисплей не найден;
	1 - SPI;
	2 - параллельный;
	
*/
typedef struct {
	unsigned inited:1;
	unsigned type:2;
	unsigned busy:1;
} tftDriverStatus_t;

enum{
	NO_DISP = 0,
	SPI,
	PARAL
};

/*Тип данных для отправки*/
enum {
	DATA = 1,
	COMMAND
};

/*Структура внутреннего состояния дисплея*/
//typedef struct {
//	unsigned reserved:5;
//	unsigned 
//} tftStatus_t;


/*Структура пикселя*/
typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} pixel_t;

/*Global params*/
extern tftDriverStatus_t tftStatus;

/*Prototypes */
tftDriverStatus_t initTFT (void);
uint32_t sendData (uint16_t *dataBuf, uint16_t dataSize);
uint16_t* receiveData (uint16_t *dataBuf, uint16_t dataSize);
#endif /* __TFT_H__ */

