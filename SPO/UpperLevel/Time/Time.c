/**
  ******************************************************************************
  * @file           : Time.c
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
#include "Time.h"
#include "FlashParams/FlashParam.h"
#include <math.h>
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
typedef struct {
	uint8_t* monthName;
	uint8_t* monthShortName;
	uint8_t* dayName;
	uint8_t* dayShortName;
} date_name_t;
/* Private define ------------------------------------------------------------*/
 uint8_t* engMonthName[] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};
uint8_t* engShortMonthName[] = {
	"JAN",
	"FEB",
	"MAR",
	"APR",
	"MAY",
	"JUN",
	"JUL",
	"AUG",
	"SEP",
	"OCT",
	"NOV",
	"DEC"
};
uint8_t* engDayName[] = {
	"Monday",
	"Tuesday",
	"Wendsday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday"
};
uint8_t* engShortDayName[] = {
	"MO",
	"TU",
	"WE",
	"TH",
	"FR",
	"SA",
	"SU"
};

uint8_t* ruMonthName[] = {
	"Январь",
	"Февраль",
	"Март",
	"Апрель",
	"Май",
	"Июнь",
	"Июль",
	"Август",
	"Сентябрь",
	"Октябрь",
	"Ноябрь",
	"Декабрь"
};

uint8_t* ruShortMonthName[] = {
	"ЯНВ",
	"ФЕВ",
	"МАР",
	"АПР",
	"МАЙ",
	"ИЮН",
	"ИЮЛ",
	"АВГ",
	"СЕН",
	"ОКТ",
	"НОЯ",
	"ДЕК"
};
uint8_t* ruDayName[] = {
	"Понедельник",
	"Вторник",
	"Среда",
	"Четверг",
	"Пятница",
	"Суббота",
	"Воскресенье"
};
uint8_t* ruShortDayName[] = {
	"ПН",
	"ВТ",
	"СР",
	"ЧТ",
	"ПТ",
	"СБ",
	"ВС"
};
uint8_t monthCodeTable [] = {
	0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5
};

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

date_name_t engName = {
	engMonthName,
	engShortMonthName,
	engDayName,
	engShortDayName
};

date_name_t ruName = {
	ruMonthName,
	ruShortMonthName,
	ruDayName,
	ruShortDayName
};

uint8_t formatedString[FORMATED_STRING_LENGTH];
date_name_t* dateName = &engName;
uint8_t	yearNum = 0, strLength = 0, monthNum = 0, dayNum = 0, hourNum =0, minuteNum = 0, secondNum = 0;
uint8_t *ptr = formatedString;
time_t sysTime;
bool isInited;

/* Private function prototypes -----------------------------------------------*/
bool isLeapYear(uint16_t year);
uint8_t maxDayInMonth(uint8_t month);
uint8_t intToChar(uint8_t num);
void processChar(uint8_t curCh);
void changeTimeLanguage(language_t lang);
uint8_t getDayNameByDate(time_t date);
/* Private user code ---------------------------------------------------------*/

void Time_init(){
	if (!isInited){
		time_t defTime = DEFAULT_TIME;
		setTime(defTime);
	}
}
time_t* getTime (){
	return &sysTime;
}

void setTime (time_t time){
	assert_param(time.day != 0);
	assert_param(time.month != 0);
	assert_param(time.year != 0);
	assert_param(time.month < 13);
	assert_param(time.day <= maxDayInMonth(time.month));
	
	LL_RTC_TimeTypeDef timeStr = {0};
	
	timeStr.Hours = time.hour;
	timeStr.Minutes = time.minute;
	timeStr.Seconds = time.second;
	
	LL_RTC_TIME_Init(RTC,LL_RTC_FORMAT_BIN,&timeStr);
	
	sysTime = time;
}

void RTC_Interrupt(){
	sysTime.second++;
	if (sysTime.second > 59){
		sysTime.second = 0;
		sysTime.minute++;
		if (sysTime.minute > 59){
			sysTime.minute = 0;
			sysTime.hour++;
			if (sysTime.hour > 23){
				sysTime.hour = 0;
				sysTime.day++;
				if (sysTime.day > maxDayInMonth(sysTime.month)){
					sysTime.day = 1;
					sysTime.month++;
					if (sysTime.month > 12){
						sysTime.year++;
						sysTime.month = 1;
					}	
				}	
			}
		}
	}
}

bool isLeapYear(uint16_t year){
	return ((year%4 == 0 && year % 100 != 0) || year % 400 == 0);
}

uint8_t maxDayInMonth(uint8_t month){
	switch (month){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:{
			return 31;
		}
		case 2:{
			if (isLeapYear(sysTime.year)){
				return 29;
			} else {
				return 28;
			}
		}
		case 4:
		case 6:
		case 9: 
		case 11: {
			return 30;
		}
		default: {
			errorCause = "Неправильный месяц";
			Error_Handler();
		}
	}
}

