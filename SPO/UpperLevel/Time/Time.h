/**
  ******************************************************************************
  * @file    TIME.h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TIME_H_
#define _TIME_H_

/*Includes */
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

/*Public defines */
#define DEFAULT_TIME {2000, 1, 1,12,0,0}

//Макс длина строки: 4 цифры года, 9 букв месяца, 11 букв дня, 5 знака препинания, 1конец строки
#define FORMATED_STRING_LENGTH 4 + 9 + 11 + 5 + 1
typedef struct {
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	bool isSecondSecHalf;
} time_t;
/*Global params*/

/*Prototypes */
void Time_init();
//Установка вереми. Формат BIN (обычный)
void setTime (time_t time);

//Возвращает указатель на системное время
time_t* getTime ();
//Прерывание для работы часов
void RTC_Interrupt();

/*
	Функция для вывода времени на экран
Входные данные: строка с форматом ответа на языке, указаном в System.language:
	Y - год. 
		Допустимые значения 
		YY - крайние 2 числа года);
		YYYY - полное обозначение года.
	M - месяц.
		Допустимые значения
		M - Возврат короткого названия месяца
		MM - возврат числового значения месяца (с 0)
		MMM - возврат длинного имени месяца
	D - месяц.
		Допустимые значения
		D - Возврат короткого названия дня
		DD - возврат числового значения дня (с 0)
		DDD -возврат длинного имени дня
		
	h - час
	Допустимые значения
		hh
		
	m - час
	Допустимые значения
		mm
		
	s - час
	Допустимые значения
		ss

Пример:
	uint8_t* str = "YYYY.MM.DD hh:mm:ss";
	str = getFormatedTime(str);
	Ответ - "2022.09.14 14:50:00"
	
	str = "YY.M.D hh:mm:ss";
	str = getFormatedTime(str);
	Ответ - "22.SEP.TH 14:50:00"  
	
	str = "YYYY.MMM.DDD hh:mm:ss";
	str = getFormatedTime(str);
	Ответ - "2022.September.Thursday 14:50:00"
*/
uint8_t* getFormatedTime(uint8_t* fStr);

uint8_t* getTimeString();

uint8_t timeTest ();
#endif /* __TIME_H__ */

