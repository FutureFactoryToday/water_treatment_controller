/**
  ******************************************************************************
  * @file           : TFT_LL.c
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
typedef struct {
	dataType_t dataType;
	readResult_t *result;
	uint16_t bufSize;
	dirType_t dir;
	uint8_t hold;
} msg_t;
/* Private macro -------------------------------------------------------------*/
#define WAIT_TRANSMIT while (LL_SPI_IsActiveFlag_BSY(TFT_SPI));
#define checkNull(a) do {if (a == NULL) return NULL;} while (0);

/* Private variables ---------------------------------------------------------*/
tftDriverStatus_t tftStatus;
handlerStatus_t handlerStatus;
msg_t *curMsg;
fifo_t* msgFifo;
uint16_t curEl;
uint8_t firstByte;
uint8_t dummyByte = 0xAA;
uint8_t step = 0;
uint8_t	tCnt = 0;
/* Private function prototypes -----------------------------------------------*/


perifType_t sendCommand (uint8_t *cmdBuf, uint8_t bufSize);
perifType_t sendData (uint8_t *dataBuf, uint16_t bufSize);
perifType_t receiveData (uint8_t *dataBuf, uint16_t bufSize);
perifType_t send (uint8_t *dataBuf, uint16_t bufSize);
perifType_t receive (uint8_t *dataBuf, uint16_t bufSize);


uint8_t transNewMsg(void);
uint8_t transCurMsg(void);

uint32_t spiManualSend (uint32_t size, uint8_t *data);
uint32_t spiDMASend (uint32_t size, uint8_t *data);
uint32_t spiITSend (uint32_t size, uint8_t *data);
uint16_t* spiManualReceive (uint32_t size, uint8_t *data);
uint16_t* spiDMAReceive (uint32_t size, uint8_t *data);
uint16_t* spiITReceive (uint32_t size, uint8_t *data);

void initDMA(void);
void enableTFTCommunication(void);
void disableTFTCommunication(void);
void selectData (void);
void selectCommand (void);
void readStrobe (void);
void writeStrobe (void);
void SetParalPortOutput(void);
void SetParalPortInput(void);
void finishTransmission(void);

void initPerifTFT(perifType_t type);
/* Private user code ---------------------------------------------------------*/
/*** Главные функции ***/
tftDriverStatus_t initTFT_LL(perifType_t type){
	msgFifo = initFifo();
	curMsg = NULL;
	curEl = 0;
	firstByte = 0;
	handlerStatus.DMA = 0;
	handlerStatus.ERR = 0;
	handlerStatus.INT = 0;
	handlerStatus.FREE = 1;
	
	tftStatus.BUSY = 0;
	tftStatus.TYPE = 0;
	tftStatus.ERROR = 0;
	tftStatus.INITED = 1;
	
	tftStatus.TYPE = type;
	initPerifTFT(type);
	
	return tftStatus;
}

uint8_t processMsg(readResult_t *result, uint8_t bufSize, dataType_t type, uint8_t dir, uint8_t hold){
	uint8_t opRes = 0;
	step = 1;
  if (bufSize != 0){
		msg_t* msg = (msg_t*)malloc(sizeof(msg_t));
		checkNull(msg);
		msg->dataType = type;
		msg->bufSize = bufSize;
		msg->result = result;
		msg->dir = dir;
		msg->hold = hold;
		checkNull(push(&msgFifo,msg));
		opRes = 1;
	}
	if (result && handlerStatus.FREE == 1) {
		step = 2;
		registerHandler(TFT_SPI, tftSpiHandler);
	}
	return opRes;
}

//Определяем ситуацию
	//1. SPI свободен - загружаем новое сообщение
handlerStatus_t tftSpiHandler(void){
	tCnt++;
	step = 3;
	//Еще не запускались
	if (tftStatus.BUSY == 0){
		if (!transNewMsg()){
			if (curMsg != NULL){
				curMsg->result->result = ERR;
			}
			handlerStatus.ERR = 1;
			handlerStatus.FREE = 1;
		}
		step = 4;
		handlerStatus.cnt = tCnt;
		return handlerStatus;
	}
	//Еще в процессе
	else {
		transCurMsg();
	}
	step = 5;
	handlerStatus.cnt = tCnt;
	return handlerStatus;
}

