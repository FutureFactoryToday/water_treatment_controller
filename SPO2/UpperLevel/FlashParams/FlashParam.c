/**
  ******************************************************************************
  * @file           : FlashParam.c
  * @brief          : 
  ******************************************************************************
  * @attention
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
static volatile uint8_t lock, lock2;
static uint8_t currentHandler;
volatile static flash_params_t flashParams = {0};
flash_params_t* fp = &flashParams;
uint32_t sysVers;
uint32_t irqStatus;
uint16_t baseAddress[FLASH_SECTORS];
flash_driver_t *fram = &FM25_driver;
flash_driver_t *logger = &W25_driver;
flash_params_t bufFlash[FLASH_SECTORS];

volatile flash_queue_t fQueue; 
uint8_t transmitCnt;
bool oldIRQStatus;
int8_t lastBuffer;
void (*cbFunc)(void);

/* Private function prototypes -----------------------------------------------*/
void loadParams(void);
void endTransmit(void);
void transmitCount(void);
void queueHandler(void);
void saveFRAMParam(void);
void saveRAMParam(uint8_t handler);
void getRAMParam(uint8_t handler);
mem_buffer_t* getMemBuffer(msg_type_t type);
uint8_t getCurMsgNum (void);
/* Private user code ---------------------------------------------------------*/

bool FP_Init(void){
	lock = UNLOCKED;
	lock2 = lock;
	sysVers = SYSTEM_PO_VERSION;
	gpio_t framCS = {FRAM_CS_GPIO_Port,FRAM_CS_Pin};
	gpio_t framWP	=	{FRAM_WP_GPIO_Port, FRAM_WP_Pin};
	gpio_t framHOLD	=	{FRAM_HOLD_GPIO_Port, FRAM_HOLD_Pin};
	gpio_t logCS = {MEM_CS_GPIO_Port,MEM_CS_Pin};
	gpio_t logWP = {MEM_WP_GPIO_Port,MEM_WP_Pin};
	gpio_t logHOLD = {MEM_RES_GPIO_Port,MEM_RES_Pin};
		
	if (fram->init(MEM_SPI,framCS, framWP, framHOLD,endTransmit) == HAL_OK){
		sysParams.vars.status.flags.FRAMInited = 1;
	} else {
		sysParams.vars.error.flags.FRAMFail = 1;
	}
	
	if (logger->init(MEM_SPI,logCS, logWP, logHOLD,endTransmit) == HAL_OK){
		sysParams.vars.status.flags.RAMInited = 1;
	} else {
		sysParams.vars.error.flags.RAMFail = 1;
	}
	
	for (uint8_t i = 0; i < FLASH_SECTORS; i++){
		baseAddress[i] = i*sizeof(stored_params_t) + i;
	}
	
	//Flash queue init
	fQueue.empty = true;
	fQueue.full = false;
	fQueue.isTransmiting = false;
	fQueue.head = 0;
	fQueue.tail = 0;
	for (uint8_t i =0; i < FLASH_QUEUE_SIZE; i++){
		fQueue.msgs[i] = (flash_message_t){0,0,0,0,0,true};
	}

}
HAL_StatusTypeDef FP_StoreLog(msg_type_t type, uint32_t entryNum, log_data_t *buf, void (*cb)(void)){
	bool oneMsg;
	uint8_t curMsgNum;
	if (sysParams.vars.status.flags.RAMInited != 1 || sysParams.vars.error.flags.RAMFail == 1){
		return HAL_ERROR;
	}
	//Choose current memory buffer
	mem_buffer_t* memBuf = getMemBuffer(type);
	//Find limits
	uint32_t maxEntries = ((memBuf->stopAdr+1) - memBuf->startAdr)/sizeof(log_data_t);
	oneMsg = (memBuf->nextEntryPoz + entryNum - 1 > maxEntries)?false:true;
	
	curMsgNum = getCurMsgNum();
	//Current msg fits in buffer
	if (oneMsg){
		fQueue.msgs[curMsgNum].type = WRITE_RAM;
		fQueue.msgs[curMsgNum].buf = buf;
		fQueue.msgs[curMsgNum].size = entryNum*sizeof(log_data_t);
		fQueue.msgs[curMsgNum].adress = memBuf->startAdr + memBuf->nextEntryPoz*sizeof(log_data_t);
		fQueue.msgs[curMsgNum].cb = cb;
	} else {
		//Current msg will overlap buffer limit
		curMsgNum = getCurMsgNum();
		uint32_t firstMsgSize = maxEntries - memBuf->nextEntryPoz;
		fQueue.msgs[curMsgNum].type = WRITE_RAM;
		fQueue.msgs[curMsgNum].buf = buf;
		fQueue.msgs[curMsgNum].size = firstMsgSize*sizeof(log_data_t);
		fQueue.msgs[curMsgNum].adress = memBuf->startAdr + memBuf->nextEntryPoz*sizeof(log_data_t);
		fQueue.msgs[curMsgNum].cb = 0;
		
		uint32_t secondMsgSize = entryNum - firstMsgSize;
		curMsgNum = getCurMsgNum();
		fQueue.msgs[curMsgNum].type = WRITE_RAM;
		fQueue.msgs[curMsgNum].buf = buf;
		fQueue.msgs[curMsgNum].size = secondMsgSize*sizeof(log_data_t);
		fQueue.msgs[curMsgNum].adress = memBuf->startAdr;
		fQueue.msgs[curMsgNum].cb = cb;
		
	}
	//Check which half of buffer marked
	if (memBuf->nextEntryPoz < SECTOR_SIZE){
		memBuf->firstSectorErased = false;
	}else {
		memBuf->secondSectorErased = false;
	}
	//Increment pointer with limit check
	memBuf->nextEntryPoz += entryNum;
	if (memBuf->nextEntryPoz >= maxEntries){
		memBuf->nextEntryPoz = memBuf->nextEntryPoz - maxEntries;
	}
	//Check is it necessary to flush half buffer
	if (memBuf->firstSectorErased != true && memBuf->nextEntryPoz > DAYS_TO_STORE){
		curMsgNum = getCurMsgNum();
		fQueue.msgs[curMsgNum].type = CLEAR_SECTOR;
		fQueue.msgs[curMsgNum].adress = memBuf->startAdr;
		fQueue.msgs[curMsgNum].cb = 0;
		memBuf->firstSectorErased = true;
	}
	if (memBuf->secondSectorErased != true && memBuf->nextEntryPoz > DAYS_TO_STORE + SECTOR_SIZE){
		curMsgNum = getCurMsgNum();
		fQueue.msgs[curMsgNum].type = CLEAR_SECTOR;
		fQueue.msgs[curMsgNum].adress = memBuf->startAdr + SECTOR_SIZE;
		fQueue.msgs[curMsgNum].cb = 0;
		memBuf->secondSectorErased = true;
	}
	return HAL_OK;
}

