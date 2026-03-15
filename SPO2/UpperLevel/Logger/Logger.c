/*Includes*/
#include "main.h"

/*Macro and defines*/
#define LOG_FIFO_SIZE 10
#define LOG_DISPLAY_SIZE 4

#define MAX_ADRESS 0xFFFFFF


/*Global parameters*/
sys_status_flags_t oldFlags;
sys_error_flags_t	oldErrors;
static uint8_t oldDay; 
static uint32_t oldWater;
volatile log_data_t displayData[LOG_DISPLAY_SIZE];
log_data_t logFifo[LOG_FIFO_SIZE];
log_data_t dayValues[2];
log_data_t washEvent;
static planer_status_t oldStatus;
uint8_t logBufEntryNum;
volatile bool processing;
static uint32_t fifoEntryNum = 0;

uint8_t memBuf[128];
uint32_t memAdr, memSize;
uint8_t washSave;
volatile ulog_queue_t uLogQ;
volatile ulog_entry_t logEntry[UART_LOG_Q_SIZE];
sys_param_t sysParCopy;
uint8_t transmitStep;
uint8_t header[2];
wtc_time_t lastSave;

uint8_t LOG_STEP;
/*Local prototypes*/
static bool addEntry (log_data_t entry);
static void processComplete (void);
static HAL_StatusTypeDef SaveErrors (uint32_t size, uint32_t adress, uint8_t *buf);
static uint8_t StoreDayValues(void);
static uint8_t StoreWashEvent(void);
static uint32_t checkErrorEmptySpace();
static uint32_t checkWashEmptySpace();
static void UL_Continue(UART_HandleTypeDef *huart);
static void UL_Start(void);
/*Code*/
uint8_t LOG_Init(){
	oldFlags.all = 0;
	oldErrors.all = 0;
	oldStatus = sysParams.consts.planerConsts.status;
	processing = false;
	washSave = 0;
	oldDay = 0; 
	oldWater = sysParams.consts.waterFromLastFilter;
	for(uint8_t i =0; i < LOG_FIFO_SIZE; i++){
		logFifo[i] = (log_data_t){0,0,0,0};
	}
	for(uint8_t i =0; i < LOG_DISPLAY_SIZE; i++){
		displayData[i] = (log_data_t){0,0,0,0};
	}
	
	/*UART LOG INIT*/
	uLogQ.full = false;
	uLogQ.empty = true;
	for(uint8_t i = 0; i < UART_LOG_Q_SIZE; i++){
		uLogQ.msgs[i].data = NULL;
		uLogQ.msgs[i].size = 0;
		uLogQ.msgs[i].type = 0;
		
		logEntry[i].text = NULL;
		logEntry[i].data = NULL;
	}
	uLogQ.head = 0;
	uLogQ.tail = 0;
	transmitStep = 0;
	LOG_STEP = 0;
	HAL_UART_RegisterCallback(&huart1,HAL_UART_TX_COMPLETE_CB_ID, UL_Continue);
}

uint8_t LOG_GetErrors(uint16_t startEntry){
	if (sysParams.vars.status.flags.RAMInited != 1){
		return 0;
	}
	if (sysParams.consts.storedEntryNum > 0){
		processing = true;
		uint8_t size = MIN(sysParams.consts.storedEntryNum - startEntry,LOG_DISPLAY_SIZE);
		
		while (FP_GetStoredLog(ERROR_SECTOR_ADDR + (sysParams.consts.storedEntryNum - size - startEntry)*sizeof(log_data_t),size*sizeof(log_data_t),displayData,processComplete) != HAL_OK);
		while(processing);

		return sysParams.consts.storedEntryNum;
	}
	return 0;
}

