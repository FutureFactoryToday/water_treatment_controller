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
	uint8_t spiStep = 0;
uint8_t hCnt = 0;
/* Private function prototypes -----------------------------------------------*/
void interruptSend (spi_handler_t *handler);
void dmaSend(spi_handler_t *handler);
void initHandler(spi_handler_t *handler);
spi_handler_t* findOrCreateHandler (SPI_TypeDef* SPI);
spi_handler_t* createHandler (SPI_TypeDef* SPI);
handlerStatus_t procNewMsg(spi_handler_t *handler);
//handlerStatus_t intSendNewByte (spi_msg_t* msg);
//handlerStatus_t intRcvNewByte (spi_msg_t* msg);
handlerStatus_t finishTransmission(spi_handler_t* handler);
handlerStatus_t stopHandler (spi_handler_t* handler);
spi_handler_t* findHandler (SPI_TypeDef* SPI);

#ifdef TESTS
/*Inner Tests*/
uint8_t cnt = 0;
void testHandlerList (void);
void testRegistration(void);
handlerStatus_t mockHandlerFunc(void);
#endif
/* Private user code ---------------------------------------------------------*/
/*Outter functions*/

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
		newHandler->handlerFifo = initFifo(SPI_H_FIFO_SIZE, sizeof(uint32_t*));
		return newHandler;
}

uint8_t spiInterruptHandler (SPI_TypeDef *SPI){
	hCnt++;
	spiStep = 5;
	//Находим нужный обработчик
	spi_handler_t* spiHandler = findHandler(SPI);
	checkNull(spiHandler);
	if (spiHandler->lastResult.ERR == 1) {
		return NULL;
	}
	
	if (spiHandler->lastResult.FREE == 1){
		spiStep = 6;
		spiHandler->curHandler = pop(&spiHandler->handlerFifo);
		if (spiHandler->curHandler == NULL){
			if (LL_SPI_IsActiveFlag_TXE(SPI) && LL_SPI_IsEnabledIT_TXE(SPI)){
				LL_SPI_DisableIT_TXE(SPI);
			}
			if (LL_SPI_IsActiveFlag_RXNE(SPI) && LL_SPI_IsEnabledIT_RXNE(SPI)){
				LL_SPI_DisableIT_RXNE(SPI);
			}
			spiHandler->status.BUSY = 0;
			return 1;
		}
		spiHandler->lastResult.FREE = 0;
		spiStep = 7;
		spiHandler->lastResult = spiHandler->curHandler();
	} else {
		spiHandler->lastResult.FREE = 0;
		spiStep = 8;
		spiHandler->lastResult = spiHandler->curHandler();
	}
	if (spiHandler->lastResult.FREE == 1) {
		spiStep = 8;
		spiHandler->status.BUSY = 0;
		spiInterruptHandler(SPI);
	}
	return 1;
}

uint8_t registerHandler(SPI_TypeDef *SPI, handlerStatus_t (*handlerFunc)(void)){
	spiStep = 1;
	spi_handler_t* spiHandler = findOrCreateHandler(SPI);
	spiStep = 2;
	checkNull(spiHandler);
	if (spiHandler->curHandler == NULL && spiHandler->status.BUSY == 0){
		spiHandler->status.BUSY = 1;
		spiHandler->curHandler = handlerFunc;
		spiStep = 3;
		spiHandler->lastResult.FREE = 0;
		spiHandler->lastResult.ERR = 0;
		spiHandler->lastResult = spiHandler->curHandler();
	} else {
		spiStep = 4;
		push(&spiHandler->handlerFifo, handlerFunc);
	}
	return 1;
}

#ifdef TESTS
/*Tests*/
void testSPIHandler (void){
	testHandlerList();
	testRegistration();
	handlerList = NULL;
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
}

handlerStatus_t mockHandlerFunc(void){
	cnt++;
	handlerStatus_t result;
	result.FREE = 1;
	return result;
}
#endif
