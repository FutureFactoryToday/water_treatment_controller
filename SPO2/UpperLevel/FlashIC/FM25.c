/*Includes*/
#include "FM25.h"
/*Local prototypes*/
static HAL_StatusTypeDef init (SPI_HandleTypeDef* SPI, gpio_t csPin, gpio_t wpPin, gpio_t holdPin, void (*callBack) (void));
static bool detect (void);
static HAL_StatusTypeDef readData (uint32_t addr, uint8_t* buf, uint32_t size);
static HAL_StatusTypeDef writeData (uint32_t addr, uint8_t* buf, uint32_t size);
static HAL_StatusTypeDef abortCom (void);
static HAL_StatusTypeDef erase (void);
static void commEnd (SPI_HandleTypeDef *hspi);
/*Macro and defines*/
#define WREN	0x06
#define WRDI	0x04
#define RDSR	0x05
#define WRSR	0x01
#define READ	0x03
#define WRITE	0x02

#define WEL_BIT 	0x02
#define BP0 			0x04
#define BP1				0x08
#define WPEN_BIT	0x80

#define UPPER_QUARTER 0x600
#define UPPER_HALF 		0x400
#define MAX_ADR 			0x7FF
#define MAX_SIZE 			0x1000

/*Global parameters*/
	flash_driver_t FM25_driver = 
	{
		0,
		init,
		readData,
		writeData,
		abortCom,
		erase
	};
	
	static SPI_HandleTypeDef* spi;
	static gpio_t wpGpio, csGpio, holdGpio;
	static uint8_t commandBuffer[3];
	static void (*cb) (void);
	
/*Code*/
HAL_StatusTypeDef abortCom (void){
	HAL_SPI_Abort(MEM_SPI);
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	commEnd(MEM_SPI);
}

HAL_StatusTypeDef init (SPI_HandleTypeDef* SPI, gpio_t csPin, gpio_t wpPin, gpio_t holdPin, void (*callBack) (void)){
	spi = SPI;
	wpGpio = wpPin;
	csGpio = csPin;
	holdGpio = holdPin;
	cb = callBack;
	LL_GPIO_SetOutputPin(wpGpio.port,wpGpio.pin);
	LL_GPIO_SetOutputPin(holdGpio.port,holdGpio.pin);
	
	commandBuffer[0] = WREN;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	HAL_SPI_Transmit(spi, commandBuffer, 1, 10);
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	if (!detect()){
		return HAL_ERROR;
	}
	return HAL_OK;
}

bool detect (void){
	HAL_StatusTypeDef halSt;
	
	commandBuffer[0] = RDSR;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	
	halSt = HAL_SPI_Transmit(spi,&commandBuffer[0],1,10);
	if (halSt != HAL_OK){
		LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
		return 0;
	} 
	halSt = HAL_SPI_Receive(spi,&FM25_driver.status,1,10);
	if (halSt != HAL_OK){
		LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
		return 0;
	} 
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	if (!(FM25_driver.status & WEL_BIT)){
		return 0;
	}
	return 1;
}

HAL_StatusTypeDef readData (uint32_t addr, uint8_t* buf, uint32_t size){
	detect();
	HAL_StatusTypeDef halSt;
	if (spi->State == HAL_BUSY)
		return HAL_BUSY;
	commandBuffer[0] = READ;
	commandBuffer[1] = (uint8_t)((addr & 0xFF00) >> 8);
	commandBuffer[2] = (uint8_t) (addr & 0x00FF);
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,3,10);
	if (halSt != HAL_OK){
		commEnd(spi);
		return halSt;
	} 
	HAL_SPI_RegisterCallback(spi,HAL_SPI_RX_COMPLETE_CB_ID, commEnd);
	halSt = HAL_SPI_Receive_DMA(spi,buf,size);
	if (halSt != HAL_OK){
		commEnd(spi);
		return halSt;
	} 
	
	return HAL_OK;
}
HAL_StatusTypeDef writeData (uint32_t addr, uint8_t* buf, uint32_t size){
	
	HAL_StatusTypeDef halSt;
	if (spi->State == HAL_BUSY)
		return HAL_BUSY;
	commandBuffer[0] = WREN;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	HAL_SPI_Transmit(spi, commandBuffer, 1, 10);
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	commandBuffer[0] = WRITE;
	commandBuffer[1] = (uint8_t)((addr & 0xFF00) >> 8);
	commandBuffer[2] = (uint8_t) (addr & 0x00FF);
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,3,10);
	if (halSt != HAL_OK){
		commEnd(spi);
		return 0;
	} 
 
	HAL_SPI_RegisterCallback(spi,HAL_SPI_TX_COMPLETE_CB_ID, commEnd);
	halSt = HAL_SPI_Transmit_DMA(spi,buf,size);
	if (halSt != HAL_OK){
		commEnd(spi);
		return 0;
	} 

	return 1;
}

void commEnd (SPI_HandleTypeDef *hspi){
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	HAL_SPI_UnRegisterCallback(spi,HAL_SPI_TX_COMPLETE_CB_ID);
	HAL_SPI_UnRegisterCallback(spi,HAL_SPI_RX_COMPLETE_CB_ID);
	if (cb != NULL)
		cb();
}

/*NOT TESTED*/
HAL_StatusTypeDef erase (void){
	uint8_t data = 0xFF;
	HAL_StatusTypeDef halSt;
	if (spi->State == HAL_BUSY)
		return HAL_BUSY;
	commandBuffer[0] = WREN;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	HAL_SPI_Transmit(spi, commandBuffer, 1, 10);
	LL_GPIO_SetOutputPin(csGpio.port,csGpio.pin);
	commandBuffer[0] = WRITE;
	commandBuffer[1] = 0;
	commandBuffer[2] = 0;
	LL_GPIO_ResetOutputPin(csGpio.port,csGpio.pin);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,3,10);
	if (halSt != HAL_OK){
		commEnd(spi);
		return 0;
	} 
	for (uint16_t i = 0; i < MAX_SIZE; i++){
		halSt = HAL_SPI_Transmit(spi,&data,1,10);
		if (halSt != HAL_OK){
			commEnd(spi);
			return 0;
		} 
	}
	commEnd(spi);
	return 1;
}
