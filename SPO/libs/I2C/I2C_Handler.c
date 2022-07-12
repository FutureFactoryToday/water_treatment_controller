#include "I2C/I2C_Handler.h"
#include "stdlib.h"

/*Структура сообщения*/	
	typedef struct {
	i2c_buf_t* buf;
	uint8_t dir;
	void* next;
} i2c_msg_t;


	#define SEND 1
	#define READ 2

///*Структура элемента в очереди*/
//typedef struct {
//	i2c_buf_t* buf;
//	uint8_t dir;
//	void* next;
//} i2c_msg_t;


/*Прототипы внутренних функций */
void initI2CHandler(void);	
uint8_t isInited(i2c_msg_t* node);
uint8_t hasNext(i2c_msg_t* node);
//i2c_msg_t* addNode (i2c_msg_t* msg);
i2c_msg_t* findTail(i2c_msg_t* head);
void deleteNode (i2c_msg_t* node);
void addMsg (i2c_buf_t* buf, uint8_t dir);

void i2cInterSend(i2c_msg_t* msg);
void i2cDMASend(i2c_msg_t* msg);
void i2cInterReceive(void);
void i2cDMAReceive(void);
void checkQueue(void);
void handleInProcessTransmission(void);
void sendNewMsg(i2c_msg_t* msg);
void receiveNewMsg(void);
void handleNewMsg (void);
void finishTransmission(void);
void enableIT(void);
void disableIT(void);
void findSlave (i2c_msg_t* msg);
void initDMA(uint8_t* dataPtr, uint16_t dataSize);
void disableDMA(void);

void initQueue(void);
i2c_buf_t* makeMass(uint8_t size);

/*Внутренние переменные*/
static uint32_t byteCnt;
static i2c_msg_t* queue;
static i2c_msg_t* curMsg;
static union i2cHandlerStatusSRK statusSRK = {0};


/*Поиск устройства и начало общения*/
uint8_t I2C_Find_Slave (uint8_t adr) {
	LL_I2C_HandleTransfer(I2C,
												adr,
												LL_I2C_ADDRSLAVE_7BIT,
												0,
												LL_I2C_MODE_AUTOEND,
												LL_I2C_GENERATE_START_WRITE);
	while (!LL_I2C_IsActiveFlag_TXE(I2C));
	if (LL_I2C_IsActiveFlag_NACK(I2C)){
		return 0;
	}
	if (LL_I2C_IsActiveFlag_STOP(I2C)){
		return 1;
	}
	return 0;
}

/*Ручная отправка сообщения*/
uint8_t I2C_Manual_Send(uint8_t adr, uint8_t* data, uint8_t bufSize){
	
	LL_I2C_HandleTransfer(I2C,
												adr,
												LL_I2C_ADDRSLAVE_7BIT,
												bufSize,
												LL_I2C_MODE_AUTOEND,
												LL_I2C_GENERATE_START_WRITE);
	for (uint8_t cnt = 0; cnt < bufSize; cnt++)
	{
		LL_I2C_TransmitData8(I2C,*data++);
		while (!LL_I2C_IsActiveFlag_TXE(I2C))
		{
			if (LL_I2C_IsActiveFlag_NACK(I2C)){
				LL_I2C_ClearFlag_NACK(I2C);
				return 0;
			}
		}
	}
	return 1;
}

/*Ручное чтение данных*/
uint8_t I2C_Manual_Read (uint8_t adr, uint8_t* destination, uint8_t msgSize){
	LL_I2C_HandleTransfer(I2C,
												adr,
												LL_I2C_ADDRSLAVE_7BIT,
												msgSize,
												LL_I2C_MODE_AUTOEND,
												LL_I2C_GENERATE_START_READ);
	
	for (uint8_t cnt = 0; cnt < msgSize; cnt++)
	{
		while (!LL_I2C_IsActiveFlag_RXNE(I2C))
		{
			if (LL_I2C_IsActiveFlag_NACK(I2C)){
				LL_I2C_ClearFlag_NACK(I2C);
				return 0;
			}
		}
		*destination++ = LL_I2C_ReceiveData8(I2C);
	}
	return 1;
}

void I2C_Send(i2c_buf_t* buf){
	addMsg(buf, SEND);
	if (statusSRK.bits.WAITING == 1) {
		I2C_Handler();
	}
}



void I2C_Read(i2c_buf_t* buf)
{
	addMsg(buf, READ);
	I2C_Handler();
}