uint8_t transNewMsg(void){
	step = 6;
	//Получаем новое сообщение
	curMsg = pop(&msgFifo);
	//Если сообщений нет, выходим
	checkNull(curMsg);
	//Если есть, занимаем передатчик
	handlerStatus.FREE = 0;
	tftStatus.BUSY = 1;
	//Отправляем первый байт
	firstByte = 1;
	curEl = 0;
	curMsg->result->result = IN_PROC;
	if (curMsg->dir == SEND){
		//CS = 0
		enableTFTCommunication();
		//Выставляем пин D/CX
		if (curMsg->dataType == DATA){
			selectData();
		} 
		if (curMsg->dataType == COMMAND){
			selectCommand();
		}
		//Если дисплей SPI
		if (tftStatus.TYPE == SPI){
			//И разрешена DMA
			#ifdef ALLOW_TFT_DMA
			//Отправляем байты в соответсвие с граничным условием
			if (curMsg->bufSize > DMA_MIN_SIZE){
				handlerStatus.DMA = 1;
				//Настраиваем DMA
				initDMA();
				LL_SPI_EnableDMAReq_TX(TFT_SPI);
			} else {
				//Настраиваем прерывания
				handlerStatus.INT = 1;
				curEl++;
				step = 7;
				LL_SPI_TransmitData8(TFT_SPI, *curMsg->result->dataBuf);
				LL_SPI_EnableIT_TXE(TFT_SPI);				
			}
			#elif
			LL_SPI_EnableIT_TXE(TFT_SPI);
			LL_SPI_TransmitData8(TFT_SPI, *curMsg->result->dataBuf);
			curEl++;
			handlerStatus.INT = 1;
			
			#endif
			}
		  else {
	
		}
	} else if (curMsg->dir == RCV){
			curEl = 0;
			#ifdef ALLOW_TFT_DMA
			if (curMsg->bufSize > DMA_MIN_SIZE){
				initDMA();
				LL_SPI_EnableDMAReq_TX(TFT_SPI);
				LL_SPI_EnableDMAReq_RX(TFT_SPI);
				handlerStatus.DMA = 1;
			} else {
				LL_SPI_EnableIT_RXNE(TFT_SPI);
				LL_SPI_TransmitData8(TFT_SPI, dummyByte);
				handlerStatus.INT = 1;
			}
			#elif
				LL_SPI_EnableIT_RXNE(TFT_SPI);
				LL_SPI_TransmitData8(TFT_SPI, dummyByte);
				handlerStatus.INT = 1;
			#endif
		} else {
			return NULL;
		}
	return 1;
}

uint8_t transCurMsg(void){
	step = 8;
	__disable_irq();
	
	//Передача через прерывание
	if (handlerStatus.INT == 1){
		//Продолжаем отправлять сообщение
	if (curMsg->dir == SEND){
		//Если отправили не все сообщение
		if (curEl < curMsg->bufSize){
			//Отправляем следующий байт
			//send(
			uint8_t el = *(curMsg->result->dataBuf + curEl);
			curEl++;
			step = 9;
			LL_SPI_TransmitData8(TFT_SPI, el);
		} else {
			step = 10;
			//Если закончили, ищем новое сообщение в очереди
			finishTransmission();
			tftStatus.BUSY = 0;
			transNewMsg();
		}
	} 
	//Продолжаем получать сообщение
		else {
			uint8_t el = LL_SPI_ReceiveData8(TFT_SPI);
			*(curMsg->result->dataBuf + curEl) = el;
			curEl++;
			
			//если получили не все сообщения, продолжаем получать
			if (curEl < curMsg->bufSize){	
				LL_SPI_TransmitData8(TFT_SPI, 0xFF);
			}
			//если получили все, то ищем новое сообщение
			else {
				if (curMsg->hold == TRUE){
					tftStatus.BUSY = 0;
					tftSpiHandler();
				}
				else {
					finishTransmission();
				}
			}
		}
	}		
	//Передача через DMA
	if (handlerStatus.DMA == 1) {
		if (curMsg->hold == TRUE){
					tftStatus.BUSY = 0;
					tftSpiHandler();
		} else {
					finishTransmission();
		}
	}
	__enable_irq();
	return 1;
}

