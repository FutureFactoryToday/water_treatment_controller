/**
  ******************************************************************************
  * @file           : TFT.c
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
/* Private includes ----------------------------------------------------------*/
#include "Settings.h"
#include "TFT_Commands.h"
/* Private typedef -----------------------------------------------------------*/
#ifndef TFT_SPI 
#error "SPI for TFT Display not specified"
#endif
#ifndef TOUCH_SPI 
#error "SPI for Touch controller not specified"
#endif
#ifdef ALLOW_TFT_DMA
	#ifndef TFT_DMA 
	#error "DMA for TFT Display not specified"
	#endif
#endif
#ifdef ALLOW_TOUCH_DMA
	#ifndef TOUCH_DMA 
	#error "DMA for Touch controller not specified"
	#endif
#endif
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
#define WAIT_TRANSMIT while (LL_SPI_IsActiveFlag_BSY(TFT_SPI));

/* Private variables ---------------------------------------------------------*/
tftStatus_t tftStatus;
/* Private function prototypes -----------------------------------------------*/
uint32_t spiManualSend (uint32_t size, uint8_t *data);
uint32_t spiDMASend (uint32_t size, uint8_t *data);
uint32_t spiITSend (uint32_t size, uint8_t *data);
uint16_t* spiManualReceive (uint32_t size, uint8_t *data);
uint16_t* spiDMAReceive (uint32_t size, uint8_t *data);
uint16_t* spiITReceive (uint32_t size, uint8_t *data);
void rebootTFT (void);
void enableTFTCommunication(void);
void disableTFTCommunication(void);
void selectData (void);
void selectCommand (void);
void readStrobe (void);
void writeStrobe (void);
void SetParalPortOutput(void);
void SetParalPortInput(void);
/* Private user code ---------------------------------------------------------*/

/******* Функции для SPI дисплея *******/

/*
	Отправка данных с помощью SPI с ожиданием окончания в цикле
	size - размер данных для отправки
	*data - буфер с данными для отправки
*/
uint32_t spiManualSend (uint32_t size, uint8_t *data){
	
	if (tftStatus.busy == 0 && 
		tftStatus.inited == 1 && 
		tftStatus.type == SPI)
	{
		enableTFTCommunication();
		tftStatus.busy = 1;
		for(uint32_t i = 0; i < size; i++){
			LL_SPI_TransmitData8(TFT_SPI,*data++);
			WAIT_TRANSMIT;
		}
		disableTFTCommunication();
		tftStatus.busy = 0;
		return 1;
	}
	else {
		return 0;
	}
}

/*
	Отправка данных с помощью SPI через DMA
	size - размер данных для отправки
	*data - буфер с данными для отправки
*/
uint32_t spiDMASend (uint32_t size, uint8_t *data){
	
	return 0;
}

/*
	Отправка данных с помощью SPI через прерывания
	size - размер данных для получения
	*data - буфер с данными для получения
*/
uint32_t spiITSend (uint32_t size, uint8_t *data){
	
	return 0;
}

/*
	Получение данных с помощью SPI с ожиданием окончания в цикле
	size - размер данных для получения
	*data - буфер с данными для получения
*/
uint16_t* spiManualReceive (uint32_t size, uint8_t *data){
	
	
	return NULL;
}

/*
	Получение данных с помощью SPI через DMA
	size - размер данных для получения
	*data - буфер с данными для получения
*/
uint16_t* spiDMAReceive (uint32_t size, uint8_t *data){
	
	return NULL;
}

/*
	Получение данных с помощью SPI через прерывания
	size - размер данных для получения
	*data - буфер с данными для получения
*/
uint16_t* spiITReceive (uint32_t size, uint8_t *data){
	
	return NULL;
}

/******* Функции для параллельного дисплея *******/
/*
	Чтение данных/команд через параллельный порт
	size - размер данных на передачу
	*data - буффер для данных
	dataType - тип данных
		DATA - данные
		COMMAND - команда
*/
uint32_t manualParalRead(uint32_t size, uint8_t *data, uint8_t dataType){
	if (tftStatus.busy == 0 &&
			tftStatus.inited == 1 &&
			tftStatus.type == PARAL){
		enableTFTCommunication();
		if (dataType == DATA){
			selectData();
		} 
		if (dataType == COMMAND){
			selectCommand();
		} else {
			disableTFTCommunication();
			return 0;
		}
		SetParalPortInput();
		for (uint32_t i = 0; i <size; i++){
			writeStrobe();
			*data = LL_GPIO_ReadInputPort(TFT_PATAL_PORT);
			data++;
		}
		disableTFTCommunication();
		return 1;
	}
	else{
		
		return 0;
	}
}
/*
	Отправка данных/команд через параллельный порт
	size - размер данных на прием
	*data - буффер с данными
	dataType - тип данных
		DATA - данные
		COMMAND - команда
*/
uint32_t manualParalSend (uint32_t size, uint8_t *data, uint8_t dataType){
	if (tftStatus.busy == 0 &&
			tftStatus.inited == 1 &&
			tftStatus.type == PARAL){
		enableTFTCommunication();
		if (dataType == DATA){
			selectData();
		} 
		if (dataType == COMMAND){
			selectCommand();
		} else {
			disableTFTCommunication();
			return 0;
		}
		SetParalPortOutput();
		for (uint32_t i = 0; i <size; i= i+2){
			uint16_t tempData = (*data++) << 8;
			tempData &= 0xFF00;
			tempData |= *data++;
			LL_GPIO_WriteOutputPort(TFT_PATAL_PORT, tempData);
			writeStrobe();
		}
		disableTFTCommunication();
		return 1;
	}
	else{
		
		return 0;
	}
}
/*
	Отправка данных через параллельную шину с помощью прерывания (TIM2 или TIM5)
	size - размер данных на передачу
	*data - буффер с данными
	dataType - тип данных
		DATA - данные
		COMMAND - команда
*/
uint32_t paralItSend (uint32_t size, uint8_t *data, uint32_t dataType){
	
	return 0;
}