void I2C_Handler() {
	//Первый раз? Иниацилизируем 
	if (!statusSRK.bits.INITED){
		initI2CHandler();
	}
	
	//Ждем запуск
	if (statusSRK.bits.WAITING){
		//В очереди 
		if (queue != NULL) {
				{
					curMsg = queue;
					handleNewMsg();
				}
			}
		return;
	} 
	
	//В процессе передачи или приема
	if (statusSRK.bits.RCV_IN_PROCESS || statusSRK.bits.SEND_IN_PROCESS) {
		handleInProcessTransmission();
		return;
	}
}		

void handleInProcessTransmission(){
	//Получили NACK
 	if (LL_I2C_IsActiveFlag_NACK(I2C))
	{
		curMsg->buf->status.bits.error = NO_SLAVE;
		statusSRK.bits.SEND_IN_PROCESS = 0;
		statusSRK.bits.RCV_IN_PROCESS = 0;
		LL_I2C_ClearFlag_NACK(I2C);
		disableIT();
		finishTransmission();
	}
	
	
	if (LL_I2C_IsActiveFlag_TCR(I2C)){
		byteCnt += LL_I2C_GetTransferSize(I2C);
		uint32_t delt = curMsg->buf->dataSize - byteCnt;
		if (delt > 255) {
			LL_I2C_SetTransferSize(I2C, 255);
		} else {
			LL_I2C_HandleTransfer(I2C,
													curMsg->buf->adr,
													LL_I2C_ADDRSLAVE_7BIT,
													delt,
													LL_I2C_MODE_SOFTEND,
													LL_I2C_GENERATE_NOSTARTSTOP);
		}
		return;
	}
	
	if (LL_I2C_IsActiveFlag_TC(I2C)) {
		LL_I2C_GenerateStopCondition(I2C);
		
		curMsg->buf->status.bits.newData = 0;
		finishTransmission();
	}

	if (LL_I2C_IsActiveFlag_TXIS(I2C))
		if( statusSRK.bits.TRANS_TYPE == INTERRUPT){
			//Закидываем новый байт для отправки
			LL_I2C_TransmitData8(I2C,*(curMsg->buf->buf + byteCnt++));
		} 
}




/*********************************************************************/
void initI2CHandler(){
	//queue = NULL;
	statusSRK.bits.INITED = 1;
	statusSRK.bits.WAITING = 1;
	//Разрешаем прерывания
	LL_I2C_EnableIT_NACK(I2C);
	LL_I2C_EnableIT_TC(I2C);
	
	
	byteCnt = 0;
}


void handleNewMsg (){
	byteCnt = 0;
	statusSRK.bits.WAITING = 0;
	if (curMsg->dir == SEND)
		{
			
			statusSRK.bits.SEND_IN_PROCESS = 1;
			sendNewMsg(curMsg);
			return;
		}
		if (curMsg->dir == READ)
		{
			statusSRK.bits.RCV_IN_PROCESS = 1;
			receiveNewMsg();
			return;
		}
}

void sendNewMsg(i2c_msg_t* msg){
	
	if (msg->buf->dataSize <= BORDER_DATA_SIZE)
	{
		statusSRK.bits.TRANS_TYPE = INTERRUPT;
		i2cInterSend(msg);
	}
	else {
		statusSRK.bits.TRANS_TYPE = DMA;
		i2cDMASend (msg);
	}
}

void receiveNewMsg(){
	if (curMsg->buf->dataSize <= BORDER_DATA_SIZE)
	{
		statusSRK.bits.TRANS_TYPE = INTERRUPT;
		i2cInterReceive();
	}
	else {
		statusSRK.bits.TRANS_TYPE = DMA;
		i2cDMAReceive();
	}
}



void finishTransmission(void){
	if (statusSRK.bits.TRANS_TYPE == INTERRUPT) {
		disableIT();
	}
	if (statusSRK.bits.TRANS_TYPE == DMA) {
		LL_I2C_DisableDMAReq_TX(I2C);
		LL_DMA_DisableChannel(I2C_DMA, I2C_DMA_CH);
	}
	
	__disable_irq();
	
	curMsg->buf->status.bits.inProcess = 0;
	if (curMsg->buf->callBack != NULL){
		curMsg->buf->callBack();
	}
	deleteNode(queue);
	statusSRK.bits.TRANS_TYPE = NOT_INITED;
	statusSRK.bits.WAITING = 1;
	
	__enable_irq();
}

