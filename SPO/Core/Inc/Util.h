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
#include "Time/Time.h"
/*Public defines */

/*Global params*/
extern uint8_t numBuf[11];
/*Prototypes */

/*Возведение в степень*/
uint16_t POWC(uint32_t a,uint8_t b);
/*Возврат строкового аналога числа (от 0 до 9)*/
uint8_t intToChar(uint8_t num);

uint8_t* intToStr (uint32_t num);

uint32_t mod(int32_t a);

#endif /* __UTIL_H__ */

