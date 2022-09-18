/**
  ******************************************************************************
  * @file    FlashParam.h
  * @brief   This file contains all the function prototypes for
  *          the FlashParam.c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _FLASH_PARAM_H_
#define _FLASH_PARAM_H_

/*Includes */
#include "main.h"

/*Public defines */
#define USER_FLASH_START 0x0800FC00
//#define FL_KEY1 0x45670123
//#define FL_KEY2 0xCDEF89AB
#define USER_FLASH_PAGE 
/*Global params*/
typedef struct {
	uint32_t hours;
	uint32_t minutes;
	uint32_t seconds;
}flash_params_t;

#define FIRST_ELEMENT hours
/*Prototypes */
flash_params_t* FP_GetParam(void);
uint8_t FP_SaveParam(void);
uint8_t FP_DeleteParam(void);
uint8_t FP_SaveOneParam(uint32_t data, uint32_t adr);
#endif /* __FLASH_PARAM_H__ */

