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

#define FLASH_QUEUE_SIZE 20

//#define FL_KEY1 0x45670123
//#define FL_KEY2 0xCDEF89AB
#define USER_FLASH_PAGE 
/*Global params*/
typedef enum {
	ERROR_LOG = 1,
	WASH_LOG,
	WATER_QUANT,
	WATER_USAGE
}msg_type_t;

typedef enum {
	READ_FRAM = 1,
	WRITE_FRAM,
	READ_RAM,
	WRITE_RAM,
	CLEAR_LOG,
	CLEAR_PARAMS,
	CLEAR_SECTOR
} flash_message_type_t;

typedef struct {
	flash_message_type_t type;
	uint32_t* buf;
	uint32_t size;
	uint32_t adress;
	void (*cb)(void);
	bool isTransmited;
} flash_message_t;

typedef struct {
	flash_message_t msgs[FLASH_QUEUE_SIZE];
	uint8_t head;
	uint8_t tail;
	bool empty;
	bool full;
	bool isTransmiting;
} flash_queue_t;

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
HAL_StatusTypeDef FP_StoreLog(msg_type_t type, uint32_t entryNum, log_data_t *buf, void (*cb)(void));
HAL_StatusTypeDef FP_GetStoredLog(msg_type_t type, uint32_t readNum, uint32_t offset, log_data_t *buf, void (*cb)(void));
void FP_StartStore(void);
bool FP_isEmpty();
uint8_t FP_Manual_FRAM_Write(uint8_t* data, uint32_t adr, uint32_t size, void (*cb)(void));
uint8_t FP_Manual_FRAM_Read(uint8_t* data, uint32_t adr, uint32_t size, void (*cb)(void));
uint8_t FP_Manual_RAM_Write(uint8_t* data, uint32_t adr, uint32_t size, void (*cb)(void));
uint8_t FP_Manual_RAM_Read(uint8_t* data, uint32_t adr, uint32_t size, void (*cb)(void));	
//uint8_t FP_SaveOneParam(uint32_t data, uint32_t adr);
#endif /* __FLASH_PARAM_H__ */

