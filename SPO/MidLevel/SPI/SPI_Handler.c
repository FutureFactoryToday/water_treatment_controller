/**
  ******************************************************************************
  * @file           : SPI_Handler.c
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

/* Private typedef -----------------------------------------------------------*/



/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
#define checkNull(a) do {if (a == NULL) return NULL;} while (0);
/* Private variables ---------------------------------------------------------*/
	spi_handler_t* handlerList = NULL;

/* Private function prototypes -----------------------------------------------*/
void interruptSend (spi_handler_t *handler);
void dmaSend(spi_handler_t *handler);
void initHandler(spi_handler_t *handler);
spi_handler_t* findOrCreateHandler (SPI_TypeDef* SPI);
spi_handler_t* createHandler (SPI_TypeDef* SPI);
result_t procNewMsg(spi_handler_t *handler);
//result_t intSendNewByte (spi_msg_t* msg);
//result_t intRcvNewByte (spi_msg_t* msg);
result_t finishTransmission(spi_handler_t* handler);
result_t stopHandler (spi_handler_t* handler);
spi_handler_t* findHandler (SPI_TypeDef* SPI);
void finishTransaction(spi_handler_t* handler);
#ifdef TESTS
/*Inner Tests*/
uint8_t cnt = 0;
void testHandlerList (void);
void testRegistration(void);
result_t mockHandlerFunc(void);
#endif
/* Private user code ---------------------------------------------------------*/
/*Outter functions*/
//result_t sendMsg (SPI_TypeDef* SPI, spi_data_t *data){
//	spi_handler_t* spiHandler = findOrCreateHandler(SPI);
//	checkNull(spiHandler);
//	spi_msg_t* newMsg = (spi_msg_t*)malloc(sizeof(spi_msg_t));
//	checkNull(newMsg);
//	newMsg->dir = SEND;
//	newMsg->data = data;
//	push(&(spiHandler->msgFifo),newMsg);
//	return handler(SPI);
//}

//result_t receiveMsg (SPI_TypeDef *SPI, spi_data_t *data){
//	spi_handler_t* spiHandler = findOrCreateHandler(SPI);
//	checkNull(spiHandler);
//	spi_msg_t* newMsg = (spi_msg_t*)malloc(sizeof(spi_msg_t));
//	checkNull(newMsg);
//	newMsg->dir = RCV;
//	newMsg->data = data;
//	push(&(spiHandler->msgFifo),newMsg);
//	return handler(SPI);
//}

/*Inner functions*/
void initHandler(spi_handler_t *handler){
}
spi_handler_t* findHandler (SPI_TypeDef* SPI){
		//lets find handler 
	spi_handler_t* result = handlerList;
	if (result->SPI == SPI){
			return  result;
		}
	while (result->next != NULL) {
		result = result-> next;
		if (result->SPI == SPI){
			return  result;
		}
	}
	return NULL;
}	


spi_handler_t* findOrCreateHandler (SPI_TypeDef* SPI){
	//if list is empty
	if (handlerList == NULL){
		handlerList = createHandler(SPI);
	} else {
		
		//if not, lets find handler 
		spi_handler_t* result = handlerList;
		if (result->SPI == SPI){
				return  result;
			}
		while (result->next != NULL) {
			result = result-> next;
			if (result->SPI == SPI){
				return  result;
			}
		}
		//if still not found, create new handler
		result->next = createHandler(SPI);
		return result->next;
	}
	return handlerList;	
}

spi_handler_t* createHandler (SPI_TypeDef* SPI){
		//create new list                                               
		 spi_handler_t* newHandler = (spi_handler_t*)malloc(sizeof(spi_handler_t));
	
		//return NULL if not enough memory
		if (newHandler == NULL){
			 return NULL;
		}
		//init inner structure
		newHandler->SPI = SPI;
		newHandler->next = NULL;
		newHandler->handlerFifo = initFifo();
		return newHandler;
}

uint8_t spiInterruptHandler (SPI_TypeDef *SPI){
	//Находим нужный обработчик
	spi_handler_t* spiHandler = findHandler(SPI);
	checkNull(spiHandler);
	if (spiHandler->lastResult.ERR == 1) {
		finishTransaction(spiHandler);
		return NULL;
	}
	
	if (spiHandler->lastResult.FREE == 1){
		finishTransaction(spiHandler);
		spiHandler->curHandler = pop(&spiHandler->handlerFifo);
		if (spiHandler->curHandler == NULL){
			spiHandler->status.BUSY = 0;
		}
		spiHandler->lastResult = spiHandler->curHandler();
	} else {
		spiHandler->lastResult = spiHandler->curHandler();
	}
	return 1;
}

uint8_t registerHandler(SPI_TypeDef *SPI, result_t (*handlerFunc)(void)){
	spi_handler_t* spiHandler = findOrCreateHandler(SPI);
	checkNull(spiHandler);
	if (spiHandler->curHandler == NULL && spiHandler->status.BUSY == 0){
		spiHandler->status.BUSY = 1;
		spiHandler->curHandler = handlerFunc;
		spiHandler->lastResult = spiHandler->curHandler();
	} else {
		push(&spiHandler->handlerFifo, handlerFunc);
	}
	return 1;
}

void finishTransaction(spi_handler_t* handler){
	LL_SPI_DisableIT_ERR(handler->SPI);
	LL_SPI_DisableIT_RXNE(handler->SPI);
	LL_SPI_DisableIT_TXE(handler->SPI);
}

#ifdef TESTS
/*Tests*/
void testSPIHandler (void){
	testHandlerList();
	testRegistration();
}
void testHandlerList (void){
	SPI_TypeDef* n1SPI = (void*)0x20000001;
	SPI_TypeDef* n2SPI = (void*)0x20000005;
	SPI_TypeDef* n3SPI = (void*)0x20000009;
	
	spi_handler_t* fH = findOrCreateHandler(n1SPI);
	spi_handler_t* sH = findOrCreateHandler(n2SPI);
	spi_handler_t* tH = findOrCreateHandler(n3SPI);
	
	if (fH == NULL) Error_Handler();
	if (sH == NULL) Error_Handler();
	if (tH == NULL) Error_Handler();
	if (fH == sH) Error_Handler();
	if (sH == tH) Error_Handler();
	if (tH == fH) Error_Handler();
	
	spi_handler_t* nfH = findOrCreateHandler(n1SPI);
	spi_handler_t* nsH = findOrCreateHandler(n2SPI);
	spi_handler_t* ntH = findOrCreateHandler(n3SPI);
	
	if (!(fH == nfH)) Error_Handler();
	if (!(sH == nsH)) Error_Handler();
	if (!(tH == ntH)) Error_Handler();
	
	free(fH);
	free(sH);
	free(tH);
}

void testRegistration(void){
	SPI_TypeDef* n1SPI = (void*)0x20000001;
	SPI_TypeDef* n2SPI = (void*)0x20000005;
	SPI_TypeDef* n3SPI = (void*)0x20000009;
	
	registerHandler(n1SPI, mockHandlerFunc);
	if (cnt != 1) Error_Handler();
	registerHandler(n2SPI, mockHandlerFunc);
	if (cnt != 2) Error_Handler();
	registerHandler(n3SPI, mockHandlerFunc);
	if (cnt != 3) Error_Handler();
	registerHandler(n1SPI, mockHandlerFunc);
	if (cnt != 3) Error_Handler();
}

result_t mockHandlerFunc(void){
	cnt++;
	result_t result;
	result.FREE = 1;
	return result;
}
#endif
