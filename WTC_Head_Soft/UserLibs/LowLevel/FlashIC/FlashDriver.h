#ifndef _Flash_Driver_
#define _Flash_Driver_

/*Includes*/
#include "main.h"
/*Typedef*/
	typedef struct{
		uint8_t status;
		HAL_StatusTypeDef (*init) (SPI_HandleTypeDef* SPI, gpio_t csPin, gpio_t wpPin, gpio_t holdPin);
		HAL_StatusTypeDef (*readData) (uint16_t addr, uint8_t* buf, uint32_t size);
		HAL_StatusTypeDef (*writeData) (uint16_t addr, uint8_t* buf, uint32_t size);
	} flash_driver_t;
/*Extern parameters*/

/*Prototypes*/

#endif //_Flash_Driver_