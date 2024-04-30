#ifndef _Flash_Driver_
#define _Flash_Driver_

/*Includes*/
#include "main.h"

/*Typedef*/
	typedef struct{
		uint8_t status;
		HAL_StatusTypeDef (*init) (SPI_HandleTypeDef* SPI, gpio_t csPin, gpio_t wpPin, gpio_t holdPin, void (*callBack) (void));
		HAL_StatusTypeDef (*readData) (uint32_t addr, uint8_t* buf, uint32_t size);
		HAL_StatusTypeDef (*writeData) (uint32_t addr, uint8_t* buf, uint32_t size);
		HAL_StatusTypeDef (*abortCom) (void);
		HAL_StatusTypeDef (*eraseChip)(void);
	} flash_driver_t;
/*Extern parameters*/

/*Prototypes*/

#endif //_Flash_Driver_