HAL_StatusTypeDef FP_GetStoredLog(msg_type_t type, uint32_t readNum, uint32_t offset, log_data_t *buf, void (*cb)(void)){

	bool oneMsg;
	uint8_t curMsgNum;
	if (sysParams.vars.status.flags.RAMInited != 1 || sysParams.vars.error.flags.RAMFail == 1){
		return HAL_ERROR;
	}
	//Choose current memory buffer
	mem_buffer_t* memBuf = getMemBuffer(type);
	//Find limits
	uint32_t maxEntries = ((memBuf->stopAdr+1) - memBuf->startAdr)/sizeof(log_data_t);
	int32_t startOffset = memBuf->nextEntryPoz - offset - readNum;
	
	oneMsg = (startOffset >= 0)?true:false;
	
	curMsgNum = getCurMsgNum();
	
	if (oneMsg){
		fQueue.msgs[curMsgNum].type = READ_RAM;
		fQueue.msgs[curMsgNum].buf = buf;
		fQueue.msgs[curMsgNum].size = readNum*sizeof(log_data_t);
		fQueue.msgs[curMsgNum].adress = memBuf->startAdr + (memBuf->nextEntryPoz - offset - readNum)*sizeof(log_data_t);
		fQueue.msgs[curMsgNum].cb = cb;
	} else {
		uint32_t firstSize = abs(startOffset);
		fQueue.msgs[curMsgNum].type = READ_RAM;
		fQueue.msgs[curMsgNum].buf = buf;
		fQueue.msgs[curMsgNum].size = firstSize*sizeof(log_data_t);
		fQueue.msgs[curMsgNum].adress = memBuf->stopAdr - firstSize*sizeof(log_data_t);
		fQueue.msgs[curMsgNum].cb = 0;
		
		uint32_t secondSize = readNum - firstSize;
		curMsgNum = getCurMsgNum();
		fQueue.msgs[curMsgNum].type = READ_RAM;
		fQueue.msgs[curMsgNum].buf = buf;
		fQueue.msgs[curMsgNum].size = secondSize*sizeof(log_data_t);
		fQueue.msgs[curMsgNum].adress = memBuf->startAdr;
		fQueue.msgs[curMsgNum].cb = cb;
	}
	
	return HAL_OK;
}
uint8_t FP_GetParam(void){
//	oldIRQStatus = __get_PRIMASK(); __disable_irq();
//	if (lock != UNLOCKED){
//		__set_PRIMASK(oldIRQStatus);
//		return HAL_BUSY;
//	}
//	manualLockSPI();
//	__set_PRIMASK(oldIRQStatus);
//	uint8_t timeout;
//	lastBuffer = -1;
//	if (sysParams.vars.status.flags.FRAMInited != 1 && sysParams.vars.error.flags.FRAMFail == 1){
//		manualUnlockSPI();
//		return HAL_ERROR;
//	}
//	
//	for (uint8_t i = 0; i < FLASH_SECTORS; i++){
//		fram->readData(baseAddress[i], &bufFlash[i].params,sizeof(stored_params_t));
//		LL_mDelay(1);
//		if (HAL_SPI_GetState(MEM_SPI) == HAL_BUSY){
//			fram->abortCom();
//			sysParams.vars.error.flags.FRAMFail = 1;
//			sysParams.vars.status.flags.StoredParamsLoaded = 0;
//			manualUnlockSPI();
//			return HAL_ERROR;
//		}
//		if (bufFlash[i].params.startLoadFlag == START_FP_FLAG &&
//			bufFlash[i].params.endLoadFlag == END_FP_FLAG &&
//			(bufFlash[i].params.sysParConsts.sysVersion) == (sysVers) ){
//				bufFlash[i].isCorrect = true;
//				if (lastBuffer < 0){
//					lastBuffer = i;
//				} else {
//					lastBuffer = (bufFlash[i].params.timeStamp > bufFlash[lastBuffer].params.timeStamp)?i:lastBuffer;
//				}
//			}
//	}
//	manualUnlockSPI();
//	if (lastBuffer < 0){
//		sysParams.vars.status.flags.StoredParamsLoaded = 0;
//	} else {
//		flashParams = bufFlash[lastBuffer];
//		sysParams.vars.status.flags.StoredParamsLoaded = 1;
//	}
//	return HAL_OK;

	
	uint32_t timeoutStart = HAL_GetTick();
	lastBuffer = -1;
	if (sysParams.vars.status.flags.FRAMInited != 1 && sysParams.vars.error.flags.FRAMFail == 1){
		return HAL_ERROR;
	}
	
	transmitCnt = 0;
	for (uint8_t i = 0; i < FLASH_SECTORS; i++){
		if (fQueue.full){
			return HAL_ERROR;
		}
	
		fQueue.empty = false;
		__disable_irq();
	
		uint8_t curMsgNum = fQueue.head++;
		
		if (fQueue.head > FLASH_QUEUE_SIZE-1){
			fQueue.head = 0;
		}
		if (fQueue.head == fQueue.tail){
			fQueue.full = true;
		}
		
		fQueue.msgs[curMsgNum].type = READ_FRAM;
		fQueue.msgs[curMsgNum].buf = &bufFlash[i].params;
		fQueue.msgs[curMsgNum].size = sizeof(stored_params_t);
		fQueue.msgs[curMsgNum].adress = baseAddress[i];
		fQueue.msgs[curMsgNum].cb = transmitCount;
		__enable_irq();
		//queueHandler();
	}
	
	while (transmitCnt<3){
		if (HAL_GetTick() - timeoutStart > 1*1000){
			return HAL_ERROR;
		}
	}

	for (uint8_t i = 0; i < FLASH_SECTORS; i++){
		if (bufFlash[i].params.startLoadFlag == START_FP_FLAG &&
			bufFlash[i].params.endLoadFlag == END_FP_FLAG &&
			(bufFlash[i].params.sysParConsts.sysVersion) == (sysVers) ){
				bufFlash[i].isCorrect = true;
				if (lastBuffer < 0){
					lastBuffer = i;
				} else {
					lastBuffer = (bufFlash[i].params.timeStamp > bufFlash[lastBuffer].params.timeStamp)?i:lastBuffer;
				}
			}
	}
	
	if (lastBuffer < 0){
		sysParams.vars.status.flags.StoredParamsLoaded = 0;
	} else {
		flashParams = bufFlash[lastBuffer];
		sysParams.vars.status.flags.StoredParamsLoaded = 1;
	}
	return HAL_OK;
}

