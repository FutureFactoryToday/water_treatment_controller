/*Includes*/
#include "FM25.h"
/*Local prototypes*/
static HAL_StatusTypeDef init (SPI_HandleTypeDef* SPI, gpio_t csPin, gpio_t wpPin, gpio_t holdPin);
static bool detect (void);
static HAL_StatusTypeDef readData (uint16_t addr, uint8_t* buf, uint32_t size);
static HAL_StatusTypeDef writeData (uint16_t addr, uint8_t* buf, uint32_t size);
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

/*Global parameters*/
	flash_driver_t FM25_driver = 
	{
		0,
		init,
		readData,
		writeData,
	};
	
	SPI_HandleTypeDef* spi;
	gpio_t wpGpio, csGpio, holdGpio;
	uint8_t commandBuffer[3];
	
/*Code*/
HAL_StatusTypeDef init (SPI_HandleTypeDef* SPI, gpio_t csPin, gpio_t wpPin, gpio_t holdPin){
	spi = SPI;
	wpGpio = wpPin;
	csGpio = csPin;
	holdGpio = holdPin;
	HAL_GPIO_WritePin(wpGpio.port,wpGpio.pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(holdGpio.port,holdGpio.pin, GPIO_PIN_SET);
	
	commandBuffer[0] = WREN;
	HAL_GPIO_WritePin(csGpio.port,csGpio.pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(spi, commandBuffer, 1, 10);
	HAL_GPIO_WritePin(csGpio.port,csGpio.pin, GPIO_PIN_SET);
	if (!detect()){
		return HAL_ERROR;
	}
	
}

bool detect (void){
	HAL_StatusTypeDef halSt;
	
	commandBuffer[0] = RDSR;
	HAL_GPIO_WritePin(csGpio.port,csGpio.pin, GPIO_PIN_RESET);
	
	halSt = HAL_SPI_Transmit(spi,&commandBuffer[0],1,10);
	if (halSt != HAL_OK){
		HAL_GPIO_WritePin(csGpio.port,csGpio.pin, GPIO_PIN_SET);
		return 0;
	} 
	halSt = HAL_SPI_Receive(spi,&FM25_driver.status,1,10);
	if (halSt != HAL_OK){
		HAL_GPIO_WritePin(csGpio.port,csGpio.pin, GPIO_PIN_SET);
		return 0;
	} 
	HAL_GPIO_WritePin(csGpio.port,csGpio.pin, GPIO_PIN_SET);
	if (!(FM25_driver.status & WEL_BIT)){
		return 0;
	}
	return 1;
}

HAL_StatusTypeDef readData (uint16_t addr, uint8_t* buf, uint32_t size){
	HAL_StatusTypeDef halSt;
	if (spi->State == HAL_BUSY)
		return HAL_BUSY;
	commandBuffer[0] = READ;
	commandBuffer[1] = (uint8_t)((addr & 0xFF00) >> 8);
	commandBuffer[2] = (uint8_t) (addr & 0x00FF);
	HAL_GPIO_WritePin(csGpio.port,csGpio.pin, GPIO_PIN_RESET);
	halSt = HAL_SPI_Transmit(spi,commandBuffer,3,10);
	if (halSt != HAL_OK){
		commEnd(spi);
		return halSt;
	} 
	
	halSt = HAL_SPI_Receive_DMA(spi,buf,size);
	if (halSt != HAL_OK){
		commEnd(spi);
		return halSt;
	} 
	
	return HAL_OK;
}
HAL_StatusTypeDef writeData (uint16_t addr, uint8_t* buf, uint32_t size){
	HAL_StatusTypeDef halSt;
	if (spi->State == HAL_BUSY)
		return HAL_BUSY;
	commandBuffer[0] = WRITE;
	commandBuffer[1] = (uint8_t)((addr & 0xFF00) >> 8);
	commandBuffer[2] = (uint8_t) (addr & 0x00FF);
	HAL_GPIO_WritePin(csGpio.port,csGpio.pin, GPIO_PIN_RESET);
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
	HAL_GPIO_WritePin(csGpio.port,csGpio.pin, GPIO_PIN_SET);
	HAL_SPI_UnRegisterCallback(spi,HAL_SPI_TX_COMPLETE_CB_ID);
}
