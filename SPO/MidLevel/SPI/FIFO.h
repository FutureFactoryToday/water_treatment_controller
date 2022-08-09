/**
  ******************************************************************************
  * @file    FIFOh
  * @brief   This file contains all the function prototypes for
  *          the FIFO.c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _FIFO_H_
#define _FIFO_H_

/*Includes */
#include "main.h"

/*Public defines */
#define MIN_FIFO 2

typedef struct{
	void* data;
	void* next;
}fifo_t;
/*Global params*/

/*Prototypes */
/*
	Иниацилизация очереди.
	Входные данные: 
	Результат:
		Указатель на очередь
			либо
		NULL (если нет свободной памяти)
*/
fifo_t* initFifo(void);

/*
	Добавления новых данных в очередь.
	Входные данные: 
		Указатель на очередь
	Результат:
		Указатель на данные
			либо
		NULL
*/
fifo_t* push (fifo_t** fifo, void* data);

/*
	Получение данных из очереди.
	Входные данные: 
		Указатель на очередь (либо NULL)
		Указатель на данные
	Результат:
		Указатель на очередь
			либо
		NULL (если нет свободной памяти)
*/
void* pop (fifo_t** fifo);

/*
	Проверка есть ли данные в очереди
	Входные данные: 
		Указатель на очередь
	Результат:
		Есть или нет данных
*/
uint8_t isEmpty(fifo_t* fifo);
/*Tests*/
void testFifo (void);
#endif /* __FIFO_H__ */

