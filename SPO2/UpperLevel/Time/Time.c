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


/* Private define ------------------------------------------------------------*/
char* engMonthName[] = {
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
char* engShortMonthName[] = {
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
char* engDayName[] = {
	"Monday",
	"Tuesday",
	"Wendsday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday"
};
char* engShortDayName[] = {
	"MO",
	"TU",
	"WE",
	"TH",
	"FR",
	"SA",
	"SU"
};

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
wtc_time_t sysTime;
bool isInited;

/* Private function prototypes -----------------------------------------------*/
bool isLeapYear(uint16_t year);

uint8_t intToChar(uint8_t num);
void processChar(uint8_t curCh, wtc_time_t *source);
void changeTimeLanguage(language_t lang);

/* Private user code ---------------------------------------------------------*/

void Time_init(){
	if (LL_RTC_TIME_Get(RTC) == 0){
		wtc_time_t defTime = DEFAULT_TIME;
		LL_RTC_AlarmTypeDef alarm = {0};
		
		LL_RTC_ALARM_StructInit(&alarm);
		setSysTime(&defTime);
		LL_RTC_ALARM_Init(RTC,LL_RTC_FORMAT_BIN,&alarm);
	} else {
		time_t rawtime = LL_RTC_TIME_Get(RTC);
		struct tm *breakTime = localtime(&rawtime);
		
		sysTime.year = 1900 + breakTime->tm_year;
		sysTime.month = 1 + breakTime->tm_mon;
		sysTime.day = breakTime->tm_mday;
		sysTime.hour = breakTime->tm_hour;
		sysTime.minute = breakTime->tm_min;
		sysTime.second = breakTime->tm_sec;
	}
	LL_RTC_EnableIT_ALR(RTC);
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
	return &sysTime;
}

void setSysTime (wtc_time_t* time){
	LL_RTC_TimeTypeDef timeStr = {0};
	
	assert_param(time->day != 0);
	assert_param(time->month != 0);
	assert_param(time->year != 0);
	assert_param(time->month < 13);
	assert_param(time->day <= maxDayInMonth(time->month, sysTime.year));
	
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
	
	sysTime = *time;
	
	
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
				if (sysTime.day > maxDayInMonth(sysTime.month, sysTime.year)){
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

wtc_time_t* addMonth (wtc_time_t* initTime, uint8_t numMonth){
	wtc_time_t time = *initTime;
	if (numMonth == 0)
		return &time;
	
	time.month += numMonth;
	if (time.month > 12){
		uint8_t div = time.month / 12;
		time.year += div;	
		time.month = time.month - (div)*12;
	}
	if (time.day > maxDayInMonth(time.month, time.year)){
		time.day = maxDayInMonth(time.month, time.year);
	}
	return &time;
}
wtc_time_t* decMonth (wtc_time_t* initTime, uint8_t numMonth){
	wtc_time_t time = *initTime;
	int16_t tempDec = 0;
	bool isLastDay = false;
	
	if (numMonth == 0)
		return &time;
	if (time.day == maxDayInMonth(time.month,time.year)){
		isLastDay = true;
	}
	tempDec = time.month - numMonth;
	if (tempDec <= 0){
		time.year -= (-tempDec) / 12;	
		tempDec += (tempDec / 12)*12;
		if (tempDec <= 0){
			time.year -= 1;
			tempDec += 12;
		}
		time.month = tempDec;
	} else {
		time.month -= numMonth;
	}
	
	if (time.day > maxDayInMonth(time.month, time.year) || isLastDay){
		time.day = maxDayInMonth(time.month, time.year);
	}
	return &time;
}

wtc_time_t* addDay (wtc_time_t* initTime, uint8_t numDay){
	wtc_time_t time = *initTime;
	if (numDay == 0)
		return &time;
	
	time.day += numDay;
	while (time.day > maxDayInMonth(time.month, time.year)){
		time.day -= maxDayInMonth(time.month, time.year);	
		time = *addMonth(&time,1);
	}
	return &time;
}
wtc_time_t* decDay (wtc_time_t* initTime, uint8_t numDay){
	wtc_time_t time = *initTime;
	int16_t tempDec = 0;
	
	if (numDay == 0)
		return &time;
	
	tempDec = time.day - numDay;
	
	while (tempDec < 0){
		time = *decMonth(&time,1);
		tempDec += maxDayInMonth(time.month, time.year);
		
	}
	time.day = tempDec;
	return &time;
}

wtc_time_t* addHour (wtc_time_t* initTime, uint8_t numHour){
	wtc_time_t time = *initTime;
	if (numHour == 0)
		return &time;
	
	time.hour += numHour;
	if (time.hour >= 24){
		uint16_t dec = time.hour / 24;
		time = *addDay(&time,dec);
		time.hour -= dec*24;
	}
	return &time;
}
wtc_time_t* decHour (wtc_time_t* initTime, uint8_t numHour){
	wtc_time_t time = *initTime;
	int16_t tempDec = 0;
	
	if (numHour == 0)
		return &time;
	
	tempDec = time.hour - numHour;
	if (tempDec < 0){
		uint16_t dec = tempDec / 24;
		time = *decDay(&time, dec);	
		tempDec += dec*24;
		if (tempDec < 0){
			time = *decDay(&time, 1);
			tempDec += 24;
		}
		time.hour = tempDec;
	} else {
		time.hour -= numHour;
	}
	
	return &time;
}

wtc_time_t* addMinute (wtc_time_t* initTime, uint8_t numMinute){
	wtc_time_t time = *initTime;
	if (numMinute == 0)
		return &time;
	
	time.minute += numMinute;
	if (time.minute >= 60){
		uint16_t dec = time.minute / 60;
		time = *addHour(&time,dec);
		time.minute -= dec*60;
	}
	return &time;
}
wtc_time_t* decMinute (wtc_time_t* initTime, uint8_t numMinute){
	wtc_time_t time = *initTime;
	int16_t tempDec = 0;
	
	if (numMinute == 0)
		return &time;
	
	tempDec = time.minute - numMinute;
	if (tempDec < 0){
		uint16_t dec = tempDec / 60;
		time = *decHour(&time, dec);	
		tempDec += dec*60;
		if (tempDec < 0){
			time = *decHour(&time, 1);
			tempDec += 60;
		}
		time.minute = tempDec;
	} else {
		time.minute -= numMinute;
	}
	return &time;
}

wtc_time_t* addSec (wtc_time_t* initTime, uint8_t numSec){
	wtc_time_t time = *initTime;
	if (numSec == 0)
		return &time;
	
	time.second += numSec;
	if (time.second >= 60){
		uint16_t dec = time.second / 60;
		time = *addMinute(&time,dec);
		time.second -= dec*60;
	}
	return &time;
}
wtc_time_t* decSec (wtc_time_t* initTime, uint8_t numSec){
	int16_t tempDec = 0;
	wtc_time_t time = *initTime;
	if (numSec == 0)
		return &time;
	
	tempDec = time.second - numSec;
	if (tempDec < 0){
		uint16_t dec = tempDec / 60;
		time = *decMinute(&time, dec);	
		tempDec += dec*60;
		if (tempDec < 0){
			time = *decMinute(&time, 1);
			tempDec += 60;
		}
		time.second = tempDec;
	} else {
		time.second -= numSec;
	}
	return &time;
}

//firstTime + secondTime
wtc_time_t* addDateTime (wtc_time_t* firstTime, wtc_time_t* secondTime){
	wtc_time_t tempTime = *firstTime;
	tempTime = *addSec(&tempTime, secondTime->second);
	tempTime = *addMinute(&tempTime, secondTime->minute);
	tempTime = *addHour(&tempTime, secondTime->hour);
	tempTime = *addDay(&tempTime, secondTime->day);
	tempTime = *addMonth(&tempTime, secondTime->month);
	tempTime.year += secondTime->year;
	return &tempTime;
}

//firstTime - secondTime
wtc_time_t* decDateTime (wtc_time_t* firstTime, wtc_time_t* secondTime){
	wtc_time_t tempTime = *firstTime;
	tempTime = *decSec(&tempTime, secondTime->second);
	tempTime = *decMinute(&tempTime, secondTime->minute);
	tempTime = *decHour(&tempTime, secondTime->hour);
	tempTime = *decDay(&tempTime, secondTime->day);
	tempTime = *decMonth(&tempTime, secondTime->month);
	tempTime.year -= secondTime->year;
	return &tempTime;
}

wtc_time_t* addDate (wtc_time_t* firstTime, wtc_time_t* secondTime){
	wtc_time_t tempTime = *firstTime;
	tempTime = *addDay(&tempTime, secondTime->day);
	tempTime = *addMonth(&tempTime, secondTime->month);
	tempTime.year += secondTime->year;
	return &tempTime;
}

wtc_time_t* addTime (wtc_time_t* firstTime, wtc_time_t* secondTime){
	wtc_time_t tempTime = *firstTime;
	tempTime = *addSec(&tempTime, secondTime->second);
	tempTime = *addMinute(&tempTime, secondTime->minute);
	tempTime = *addHour(&tempTime, secondTime->hour);
	return &tempTime;
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
			errorCause = "Неправильный месяц";
			Error_Handler();
		}
	}
}
uint8_t* getFormatedTime(uint8_t* fStr){
	return getFormatedTimeFromSource(fStr, &sysTime);
}
uint8_t* getFormatedTimeFromSource(uint8_t* fStr, wtc_time_t *source){
	uint8_t curCh = 0;
	yearNum = 0, strLength = 0, monthNum = 0, dayNum = 0, hourNum =0, minuteNum = 0, secondNum = 0;
	ptr = formatedString;
	
	
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
					dayNamePtr= dayNamePtr + getDayNameByDate(&sysTime);
					
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
void changeTimeLanguage(language_t lang){
	if (lang == RUSSIAN){
		dateName = &ruName;
	}
	if (lang == ENGLISH){
		dateName = &engName;
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
	
	testTime = *addMonth(&testTime, 1);
	assert_param(testTime.year == 2022 &&
				testTime.month == 10 && 
				testTime.day == 15);
	
	testTime = *addMonth(&testTime, 3);
	assert_param(testTime.year == 2023 &&
				testTime.month == 1 && 
				testTime.day == 15);
	
	testTime.day = 31;
	testTime = *addMonth(&testTime, 1);
	assert_param(testTime.year == 2023 &&
				testTime.month == 2 && 
				testTime.day == 28);
	
	testTime = *addMonth(&testTime, 1);
	assert_param(testTime.year == 2023 &&
				testTime.month == 3 && 
				testTime.day == 28);
				
	testTime.day = 31;			
	testTime = *addMonth(&testTime, 12);
	assert_param(testTime.year == 2024 &&
				testTime.month == 3 && 
				testTime.day == 31);
				
	testTime = *decMonth(&testTime, 1);
	assert_param(testTime.year == 2024 &&
				testTime.month == 2 && 
				testTime.day == 29);	
			
	testTime = *decMonth(&testTime, 12);
	assert_param(testTime.year == 2023 &&
				testTime.month == 2 && 
				testTime.day == 28);
				
	testTime = *decMonth(&testTime, 1);
	assert_param(testTime.year == 2023 &&
				testTime.month == 1 && 
				testTime.day == 31);	

	testTime = *decMonth(&testTime, 3);
	assert_param(testTime.year == 2022 &&
				testTime.month == 10 && 
				testTime.day == 31);	
	
	testTime.day = 15;	
	testTime = *decMonth(&testTime, 2);
	assert_param(testTime.year == 2022 &&
				testTime.month == 8 && 
				testTime.day == 15);	
				
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
				
	uint32_t intTestTime = wtcTimeToInt(&testTime);
	wtc_time_t newTestTime = intToWTCTime(intTestTime);
	assert_param(compareDateTime(&newTestTime,&testTime) == 0);
}

 