uint8_t LOG_GetWash(uint16_t startEntry){
	if (sysParams.vars.status.flags.RAMInited != 1){
		return 0;
	}
	if (sysParams.consts.storedWashNum > 0){
		processing = true;
		uint8_t size = MIN(sysParams.consts.storedWashNum - startEntry,LOG_DISPLAY_SIZE);
		
		while (FP_GetStoredLog(WASH_SECTOR_ADDR + (sysParams.consts.storedWashNum - size - startEntry)*sizeof(log_data_t),size*sizeof(log_data_t),displayData,processComplete) != HAL_OK);
		while(processing);

		return sysParams.consts.storedWashNum;
	}
	return 0;
}
uint8_t LOG_GetWaterUsage(uint16_t startEntry){
	uint32_t offset = 0;
	if (sysParams.vars.status.flags.RAMInited != 1){
		return 0;
	}
	if (sysParams.consts.storedDayValueNum > 0){
		processing = true;
		offset = startEntry;
		if (offset > 0){
			offset--;
		}
		uint8_t size = MIN(sysParams.consts.storedDayValueNum - offset,LOG_DISPLAY_SIZE);
		if (startEntry == 0 && size == 4){
			size--;
		}
		offset = size;
		if (startEntry > 0)
			offset += startEntry - 1;
		uint32_t sizeOfLog = sizeof(log_data_t);
		while (FP_GetStoredLog(WATER_QUANT_SECTOR_ADDR + (sysParams.consts.storedDayValueNum - offset)*sizeOfLog,size*sizeOfLog,displayData,processComplete) != HAL_OK);
		while(processing);
		if (startEntry == 0){
			displayData[size].timeStamp = LL_RTC_TIME_Get(RTC);
			displayData[size].param = sysParams.consts.dayWaterUsage;
		}
		return sysParams.consts.storedDayValueNum+1;
	} else {
		displayData[0].timeStamp = LL_RTC_TIME_Get(RTC);
		displayData[0].param = sysParams.consts.dayWaterUsage;
	}
	return 1;
}
uint8_t LOG_GetWaterSpeed(uint16_t startEntry){
	uint32_t offset = 0;
	if (sysParams.vars.status.flags.RAMInited != 1){
		return 0;
	}
	if (sysParams.consts.storedDayValueNum > 0){
		processing = true;
		offset = startEntry;
		if (offset > 0){
			offset--;
		}
		uint8_t size = MIN(sysParams.consts.storedDayValueNum - offset,LOG_DISPLAY_SIZE);
		if (startEntry == 0 && size == 4){
			size--;
		}
		offset = size;
		if (startEntry > 0)
			offset += startEntry - 1;
		while (FP_GetStoredLog(WATER_USAGE_SECTOR_ADDR + (sysParams.consts.storedDayValueNum - offset)*sizeof(log_data_t),size*sizeof(log_data_t),displayData,processComplete) != HAL_OK);
		while(processing);
		if (startEntry == 0){
			displayData[size].timeStamp = LL_RTC_TIME_Get(RTC);
			displayData[size].param = sysParams.consts.maxWaterUsage;
		}
		return sysParams.consts.storedDayValueNum+1;
	} else {
		displayData[0].timeStamp = LL_RTC_TIME_Get(RTC);
		displayData[0].param = sysParams.consts.maxWaterUsage;
	}
	return 1;
}
//uint8_t LOG_GetWater(uint16_t startEntry){
//	if (sysParams.consts.storedDayValueNum > 0){
//		processing = true;
//		uint32_t address = MAX_ADRESS - ((sysParams.consts.storedDayValueNum - startEntry))*sizeof(log_data_t);
//		if (sysParams.consts.storedDayValueNum < 8){
//			while (FP_GetStoredLog(address,sysParams.consts.storedDayValueNum*sizeof(log_data_t),displayData,processComplete)!= HAL_OK);
//			
//		} else {
//			while (FP_GetStoredLog(address,8*sizeof(log_data_t),displayData,processComplete)!= HAL_OK);
//		}
//		while(processing);
//		return sysParams.consts.storedDayValueNum;
//	}
//	return 0;
//}


bool addEntry (log_data_t entry){
	if (entry.cause == 0 && 
			entry.param == 0 && 
	entry.timeStamp == 0){
		errorCause = "Empty entry";
		Error_Handler();
	}
	logFifo[fifoEntryNum] = entry;
	fifoEntryNum++;
	uint8_t sizeMul = sizeof(log_data_t);
	if (checkErrorEmptySpace() - fifoEntryNum == 1){
		SaveErrors(fifoEntryNum*sizeMul,sysParams.consts.storedEntryNum*sizeMul,logFifo);
		sysParams.vars.error.flags.RAMFull = 1;
		return false;
	}
	if (fifoEntryNum == (sizeof(logFifo)/sizeof(log_data_t))){
		SaveErrors(fifoEntryNum*sizeMul,sysParams.consts.storedEntryNum*sizeMul,logFifo);
		return false;
	}
	else
		return true;
}




