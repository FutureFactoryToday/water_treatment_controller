/**
  ******************************************************************************
  * @file    Util.h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _UTIL_H_
#define _UTIL_H_

/*Includes */
#include "main.h"

/*Public defines */

/*Global params*/
extern uint8_t numBuf[11];
/*Prototypes */

/*���������� � �������*/
uint16_t POWC(uint8_t a,uint8_t b);
/*������� ���������� ������� ����� (�� 0 �� 9)*/
uint8_t intToChar(uint8_t num);

uint8_t* intToStr (uint32_t num);
#endif /* __UTIL_H__ */
