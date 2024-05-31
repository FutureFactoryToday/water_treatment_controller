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
#include "FlashIC/FlashDriver.h"
#include "FlashIC/FM25.h"
#include "FlashIC/W25.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define FLASH_SECTORS 3

#define UNLOCKED 0
#define AUTO_LOCK 1
#define MANUAL_LOCK 2
#define MANUAL_UNLOCK 1
#define AUTO_UNLOCK 2
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint8_t lock;
static uint8_t currentHandler;
volatile static flash_params_t flashParams = {0};
flash_params_t* fp = &flashParams;
uint32_t sysVers;
uint32_t irqStatus;
uint16_t baseAddress[FLASH_SECTORS];
flash_driver_t *fram = &FM25_driver;
flash_driver_t *logger = &W25_driver;
flash_params_t bufFlash[FLASH_SECTORS];
flash_params_t recBufFlash[FLASH_SECTORS];
flash_message_t queue[4]; 
bool oldIRQStatus;
int8_t lastBuffer;
void (*cbFunc)(void);

/* Private function prototypes -----------------------------------------------*/
void loadParams(void);
void unlockSPI(void);
void lockSPI(void);
void manualUnlockSPI(void);
void manualLockSPI(void);
void queueHandler(void);
void saveFRAMParam(void);
void saveRAMParam(uint8_t handler);
void getRAMParam(uint8_t handler);
/* Private user code ---------------------------------------------------------*/

bool FP_Init(void){
	lock = UNLOCKED;
	sysVers = SYSTEM_PO_VERSION;
	gpio_t framCS = {FRAM_CS_GPIO_Port,FRAM_CS_Pin};
	gpio_t framWP	=	{FRAM_WP_GPIO_Port, FRAM_WP_Pin};
	gpio_t framHOLD	=	{FRAM_HOLD_GPIO_Port, FRAM_HOLD_Pin};
	gpio_t logCS = {MEM_CS_GPIO_Port,MEM_CS_Pin};
	gpio_t logWP = {MEM_WP_GPIO_Port,MEM_WP_Pin};
	gpio_t logHOLD = {MEM_RES_GPIO_Port,MEM_RES_Pin};
		
	if (fram->init(MEM_SPI,framCS, framWP, framHOLD,unlockSPI) == HAL_OK){
		sysParams.vars.status.flags.FRAMInited = 1;
	} else {
		sysParams.vars.error.flags.FRAMFail = 1;
	}
	if (logger->init(MEM_SPI,logCS, logWP, logHOLD,unlockSPI) == HAL_OK){
		sysParams.vars.status.flags.RAMInited = 1;
	} else {
		sysParams.vars.error.flags.RAMFail = 1;
	}
	for (uint8_t i = 0; i < FLASH_SECTORS; i++){
		baseAddress[i] = i*sizeof(stored_params_t) + i;
	}
	for (uint8_t i =0; i < 3; i++){
		queue[i] = (flash_message_t){0,0,0};
	}

}
HAL_StatusTypeDef FP_StoreLog(uint8_t handler, uint32_t startAddress, uint32_t size, log_data_t *buf, void (*cb)(void)){
	if(queue[handler].set == 1)
		return HAL_BUSY;
	queue[handler].set = 1;
	queue[handler].adress = startAddress;
	queue[handler].buf = buf;
	queue[handler].cb = cb;
	queue[handler].size = size;
	return HAL_OK;
}

HAL_StatusTypeDef FP_GetStoredLog( uint32_t startAddress, uint32_t size, log_data_t *buf, void (*cb)(void)){
	if(queue[3].set == 1)
		return HAL_BUSY;
		queue[3].set = 1;
		queue[3].adress = startAddress;
		queue[3].buf = buf;
		queue[3].cb = cb;
		queue[3].size = size;
	return HAL_OK;
}
uint8_t FP_GetParam(void){
	oldIRQStatus = __get_PRIMASK(); __disable_irq();
	if (lock != UNLOCKED){
		__set_PRIMASK(oldIRQStatus);
		return HAL_BUSY;
	}
	manualLockSPI();
	__set_PRIMASK(oldIRQStatus);
	uint8_t timeout;
	lastBuffer = -1;
	if (sysParams.vars.status.flags.FRAMInited != 1 && sysParams.vars.error.flags.FRAMFail == 1){
		manualUnlockSPI();
		return HAL_ERROR;
	}
	
	for (uint8_t i = 0; i < FLASH_SECTORS; i++){
		fram->readData(baseAddress[i], &bufFlash[i].params,sizeof(stored_params_t));
		LL_mDelay(1);
		if (HAL_SPI_GetState(MEM_SPI) == HAL_BUSY){
			fram->abortCom();
			sysParams.vars.error.flags.FRAMFail = 1;
			sysParams.vars.status.flags.StoredParamsLoaded = 0;
			manualUnlockSPI();
			return HAL_ERROR;
		}
		if (bufFlash[i].params.startLoadFlag == START_FP_FLAG &&
			bufFlash[i].params.endLoadFlag == END_FP_FLAG &&
			(bufFlash[i].params.sysParConsts.sysVersion & 0x1) == (sysVers & 0x1) ){
				bufFlash[i].isCorrect = true;
				if (lastBuffer < 0){
					lastBuffer = i;
				} else {
					lastBuffer = (bufFlash[i].params.timeStamp > bufFlash[lastBuffer].params.timeStamp)?i:lastBuffer;
				}
			}
	}
	manualUnlockSPI();
	if (lastBuffer < 0){
		sysParams.vars.status.flags.StoredParamsLoaded = 0;
	} else {
		flashParams = bufFlash[lastBuffer];
		sysParams.vars.status.flags.StoredParamsLoaded = 1;
	}
	return HAL_OK;
}

