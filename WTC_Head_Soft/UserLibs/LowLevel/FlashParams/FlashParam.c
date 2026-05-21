/**
  ******************************************************************************
  * @file           : FlashParam.c
  * @brief          : 
  ******************************************************************************
  * @attention
  *
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "FlashParams\FlashParam.h"
#include "FlashIC/FlashDriver.h"
#include "stdlib.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
volatile static flash_params_t flashParams = {0};
flash_params_t* fp = &flashParams;
/* Private function prototypes -----------------------------------------------*/
void loadParams(void);
void unlockFlash(void);
void lockFlash(void);

/* Private user code ---------------------------------------------------------*/
flash_params_t* FL_GetStoredParams(void){
	
	
	return 0;
}


/*
flash_params_t* FP_GetParam(void){
	if (!flashParams.isLoaded){
		loadParams();
	}
	return &flashParams;
}

void loadParams(void){
	__disable_irq();
	
	uint32_t *temp = 0;
	uint32_t *ptr = &flashParams.params.FIRST_ELEMENT;
	uint32_t paramSize = sizeof(flash_params_t)/sizeof(uint32_t);
	flashParams.params.startLoadFlag = 0;
	flashParams.params.endLoadFlag = 0;
	for(uint32_t parNum = 0; parNum < paramSize; parNum++){
		temp = (uint32_t*)(USER_FLASH_START + 4*parNum);
		*ptr = *temp;
		ptr++;
		
	}
	if (flashParams.params.startLoadFlag == START_FP_FLAG && flashParams.params.endLoadFlag == END_FP_FLAG) {
		flashParams.isLoaded = true;
	} else {
		flashParams.params.startLoadFlag = START_FP_FLAG;
		flashParams.params.endLoadFlag = END_FP_FLAG;
		flashParams.needToSave = 1;
		flashParams.isLoaded = false;
	}
	__enable_irq();
	
}

uint8_t FP_SaveParam(void){
	if (flashParams.needToSave == 1){
		if(!FP_DeleteParam()){
			return ERROR;
		}
		__disable_irq();
		while (FLASH->SR2 & FLASH_SR2_BSY);
		if (FLASH->CR2 & FLASH_CR2_LOCK){
			unlockFlash();
		}
		if (FLASH->SR2 & FLASH_SR2_EOP){
			FLASH->SR2 |= FLASH_SR2_EOP;
		}
		FLASH->AR2 = USER_FLASH_START;
		FLASH->CR2 |= FLASH_CR2_PG;
		uint16_t *ptr = (uint16_t*)&flashParams.params;
		uint32_t paramSize = sizeof(stored_params_t)/sizeof(uint32_t);
		for(uint16_t i = 0; i < paramSize*2; i++){
			//uint32_t adr = USER_FLASH_START+2*i;
			*(volatile uint16_t*)(USER_FLASH_START+2*i) = 	*ptr;
			ptr++;
			//while(FLASH->SR & FLASH_SR_BSY){
			while(!(FLASH->SR2 & FLASH_SR2_EOP)){
				uint32_t fl = FLASH->SR2;
				if(FLASH->SR2 & FLASH_SR2_PGERR){
					lockFlash();
					FLASH->CR2 &= ~FLASH_CR2_PG;
					FLASH->SR2 = FLASH_SR2_PGERR;
					return ERROR;
				}
			}
			FLASH->SR2 |= FLASH_SR2_EOP;
			if (i == paramSize*2 - 2){
				flashParams.needToSave = 1;
			}
		}
		FLASH->CR2 &= ~FLASH_CR2_PG;
		lockFlash();
		flashParams.needToSave = false;
		__enable_irq();
		return 1;
	}
	return 0;
}
uint8_t FP_DeleteParam(void){
	__disable_irq();
	while (FLASH->SR2 & FLASH_SR2_BSY);
	unlockFlash();
	if (FLASH->SR2 & FLASH_SR2_EOP){
		FLASH->SR2 |= FLASH_SR2_EOP;
	}
	FLASH->CR2 |= FLASH_CR2_PER;
	FLASH->AR2 = USER_FLASH_START;
	FLASH->CR2 |= FLASH_CR2_STRT;
	while (!(FLASH->SR2 & FLASH_SR2_EOP));
	FLASH->SR2 = FLASH_SR2_EOP;
	while (FLASH->SR2 & FLASH_SR2_BSY);
	FLASH->CR2 &= ~FLASH_CR2_PER;
	lockFlash();
	__enable_irq();
	return 1;
}
//uint8_t flashParams_SaveOneParam(uint32_t data, uint32_t adr){
//	__disable_irq();
//	while (FLASH->SR & FLASH_SR_BSY);
//	unlockFlash();
//	if (FLASH->SR & FLASH_SR_EOP){
//		FLASH->SR |= FLASH_SR_EOP;
//	}
//		FLASH->CR |= FLASH_CR_PG;
//	uint16_t *ptr = (uint16_t*)&data;
//	for(uint8_t i = 0; i < 2; i++){
//		*(volatile uint16_t*)(adr+2*i) = 	*ptr;
//		ptr++;
//		while(!(FLASH->SR & FLASH_SR_EOP)){
//			if(FLASH->SR & FLASH_SR_PGERR){
//				lockFlash();
//				FLASH->CR &= ~FLASH_CR_PG;
//				FLASH->SR = FLASH_SR_PGERR;
//				return ERROR;
//			}
//		}
//		FLASH->SR = FLASH_SR_EOP;
//	}
//	FLASH->CR &= ~FLASH_CR_PG;
//	lockFlash();
//	__enable_irq();
//	return 1;
//}

void unlockFlash(void){
	while ((FLASH->SR2 & FLASH_SR2_BSY) != 0)
	{
		
	}
	if ((FLASH->CR2 & FLASH_CR2_LOCK) != 0)
	{
		FLASH->KEYR2 = FLASH_KEY1;
		FLASH->KEYR2 = FLASH_KEY2;
	}
	
}

void lockFlash(void){
	FLASH->CR2 = FLASH_CR2_LOCK;
}
*/

