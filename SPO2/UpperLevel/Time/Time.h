/**
  ******************************************************************************
  * @file    TIME.h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIME_H__
#define __TIME_H__

/*Includes */
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

/*Public defines */
#define MIN_DATE_TIME {1900, 1, 1, 0,0,0}
#define DEFAULT_TIME {2022, 10, 22,12,0,0}
#define DAYS_NUM 7
#define MONTHS_NUM 12

//���� ����� ������: 4 ����� ����, 9 ���� ������, 11 ���� ���, 5 ����� ����������, 1����� ������
#define FORMATED_STRING_LENGTH 4 + 9 + 11 + 5 + 1


typedef struct {
	uint16_t year;
	uint32_t month;
	uint32_t day;
	uint32_t hour;
	uint32_t minute;
	uint32_t second;
} wtc_time_t;

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
void setSysTime (wtc_time_t *time);

//���������� ��������� �� ��������� �����
wtc_time_t* getTime (void);
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

uint8_t* getFormatedTimeFromSource(uint8_t* fStr, wtc_time_t *source);

uint8_t* getTimeString(void);

uint32_t wtcTimeToInt(wtc_time_t *time);

wtc_time_t intToWTCTime (uint32_t time);

uint8_t maxDayInMonth(uint8_t month,uint16_t year);

uint8_t getDayNameByDate(wtc_time_t *date);

uint8_t timeTest (void);

struct tm wtcTimeToStdTime (wtc_time_t* time);
wtc_time_t stdTimeToWTCTime (struct tm* time);


wtc_time_t* addMonth (wtc_time_t* initTime, uint32_t numMonth);
wtc_time_t* decMonth (wtc_time_t* initTime, uint32_t numMonth);

wtc_time_t* addDay (wtc_time_t* initTime, uint32_t numDay);
wtc_time_t* decDay (wtc_time_t* initTime, uint32_t numDay);

wtc_time_t* addHour (wtc_time_t* initTime, uint32_t numHour);
wtc_time_t* decHour (wtc_time_t* initTime, uint32_t numHour);

wtc_time_t* addMinute (wtc_time_t* initTime, uint32_t numMinute);
wtc_time_t* decMinute (wtc_time_t* initTime, uint32_t numMinute);

wtc_time_t* addSec (wtc_time_t* initTime, uint32_t numSec);
wtc_time_t* decSec (wtc_time_t* initTime, uint32_t numSec);

wtc_time_t* addDateTime (wtc_time_t* firstTime, wtc_time_t* secondTime);

wtc_time_t* addDate (wtc_time_t* firstTime, wtc_time_t* secondTime);

wtc_time_t* addTime (wtc_time_t* firstTime, wtc_time_t* secondTime);

wtc_time_t* setTime (wtc_time_t* firstTime, wtc_time_t* secondTime);
wtc_time_t* setDate (wtc_time_t* firstTime, wtc_time_t* secondTime);
wtc_time_t* setDateTime (wtc_time_t* firstTime, wtc_time_t* secondTime);
//firstTime - secondTime
wtc_time_t* decDateTime (wtc_time_t* firstTime, wtc_time_t* secondTime);

bool equalDateTime(wtc_time_t* firstTime, wtc_time_t* secondTime);
bool equalDate(wtc_time_t* firstTime, wtc_time_t* secondTime);
bool equalTime(wtc_time_t* firstTime, wtc_time_t* secondTime);

/*
1 if firstTime > secondTime
-1 if firstTime < secondTime
0 if equal
*/
int8_t compareTime(wtc_time_t* firstTime, wtc_time_t* secondTime);
int8_t compareDate(wtc_time_t* firstTime, wtc_time_t* secondTime);
int8_t compareDateTime(wtc_time_t* firstTime, wtc_time_t* secondTime);

bool isZeroDateTime(wtc_time_t* time);
bool isZeroDate(wtc_time_t* time);
bool isZeroTime(wtc_time_t* time);

int32_t countDaysBetween (wtc_time_t* startTime, wtc_time_t* stopTime);
#endif /* _TIME_H_ */

