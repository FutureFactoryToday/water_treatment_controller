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
 
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
time_t sysTime;
bool isInited;

/* Private function prototypes -----------------------------------------------*/
bool isLeapYear(uint16_t year);
uint8_t maxDayInMonth(uint8_t month);
uint8_t intToChar(uint8_t num);
uint16_t POWC(uint8_t a,uint8_t b); 
/* Private user code ---------------------------------------------------------*/
uint16_t POWC (uint8_t a, uint8_t b){
	while(b !=0){a = a*a; b--;}
	return a;
}
void initTime(){
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
	return (year%4 == 0);
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
	uint8_t yearNum = 0, strLength = 0, monthNum = 0, dayNum = 0, hourNum =0, minuteNum = 0, secondNum = 0;
	uint8_t *ptr = fStr;
	while(*ptr!= 0){
		strLength++;
		switch (*ptr++){
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
	}
	uint16_t bcdYear = __LL_RTC_CONVERT_BIN2BCD((sysTime.year/1000 + sysTime.year/100)/100);
	uint8_t bcdMonth = __LL_RTC_CONVERT_BIN2BCD(sysTime.month);
	uint8_t bcdDay = __LL_RTC_CONVERT_BIN2BCD(sysTime.day);
	uint8_t bcdHour = __LL_RTC_CONVERT_BIN2BCD(sysTime.hour);
	uint8_t bcdMinute = __LL_RTC_CONVERT_BIN2BCD(sysTime.minute);
	uint8_t bcdSecond = __LL_RTC_CONVERT_BIN2BCD(sysTime.second);
	while(*fStr!= 0){
		switch (*fStr){
			case 'Y':{
					*fStr = intToChar(bcdYear/(POWC(10,yearNum--)));
				break;
			}
			case 'M':{
				*fStr = intToChar(bcdMonth/(POWC(10,monthNum--)));
				break;
			}
			case 'D':{
				*fStr = intToChar(bcdDay/(POWC(10,dayNum--)));
				break;
			}
			case 'h':{
				*fStr = intToChar(bcdHour/(POWC(10,hourNum--)));
				break;
			}
			case 'm':{
				*fStr = intToChar(bcdMinute/(POWC(10,minuteNum--)));
				break;
			}
			case 's':{
				*fStr = intToChar(bcdSecond/(POWC(10,secondNum--)));
				break;
			}
			default: break;
		}
		*fStr++;
	}
}

uint8_t intToChar(uint8_t num){
	assert_param(num< 10);
	uint32_t modNum = num;
	if (num == 0){
		return 48;
	} else {
		return 48 + num;
	}
	
}