/**
  ******************************************************************************
  * @file           : FIFO.c
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
#include "fifo.h"
#include "stdint.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/*Поиск конца очереди*/
fifo_t* findTail (fifo_t* fifo);
uint32_t getEmptySize(fifo_t** fifo);
/* Private user code ---------------------------------------------------------*/

/*Получение данных из очереди*/
void* pop (fifo_t** fifo){
	/*Если очереди нет, то возвращаем NULL*/
	if ((*fifo) == NULL) {
		 return NULL;
	}
	//Очередь пуста
	if ((*fifo)->emptyElement == (*fifo)->firstElement 
		&& *(*fifo)->firstElement == NULL){
			return NULL;
	}
		
	void* data = *(*fifo)->firstElement;
	*(*fifo)->firstElement = NULL;
	(*fifo)->firstElement++;
	
	void** lastElement = (*fifo)->buf + ((*fifo)->size - 1);
	
	if ((*fifo)->firstElement > lastElement){
		(*fifo)->firstElement = (*fifo)->buf;
	}
	return data;
}
 
/*Добавление данных в очередь*/
void* push (fifo_t** fifo, void* data){
	if (*fifo == NULL) {         //Если очередь не иниацилизирована,
		return NULL;       //ошибка
	}

	//Очередь полна
	if ((*fifo)->emptyElement == (*fifo)->firstElement 
		&& *(*fifo)->firstElement != NULL){
			return NULL;
	}
		
	*(*fifo)->emptyElement = data;
	
	(*fifo)->emptyElement++;
	
	void** lastElement = (*fifo)->buf + ((*fifo)->size - 1);
	
	if ((*fifo)->emptyElement > lastElement){
		(*fifo)->emptyElement = (*fifo)->buf;
	}
	
	return *fifo;
}

/*Иниацилизация очереди*/
fifo_t* initFifo(const uint32_t size, uint32_t dataSize){
	fifo_t* fifo = (fifo_t*)malloc(sizeof(fifo_t));      //Выделяем место для очереди
	if (fifo == NULL) {                                 //Если не получилось, 
		return NULL;                                      //возвращаем ошибку
	}
	void* buf = (void*)malloc (size*dataSize);
	for(uint32_t i=0; i< size; i++){
		(*((uint32_t*)buf+i)) = NULL;
	}
	if (buf == NULL){
		free(fifo);
		return NULL;
	}
	
	fifo->buf = buf;																	//Чистим данные
	fifo->emptyElement = buf; 
	fifo->firstElement = buf;                                   
	fifo->size = size;
	fifo->step = dataSize;
	return fifo;
}


uint8_t isEmpty(fifo_t* fifo){
	return (fifo == NULL) || (fifo->emptyElement - fifo->firstElement == 0);
}
/* Tests*/
void testFifo (void){
	uint8_t bufSize = 5;
	fifo_t* spiFifo = initFifo(bufSize, sizeof(uint8_t*));
	if (spiFifo == NULL)
	{
		Error_Handler();
	}
	
	uint8_t fBuf[5] = {1,2,3,4,5};
	uint8_t sBuf[10] = {0};
	uint8_t tBuf[6] = {6,7,8,9,10,11};
	
	push(&spiFifo, fBuf);
	push(&spiFifo, sBuf);
	push(&spiFifo, tBuf);
	uint8_t* newBuf1 = (uint8_t*)pop(&spiFifo);
	uint8_t* newBuf2 = (uint8_t*)pop(&spiFifo);
	uint8_t* newBuf3 = (uint8_t*)pop(&spiFifo);
	if(!(newBuf1 == fBuf)) Error_Handler();
	if(!(newBuf2 == sBuf)) Error_Handler();
	if(!(newBuf3 == tBuf)) Error_Handler();
	push(&spiFifo, sBuf);
	push(&spiFifo, tBuf);
	push(&spiFifo, fBuf);
	newBuf1 = (uint8_t*)pop(&spiFifo);
	newBuf2 = (uint8_t*)pop(&spiFifo);
	newBuf3 = (uint8_t*)pop(&spiFifo);
	if(!(newBuf1 == sBuf)) Error_Handler();
	if(!(newBuf2 == tBuf)) Error_Handler();
	if(!(newBuf3 == fBuf)) Error_Handler();
	
	newBuf1 = pop(&spiFifo);
	if(!(newBuf1 == NULL)) Error_Handler();
	
	void* res = 0;
	
	for(uint8_t i = 0; i < bufSize; i++){
		res = push(&spiFifo, fBuf);
		if (res == NULL) Error_Handler();
	}
	
		res = push(&spiFifo, fBuf);
		if (res != NULL) Error_Handler();
	
	for(uint32_t i = 0; i < 1000; i++){
		push(&spiFifo, fBuf);
		newBuf1 = pop (&spiFifo);
		if (newBuf1 != fBuf) Error_Handler();
	}
	
	free(spiFifo->buf);
	free(spiFifo);
}
