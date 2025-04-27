/*Includes*/
#include "W25.h"

/*Local prototypes*/
static HAL_StatusTypeDef init (SPI_HandleTypeDef* SPI, gpio_t csPin, gpio_t wpPin, gpio_t holdPin, void (*callBack) (void));
static HAL_StatusTypeDef readData (uint32_t addr, uint8_t* buf, uint32_t size);
static HAL_StatusTypeDef writeData (uint32_t addr, uint8_t* buf, uint32_t size);
static HAL_StatusTypeDef abortCom (void);
static void commEndW25 (SPI_HandleTypeDef *hspi);
static HAL_StatusTypeDef eraseChip (void);
static HAL_StatusTypeDef readStatus(void);
static bool isBusy (void);
static void readID(void);
static void partWriteData (SPI_HandleTypeDef *hspi);




/*Macro and defines*/
#define SECTOR_SIZE 4096
#define PACKET_SIZE 256
#define RESET_DELAY 1


/*COMMANDS*/
#define WREN		0x06
#define VSRWREN 0x50
#define WRDI		0x04
#define RDSR1		0x05
#define WRSR1		0x01
#define RDSR2		0x05
#define WRSR2		0x01
#define RDSR3		0x05
#define WRSR3		0x01
#define CHER		0xC7 //0x60
#define JEDID		0x9F
#define RES			0x99
#define S4ER		0x20
#define S32ER		0x52
#define	S64ER		0xD8
#define READ		0x0B//0x03
#define WRITE		0x02

#define MAX

#define UPPER_QUARTER 0x600
#define UPPER_HALF 		0x400
#define MAX_ADR 			0x7FF

/*Global parameters*/
	flash_driver_t W25_driver = 
	{
		0,
		init,
		readData,
		writeData,
		abortCom,
		eraseChip
	};
	
	static SPI_HandleTypeDef* spi;
	static gpio_t wpGpio, csGpio, holdGpio;
	static uint8_t commandBuffer[5];
	w25_status1_t w25Status;
	w25_status2_t w25Status2;
w25_status3_t w25Status3;
	static uint32_t ID;
	static void (*cb) (void);
	
	static uint32_t addressToContinue;
	static uint8_t* bufStartPtr;
	static uint32_t remWriteSize; 
	static SPI_InitTypeDef oldSPIConfig;
/*Code*/
	HAL_StatusTypeDef abortCom (void){
	HAL_SPI_Abort(MEM_SPI);
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	commEndW25(MEM_SPI);
}
	
HAL_StatusTypeDef init (SPI_HandleTypeDef* SPI, gpio_t csPin, gpio_t wpPin, gpio_t holdPin, void (*callBack) (void)){
	HAL_StatusTypeDef halSt;
	uint8_t tryCnt = 0;
	spi = SPI;
	wpGpio = wpPin;
	csGpio = csPin;
	holdGpio = holdPin;
	cb = callBack;
	
	LL_GPIO_SetOutputPin(wpGpio.port,wpGpio.pin);
	LL_GPIO_SetOutputPin(holdGpio.port,holdGpio.pin);
	LL_mDelay(10);
	//Read ID
	
	commandBuffer[0] = JEDID;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,1,10);
	if (halSt != HAL_OK){
		commEndW25(spi);
		return halSt;
	} 
	halSt = HAL_SPI_Receive(spi,&ID,3,10);
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	
	#ifdef PROD_TEST
	commandBuffer[0] = WREN;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,1,10);
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	
	commandBuffer[0] = S32ER;
	commandBuffer[1] = 0x00;
	commandBuffer[2] = 0x00;
	commandBuffer[3] = 0x00;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,4,10);
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	
	while (isBusy()){
			LL_mDelay(100);
	}
	#endif
	
	return halSt;
}


HAL_StatusTypeDef readData (uint32_t addr, uint8_t* buf, uint32_t size){
	HAL_StatusTypeDef halSt;
	if (HAL_SPI_GetState(spi) != HAL_SPI_STATE_READY)
		return HAL_BUSY;
	while((isBusy()));
//		return HAL_BUSY;
	
	commandBuffer[0] = READ;
	commandBuffer[1] = (uint8_t)((addr & 0x00FF0000) >> 16);
	commandBuffer[2] = (uint8_t)((addr & 0x0000FF00) >> 8);
	commandBuffer[3] = (uint8_t) (addr & 0x000000FF);
	commandBuffer[4] = 0;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,5,10);
	if (halSt != HAL_OK){
		commEndW25(spi);
		return halSt;
	} 
	HAL_SPI_RegisterCallback(spi,HAL_SPI_RX_COMPLETE_CB_ID, commEndW25);
	halSt = HAL_SPI_Receive_DMA(spi,buf,size);
	if (halSt != HAL_OK){
		commEndW25(spi);
		return halSt;
	} 
	
	return HAL_OK;
}

