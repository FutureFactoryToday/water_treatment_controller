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
#include <math.h>

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/

char* ruMonthName[] = {
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

char* ruShortMonthName[] = {
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
char* ruDayName[] = {
	"Понедельник",
	"Вторник",
	"Среда",
	"Четверг",
	"Пятница",
	"Суббота",
	"Воскресенье"
};
char* ruShortDayName[] = {
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


date_name_t ruName = {
	ruMonthName,
	ruShortMonthName,
	ruDayName,
	ruShortDayName
};

uint8_t formatedString[FORMATED_STRING_LENGTH];
date_name_t* dateName = &ruName;
uint8_t	yearNum = 0, strLength = 0, monthNum = 0, dayNum = 0, hourNum =0, minuteNum = 0, secondNum = 0;
uint8_t *ptr = formatedString;

bool isInited;

/* Private function prototypes -----------------------------------------------*/
bool isLeapYear(uint16_t year);

uint8_t intToChar(uint8_t num);
void processChar(uint8_t curCh, wtc_time_t *source);

/* Private user code ---------------------------------------------------------*/

void Time_init(){
	if (LL_RTC_TIME_Get(RTC) == 0){
		wtc_time_t defTime = DEFAULT_TIME;
		setSysTime(&defTime);
	} else {
		sysParams.vars.sysTime = *getTime();
	}
}

uint32_t wtcTimeToInt(wtc_time_t *time){
	struct tm timeSt = wtcTimeToStdTime(time);
	return mktime(&timeSt);
}

wtc_time_t intToWTCTime (uint32_t time){
	struct tm timeSt = *localtime(&time);
	return stdTimeToWTCTime(&timeSt);
}

wtc_time_t* getTime (){
	wtc_time_t resTime;
	time_t rawtime = LL_RTC_TIME_Get(RTC);
	struct tm *breakTime = localtime(&rawtime);
	resTime.year = 1900 + breakTime->tm_year;
	resTime.month = 1 + breakTime->tm_mon;
	resTime.day = breakTime->tm_mday;
	resTime.hour = breakTime->tm_hour;
	resTime.minute = breakTime->tm_min;
	resTime.second = breakTime->tm_sec;
	
	return &resTime;
}

time_t getRTC(){
	return LL_RTC_TIME_Get(RTC);
}
void setSysTime (wtc_time_t* time){
	LL_RTC_TimeTypeDef timeStr = {0};
	
	assert_param(time->day != 0);
	assert_param(time->month != 0);
	assert_param(time->year != 0);
	assert_param(time->month < 13);
	assert_param(time->day <= maxDayInMonth(time->month, sysParams.vars.sysTime.year));
	
	struct tm newTime;
	newTime = wtcTimeToStdTime(time);

	/* Enter Initialization mode */
  if (LL_RTC_EnterInitMode(RTC) != ERROR)
  {	
		time_t rawtime = mktime(&newTime);
    LL_RTC_TIME_Set(RTC, rawtime);
  }
  /* Exit Initialization mode */
  LL_RTC_ExitInitMode(RTC);
	
	sysParams.vars.sysTime = *time;
	
}

void RTC_Interrupt(){
	sysParams.vars.sysTime = *getTime();
}
struct tm wtcTimeToStdTime (wtc_time_t* time){
	struct tm newTime;
	newTime.tm_hour = time->hour;
	newTime.tm_min = time->minute;
	newTime.tm_sec = time->second;
	newTime.tm_mday = time->day;
	newTime.tm_mon = time->month - 1;
	newTime.tm_year = time->year - 1900;
	return newTime;
}

wtc_time_t stdTimeToWTCTime (struct tm* time){
	wtc_time_t newTime;
	newTime.hour = time->tm_hour;
	newTime.minute = time->tm_min;
	newTime.second = time->tm_sec;
	newTime.day = time->tm_mday;
	newTime.month = time->tm_mon + 1;
	newTime.year = time->tm_year + 1900;
	return newTime;
}



wtc_time_t* addDay (wtc_time_t* initTime, uint32_t numDay){
	wtc_time_t time = *initTime;

	time_t rawTime = wtcTimeToInt(&time);
	time_t addTime = numDay*24*60*60;
	rawTime += addTime;
	
	time = intToWTCTime(rawTime);
	
	return &time;
}
wtc_time_t* decDay (wtc_time_t* initTime, uint32_t numDay){
	wtc_time_t time = *initTime;

	
	time_t rawTime = wtcTimeToInt(&time);
	time_t addTime = numDay*24*60*60;
	rawTime -= addTime;
	
	time = intToWTCTime(rawTime);
	
	return &time;
}

wtc_time_t* addHour (wtc_time_t* initTime, uint32_t numHour){
	wtc_time_t time = *initTime;

	time_t rawTime = wtcTimeToInt(&time);
	time_t addTime = numHour*60*60;
	rawTime += addTime;
	
	time = intToWTCTime(rawTime);
	return &time;
}
wtc_time_t* decHour (wtc_time_t* initTime, uint32_t numHour){
	wtc_time_t time = *initTime;

	time_t rawTime = wtcTimeToInt(&time);
	time_t addTime = numHour*60*60;
	rawTime -= addTime;
	
	time = intToWTCTime(rawTime);
	
	return &time;
}

wtc_time_t* addMinute (wtc_time_t* initTime, uint32_t numMinute){
	wtc_time_t time = *initTime;

	time_t rawTime = wtcTimeToInt(&time);
	time_t addTime = numMinute*60;
	rawTime += addTime;
	
	time = intToWTCTime(rawTime);
	
	return &time;
}
wtc_time_t* decMinute (wtc_time_t* initTime, uint32_t numMinute){
	wtc_time_t time = *initTime;

	time_t rawTime = wtcTimeToInt(&time);
	time_t addTime = numMinute*60;
	rawTime -= addTime;
	
	time = intToWTCTime(rawTime);
	return &time;
}

wtc_time_t* addSec (wtc_time_t* initTime, uint32_t numSec){
	wtc_time_t time = *initTime;

	time_t rawTime = wtcTimeToInt(&time);
	
	rawTime += numSec;
	
	time = intToWTCTime(rawTime);
	
	return &time;
}
wtc_time_t* decSec (wtc_time_t* initTime, uint32_t numSec){

	wtc_time_t time = *initTime;

	time_t rawTime = wtcTimeToInt(&time);
	
	rawTime -= numSec;
	
	time = intToWTCTime(rawTime);
	
	return &time;
}

//firstTime + secondTime
wtc_time_t* addDateTime (wtc_time_t* firstTime, wtc_time_t* secondTime){
	wtc_time_t time = *firstTime;

	time_t rawTime = wtcTimeToInt(&time);
	time_t addTime = wtcTimeToInt(&secondTime);
	rawTime += addTime;
	time = intToWTCTime(rawTime);
	return &time;
}

//firstTime - secondTime
wtc_time_t* decDateTime (wtc_time_t* firstTime, wtc_time_t* secondTime){
	wtc_time_t time = *firstTime;

	
	time_t rawTime = wtcTimeToInt(&time);
	time_t addTime = wtcTimeToInt(&secondTime);
	rawTime -= addTime;
	time = intToWTCTime(rawTime);
	
	return &time;
}

wtc_time_t* addDate (wtc_time_t* firstTime, wtc_time_t* secondTime){

	return addDateTime(firstTime,secondTime);
}

wtc_time_t* addTime (wtc_time_t* firstTime, wtc_time_t* secondTime){

	return addDateTime(firstTime,secondTime);
}

wtc_time_t* setTime (wtc_time_t* firstTime, wtc_time_t* secondTime){
	wtc_time_t tempTime = *firstTime;
	tempTime.second = secondTime->second;
	tempTime.minute = secondTime->minute;
	tempTime.hour = secondTime->hour;
	return &tempTime;
}
wtc_time_t* setDate (wtc_time_t* firstTime, wtc_time_t* secondTime){
	wtc_time_t tempTime = *firstTime;
	tempTime.year = secondTime->year;
	tempTime.month = secondTime->month;
	tempTime.day = secondTime->day;
	return &tempTime;
}
wtc_time_t* setDateTime (wtc_time_t* firstTime, wtc_time_t* secondTime){
	wtc_time_t tempTime = *firstTime;
	tempTime.year = secondTime->year;
	tempTime.month = secondTime->month;
	tempTime.day = secondTime->day;
	tempTime.second = secondTime->second;
	tempTime.minute = secondTime->minute;
	tempTime.hour = secondTime->hour;
	return &tempTime;
}

bool equalDateTime(wtc_time_t* firstTime, wtc_time_t* secondTime){
	return firstTime->year == secondTime->year &&
	firstTime->month == secondTime->month &&
	firstTime->day == secondTime->day &&
	firstTime->hour == secondTime->hour &&
	firstTime->minute == secondTime->minute &&
	firstTime->second == secondTime->second;
}

bool equalTime(wtc_time_t* firstTime, wtc_time_t* secondTime){
	return firstTime->hour == secondTime->hour &&
	firstTime->minute == secondTime->minute &&
	firstTime->second == secondTime->second;
}

bool equalDate(wtc_time_t* firstTime, wtc_time_t* secondTime){
	return firstTime->year == secondTime->year &&
	firstTime->month == secondTime->month &&
	firstTime->day == secondTime->day;
}
/*
1 if firstTime > secondTime
-1 if firstTime < secondTime
0 if equal
*/
int8_t compareTime(wtc_time_t* firstTime, wtc_time_t* secondTime){
	if (equalTime(firstTime,secondTime)){
		return 0;
	}
	
	if (firstTime->hour > secondTime->hour){
		return 1;
	} else if (firstTime->hour < secondTime->hour){
		return -1;
	} else {
		if (firstTime->minute > secondTime->minute){
		return 1;
		} else if (firstTime->minute < secondTime->minute){
			return -1;
		} else {
			if (firstTime->second > secondTime->second){
			return 1;
			} else if (firstTime->second < secondTime->second){
				return -1;
			} else {
				return 0;
			}
		}
	}
}
bool isZeroDateTime(wtc_time_t* time){
	wtc_time_t zeroTime = {0};
	if (compareDateTime(time, &zeroTime) == 0){
		return 1;
	} else {
		return 0;
	}
}
bool isZeroDate(wtc_time_t* time){
	wtc_time_t zeroTime = {0};
	if (compareDate(time, &zeroTime) == 0){
		return 1;
	} else {
		return 0;
	}
}
bool isZeroTime(wtc_time_t* time){
	wtc_time_t zeroTime = {0};
	if (compareTime(time, &zeroTime) == 0){
		return 1;
	} else {
		return 0;
	}
}

int8_t compareDate(wtc_time_t* firstTime, wtc_time_t* secondTime){
	if (equalDate(firstTime,secondTime)){
		return 0;
	}
	if (firstTime->year > secondTime->year){
		return 1;
	} else if (firstTime->year < secondTime->year){
		return -1;
	} else {
		if (firstTime->month > secondTime->month){
			return 1;
		} else if (firstTime->month < secondTime->month){
			return -1;
		} else {
			if (firstTime->day > secondTime->day){
				return 1;
			} else if (firstTime->day < secondTime->day){
				return -1;
			} else {
				return 0;
			}
		}
	}
}
int8_t compareDateTime(wtc_time_t* firstTime, wtc_time_t* secondTime){
	if (equalDateTime(firstTime,secondTime)){
		return 0;
	}
	if (firstTime->year > secondTime->year){
		return 1;
	} else if (firstTime->year < secondTime->year){
		return -1;
	} else {
		if (firstTime->month > secondTime->month){
			return 1;
		} else if (firstTime->month < secondTime->month){
			return -1;
		} else {
			if (firstTime->day > secondTime->day){
				return 1;
			} else if (firstTime->day < secondTime->day){
				return -1;
			} else {
				if (firstTime->hour > secondTime->hour){
				return 1;
				} else if (firstTime->hour < secondTime->hour){
					return -1;
				} else {
					if (firstTime->minute > secondTime->minute){
					return 1;
					} else if (firstTime->minute < secondTime->minute){
						return -1;
					} else {
						if (firstTime->second > secondTime->second){
						return 1;
						} else if (firstTime->second < secondTime->second){
							return -1;
						} else {
							return 0;
						}
					}
				}
			}
		}
	}
}
int32_t countDaysBetween (wtc_time_t* startTime, wtc_time_t* stopTime){
	wtc_time_t tempTime = *startTime;
	uint32_t result;
	
	if (compareDateTime(startTime,stopTime) > 0 ||
		compareDateTime(startTime, &(wtc_time_t)MIN_DATE_TIME) < 0){
		return -1;
	} 
	if (equalDate(startTime,stopTime)){
		return 0;
	}
	struct tm startEdTime = wtcTimeToStdTime(startTime);
	struct tm stopEdTime = wtcTimeToStdTime(stopTime);
	uint32_t secNum = mktime(&stopEdTime) - mktime(&startEdTime);
	
	return (secNum/(24*60*60));
}
bool isLeapYear(uint16_t year){
	return ((year%4 == 0 && year % 100 != 0) || year % 400 == 0);
}

uint8_t maxDayInMonth(uint8_t month, uint16_t year){
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
			if (isLeapYear(year)){
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
			Error_Handler();
		}
	}
}
uint8_t* getFormatedTime(uint8_t* fStr){
	return getFormatedTimeFromSource(fStr, &sysParams.vars.sysTime);
}
uint8_t* getFormatedTimeFromSource(uint8_t* fStr, wtc_time_t *source){
	uint8_t curCh = 0;
	yearNum = 0, strLength = 0, monthNum = 0, dayNum = 0, hourNum =0, minuteNum = 0, secondNum = 0;
	ptr = formatedString;
	uint8_t format[6*2];
	uint8_t i = 0;

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
			processChar(curCh, source);
		}
	}
	*ptr = 0;
	return formatedString;
}