uint8_t FP_SaveParam(void){
#if defined (TEST_VERSION)&& defined (DISABLE_FRAM)
	//Version - 1.28
	//Remove fast flash to check how slow mem works
	
	return 0;
#endif
	if (fQueue.full){
		return HAL_BUSY;
	}
	
	fQueue.empty = false;
	__disable_irq();
	
	uint8_t curMsgNum = fQueue.head++;
	
	if (fQueue.head > FLASH_QUEUE_SIZE-1){
		fQueue.head = 0;
	}
	if (fQueue.head == fQueue.tail){
		fQueue.full = true;
	}
	
	stored_params_t buf = {0};
	lastBuffer++;
	if (lastBuffer >= FLASH_SECTORS || lastBuffer < 0){
		lastBuffer = 0;
	}
	
	bufFlash[lastBuffer].params.startLoadFlag = START_FP_FLAG;
	bufFlash[lastBuffer].params.endLoadFlag = END_FP_FLAG;
	bufFlash[lastBuffer].params.sysParConsts = sysParams.consts;
	bufFlash[lastBuffer].params.timeStamp = wtcTimeToInt(&sysParams.vars.sysTime);
	
	fQueue.msgs[curMsgNum].type = WRITE_FRAM;
	fQueue.msgs[curMsgNum].buf = &bufFlash[lastBuffer].params;
	fQueue.msgs[curMsgNum].size = sizeof(stored_params_t);
	fQueue.msgs[curMsgNum].adress = baseAddress[lastBuffer];
	fQueue.msgs[curMsgNum].cb = NULL;
	__enable_irq();
	//queueHandler();
}