HAL_StatusTypeDef writeData (uint32_t addr, uint8_t* buf, uint32_t size){
	HAL_StatusTypeDef halSt;
	if (HAL_SPI_GetState(spi) != HAL_SPI_STATE_READY)
		return HAL_BUSY;
	while (isBusy());
	
	addressToContinue = addr;
	bufStartPtr = buf;
	remWriteSize = size;
	
//	halSt = readStatus();
//	if (halSt != HAL_OK)
//		return halSt;
	while (isBusy());
	partWriteData(spi);
	
	return HAL_OK;
}

void partWriteData (SPI_HandleTypeDef *hspi){
	HAL_StatusTypeDef halSt;
	bool continueWrite;
	uint32_t addr;
	uint8_t* buf;
	uint32_t size;
	uint32_t lowAddr;
	
	addr = addressToContinue;
	lowAddr = addressToContinue&0x000000FF;
	uint16_t pageRemainSpace;
	
	pageRemainSpace = 0x100 - lowAddr;

	
	buf = bufStartPtr;
	size = MIN(pageRemainSpace,remWriteSize);
	remWriteSize -= size;
	continueWrite = (remWriteSize > 0)?true:false;
	
	bufStartPtr = bufStartPtr+size;
	addressToContinue += size;
	
	readStatus();
	if (w25Status.bits.WEL != 1){
		
		commandBuffer[0] = WREN;
		LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
		halSt = HAL_SPI_Transmit(spi,commandBuffer,1,10);
		LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
			
		//readStatus();
	}
	
	//readStatus();
	commandBuffer[0] = WRITE;
	commandBuffer[1] = (uint8_t)((addr & 0x00FF0000) >> 16);
	commandBuffer[2] = (uint8_t)((addr & 0x0000FF00) >> 8);
	commandBuffer[3] = lowAddr;
	
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	
	halSt = HAL_SPI_Transmit(spi,commandBuffer,4,10);
	if (continueWrite){
		HAL_SPI_RegisterCallback(spi,HAL_SPI_TX_COMPLETE_CB_ID, partWriteData);
	} else {
		HAL_SPI_RegisterCallback(spi,HAL_SPI_TX_COMPLETE_CB_ID, commEndW25);
	}
	halSt = HAL_SPI_Transmit_DMA(spi,buf,size);
	
	return;
}

HAL_StatusTypeDef readStatus(void){
	HAL_StatusTypeDef halSt;
	
	commandBuffer[0] = RDSR1;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,1,10);
	halSt = HAL_SPI_Receive(spi,&w25Status,1,10);
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	commandBuffer[0] = RDSR2;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,1,10);
	halSt = HAL_SPI_Receive(spi,&w25Status2,1,10);
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	commandBuffer[0] = RDSR3;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,1,10);
	halSt = HAL_SPI_Receive(spi,&w25Status3,1,10);
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	return halSt;
}

void commEndW25 (SPI_HandleTypeDef *hspi){
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	HAL_SPI_UnRegisterCallback(spi,HAL_SPI_TX_COMPLETE_CB_ID);
	HAL_SPI_UnRegisterCallback(spi,HAL_SPI_RX_COMPLETE_CB_ID);
	if (cb != NULL)
		cb();
}

bool isBusy (void){
	if (readStatus() != HAL_OK){
		return true;
	}
	
	return w25Status.bits.BUSY;
}

void readID(void){
	HAL_StatusTypeDef halSt;
	
	commandBuffer[0] = JEDID;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,1,10);
	
}

HAL_StatusTypeDef eraseChip (void){
	HAL_StatusTypeDef halSt;
	
	commandBuffer[0] = WREN;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,1,10);
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	
	commandBuffer[0] = CHER;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,1,10);
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	if (halSt != HAL_OK)
		return halSt;
	else {
		while (isBusy()){
			LL_mDelay(100);
		}
		if (cb != NULL)
			cb();
		return HAL_OK;
	}
}