/*
	Отправка данных через параллельную шину с помощью DMA и прерывания (TIM2 или TIM5)
	size - размер данных на передачу
	*data - буффер с данными
	dataType - тип данных
		DATA - данные
		COMMAND - команда
*/
uint32_t paralDMASend (uint32_t size, uint8_t *data, uint32_t dataType){
	
	return 0;
}
/*
	Чтение данных через параллельную шину с помощью прерывания (TIM2 или TIM5)
	size - размер данных на прием
	*data - буффер для данных
	dataType - тип данных
		DATA - данные
		COMMAND - команда
*/

uint32_t paralItRead (uint32_t size, uint8_t *data, uint32_t dataType){
	
	return 0;
}

/*
	Чтение данных через параллельную шину с помощью DMA и прерывания (TIM2 или TIM5)
	size - размер данных на прием
	*data - буффер для данных
	dataType - тип данных
		DATA - данные
		COMMAND - команда
*/
uint32_t paralDMARead (uint32_t size, uint8_t *data, uint32_t dataType){
	
	return 0;
}

void SetParalPortOutput(void){
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DB0_Pin|DB1_Pin|DB2_Pin|DB10_Pin
                          |DB11_Pin|DB12_Pin|DB13_Pin|DB14_Pin|DB15_Pin
													|DB3_Pin|DB4_Pin|DB5_Pin|DB6_Pin|DB7_Pin|DB8_Pin
                          |DB9_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(TFT_PATAL_PORT, &GPIO_InitStruct);
}

void SetParalPortInput(){
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DB0_Pin|DB1_Pin|DB2_Pin|DB10_Pin
                          |DB11_Pin|DB12_Pin|DB13_Pin|DB14_Pin|DB15_Pin
													|DB3_Pin|DB4_Pin|DB5_Pin|DB6_Pin|DB7_Pin|DB8_Pin
                          |DB9_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  LL_GPIO_Init(TFT_PATAL_PORT, &GPIO_InitStruct);
}
/******* Общие функции *******/

/*
	Перезапуск дисплея
*/
void rebootTFT (void){
	LL_GPIO_ResetOutputPin(TFT_RES_GPIO_Port,TFT_RES_Pin);
	LL_mDelay(RESET_DELAY_MS);
	LL_GPIO_SetOutputPin(TFT_RES_GPIO_Port,TFT_RES_Pin);
}

/*
	Включение обмена с дисплеем (пин CSX low)
*/
void enableTFTCommunication(void){
	LL_GPIO_ResetOutputPin(TFT_COM_EN_GPIO_Port,TFT_COM_EN_Pin);
}

/*
	Отключения обмена с дисплеем (пин CSX high)
*/
void disableTFTCommunication(void){
	LL_GPIO_SetOutputPin(TFT_COM_EN_GPIO_Port,TFT_COM_EN_Pin);
}

/*
Выбор типа данных на шине: Данные (D/CX low)
*/
void selectData (void){
	LL_GPIO_SetOutputPin(TFT_DATA_COM_GPIO_Port,TFT_DATA_COM_Pin);
}

/*
Выбор типа данных на шине: Команда(D/CX high)
*/
void selectCommand (void){
	LL_GPIO_ResetOutputPin(TFT_DATA_COM_GPIO_Port,TFT_DATA_COM_Pin);
}

/*
Строб для записи данных
*/
void writeStrobe (void){
	LL_GPIO_ResetOutputPin(TFT_WR_GPIO_Port,TFT_WR_Pin);
	__ASM("nop");
	LL_GPIO_SetOutputPin(TFT_WR_GPIO_Port,TFT_WR_Pin);
}

/*
Строб для записи данных
*/
void readStrobe (void){
	LL_GPIO_ResetOutputPin(TFT_RD_GPIO_Port,TFT_RD_Pin);
	__ASM("nop");
	LL_GPIO_SetOutputPin(TFT_RD_GPIO_Port,TFT_RD_Pin);
}