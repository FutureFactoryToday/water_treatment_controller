/**
  ******************************************************************************
  * @file           : Calendar.c
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
 static wtc_time_t displayedTime;
 static button_t nextMonth, prevMonth, setYear;
/* Private function prototypes -----------------------------------------------*/
 static void createFrame();
 void drawCalendar ();
 void drawMonth();
/* Private user code ---------------------------------------------------------*/

void CAL_showFrame(wtc_time_t* time){
	
	displayedTime = *time;
	TC_clearButtons();
	createFrame();
	
	while(1)
    {	
			if (updateFlags.sec){
				displayedTime = *addSec(&displayedTime,1);
				drawClock();
				updateFlags.sec = false;
			} 
			if (nextMonth.isPressed == 1){
				
				nextMonth.isPressed = 0;
			}
			if (prevMonth.isPressed == 1){
				
				prevMonth.isPressed = 0;
			}
			if (setYear.isPressed == 1){
				
				setYear.isPressed = 0;
			}
			if (retBut.isPressed == 1){
				
				retBut.isPressed = 0;
				return;
			}
//			if (touchHandler()){
//					if (refreshFrame()){
//						return;
//					}
//			}		
    }
}

void createFrame (void){
	drawClock();
	
}