HAL_StatusTypeDef LOG_Interrupt(void){
	if (sysParams.vars.status.flags.AllInited == 0){
		return HAL_BUSY;
	}
	sys_status_flags_t tempFlags;
	sys_error_flags_t tempError;
	sys_error_flags_t error;
	
	/**/
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
	if (oldDay == 0){
		oldDay = sysParams.vars.sysTime.day; 
	}
	
	switch (LOG_STEP){
		case 0: {
			if (sysParams.vars.status.flags.LogWash){
				if (StoreWashEvent() == HAL_OK){
					washSave++;
					oldStatus = sysParams.consts.planerConsts.status;
					sysParams.vars.status.flags.LogWash = false;
				}
			}
			LOG_STEP = 2;
			break;
		}
		case 1: {
			
			break;
		}
		case 2: {
			lastSave = intToWTCTime(sysParams.consts.waterUsageLastTimeSave);
	
			if (sysParams.vars.sysTime.year != lastSave.year ||
				sysParams.vars.sysTime.month != lastSave.month ||
			sysParams.vars.sysTime.day != lastSave.day){
				if (StoreDayValues() == HAL_OK){
					sysParams.consts.waterUsageLastTimeSave = LL_RTC_TIME_Get(RTC);
					//lastSave = intToWTCTime(sysParams.consts.waterUsageLastTimeSave);
					LOG_STEP = 3;
				}
			}
			break;
		}
		case 3: {
			tempFlags.all = oldFlags.all ^ sysParams.vars.status.all; 
			tempError.all = oldErrors.all ^ sysParams.vars.error.all;
			tempFlags.all = tempFlags.all & sysParams.vars.status.all;
			tempError.all = tempError.all & sysParams.vars.error.all;
			
			uint32_t timeStamp = LL_RTC_TIME_Get(RTC);
			uint32_t cause;
			
		//	if(tempError.flags.RAMFull == 1){
		//		error.all = 0;
		//		error.flags.RAMFull = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,0})){
		//			oldErrors.flags.RAMFull = 1;
		//			return HAL_ERROR;
		//		} 
		//	}
			
		//	if(tempFlags.flags.AllInited == 1){
		//		error.all = 0;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,sysParams.vars.rtcTime})){
		//			oldFlags.flags.AllInited = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	} 
			
		//	if(tempError.flags.mainPowerFail == 1){
		//		error.all = 0;
		//		error.flags.mainPowerFail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,sysParams.vars.adc.rawADC[Vin]})){
		//			oldErrors.flags.mainPowerFail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	} 
			
		//	if(tempError.flags.BatteryFail == 1){
		//		error.all = 0;
		//		error.flags.BatteryFail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,sysParams.vars.adc.rawADC[Vbat]})){
		//			oldErrors.flags.BatteryFail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	} 
		//	if(tempError.flags._5VPowerFail == 1){
		//		error.all = 0;
		//		error.flags._5VPowerFail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,sysParams.vars.adc.rawADC[_5V]})){
		//			oldErrors.flags._5VPowerFail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	} 
		//	if(tempError.flags.RelPowerFail == 1){
		//		error.all = 0;
		//		error.flags.RelPowerFail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,sysParams.vars.adc.rawADC[VrelDC]})){
		//			oldErrors.flags.RelPowerFail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	}
		//	if(tempError.flags.TempFail == 1){
		//		error.all = 0;
		//		error.flags.TempFail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,sysParams.vars.adc.rawADC[Temp]})){
		//			oldErrors.flags.TempFail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	}
			
		//	if(tempError.flags.Drive1Fail == 1){
		//		error.all = 0;
		//		error.flags.Drive1Fail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,0})){
		//			oldErrors.flags.Drive1Fail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	}
		//	if(tempError.flags.Drive2Fail == 1){
		//		error.all = 0;
		//		error.flags.Drive2Fail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,0})){
		//			oldErrors.flags.Drive2Fail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	}
		//	if(tempError.flags.MotorFail == 1){
		//		error.all = 0;
		//		error.flags.MotorFail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,0})){
		//			oldErrors.flags.MotorFail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	}
			
			if(tempError.flags.PistonStallFail == 1){
				error.all = 0;
				error.flags.PistonStallFail = 1;
				cause = error.all;
				if (addEntry((log_data_t){timeStamp,cause,sysParams.vars.pistonParams.curPoz})){
					oldErrors.flags.PistonStallFail = 1;
				} else {
					return HAL_OK;
				}
			}
			if(tempError.flags.PistonLongRun == 1){
				error.all = 0;
				error.flags.PistonLongRun = 1;
				cause = error.all;
				if (addEntry((log_data_t){timeStamp,cause,sysParams.vars.pistonParams.curPoz})){
					oldErrors.flags.PistonLongRun = 1;
				} else {
					return HAL_OK;
				}
			}
			
		//	if(tempError.flags.PistonFail == 1){
		//		error.all = 0;
		//		error.flags.PistonFail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,sysParams.vars.pistonParams.curPoz})){
		//			oldErrors.flags.PistonFail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//		oldErrors.flags.PistonFail = 1;
		//	} 		
			
		//	if(tempError.flags.RelayDCFail == 1){
		//		error.all = 0;
		//		error.flags.RelayDCFail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,sysParams.vars.status.flags.RelDCOn})){
		//			oldErrors.flags.RelayDCFail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	}
		//	if(tempError.flags.RelayACFail == 1){
		//		error.all = 0;
		//		error.flags.RelayACFail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,sysParams.vars.status.flags.RelACOn})){
		//			oldErrors.flags.RelayACFail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	}
			
		//	if(tempError.flags.TFTFail == 1){
		//		error.all = 0;
		//		error.flags.TFTFail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,0})){
		//			oldErrors.flags.TFTFail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	}	
		//	if(tempError.flags.TouchFail == 1){
		//		error.all = 0;
		//		error.flags.TouchFail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,0})){
		//			oldErrors.flags.TouchFail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	}
		//	if(tempError.flags.FRAMFail == 1){
		//		error.all = 0;
		//		error.flags.FRAMFail = 1;
		//		cause = error.all;
		//		if (addEntry((log_data_t){timeStamp,cause,0})){
		//			oldErrors.flags.FRAMFail = 1;
		//		} else {
		//			return HAL_OK;
		//		}
		//	} 	
			
			if (fifoEntryNum){
				SaveErrors(fifoEntryNum*sizeof(log_data_t),sysParams.consts.storedEntryNum*sizeof(log_data_t),logFifo);
			}
			LOG_STEP = 0;
			break;
		}
	}
	
	
	
	//if (oldStatus != sysParams.consts.planerConsts.status && sysParams.consts.planerConsts.status == PL_WORKING){
	
}

