/**
  ******************************************************************************
  * @file           : Alarm.c
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
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
void (*funcPtr)();
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
void waitTime(wtc_time_t time, void *func()){
	struct tm alarmTimeSt = wtcTimeToStdTime(time);
	
	/* Enter Initialization mode */
	while (!LL_RTC_IsActiveFlag_RTOF(RTC));
  if (LL_RTC_EnterInitMode(RTC) != ERROR)
  {	
		time_t rawtime = mktime(&alarmTimeSt);
    LL_RTC_ALARM_Set(RTC, rawtime);
  }
  /* Exit Initialization mode */
  LL_RTC_ExitInitMode(RTC);
	
	funcPtr = func;
}

void ALARM_INTERRUPT(){
	if (funcPtr != NULL){
		(*funcPtr)();
	}
}