uint8_t* getFormatedTime(uint8_t* fStr){
	yearNum = 0, strLength = 0, monthNum = 0, dayNum = 0, hourNum =0, minuteNum = 0, secondNum = 0;
	ptr = formatedString;
	uint8_t curCh = 0;
	
	changeTimeLanguage(sysParam.lang);
	
	while(*fStr!= 0){
		strLength++;
		curCh = *fStr++;
		switch (curCh){
			case 'Y':{
				yearNum++;
				break;
			}
			case 'M':{
				monthNum++;
				break;
			}
			case 'D':{
				dayNum++;
				break;
			}
			case 'h':{
				hourNum++;
				break;
			}
			case 'm':{
				minuteNum++;
				break;
			}
			case 's':{
				secondNum++;
				break;
			}
			default: break;
		}
		if (curCh != *fStr){
			processChar(curCh);
		}
	}
	*ptr = 0;
	return formatedString;
}
void processChar(uint8_t curCh){
	switch (curCh){
			case 'Y':{	
				uint8_t yearUpHalf = __LL_RTC_CONVERT_BIN2BCD(sysTime.year/100);
				uint8_t yearLowHalf = __LL_RTC_CONVERT_BIN2BCD(sysTime.year - (sysTime.year/100) * 100);
				if (yearNum == 4){
					*ptr++ = intToChar((yearUpHalf & 0xF0)>>4);
					*ptr++ = intToChar((yearUpHalf & 0x0F));
					*ptr++ = intToChar((yearLowHalf & 0xF0)>>4);
					*ptr++ = intToChar((yearLowHalf & 0x0F));
				}
				if (yearNum == 2){
					*ptr++ = intToChar((yearLowHalf & 0xF0)>>4);
					*ptr++ = intToChar((yearLowHalf & 0x0F));
				}
				break;
			}
			case 'M':{
				if (monthNum == 1){
					uint8_t** monthNamePtr;
					monthNamePtr = dateName->monthShortName;
					monthNamePtr= monthNamePtr + sysTime.month;
					do{
						*ptr++= *(*monthNamePtr)++;
					}
					while (**monthNamePtr!= 0);
				}
				if (monthNum == 2){
					uint8_t monthBCD = __LL_RTC_CONVERT_BIN2BCD(sysTime.month);
					*ptr++ = intToChar((monthBCD & 0xF0)>>4);
					*ptr++ = intToChar((monthBCD & 0x0F));
				}
				if (monthNum == 3){
					uint8_t** monthNamePtr;
					monthNamePtr = dateName->monthName;
					monthNamePtr= monthNamePtr + sysTime.month;
					do{
						*ptr++= *(*monthNamePtr)++;
					}
					while (**monthNamePtr!= 0);
				}
				break;
			}
			case 'D':{
				if (dayNum == 1){
					uint8_t** dayNamePtr;
					dayNamePtr = dateName->dayShortName;
					dayNamePtr= dayNamePtr + getDayNameByDate(sysTime);
					
					do{
						*ptr++= *(*dayNamePtr)++;
					}
					while (**dayNamePtr!= 0);
				}
				if (dayNum == 2){
					uint8_t monthBCD = __LL_RTC_CONVERT_BIN2BCD(sysTime.month);
					*ptr++ = intToChar((monthBCD & 0xF0)>>4);
					*ptr++ = intToChar((monthBCD & 0x0F));
				}
				if (dayNum == 3){
					uint8_t** dayNamePtr;
					dayNamePtr = dateName->dayName;
					dayNamePtr= dayNamePtr + getDayNameByDate(sysTime);
					do{
						*ptr++= *(*dayNamePtr)++;
					}
					while (**dayNamePtr!= 0);
				}
				break;
			}
			case 'h':{
				uint8_t hourBCD = __LL_RTC_CONVERT_BIN2BCD(sysTime.hour);
				*ptr++ = intToChar((hourBCD & 0xF0)>>4);
				*ptr++ = intToChar((hourBCD & 0x0F));
				break;
			}
			case 'm':{
				uint8_t minuteBCD = __LL_RTC_CONVERT_BIN2BCD(sysTime.minute);
				*ptr++ = intToChar((minuteBCD & 0xF0)>>4);
				*ptr++ = intToChar((minuteBCD & 0x0F));
				break;
			}
			case 's':{
				uint8_t secondBCD = __LL_RTC_CONVERT_BIN2BCD(sysTime.second);
				*ptr++ = intToChar((secondBCD & 0xF0)>>4);
				*ptr++ = intToChar((secondBCD & 0x0F));
				break;
			}
			default: {
				*ptr++ = curCh;
			};
		}
}
void changeTimeLanguage(language_t lang){
	if (lang == RUSSIAN){
		dateName = &ruName;
	}
	if (lang == ENGLISH){
		dateName = &engName;
	}
}

uint8_t getDayNameByDate(time_t date){
	uint8_t yearCode = date.year - (date.year/100) * 100;
	uint8_t redYearCode = (yearCode/4);
	yearCode = (yearCode + redYearCode)%7;
	uint8_t monthCode = monthCodeTable[date.month - 1];
	uint8_t centCode = (date.year > 2099)? 4 : 6;
	int8_t leapCode = (isLeapYear(date.year) && date.month < 2) ? 1 : 0;
	
	uint8_t day = (yearCode + monthCode + centCode + date.day - leapCode)%7;
	day = (day == 0)? 6 : day - 1;
	return day;
}

 uint8_t timeTest (){
	 if (!isLeapYear(2104)){
		 Error_Handler();
	 }
	 if (isLeapYear(2100)){
		 Error_Handler();
	 }
	 if (!isLeapYear(2000)){
		 Error_Handler();
	 }
	 if (isLeapYear(2103)){
		 Error_Handler();
	 }
	 if (isLeapYear(700)){
		 Error_Handler();
	 }
	 
	 
	 time_t testTime;
	
	 testTime.year = 2022;
	 testTime.month = 9;
	 testTime.day = 15;
	 
	 if (getDayNameByDate(testTime) != 3){
		 Error_Handler();
	 }
	
 }