uint8_t FP_DeleteParam(void){
	if (fQueue.full){
			return HAL_BUSY;
	}
	
	fQueue.empty = false;
	__disable_irq();
	
	uint8_t curMsgNum = fQueue.head++;
	
	if (fQueue.head > FLASH_QUEUE_SIZE-1){
		fQueue.head = 0;
	}
	if (fQueue.head == fQueue.tail){
		fQueue.full = true;
	}
	
	
	fQueue.msgs[curMsgNum].type = CLEAR_PARAMS;
	fQueue.msgs[curMsgNum].buf = 0;
	fQueue.msgs[curMsgNum].size = 0;
	fQueue.msgs[curMsgNum].adress = 0;
	fQueue.msgs[curMsgNum].cb = NULL;
	__enable_irq();
	//queueHandler();
}
uint8_t FP_ClearLog(void){
	if (fQueue.full){
			return HAL_BUSY;
	}
	
	fQueue.empty = false;
		__disable_irq();
	
	uint8_t curMsgNum = fQueue.head++;
	
	if (fQueue.head > FLASH_QUEUE_SIZE-1){
		fQueue.head = 0;
	}
	if (fQueue.head == fQueue.tail){
		fQueue.full = true;
	}
	
	
	fQueue.msgs[curMsgNum].type = CLEAR_LOG;
	fQueue.msgs[curMsgNum].buf = 0;
	fQueue.msgs[curMsgNum].size = 0;
	fQueue.msgs[curMsgNum].adress = 0;
	fQueue.msgs[curMsgNum].cb = NULL;
	__enable_irq();
	
	sysParams.consts.washBuf.firstSectorErased = true;
	sysParams.consts.washBuf.secondSectorErased = true;
	sysParams.consts.waterQuant.firstSectorErased = true;
	sysParams.consts.waterQuant.secondSectorErased = true;	
	sysParams.consts.waterUsage.firstSectorErased = true;
	sysParams.consts.waterUsage.secondSectorErased = true;
	sysParams.consts.errorBuf.firstSectorErased = true;
	sysParams.consts.errorBuf.secondSectorErased = true;
	
	//queueHandler();
}

