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
#define DEFAULT_TIME {2022, 10, 22,12,0,0}
#define DAYS_NUM 7
#define MONTHS_NUM 12

//���� ����� ������: 4 ����� ����, 9 ���� ������, 11 ���� ���, 5 ����� ����������, 1����� ������
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

typedef struct {
	char** monthName;
	char** monthShortName;
	char** dayName;
	char** dayShortName;
} date_name_t;
/*Global params*/

/*Prototypes */
void Time_init(void);

//��������� ������. ������ BIN (�������)
void setTime (time_t time);

//���������� ��������� �� ��������� �����
time_t* getTime (void);
//���������� ��� ������ �����
void RTC_Interrupt(void);

/*
	������� ��� ������ ������� �� �����
������� ������: ������ � �������� ������ �� �����, �������� � System.language:
	Y - ���. 
		���������� �������� 
		YY - ������� 2 ����� ����);
		YYYY - ������ ����������� ����.
	M - �����.
		���������� ��������
		M - ������� ��������� �������� ������
		MM - ������� ��������� �������� ������ (� 0)
		MMM - ������� �������� ����� ������
	D - �����.
		���������� ��������
		D - ������� ��������� �������� ���
		DD - ������� ��������� �������� ��� (� 0)
		DDD -������� �������� ����� ���
		
	h - ���
	���������� ��������
		hh
		
	m - ���
	���������� ��������
		mm
		
	s - ���
	���������� ��������
		ss

������:
	uint8_t* str = "YYYY.MM.DD hh:mm:ss";
	str = getFormatedTime(str);
	����� - "2022.09.14 14:50:00"
	
	str = "YY.M.D hh:mm:ss";
	str = getFormatedTime(str);
	����� - "22.SEP.TH 14:50:00"  
	
	str = "YYYY.MMM.DDD hh:mm:ss";
	str = getFormatedTime(str);
	����� - "2022.September.Thursday 14:50:00"
*/
uint8_t* getFormatedTime(uint8_t* fStr);

uint8_t* getFormatedTimeFromSource(uint8_t* fStr, time_t *source);

uint8_t* getTimeString(void);

uint8_t maxDayInMonth(uint8_t month);

uint8_t getDayNameByDate(time_t *date);

uint8_t timeTest (void);
#endif /* __TIME_H__ */

