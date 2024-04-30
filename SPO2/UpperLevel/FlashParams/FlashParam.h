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
#include "Logger/Logger.h"
#include "main.h"
#include "System/System.h"

/*Public defines */
#define USER_FLASH_START 0x080FF800
#define START_FP_FLAG 0x12345678
#define END_FP_FLAG 0x87654321

//#define FL_KEY1 0x45670123
//#define FL_KEY2 0xCDEF89AB
#define USER_FLASH_PAGE 
/*Global params*/
typedef struct {
	bool set;
	uint32_t* buf;
	uint32_t size;
	uint32_t adress;
	void (*cb)(void);
} flash_message_t;


typedef struct {
	uint32_t startLoadFlag;
	uint32_t timeStamp;
	sys_const_t sysParConsts;
	
	uint32_t endLoadFlag;
} stored_params_t;

typedef struct {
	bool isCorrect;
	stored_params_t params;
}flash_params_t;

extern flash_params_t* fp;
	
#define FIRST_ELEMENT startLoadFlag
/*Prototypes */
bool FP_Init(void);
uint8_t FP_GetParam(void);
uint8_t FP_SaveParam(void);
uint8_t FP_DeleteParam(void);
uint8_t FP_ClearLog(void);
HAL_StatusTypeDef FP_StoreLog(uint8_t handler, uint32_t startAddress, uint32_t size, log_data_t *buf, void (*cb)(void));
HAL_StatusTypeDef FP_GetStoredLog(uint32_t startAddress, uint32_t size, log_data_t *buf, void (*cb)(void));
void FP_StartStore(void);
//uint8_t FP_SaveOneParam(uint32_t data, uint32_t adr);
#endif /* __FLASH_PARAM_H__ */

