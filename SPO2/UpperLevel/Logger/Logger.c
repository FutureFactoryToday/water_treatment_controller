/*Includes*/
#include "main.h"

/*Macro and defines*/
#define LOG_FIFO_SIZE 10
#define LOG_DISPLAY_SIZE 4

#define MAX_ADRESS 0xFFFFFF
/*Global parameters*/
sys_status_flags_t oldFlags;
sys_error_flags_t	oldErrors;

log_data_t displayData[LOG_DISPLAY_SIZE];
log_data_t logFifo[LOG_FIFO_SIZE];
log_data_t dayValues[2];
static planer_status_t oldStatus;
uint8_t logBufEntryNum;
bool processing;
static uint32_t fifoEntryNum = 0;
bool washSave;
/*Local prototypes*/
static bool addEntry (log_data_t entry);
static void processComplete (void);
static HAL_StatusTypeDef saveLog (uint32_t size, uint32_t adress, uint8_t *buf);
static uint32_t checkEmptySpace();
/*Code*/
uint8_t LOG_Init(){
	oldFlags = sysParams.vars.status;
	oldErrors = sysParams.vars.error;
	oldStatus = sysParams.consts.planerConsts.status;
	processing = false;
	washSave = false;
	logBufEntryNum = 0;
	for(uint8_t i =0; i < LOG_FIFO_SIZE; i++){
		logFifo[i] = (log_data_t){0,0,0,0};
	}
	for(uint8_t i =0; i < LOG_DISPLAY_SIZE; i++){
		displayData[i] = (log_data_t){0,0,0,0};
	}
}

uint8_t LOG_GetErrors(uint16_t startEntry){
	if (sysParams.consts.storedEntryNum - sysParams.consts.storedWashNum > 0){
		processing = true;
		bool next;
		uint32_t startAddress = 0;
		for(uint8_t i = 0; i < (sysParams.consts.storedEntryNum - sysParams.consts.storedWashNum) && i < 4; i++){
			next = true;
			do{
				processing = true;
				while (FP_GetStoredLog(startAddress*sizeof(log_data_t),sizeof(log_data_t),&displayData[i],processComplete) != HAL_OK);
				while(processing);
				startAddress++;
				if (displayData[i].type == FAIL){
					if (startEntry){
						startEntry--;
						next= true;
					}else{
						next= false;
					}
				} else {
					next= true;
				}
			}while(next);
		}
		return sysParams.consts.storedEntryNum - sysParams.consts.storedWashNum;
	}
	return 0;
}

uint8_t LOG_GetWash(uint16_t startEntry){
	if (sysParams.consts.storedWashNum > 0){
		processing = true;
		bool next;
		uint32_t startAddress = 0;
		for(uint8_t i = 0; i < (sysParams.consts.storedWashNum) && i < 4; ){
			next = true;
			do{
				while (FP_GetStoredLog(startAddress*sizeof(log_data_t),sizeof(log_data_t),&displayData[i],processComplete)!= HAL_OK);
				
				while(processing);
				startAddress++;
				if (displayData[i].type == EVENT){
					if (startEntry)
						startEntry--;
				} else {
					next= false;
				}
			}while(next);
		}
		return sysParams.consts.storedWashNum;
	}
	return 0;
}

uint8_t LOG_GetWater(uint16_t startEntry){
	if (sysParams.consts.storedDayValueNum > 0){
		processing = true;
		uint32_t address = MAX_ADRESS - (sysParams.consts.storedDayValueNum)*sizeof(log_data_t);
		if (sysParams.consts.storedDayValueNum < 4){
			while (FP_GetStoredLog(address,sysParams.consts.storedDayValueNum*sizeof(log_data_t),displayData,processComplete)!= HAL_OK);
		} else {
			while (FP_GetStoredLog(address,4*sizeof(log_data_t),displayData,processComplete)!= HAL_OK);
		}
	}
	while(processing == true);
}

bool addEntry (log_data_t entry){
	
	logFifo[fifoEntryNum] = entry;
	fifoEntryNum++;
	uint8_t sizeMul = sizeof(log_data_t);
	if (checkEmptySpace() - fifoEntryNum == 1){
		saveLog(fifoEntryNum*sizeMul,sysParams.consts.storedEntryNum*sizeMul,logFifo);
		sysParams.vars.error.flags.RAMFull = 1;
		return false;
	}
	if (fifoEntryNum == (sizeof(logFifo)/sizeof(log_data_t))){
		saveLog(fifoEntryNum*sizeMul,sysParams.consts.storedEntryNum*sizeMul,logFifo);
		return false;
	}
	else
		return true;
}


