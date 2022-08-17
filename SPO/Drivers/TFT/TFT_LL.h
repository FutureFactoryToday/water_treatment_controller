/**
  ******************************************************************************
  * @file    TFT_LL.h
  * @brief   This file contains all the function prototypes for
  *          the TFT.c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TFT_LL_H_
#define _TFT_LL_H_

/*Includes */
#include "main.h"
#include "SPI/SPI_Handler.h"
#include "spi.h"
#include "gpio.h"
/*Public defines */
#define TFT_LL_FIFO_SIZE 15
/* ��������� */
//���� ��� ������������� �������
	#define TFT_PARAL_PORT GPIOB

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
	#define TFT_TX_CHANNEL LL_DMA_CHANNEL_5
	#define TFT_RX_CHANNEL LL_DMA_CHANNEL_4
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
	unsigned INITED:1;
	unsigned TYPE:2;
	unsigned BUSY:1;
	unsigned ERROR:1;
} tftDriverStatus_t;

enum{
	NO_DISP = 0,
	SPI,
	PARAL
};

/*��� ������ ��� ��������*/
typedef enum {
	DATA = 1,
	COMMAND
}dataType_t;

/*����������� ������*/
typedef enum {
	SEND = 1,
	RCV
}dirType_t;

/*��� ��������*/
typedef enum {
	DMA = 1,
	INT
}perifType_t;

typedef enum {
	ERR,
	IN_PROC,
	FINISH
} resultType_t;

typedef struct {
	resultType_t result;
	uint8_t* dataBuf; 
} readResult_t;



/*Global params*/
extern tftDriverStatus_t tftStatus;

/*Prototypes */
tftDriverStatus_t initTFT_LL (perifType_t type);
void deInitTFT_LL(void);

uint8_t processMsg(readResult_t *result, uint8_t bufSize, dataType_t type, uint8_t dir, uint8_t hold);
handlerStatus_t tftSpiHandler(void);
void rebootTFT (void);
void getTFT_Status(void);
uint32_t manIDRead(void);
void rebootTFT(void);

#endif /* __TFT_LL_H__ */