void processChar(uint8_t curCh, wtc_time_t *source)	{
	uint8_t secondBCD;
	uint8_t yearUpHalf;
	uint8_t yearLowHalf;
	
	
	switch (curCh){
			case 'Y':{	
				yearUpHalf = __LL_RTC_CONVERT_BIN2BCD(source->year/100);
				yearLowHalf = __LL_RTC_CONVERT_BIN2BCD(source->year - (source->year/100) * 100);
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
					monthNamePtr= monthNamePtr + source->month - 1;
					do{
						*ptr++= *(*monthNamePtr)++;
					}
					while (**monthNamePtr!= 0);
				}
				if (monthNum == 2){
					uint8_t monthBCD = __LL_RTC_CONVERT_BIN2BCD(source->month);
					*ptr++ = intToChar((monthBCD & 0xF0)>>4);
					*ptr++ = intToChar((monthBCD & 0x0F));
				}
				if (monthNum == 3){
					uint8_t* monthNamePtr;
					monthNamePtr = *(dateName->monthName + source->month - 1);
//					monthNamePtr = (monthNamePtr + (sysTime.month - 1));
					do{
						*ptr++= *monthNamePtr++;
					}
					while (*monthNamePtr!= 0);
					
				}
				break;
			}
			case 'D':{
				if (dayNum == 1){
					uint8_t** dayNamePtr;
					dayNamePtr = dateName->dayShortName;
					dayNamePtr= dayNamePtr + getDayNameByDate(&sysParams.vars.sysTime);
					
					do{
						*ptr++= *(*dayNamePtr)++;
					}
					while (**dayNamePtr!= 0);
				}
				if (dayNum == 2){
					uint8_t dayBCD = __LL_RTC_CONVERT_BIN2BCD(source->day);
					*ptr++ = intToChar((dayBCD & 0xF0)>>4);
					*ptr++ = intToChar((dayBCD & 0x0F));
				}
				if (dayNum == 3){
					uint8_t** dayNamePtr;
					dayNamePtr = dateName->dayName;
					dayNamePtr= dayNamePtr + getDayNameByDate(source);
					do{
						*ptr++= *(*dayNamePtr)++;
					}
					while (**dayNamePtr!= 0);
				}
				break;
			}
			case 'h':{
				uint8_t hourBCD = __LL_RTC_CONVERT_BIN2BCD(source->hour);
				*ptr++ = intToChar((hourBCD & 0xF0)>>4);
				*ptr++ = intToChar((hourBCD & 0x0F));
				break;
			}
			case 'm':{
				uint8_t minuteBCD = __LL_RTC_CONVERT_BIN2BCD(source->minute);
				*ptr++ = intToChar((minuteBCD & 0xF0)>>4);
				*ptr++ = intToChar((minuteBCD & 0x0F));
				break;
			}
			case 's':{
				uint8_t secondBCD = __LL_RTC_CONVERT_BIN2BCD(source->second);
				*ptr++ = intToChar((secondBCD & 0xF0)>>4);
				*ptr++ = intToChar((secondBCD & 0x0F));
				break;
			}
			default: {
				*ptr++ = curCh;
			};
		}
}