uint8_t StoreWashEvent(void){
	HAL_StatusTypeDef res;
//if (processing)
//	return HAL_BUSY;
	
	if (oldErrors.flags.RAMFull == 1 ||
		oldErrors.flags.RAMFail == 1)
		return HAL_ERROR;
	uint8_t sizeMul = sizeof(log_data_t);
	
	processing = true;
	washEvent.timeStamp = LL_RTC_TIME_Get(RTC);
	washEvent.cause = sysParams.consts.planerConsts.currentTaskNum;
	res = FP_StoreLog(WASH_SECTOR_ADDR+sysParams.consts.storedWashNum*sizeMul,sizeMul,&washEvent,processComplete, WASH_SECTOR_ADDR);
	if (res == HAL_OK){
		sysParams.consts.storedWashNum++;
	} 
	return res;
}

HAL_StatusTypeDef SaveErrors (uint32_t size, uint32_t adress, uint8_t *buf){
	HAL_StatusTypeDef res;
	
	if (oldErrors.flags.RAMFull == 1 ||
		oldErrors.flags.RAMFail == 1)
		return HAL_ERROR;
	uint8_t sizeMul = sizeof(log_data_t);
	if (fifoEntryNum > 0){
		
		processing = true;
		res = FP_StoreLog(adress,size,buf,processComplete, 0);
		if (res == HAL_OK){
			sysParams.consts.storedEntryNum += size/sizeMul;
			if (washSave){
				sysParams.consts.storedWashNum += washSave;
				washSave = 0;
			}
		} 
		return res;
	}
	return HAL_OK;
}
uint8_t StoreDayValues(void){
	if (sysParams.vars.error.flags.RAMFull == 1 ||
		sysParams.vars.error.flags.RAMFail == 1)
		return HAL_ERROR;
	if (sysParams.consts.storedDayValueNum == DAYS_TO_STORE){
		sysParams.vars.error.flags.RAMFull = 1;
		return HAL_ERROR;
	}
	if (processing)
		return HAL_BUSY;
	//while(processing);
	processing = true;
	
	dayValues[1].timeStamp = dayValues[0].timeStamp = sysParams.consts.waterUsageLastTimeSave;
	dayValues[0].param = sysParams.consts.maxWaterUsage;
	
	dayValues[1].param = sysParams.consts.dayWaterUsage;
	uint8_t size = sizeof(dayValues)/sizeof(log_data_t);
		
	while(FP_StoreLog(WATER_USAGE_SECTOR_ADDR + (sysParams.consts.storedDayValueNum)*sizeof(log_data_t),
							sizeof(log_data_t),
							&dayValues[0],
							processComplete,
							WATER_USAGE_SECTOR_ADDR) != HAL_OK);

	while(FP_StoreLog(WATER_QUANT_SECTOR_ADDR + (sysParams.consts.storedDayValueNum)*sizeof(log_data_t),
							sizeof(log_data_t),
							&dayValues[1],
							processComplete,
							WATER_QUANT_SECTOR_ADDR) != HAL_OK);
							
	sysParams.consts.storedDayValueNum++;
	sysParams.consts.maxWaterUsage = 0;
	sysParams.consts.dayWaterUsage = 0;
							
	return HAL_OK;
}