void finishTransmission(void){
	//Передача была по прерываниям
	if (handlerStatus.INT == 1){
		LL_SPI_DisableIT_ERR(TFT_SPI);
		LL_SPI_DisableIT_RXNE(TFT_SPI);
		LL_SPI_DisableIT_TXE(TFT_SPI);
	} 
	#ifdef ALLOW_TFT_DMA
	//Если DMA
	if (handlerStatus.DMA == 1) {
		LL_SPI_DisableDMAReq_RX(TFT_SPI);
		LL_SPI_DisableDMAReq_TX(TFT_SPI);
		LL_DMA_DisableChannel(TFT_DMA,TFT_TX_CHANNEL);
		LL_DMA_DisableChannel(TFT_DMA,TFT_RX_CHANNEL);
		LL_DMA_DisableIT_HT(TFT_DMA,TFT_TX_CHANNEL);
		LL_DMA_DisableIT_TC(TFT_DMA,TFT_TX_CHANNEL);
		LL_DMA_DisableIT_TE(TFT_DMA,TFT_TX_CHANNEL);
		LL_DMA_DisableIT_HT(TFT_DMA,TFT_RX_CHANNEL);
		LL_DMA_DisableIT_TC(TFT_DMA,TFT_RX_CHANNEL);
		LL_DMA_DisableIT_TE(TFT_DMA,TFT_RX_CHANNEL);
	}
	#endif
	tftStatus.BUSY = 0;
	handlerStatus.FREE = 1;
	handlerStatus.DMA = 0;
	handlerStatus.INT = 0;
	curMsg->result->result = FINISH;
}

void initDMA(void){
	uint32_t channel;
	if (curMsg->dir == SEND) {
		//Иниацилиируем DMA на отправку
		LL_DMA_ConfigTransfer(TFT_DMA,
												TFT_TX_CHANNEL,
												LL_DMA_DIRECTION_MEMORY_TO_PERIPH|
												LL_DMA_MODE_NORMAL|
												LL_DMA_PERIPH_NOINCREMENT|
												LL_DMA_MEMORY_INCREMENT|
												LL_DMA_PDATAALIGN_BYTE|
												LL_DMA_MDATAALIGN_BYTE|
												LL_DMA_PRIORITY_MEDIUM);
		LL_DMA_SetDataLength(TFT_DMA,
													TFT_TX_CHANNEL,
													curMsg->bufSize);
		LL_DMA_SetMemoryAddress(TFT_DMA,
														TFT_TX_CHANNEL,
														(uint32_t)curMsg->result->dataBuf);
		LL_DMA_SetPeriphAddress(TFT_DMA,
														TFT_TX_CHANNEL,
														LL_SPI_DMA_GetRegAddr(TFT_SPI));
														
		LL_DMA_EnableIT_TC(TFT_DMA,TFT_TX_CHANNEL);
		LL_DMA_EnableIT_TE(TFT_DMA,TFT_TX_CHANNEL);
		LL_DMA_EnableChannel(TFT_DMA,TFT_TX_CHANNEL);
	} else {
		//Иниацилизируем канал RX
		LL_DMA_ConfigTransfer(TFT_DMA,
												TFT_RX_CHANNEL,
												LL_DMA_DIRECTION_PERIPH_TO_MEMORY|
												LL_DMA_MODE_NORMAL|
												LL_DMA_PERIPH_NOINCREMENT|
												LL_DMA_MEMORY_INCREMENT|
												LL_DMA_PDATAALIGN_BYTE|
												LL_DMA_MDATAALIGN_BYTE|
												LL_DMA_PRIORITY_MEDIUM);
		LL_DMA_SetDataLength(TFT_DMA,
													TFT_RX_CHANNEL,
													curMsg->bufSize);
		LL_DMA_SetMemoryAddress(TFT_DMA,
														TFT_RX_CHANNEL, 
														(uint32_t)curMsg->result->dataBuf);							
		LL_DMA_SetPeriphAddress(TFT_DMA,
														TFT_RX_CHANNEL,
														LL_SPI_DMA_GetRegAddr(TFT_SPI));
														
		LL_DMA_EnableIT_TC(TFT_DMA,TFT_RX_CHANNEL);
		LL_DMA_EnableIT_TE(TFT_DMA,TFT_RX_CHANNEL);
		LL_DMA_EnableChannel(TFT_DMA,TFT_RX_CHANNEL);
		
		//Иниацилизируем канал TX на отправку dummy Byte
		LL_DMA_ConfigTransfer(TFT_DMA,
												TFT_TX_CHANNEL,
												LL_DMA_DIRECTION_MEMORY_TO_PERIPH|
												LL_DMA_MODE_NORMAL|
												LL_DMA_PERIPH_NOINCREMENT|
												LL_DMA_MEMORY_NOINCREMENT|
												LL_DMA_PDATAALIGN_BYTE|
												LL_DMA_MDATAALIGN_BYTE|
												LL_DMA_PRIORITY_MEDIUM);
		LL_DMA_SetDataLength(TFT_DMA,
													TFT_TX_CHANNEL,
													curMsg->bufSize);
		LL_DMA_SetMemoryAddress(TFT_DMA,
														TFT_TX_CHANNEL, 
														(uint32_t)&dummyByte);
														
		LL_DMA_SetPeriphAddress(TFT_DMA,
														TFT_TX_CHANNEL,
														LL_SPI_DMA_GetRegAddr(TFT_SPI));
														
		
		LL_DMA_EnableIT_TC(TFT_DMA,TFT_TX_CHANNEL);
		LL_DMA_EnableIT_TE(TFT_DMA,TFT_TX_CHANNEL);
		LL_DMA_EnableChannel(TFT_DMA,TFT_TX_CHANNEL);
	}
}
/******* Функции для SPI дисплея *******/

