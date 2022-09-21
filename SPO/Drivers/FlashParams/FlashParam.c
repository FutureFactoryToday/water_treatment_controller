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
#include "FlashParam.h"
#include "stdlib.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
volatile static flash_params_t flashParams ={0};
flash_params_t* fp = &flashParams;
/* Private function prototypes -----------------------------------------------*/
void loadParams(void);
void unlockFlash(void);
void lockFlash(void);

/* Private user code ---------------------------------------------------------*/

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
	flashParams.params.loadFlag = 0;
	for(uint32_t parNum = 0; parNum < paramSize; parNum++){
		temp = (uint32_t*)(USER_FLASH_START + 4*parNum);
		*ptr = *temp;
		ptr++;
		
	}
	if (flashParams.params.loadFlag == 0x1234ABCD) {
		flashParams.isLoaded = true;
	} else {
		flashParams.params.loadFlag = 0x1234ABCD;
		flashParams.needToSave = 1;
		flashParams.isLoaded = false;
	}
	__enable_irq();
	
}

uint8_t FP_SaveParam(void){
	if(!FP_DeleteParam()){
		return ERROR;
	}
	__disable_irq();
	while (FLASH->SR & FLASH_SR_BSY);
	unlockFlash();
	if (FLASH->SR & FLASH_SR_EOP){
		FLASH->SR |= FLASH_SR_EOP;
	}
		FLASH->CR |= FLASH_CR_PG;
	uint16_t *ptr = (uint16_t*)&flashParams.params;
	uint32_t paramSize = sizeof(stored_params_t)/sizeof(uint32_t);
	for(uint8_t i = 0; i < paramSize*2; i++){
		*(volatile uint16_t*)(USER_FLASH_START+2*i) = 	*ptr;
		ptr++;
		while(!(FLASH->SR & FLASH_SR_EOP)){
			if(FLASH->SR & FLASH_SR_PGERR){
				lockFlash();
				FLASH->CR &= ~FLASH_CR_PG;
				FLASH->SR = FLASH_SR_PGERR;
				return ERROR;
			}
		}
		FLASH->SR = FLASH_SR_EOP;
	}
	FLASH->CR &= ~FLASH_CR_PG;
	lockFlash();
	flashParams.needToSave = false;
	__enable_irq();
	return 1;
}
uint8_t FP_DeleteParam(void){
	__disable_irq();
	while (FLASH->SR & FLASH_SR_BSY);
	unlockFlash();
	if (FLASH->SR & FLASH_SR_EOP){
		FLASH->SR |= FLASH_SR_EOP;
	}
	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = USER_FLASH_START;
	FLASH->CR |= FLASH_CR_STRT;
	while (!(FLASH->SR & FLASH_SR_EOP));
	FLASH->SR = FLASH_SR_EOP;
	
	FLASH->CR &= ~FLASH_CR_PER;
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
	while ((FLASH->SR & FLASH_SR_BSY) != 0)
	{
		
	}
	if ((FLASH->CR & FLASH_CR_LOCK) != 0)
	{
		FLASH->KEYR = FLASH_KEY1;
		FLASH->KEYR = FLASH_KEY2;
	}
	
}

void lockFlash(void){
	FLASH->CR = FLASH_CR_LOCK;
}