void endTransmit(void){
	if (fQueue.msgs[fQueue.tail].cb != NULL)
		fQueue.msgs[fQueue.tail].cb();	
	fQueue.msgs[fQueue.tail].isTransmited = 1; 
	fQueue.msgs[fQueue.tail].type = 0;
	fQueue.msgs[fQueue.tail].buf = 0;
	fQueue.msgs[fQueue.tail].size = 0;
	fQueue.msgs[fQueue.tail].adress = 0;
	fQueue.msgs[fQueue.tail].cb = NULL;
	fQueue.tail++;
	fQueue.isTransmiting = false;
	if (fQueue.tail > FLASH_QUEUE_SIZE-1){
		fQueue.tail = 0;
	}
	if (fQueue.head == fQueue.tail){
		fQueue.empty = true;
	}
	
	fQueue.full = false;
	
	//queueHandler();
}

void transmitCount(void){
	transmitCnt++;
}



void queueHandler(void){
	
	if (fQueue.empty == true){
		return;
	}	
	if (fQueue.isTransmiting){
		return;
	}	
	
	switch (fQueue.msgs[fQueue.tail].type){
		case(READ_FRAM):{
			fQueue.isTransmiting = true;
			fram->readData(fQueue.msgs[fQueue.tail].adress,fQueue.msgs[fQueue.tail].buf,fQueue.msgs[fQueue.tail].size);
			
			break;	
		}
		case(WRITE_FRAM):{
			fQueue.isTransmiting = true;
			fram->writeData(fQueue.msgs[fQueue.tail].adress,fQueue.msgs[fQueue.tail].buf,fQueue.msgs[fQueue.tail].size);
			
			break;	
		}
		case(READ_RAM):{
			fQueue.isTransmiting = true;
			logger->readData(fQueue.msgs[fQueue.tail].adress,fQueue.msgs[fQueue.tail].buf,fQueue.msgs[fQueue.tail].size);
			
			break;	
		}
		case(WRITE_RAM):{
			fQueue.isTransmiting = true;
			logger->writeData(fQueue.msgs[fQueue.tail].adress,fQueue.msgs[fQueue.tail].buf,fQueue.msgs[fQueue.tail].size);
			
			break;	
		}
		case(CLEAR_LOG):{
			logger->eraseChip();
			
			break;	
		}
		case(CLEAR_PARAMS):{
			fram->eraseChip();
			break;	
		}
		case(CLEAR_SECTOR):{
			logger->eraseSector(fQueue.msgs[fQueue.tail].adress);
			break;	
		}
		default:{
			
		}
	}
}

void FP_StartStore(void){
	queueHandler();
}

