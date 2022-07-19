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
#define RESET_DELAY_MS 1
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
} tftStatus;
/*Global params*/

/*Prototypes */
tftStatus initTFT (void);
uint32_t sendData (uint16_t *dataBuf, uint32_t dataSize);
uint16_t* receiveData (uint16_t *dataBuf, uint32_t dataSize);
#endif /* __TFT_H__ */