void i2cInterSend(i2c_msg_t* msg){

	LL_I2C_EnableIT_TX(I2C);
	
	statusSRK.bits.SEND_IN_PROCESS = 1;
		
	findSlave(msg);
}

void i2cDMASend(i2c_msg_t* msg){
	statusSRK.bits.SEND_IN_PROCESS = 1;
	/*Или после отправки первого байта???*/
	msg->buf->status.bits.inProcess = 1;
	LL_I2C_EnableDMAReq_TX(I2C);
	initDMA(msg->buf->buf, msg->buf->dataSize);
	
	findSlave(msg);
}


void i2cInterReceive(){
	
}
void i2cDMAReceive(){
	
}

void findSlave (i2c_msg_t* msg){
	msg->buf->status.bits.inProcess = 1;
	if (msg->buf->dataSize > 255) {
		LL_I2C_HandleTransfer(I2C,
													msg->buf->adr,
													LL_I2C_ADDRSLAVE_7BIT,
													255,
													LL_I2C_MODE_RELOAD,
													LL_I2C_GENERATE_START_WRITE);
	} else {
				LL_I2C_HandleTransfer(I2C,
													msg->buf->adr,
													LL_I2C_ADDRSLAVE_7BIT,
													msg->buf->dataSize,
													LL_I2C_MODE_AUTOEND,
													LL_I2C_GENERATE_START_WRITE);
	}
}

void initDMA(uint8_t* dataPtr, uint16_t dataSize){
	LL_DMA_ConfigTransfer(I2C_DMA,
												I2C_DMA_CH,
												LL_DMA_DIRECTION_MEMORY_TO_PERIPH|
												LL_DMA_MODE_NORMAL|
												LL_DMA_PERIPH_NOINCREMENT|
												LL_DMA_MEMORY_INCREMENT|
												LL_DMA_PDATAALIGN_BYTE|
												LL_DMA_MDATAALIGN_BYTE|
												LL_DMA_PRIORITY_MEDIUM);
	LL_DMA_SetDataLength(I2C_DMA,
												I2C_DMA_CH,
												dataSize);
	LL_DMA_SetMemoryAddress(I2C_DMA,
													I2C_DMA_CH,
													(uint32_t)dataPtr);
	LL_DMA_SetPeriphAddress(I2C_DMA,
													I2C_DMA_CH,
													LL_I2C_DMA_GetRegAddr(I2C,LL_I2C_DMA_REG_DATA_TRANSMIT));
	
	LL_DMA_EnableIT_TC(I2C_DMA,I2C_DMA_CH);
	LL_DMA_EnableIT_TE(I2C_DMA,I2C_DMA_CH);
	LL_DMA_EnableChannel(I2C_DMA,I2C_DMA_CH);
	
}

void disableDMA(){
	LL_DMA_DisableChannel(I2C_DMA, I2C_DMA_CH);
}

void enableIT(void){
	LL_I2C_EnableIT_TX(I2C);
}

void disableIT(void){
	LL_I2C_DisableIT_TX(I2C);
}


/*************************************************************/
/*  Служебные    */
/*************************************************************/
i2c_msg_t* findTail(i2c_msg_t* head){
	i2c_msg_t* curNode = head;
	
	while (hasNext(curNode))
	{
		curNode = curNode->next;
	}
	return curNode;
}


void addMsg (i2c_buf_t* buf, uint8_t dir){
	i2c_msg_t *newMsg = NULL;
	
	__disable_irq();
	newMsg = (i2c_msg_t*)malloc(sizeof(i2c_msg_t));
	newMsg->buf = buf;
	newMsg->dir = SEND;
	newMsg->next = NULL;
	
	if (queue == NULL)
	{
		queue = newMsg;
	}
		else 
	{
		i2c_msg_t *tail = findTail(queue);
		tail->next = newMsg;
	}
	__enable_irq();
}


void deleteNode (i2c_msg_t* node){
	i2c_msg_t* tmpNode = queue;
	if (node == tmpNode) {
		queue = tmpNode->next;
	} else {
		while (tmpNode->next != node) {
			tmpNode = tmpNode->next;
		}
		tmpNode->next = node->next;
	}
	
	free (node);
}


//i2c_buf_t* makeMass(uint8_t size)
//{
//	return (i2c_buf_t*)calloc(size,sizeof(i2c_buf_t));
//}


uint8_t isInited(i2c_msg_t* node) {
	return (node!= NULL);
}
uint8_t hasNext(i2c_msg_t* node){
	return (node->next != NULL);
}