uint8_t FP_Manual_FRAM_Write(uint8_t* data, uint32_t adr, uint32_t size, void (*cb)(void)){
	if (sysParams.vars.status.flags.RAMInited != 1 || sysParams.vars.error.flags.RAMFail == 1){
		return HAL_ERROR;
	}
	
	if (fQueue.full){
		return HAL_BUSY;
	}
	
	fQueue.empty = false;
	__disable_irq();
	
	uint8_t curMsgNum = fQueue.head++;
	
	if (fQueue.head > FLASH_QUEUE_SIZE-1){
		fQueue.head = 0;
	}
	if (fQueue.head == fQueue.tail){
		fQueue.full = true;
	}
	
	fQueue.msgs[curMsgNum].type = WRITE_FRAM;
	fQueue.msgs[curMsgNum].buf = data;
	fQueue.msgs[curMsgNum].size = size;
	fQueue.msgs[curMsgNum].adress = adr;
	fQueue.msgs[curMsgNum].cb = cb;
	fQueue.msgs[curMsgNum].isTransmited = 0;
//	if (!fQueue.isTransmiting)
//		queueHandler();
__enable_irq();
	return HAL_OK;
}
uint8_t FP_Manual_FRAM_Read(uint8_t* data, uint32_t adr, uint32_t size, void (*cb)(void)){
		if (sysParams.vars.status.flags.RAMInited != 1 || sysParams.vars.error.flags.RAMFail == 1){
		return HAL_ERROR;
	}
	
	if (fQueue.full){
		return HAL_BUSY;
	}
	
	fQueue.empty = false;
		__disable_irq();
	
	uint8_t curMsgNum = fQueue.head++;
	
	if (fQueue.head > FLASH_QUEUE_SIZE-1){
		fQueue.head = 0;
	}
	if (fQueue.head == fQueue.tail){
		fQueue.full = true;
	}
	
	fQueue.msgs[curMsgNum].type = READ_FRAM;
	fQueue.msgs[curMsgNum].buf = data;
	fQueue.msgs[curMsgNum].size = size;
	fQueue.msgs[curMsgNum].adress = adr;
	fQueue.msgs[curMsgNum].cb = cb;
	fQueue.msgs[curMsgNum].isTransmited = 0;
//	if (!fQueue.isTransmiting)
//		queueHandler();
	__enable_irq();
	return HAL_OK;
}
uint8_t FP_Manual_RAM_Write(uint8_t* data, uint32_t adr, uint32_t size, void (*cb)(void)){
		if (sysParams.vars.status.flags.RAMInited != 1 || sysParams.vars.error.flags.RAMFail == 1){
		return HAL_ERROR;
	}
	
	if (fQueue.full){
		return HAL_BUSY;
	}
	
	fQueue.empty = false;
	__disable_irq();
	uint8_t curMsgNum = fQueue.head++;
		
	
	if (fQueue.head > FLASH_QUEUE_SIZE-1){
		fQueue.head = 0;
	}
	if (fQueue.head == fQueue.tail){
		fQueue.full = true;
	}
	
	fQueue.msgs[curMsgNum].type = WRITE_RAM;
	fQueue.msgs[curMsgNum].buf = data;
	fQueue.msgs[curMsgNum].size = size;
	fQueue.msgs[curMsgNum].adress = adr;
	fQueue.msgs[curMsgNum].cb = cb;
	fQueue.msgs[curMsgNum].isTransmited = 0;
//	if (!fQueue.isTransmiting)
//	queueHandler();
	__enable_irq();
	return HAL_OK;
}
uint8_t FP_Manual_RAM_Read(uint8_t* data, uint32_t adr, uint32_t size, void (*cb)(void)){
		if (sysParams.vars.status.flags.RAMInited != 1 || sysParams.vars.error.flags.RAMFail == 1){
		return HAL_ERROR;
	}
	
	if (fQueue.full){
		return HAL_BUSY;
	}
	
	fQueue.empty = false;
	__disable_irq();
	
	uint8_t curMsgNum = fQueue.head++;
	
	if (fQueue.head > FLASH_QUEUE_SIZE-1){
		fQueue.head = 0;
	}
	if (fQueue.head == fQueue.tail){
		fQueue.full = true;
	}
	
	fQueue.msgs[curMsgNum].type = READ_RAM;
	fQueue.msgs[curMsgNum].buf = data;
	fQueue.msgs[curMsgNum].size = size;
	fQueue.msgs[curMsgNum].adress = adr;
	fQueue.msgs[curMsgNum].cb = cb;
	fQueue.msgs[curMsgNum].isTransmited = 0;
//	if (!fQueue.isTransmiting)
//		queueHandler();
	__enable_irq();
	return HAL_OK;
}

bool FP_isEmpty(){
	return fQueue.empty;
}

mem_buffer_t* getMemBuffer(msg_type_t type){
	switch (type){
		case(ERROR_LOG):{
			return &sysParams.consts.errorBuf;
		}
		case(WASH_LOG):{
			return &sysParams.consts.washBuf;
		}
		case(WATER_QUANT):{
			return &sysParams.consts.waterQuant;
		}
		case(WATER_USAGE):{
			return &sysParams.consts.waterUsage;
		}
		default:{
			while(1);
			return 0;
		}
	}
}

uint8_t getCurMsgNum (void){
	while(fQueue.full);
	
	fQueue.empty = false;
	uint8_t curMsgNum = fQueue.head++;
	
	if (fQueue.head > FLASH_QUEUE_SIZE-1){
		fQueue.head = 0;
	}
	if (fQueue.head == fQueue.tail){
		fQueue.full = true;
	}
	
	return curMsgNum;
}