uint32_t checkErrorEmptySpace(){
	uint32_t res = (WASH_SECTOR_ADDR-ERROR_SECTOR_ADDR)/sizeof(log_data_t) - sysParams.consts.storedEntryNum;
	return res;
}
uint32_t checkWashEmptySpace(){
	uint32_t res = (WATER_QUANT_SECTOR_ADDR - WASH_SECTOR_ADDR)/sizeof(log_data_t) - sysParams.consts.storedWashNum;
	return res;
}
void processComplete (void){
	processing = false;
}

bool UL_LogText (uint8_t* text, uint32_t data){
	return 0;
	if (uLogQ.full){
		return false;
	}
	
	uLogQ.empty = false;
	
	uint8_t curMsgNum = uLogQ.head++;
	
	if (uLogQ.head > UART_LOG_Q_SIZE-1){
		uLogQ.head = 0;
	}
	if (uLogQ.head == uLogQ.tail){
		uLogQ.full = true;
	}
	uLogQ.msgs[curMsgNum].type = MSG;
	
	uLogQ.msgs[curMsgNum].data = &logEntry[curMsgNum];
	logEntry[curMsgNum].text = text;
	logEntry[curMsgNum].data = data;
	uint8_t* ptr = text;
	uint8_t size = 0;
	
	while (*ptr++) size++ ;
	
	uLogQ.msgs[curMsgNum].size = size + sizeof(data);
	
	UL_Start();
}

bool UL_LogCond (void){
	return 0;
	if (uLogQ.full){
		return false;
	}
	uint8_t curMsgNum = uLogQ.head++;
	uLogQ.empty = false;
	if (uLogQ.head > UART_LOG_Q_SIZE-1){
		uLogQ.head = 0;
	}
	if (uLogQ.head == uLogQ.tail){
		uLogQ.full = true;
	}
	uLogQ.msgs[curMsgNum].type = STR;
	
	uLogQ.msgs[curMsgNum].data = &sysParams;

	uLogQ.msgs[curMsgNum].size = sizeof(sysParams);
	
//	uLogQ.msgs[curMsgNum].data = &sysParams.vars.sysTime;

//	uLogQ.msgs[curMsgNum].size = sizeof(sysParams.vars.sysTime);
	
	UL_Start();
}


void UL_Start (void){
	if (uLogQ.empty == true){
		return;
	}
	if (HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY){
		return;
	}
	transmitStep = 0;
	header[0] = uLogQ.msgs[uLogQ.tail].type;
	header[1] = uLogQ.msgs[uLogQ.tail].size;
	uint8_t res = HAL_UART_Transmit_IT(&huart1,
					&header,
					2);
	if (res != HAL_OK){
		errorCause = "UART transmit error"; 
		Error_Handler();
	}

}