uint8_t FP_SaveParam(void){
	if (queue[0].set == 1)
		return HAL_BUSY;
	queue[0].set = 1;
}

uint8_t FP_DeleteParam(void){
	oldIRQStatus = __get_PRIMASK(); __disable_irq();
	if (lock != UNLOCKED){
		__set_PRIMASK(oldIRQStatus);
		return HAL_BUSY;
	}
	__set_PRIMASK(oldIRQStatus);
	fram->eraseChip();
	while (lock	!=	UNLOCKED);
	return HAL_OK;
}
uint8_t FP_ClearLog(void){
	oldIRQStatus = __get_PRIMASK(); __disable_irq();
	if (lock != UNLOCKED){
		__set_PRIMASK(oldIRQStatus);
		return HAL_BUSY;
	}
	__set_PRIMASK(oldIRQStatus);
	logger->eraseChip();
	while (lock	!=	UNLOCKED);
	return HAL_OK;
}

void unlockSPI(void){
	if (lock == MANUAL_LOCK){
		return;
	} else {
		lock = 0;
	}
	if (queue[currentHandler].cb != NULL){
		queue[currentHandler].cb();
		queue[currentHandler].cb = NULL;
	}
	queue[currentHandler].set = false;
	currentHandler++;
	queueHandler();
	
	
}
void lockSPI(void){
	if (lock == UNLOCKED)
		lock = AUTO_LOCK;
}
void manualUnlockSPI(void){
	lock = UNLOCKED;
}
void manualLockSPI(void){
	lock = MANUAL_LOCK;
}

void queueHandler(void){
	if (queue[currentHandler].set == 1){
		switch (currentHandler){
			case (0):{
				saveFRAMParam();
				break;
			}
			case (1):
			case (2):{
				saveRAMParam(currentHandler);
				break;
			}
			case (3):{
				getRAMParam(currentHandler);
				break;
			}
		}
	} else {
		currentHandler++;	
		if (currentHandler > 4)
			return;
		queueHandler();
	}
}

void FP_StartStore(void){
	if (lock == UNLOCKED){
		currentHandler = 0;
		queueHandler();
	}
}

void saveFRAMParam(void){
	if (sysParams.vars.status.flags.FRAMInited != 1 || sysParams.vars.error.flags.FRAMFail == 1)
		return;
	oldIRQStatus = __get_PRIMASK(); __disable_irq();
	if (lock != UNLOCKED){
		__set_PRIMASK(oldIRQStatus);
		queue[0].set = true;
		return;
	}
	lockSPI();
	__set_PRIMASK(oldIRQStatus);

	stored_params_t buf = {0};
	lastBuffer++;
	if (lastBuffer >= FLASH_SECTORS || lastBuffer < 0){
		lastBuffer = 0;
	}
	bufFlash[lastBuffer].params.startLoadFlag = START_FP_FLAG;
	bufFlash[lastBuffer].params.endLoadFlag = END_FP_FLAG;
	bufFlash[lastBuffer].params.sysParConsts = sysParams.consts;
	bufFlash[lastBuffer].params.timeStamp = wtcTimeToInt(&sysParams.vars.sysTime);
	
	fram->writeData(baseAddress[lastBuffer],&bufFlash[lastBuffer].params,sizeof(stored_params_t));
	return;
}

void saveRAMParam(uint8_t handler){
	if (sysParams.vars.status.flags.RAMInited != 1 || sysParams.vars.error.flags.RAMFail == 1){
		return;
	}
	oldIRQStatus = __get_PRIMASK(); __disable_irq();
	if (lock != UNLOCKED){
		__set_PRIMASK(oldIRQStatus);
		return;
	}
	
	lockSPI();
	__set_PRIMASK(oldIRQStatus);
	cbFunc = queue[handler].cb;
	logger->writeData(queue[handler].adress, queue[handler].buf, queue[handler].size);
}

void getRAMParam(uint8_t handler){
	oldIRQStatus = __get_PRIMASK(); 
	__disable_irq();
	if (lock != UNLOCKED){
		__set_PRIMASK(oldIRQStatus);
		return;
	}
	lockSPI();
	__set_PRIMASK(oldIRQStatus);
	logger->readData(queue[3].adress, queue[3].buf, queue[3].size);
}