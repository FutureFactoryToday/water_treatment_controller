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
#include "stdint.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/*Поиск конца очереди*/
fifo_t* findTail (fifo_t* fifo);
/* Private user code ---------------------------------------------------------*/

/*Получение данных из очереди*/
void* pop (fifo_t** fifo){
	/*Если очереди нет, то возвращаем NULL*/
	if ((*fifo) == NULL) {
		 return NULL;
	}
	void* data = (*fifo)->data;  //Получаем данные
	fifo_t* buf = *fifo;         //Сохраняем указатель на первый элемент очереди
	*fifo = (*fifo)->next;       //Делаем второй элемент первым
	free(buf);                   //Удаляем бывший первый элемент
	return data;
}

/*Добавление данных в очередь*/
fifo_t* push (fifo_t** fifo, void* data){
	if (*fifo == NULL) {         //Если очередь не иниацилизирована,
		 *fifo = initFifo();       //иниацилизируем
	}
	if (*fifo == NULL)	{        //Если не хватило памяти,
		return NULL; 	             //выходим с ошибкой
	}
	if ((*fifo)->data == NULL){  //Если это первый элемент и он пустой,
		(*fifo)->data = data;      //добавляем данные
	} 
	else {
		fifo_t* newNode = (fifo_t*)malloc(sizeof(fifo_t)); //Создаем новый элемент очереди
		newNode->data = data;                              //добавляем данные
		newNode->next = NULL;
		fifo_t* tail = findTail(*fifo);                    //вставляем в конец очереди
		tail->next = newNode;
	}
	return *fifo;
}

/*Иниацилизация очереди*/
fifo_t* initFifo(void){
	fifo_t* fifo = (fifo_t*)malloc(sizeof(fifo_t));      //Выделяем место для очереди
	if (fifo == NULL) {                                  //Если не получилось, 
		return NULL;                                       //возвращаем ошибку
	}
	fifo->data = NULL;                                   //Чистим данные
	fifo->next = NULL;
	return fifo;
}

/*Поиск конца очереди*/
fifo_t* findTail (fifo_t* fifo){
	while(fifo->next != NULL){
		fifo++;
	}
	return fifo;
}

uint8_t isEmpty(fifo_t* fifo){
	return (fifo == NULL) || (fifo->data == NULL);
}
/* Tests*/
void testFifo (void){
	fifo_t* spiFifo = initFifo();
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
}