void UL_Continue (UART_HandleTypeDef *huart){
	
	if (uLogQ.msgs[uLogQ.tail].type == MSG){
		switch (transmitStep){
			case 0:{
				ulog_entry_t* data = (ulog_entry_t*)(uLogQ.msgs[uLogQ.tail].data);
				uint8_t res = HAL_UART_Transmit_IT(&huart1,
				data->text,
				uLogQ.msgs[uLogQ.tail].size - sizeof(uLogQ.msgs[uLogQ.tail].data));
			if (res == HAL_OK){
				transmitStep++;
			} else {
				errorCause = "UART transmit error"; 
				Error_Handler();
			}
				break;
			}
			case 1:{
				ulog_entry_t* data = (ulog_entry_t*)(uLogQ.msgs[uLogQ.tail].data);
				uint8_t res = HAL_UART_Transmit_IT(&huart1,
											&data->data,
											sizeof(uLogQ.msgs[uLogQ.tail].data));
				if (res == HAL_OK){
					transmitStep++;
				} else {
					errorCause = "UART transmit error"; 
					Error_Handler();
				}
					break;
				}

			case 2:{
				uLogQ.tail++;
				if (uLogQ.tail > UART_LOG_Q_SIZE-1){
					uLogQ.tail = 0;
				}
				if (uLogQ.head == uLogQ.tail){
					uLogQ.empty = true;
				}
				
				uLogQ.full = false;
				
				UL_Start();
				break;
			}
			default:{
				errorCause = "Wrong transmitStep"; 
				Error_Handler();
			}
		}
		return;
	} 
	if (uLogQ.msgs[uLogQ.tail].type == STR){
		switch (transmitStep){
			case 0:{
				uint8_t res = HAL_UART_Transmit_IT(&huart1,
				uLogQ.msgs[uLogQ.tail].data,
				uLogQ.msgs[uLogQ.tail].size);
			if (res == HAL_OK){
				transmitStep++;
			} else {
				errorCause = "UART transmit error"; 
				Error_Handler();
			}
				break;
			}
			case 1:{
				uLogQ.tail++;
				if (uLogQ.tail > UART_LOG_Q_SIZE-1){
					uLogQ.tail = 0;
				}
				if (uLogQ.head == uLogQ.tail){
					uLogQ.empty = true;
				}
				
				uLogQ.full = false;
				
				UL_Start();
				break;
			}
			default:{
				errorCause = "Wrong transmitStep"; 
				Error_Handler();
			}
		}
	}
	if (uLogQ.msgs[uLogQ.tail].type == DATA){
		switch (transmitStep){
			case 0:{
//				memSize = MIN(256,memAdr - memAdr);
//				transmitStep = 1;
				FP_Manual_RAM_Read(&memBuf, memAdr, 256, (void (*)(void))UL_Continue);
				
				break;
			}
			case 1:{
				memAdr += memSize;
				
				uint8_t res = HAL_UART_Transmit_IT(&huart1,
				&memBuf,
				256);
				
				if (res == HAL_OK){
//					if (memAdr + memSize >= MAX_RAM_ADDRESS){
//						transmitStep = 2;
//					} else {
//						transmitStep = 0;
//					}
					transmitStep = 2;
				} else {
					errorCause = "UART transmit error"; 
					Error_Handler();
				}
				break;
			}
			case 2:{
				uLogQ.tail++;
				if (uLogQ.tail > UART_LOG_Q_SIZE-1){
					uLogQ.tail = 0;
				}
				if (uLogQ.head == uLogQ.tail){
					uLogQ.empty = true;
				}
				
				uLogQ.full = false;
				
				UL_Start();
				break;
			}
			default:{
				errorCause = "Wrong transmitStep"; 
				Error_Handler();
			}
		}
	}
	return;
}

bool UL_StartMemoryRead(uint32_t adr){
	if (uLogQ.full){
		return false;
	}
	uint8_t curMsgNum = uLogQ.head++;
	uLogQ.empty = false;
	if (uLogQ.head > UART_LOG_Q_SIZE-1){
		uLogQ.head = 0;
	}
	if (uLogQ.head == uLogQ.tail){
		uLogQ.full = true;
	}
	uLogQ.msgs[curMsgNum].type = DATA;
	uLogQ.msgs[curMsgNum].size = 512;
	memAdr = adr;
	UL_Start();
}
	#include "FlashIC/W25.h"
uint8_t recBuf[24];
void LOG_Test(){
	flash_driver_t *drv = &W25_driver;
	while (1){
		
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