uint8_t getDayNameByDate(wtc_time_t *date){
	uint8_t day;
	uint8_t yearCode;
	uint8_t redYearCode;
	uint8_t monthCode;
	uint8_t centCode;
	int8_t leapCode;
	
	yearCode = date->year - (date->year/100) * 100;
	redYearCode = (yearCode/4);
	yearCode = (yearCode + redYearCode)%7;
	monthCode = monthCodeTable[date->month - 1];
	centCode = (date->year > 2099)? 4 : 6;
	leapCode = (isLeapYear(date->year) && date->month < 2) ? 1 : 0;
	
	day = (yearCode + monthCode + centCode + date->day - leapCode)%7;
	day = (day == 0)? 6 : day - 1;
	return day;
}

uint8_t timeTest (){
	wtc_time_t testTime, secTempTime = {0};
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

	testTime.year = 2022;
	testTime.month = 9;
	testTime.day = 15;

	if (getDayNameByDate(&testTime) != 3){
		Error_Handler();
	}

				
	testTime = *addDay(&testTime, 2);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 17);
				
	testTime = *decDay(&testTime, 2);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 15);
				
	testTime = *addDay(&testTime, 17);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 9 && 
				testTime.day == 1);
				
	testTime = *decDay(&testTime, 16);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16);

	testTime = *addDay(&testTime, 31);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 9 && 
				testTime.day == 16);
				
	testTime = *decDay(&testTime, 31);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16);
				
	testTime.hour = 10;
	testTime.minute = 30;
	testTime.second = 30;

	testTime = *addHour(&testTime, 1);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16 &&
				testTime.hour == 11 &&
				testTime.minute == 30 &&
				testTime.second == 30);
				
	testTime = *decHour(&testTime, 1);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16 &&
				testTime.hour == 10 &&
				testTime.minute == 30 &&
				testTime.second == 30);
				
	testTime = *addHour(&testTime, 15);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 17 &&
				testTime.hour == 1 &&
				testTime.minute == 30 &&
				testTime.second == 30);
				
	testTime = *decHour(&testTime, 24);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16 &&
				testTime.hour == 1 &&
				testTime.minute == 30 &&
				testTime.second == 30);

	testTime = *decHour(&testTime, 1);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16 &&
				testTime.hour == 0 &&
				testTime.minute == 30 &&
				testTime.second == 30);
				
	testTime = *decHour(&testTime, 1);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 15 &&
				testTime.hour == 23 &&
				testTime.minute == 30 &&
				testTime.second == 30);		

	testTime = *addHour(&testTime, 1);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16 &&
				testTime.hour == 0 &&
				testTime.minute == 30 &&
				testTime.second == 30);
				
	testTime = *decMinute(&testTime, 10);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16 &&
				testTime.hour == 0 &&
				testTime.minute == 20 &&
				testTime.second == 30);
				
	testTime = *decMinute(&testTime, 20);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16 &&
				testTime.hour == 0 &&
				testTime.minute == 00 &&
				testTime.second == 30);

	testTime = *decMinute(&testTime, 10);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 15 &&
				testTime.hour == 23 &&
				testTime.minute == 50 &&
				testTime.second == 30);
				
	testTime = *addMinute(&testTime, 10);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16 &&
				testTime.hour == 0 &&
				testTime.minute == 00 &&
				testTime.second == 30);
				
	testTime = *addMinute(&testTime, 60);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16 &&
				testTime.hour == 1 &&
				testTime.minute == 00 &&
				testTime.second == 30);
				
	testTime = *addMinute(&testTime, 10);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16 &&
				testTime.hour == 1 &&
				testTime.minute == 10 &&
				testTime.second == 30);			
				
	secTempTime.year = 0;
	secTempTime.month = 0;
	secTempTime.day = 0;
	secTempTime.hour = 0;
	secTempTime.minute = 0;
	secTempTime.second = 0;
	
	testTime = *addDateTime(&testTime, &secTempTime);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16 &&
				testTime.hour == 1 &&
				testTime.minute == 10 &&
				testTime.second == 30);
				
	testTime = *decDateTime(&testTime, &secTempTime);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16 &&
				testTime.hour == 1 &&
				testTime.minute == 10 &&
				testTime.second == 30);
				
	secTempTime.year = 1;
	secTempTime.month = 2;
	secTempTime.day = 10;
	secTempTime.hour = 5;
	secTempTime.minute = 10;
	secTempTime.second = 20;
	
	testTime = *addDateTime(&testTime, &secTempTime);	
	assert_param(testTime.year == 2023 &&
				testTime.month == 10 && 
				testTime.day == 26 &&
				testTime.hour == 6 &&
				testTime.minute == 20 &&
				testTime.second == 50);
				
	testTime = *decDateTime(&testTime, &secTempTime);	
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 16 &&
				testTime.hour == 1 &&
				testTime.minute == 10 &&
				testTime.second == 30);
				
	testTime = *decDateTime(&testTime, &testTime);	
				
	uint32_t intTestTime = wtcTimeToInt(&testTime);
	wtc_time_t newTestTime = intToWTCTime(intTestTime);
	assert_param(compareDateTime(&newTestTime,&testTime) == 0);
}

 