/*
	Отправка данных с помощью SPI с ожиданием окончания в цикле
	size - размер данных для отправки
	*data - буфер с данными для отправки
*/
uint32_t spiManualSend (uint32_t size, uint8_t *data){
	if (tftStatus.BUSY == 0 && 
		tftStatus.INITED == 1 && 
		tftStatus.TYPE == SPI)
	{
		enableTFTCommunication();
		tftStatus.BUSY = 1;
		for(uint32_t i = 0; i < size; i++){
			LL_SPI_TransmitData8(TFT_SPI,*data++);
			WAIT_TRANSMIT;
		}
		disableTFTCommunication();
		tftStatus.BUSY = 0;
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
	LL_SPI_TransmitData8(TFT_SPI, *(data+curEl));
	curEl++;
	return 1;
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
	if (tftStatus.BUSY == 0 &&
			tftStatus.INITED == 1 &&
			tftStatus.TYPE == PARAL){
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
			*data = LL_GPIO_ReadInputPort(TFT_PARAL_PORT);
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
	if (tftStatus.BUSY == 0 &&
			tftStatus.INITED == 1 &&
			tftStatus.TYPE == PARAL){
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
			LL_GPIO_WriteOutputPort(TFT_PARAL_PORT, tempData);
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
  LL_GPIO_Init(TFT_PARAL_PORT, &GPIO_InitStruct);
}

void SetParalPortInput(){
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DB0_Pin|DB1_Pin|DB2_Pin|DB10_Pin
                          |DB11_Pin|DB12_Pin|DB13_Pin|DB14_Pin|DB15_Pin
													|DB3_Pin|DB4_Pin|DB5_Pin|DB6_Pin|DB7_Pin|DB8_Pin
                          |DB9_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  LL_GPIO_Init(TFT_PARAL_PORT, &GPIO_InitStruct);
}
/******* Общие функции *******/

/*
	Перезапуск дисплея
*/
void rebootTFT (void){
	LL_GPIO_ResetOutputPin(TFT_RES_GPIO_Port,TFT_RES_Pin);
	LL_mDelay(RESET_DELAY_MS);
	LL_GPIO_SetOutputPin(TFT_RES_GPIO_Port,TFT_RES_Pin);
	LL_mDelay(RESET_DELAY_MS);
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

void initPerifTFT(perifType_t type){
	if (type == SPI){
		deInitParal_TFT();
		MX_SPI2_Init();
	} else { 
		LL_SPI_DeInit(TFT_SPI);
		deInitSPI_TFT();
		initParal_TFT();
	}
	
}

uint32_t manIDRead(void){
	uint8_t ID[4];
	initPerifTFT(SPI);
	rebootTFT();
	enableTFTCommunication();
	
	selectCommand();
	LL_SPI_TransmitData8(TFT_SPI,0xB0);
	WAIT_TRANSMIT;
	selectData();
	LL_SPI_TransmitData8(TFT_SPI,0x81);
	WAIT_TRANSMIT;
	
	selectCommand();
	LL_SPI_TransmitData8(TFT_SPI,0x04);
	WAIT_TRANSMIT;
	selectData();
	uint8_t buf = LL_SPI_ReceiveData8(TFT_SPI);
	for(uint8_t i = 0; i < sizeof(ID); i++){
		LL_SPI_TransmitData8(TFT_SPI,0xAA);
		WAIT_TRANSMIT;
		buf = LL_SPI_ReceiveData8(TFT_SPI);
		ID[i] = buf;
	}
	disableTFTCommunication();
	uint32_t tftID = (ID[3]<<24) + (ID[2]<<16) + (ID[1]<<8);
	return tftID;
}