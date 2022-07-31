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

/* ��������� */
//���� ��� ������������� �������
	#define TFT_PATAL_PORT GPIOB

//������ SPI ��� ������� � ����������� ���������� �������
	#define TFT_SPI SPI2
	#define TOUCH_SPI SPI1
//���������� ���������� DMA
	#define ALLOW_TFT_DMA
	
//��������� DMA
#ifdef ALLOW_TFT_DMA
//����������� ����� ������ ��� �������� � ������ ����� DMA
	#define DMA_MIN_SIZE 3
	#define TFT_DMA DMA1
	#define TOUCH_DMA DMA2
#endif

#define ALLOW_TOUCH_DMA
#ifdef ALLOW_TOUCH_DMA
//����������� ����� ������ ��� �������� � ������ ����� DMA
	#define DMA_MIN_SIZE 3
	#define TFT_DMA DMA1
	#define TOUCH_DMA DMA2
#endif

/* ��������� ������� */
#define RESET_DELAY_MS 10
/*
��������� ��������� �������:
1. ������ �������������;
2. ��� ���������� �������:
	0 - ������� �� ������;
	1 - SPI;
	2 - ������������;
	
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

/*��� ������ ��� ��������*/
enum {
	DATA = 1,
	COMMAND
};

/*��������� ����������� ��������� �������*/
//typedef struct {
//	unsigned reserved:5;
//	unsigned 
//} tftStatus_t;


/*��������� �������*/
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