HAL_StatusTypeDef saveLog (uint32_t size, uint32_t adress, uint8_t *buf){
	HAL_StatusTypeDef res;
	if (processing)
		return HAL_BUSY;
	
	if (oldErrors.flags.RAMFull == 1 ||
		oldErrors.flags.RAMFail == 1)
		return HAL_ERROR;
	uint8_t sizeMul = sizeof(log_data_t);
	if (fifoEntryNum > 0){
		processing = true;
		res = FP_StoreLog(1,adress,size,buf,processComplete);
		if (res == HAL_OK){
			sysParams.consts.storedEntryNum += size/sizeMul;
		} 
		return res;
	}
	return HAL_OK;
}

HAL_StatusTypeDef LOG_Interrupt(void){
	sys_status_flags_t tempFlags;
	sys_error_flags_t tempError;
	sys_error_flags_t error;
	if (processing){
		return HAL_BUSY;
	}
	if (oldErrors.flags.RAMFull == 1 ||
			oldErrors.flags.RAMFail == 1)
		return HAL_ERROR;
	
	if (logFifo[0].timeStamp != 0){
		for(uint8_t i =0; i < fifoEntryNum; i++){
			logFifo[i] = (log_data_t){0,0,0,0};
		}
		fifoEntryNum = 0;
	}
	
	tempFlags.all = oldFlags.all 	^ sysParams.vars.status.all; 
	tempError.all = oldErrors.all ^ sysParams.vars.error.all;
	tempFlags.all = tempFlags.all & sysParams.vars.status.all;
	tempError.all = tempError.all & sysParams.vars.error.all;
	
	uint32_t timeStamp = LL_RTC_TIME_Get(RTC);
	uint8_t type = FAIL;
	uint8_t cause;
	
	if(tempError.flags.RAMFull == 1){
		error.all = 0;
		error.flags.RAMFull = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,0})){
			oldErrors.flags.RAMFull = 1;
			return HAL_ERROR;
		} 
	}
	
	if(tempError.flags.mainPowerFail == 1){
		error.all = 0;
		error.flags.mainPowerFail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,sysParams.vars.adc.rawADC[Vin]})){
			oldErrors.flags.mainPowerFail = 1;
		} else {
			return HAL_OK;
		}
	} 
	
	if(tempError.flags.BatteryFail == 1){
		error.all = 0;
		error.flags.BatteryFail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,sysParams.vars.adc.rawADC[Vbat]})){
			oldErrors.flags.BatteryFail = 1;
		} else {
			return HAL_OK;
		}
	} 
	if(tempError.flags._5VPowerFail == 1){
		error.all = 0;
		error.flags._5VPowerFail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,sysParams.vars.adc.rawADC[_5V]})){
			oldErrors.flags._5VPowerFail = 1;
		} else {
			return HAL_OK;
		}
	} 
	if(tempError.flags.RelPowerFail == 1){
		error.all = 0;
		error.flags.RelPowerFail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,sysParams.vars.adc.rawADC[VrelDC]})){
			oldErrors.flags.RelPowerFail = 1;
		} else {
			return HAL_OK;
		}
	}
	if(tempError.flags.TempFail == 1){
		error.all = 0;
		error.flags.TempFail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,sysParams.vars.adc.rawADC[Temp]})){
			oldErrors.flags.TempFail = 1;
		} else {
			return HAL_OK;
		}
	}
	
	if(tempError.flags.Drive1Fail == 1){
		error.all = 0;
		error.flags.Drive1Fail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,0})){
			oldErrors.flags.Drive1Fail = 1;
		} else {
			return HAL_OK;
		}
	}
	if(tempError.flags.Drive2Fail == 1){
		error.all = 0;
		error.flags.Drive2Fail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,0})){
			oldErrors.flags.Drive2Fail = 1;
		} else {
			return HAL_OK;
		}
	}
	if(tempError.flags.MotorFail == 1){
		error.all = 0;
		error.flags.MotorFail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,0})){
			oldErrors.flags.MotorFail = 1;
		} else {
			return HAL_OK;
		}
	}
	
	if(tempError.flags.PistonStallFail == 1){
		error.all = 0;
		error.flags.PistonStallFail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,sysParams.vars.pistonParams.curPoz})){
			oldErrors.flags.PistonStallFail = 1;
		} else {
			return HAL_OK;
		}
	}
	if(tempError.flags.PistonFail == 1){
		error.all = 0;
		error.flags.PistonFail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,sysParams.vars.pistonParams.curPoz})){
			oldErrors.flags.PistonFail = 1;
		} else {
			return HAL_OK;
		}
		oldErrors.flags.PistonFail = 1;
	} 		
	
	if(tempError.flags.RelayDCFail == 1){
		error.all = 0;
		error.flags.RelayDCFail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,sysParams.vars.status.flags.RelDCOn})){
			oldErrors.flags.RelayDCFail = 1;
		} else {
			return HAL_OK;
		}
	}
	if(tempError.flags.RelayACFail == 1){
		error.all = 0;
		error.flags.RelayACFail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,sysParams.vars.status.flags.RelACOn})){
			oldErrors.flags.RelayACFail = 1;
		} else {
			return HAL_OK;
		}
	}
	
	if(tempError.flags.TFTFail == 1){
		error.all = 0;
		error.flags.TFTFail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,0})){
			oldErrors.flags.TFTFail = 1;
		} else {
			return HAL_OK;
		}
	}	
	if(tempError.flags.TouchFail == 1){
		error.all = 0;
		error.flags.TouchFail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,0})){
			oldErrors.flags.TouchFail = 1;
		} else {
			return HAL_OK;
		}
	}
	if(tempError.flags.FRAMFail == 1){
		error.all = 0;
		error.flags.FRAMFail = 1;
		cause = error.all;
		if (addEntry((log_data_t){timeStamp,type,cause,0})){
			oldErrors.flags.FRAMFail = 1;
		} else {
			return HAL_OK;
		}
	} 	
	if (oldStatus != sysParams.consts.planerConsts.status && sysParams.consts.planerConsts.status == PL_WORKING){
		type = EVENT;
		cause = 0;
		if (addEntry((log_data_t){timeStamp,type,cause,0})){
			washSave = true;
			oldStatus = sysParams.consts.planerConsts.status;
		} else {
			return HAL_OK;
		}
	}
	
	if (fifoEntryNum){
		saveLog(fifoEntryNum*sizeof(log_data_t),sysParams.consts.storedEntryNum*sizeof(log_data_t),logFifo);
	}
//	oldFlags.all = sysParams.vars.status.all;
//	oldErrors.all = sysParams.vars.error.all;
}

uint8_t LOG_StoreDayValues(void){
	if (sysParams.vars.error.flags.RAMFull == 1 ||
		sysParams.vars.error.flags.RAMFail == 1)
		return HAL_ERROR;
	if (checkEmptySpace() < 2){
		sysParams.vars.error.flags.RAMFull = 1;
		return HAL_ERROR;
	}
	if (processing)
		return HAL_BUSY;
	
	processing = true;
	
	dayValues[0].timeStamp = LL_RTC_TIME_Get(RTC);
	dayValues[0].type = WATER_SPEED;
	dayValues[0].param = sysParams.consts.maxWaterUsage;
	
	dayValues[1].timeStamp = LL_RTC_TIME_Get(RTC);
	dayValues[1].type = USAGE;
	dayValues[1].param = sysParams.consts.dayWaterUsage;
	uint8_t size = sizeof(dayValues)/sizeof(log_data_t);
	if (FP_StoreLog(2, MAX_ADRESS - (sysParams.consts.storedDayValueNum + 2)*sizeof(log_data_t),
							2*sizeof(log_data_t),
							dayValues,
							processComplete));
	sysParams.consts.storedDayValueNum += 2;
}

uint32_t checkEmptySpace(){
	uint32_t res = MAX_ADRESS/sizeof(log_data_t) - (sysParams.consts.storedDayValueNum + sysParams.consts.storedEntryNum);
	return res;
}

void processComplete (void){
	processing = false;
}
	#include "FlashIC/W25.h"
uint8_t recBuf[24];
void LOG_Test(){
	flash_driver_t *drv = &W25_driver;
	while (1){
//		LOG_StoreDayValues();
//		while(processing);
//		for(uint8_t i = 0; i<12;i++){
//			recBuf[i] = 0;
//		}
//		drv->readData(0xFFFFFF - 24,recBuf,24);
//		while (HAL_SPI_GetState(MEM_SPI) != HAL_SPI_STATE_READY);
//		LOG_GetWater(0);
//		while(processing);
		
		LOG_Interrupt();
		while(processing);
		for(uint8_t i = 0; i<24;i++){
			recBuf[i] = 0;
		}
		drv->readData(0,recBuf,24);
		while (HAL_SPI_GetState(MEM_SPI) != HAL_SPI_STATE_READY);
		LOG_GetErrors(0);
		while(processing);
	}
}
//	while (HAL_SPI_GetState(MEM_SPI) != HAL_SPI_STATE_READY);
//	drv->readData(0xFFFFFF-10,recBuf2,10);
//while (HAL_SPI_GetState(MEM_SPI) != HAL_SPI_STATE_READY);
//	for(uint8_t i = 0; i<10;i++){
//		recBuf[i] = i+1;
//	}
//	drv->writeData(0,recBuf,10);
//while (HAL_SPI_GetState(MEM_SPI) != HAL_SPI_STATE_READY);
//	drv->writeData(0xFFFFFF-10,recBuf,10);
//while (HAL_SPI_GetState(MEM_SPI) != HAL_SPI_STATE_READY);
//	for(uint8_t i = 0; i<10;i++){
//		recBuf[i] = 0;
//	}
//	drv->readData(0,recBuf,10);
//while (HAL_SPI_GetState(MEM_SPI) != HAL_SPI_STATE_READY);
//	drv->readData(0xFFFFFF-10,recBuf2,10);
//while (HAL_SPI_GetState(MEM_SPI) != HAL_SPI_STATE_READY);