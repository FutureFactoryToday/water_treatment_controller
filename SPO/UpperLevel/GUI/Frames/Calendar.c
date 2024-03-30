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
#include "Calendar.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
#define LINE_1 MAINBAR_SIZE_Y + GAP
#define LINE_2 (LINE_1 + 40)
#define LINE_3 (LINE_2 + 40)
#define LINE_4 (LINE_3 + 40)
#define LINE_5 (LINE_4 + 40)

#define BUT_WIDTH 36
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
 static wtc_time_t displayedTime;
 static button_t setMonth, setDay, setYear;
 static uint8_t lineCoord[] = {LINE_1,LINE_2,LINE_3,LINE_4,LINE_5};
/* Private function prototypes -----------------------------------------------*/
 static void createFrame();
 void drawCalendar ();
static void drawMonth();
static void drawDay();
static void drawYear();
/* Private user code ---------------------------------------------------------*/

wtc_time_t CAL_showFrame(wtc_time_t* time){
	
	displayedTime = *time;
	
	createFrame();
	
	while(1)
    {	
			if (updateFlags.sec){
				displayedTime = *addSec(&displayedTime,1);
				drawClock();
				updateFlags.sec = false;
			} 
			if (setMonth.isPressed == 1){
				drawDarkTextLabel(BSP_LCD_GetXSize()/2 + GAP, BSP_LCD_GetYSize()/2 - 10, 150, 40,getFormatedTimeFromSource("MM",&displayedTime));
				setMonth.isPressed = 0;
			}
			if (setDay.isPressed == 1){
				drawDarkTextLabel(BSP_LCD_GetXSize()/2 + GAP, BSP_LCD_GetYSize()/2 - 10 - 60, 150, 40,getFormatedTimeFromSource("DD",&displayedTime));
				setDay.isPressed = 0;
			}
			if (setYear.isPressed == 1){
				drawDarkTextLabel(BSP_LCD_GetXSize()/2 + GAP, BSP_LCD_GetYSize()/2 - 10 + 60, 150, 40,getFormatedTimeFromSource("YYYY",&displayedTime));
				setYear.isPressed = 0;
			}
			if (setMonth.isReleased == 1){
				int32_t newMonth = ShowKeyboardFrame(1, 12);
				if (newMonth > 0) {
					displayedTime.month = newMonth;
					if (displayedTime.day > maxDayInMonth( displayedTime.month,displayedTime.year)){
						 displayedTime.day = maxDayInMonth(  displayedTime.month,displayedTime.year);
					}
					
				}
				createFrame();
				setMonth.isReleased = 0;
			}
			if (setDay.isReleased == 1){
				int32_t newDay = ShowKeyboardFrame(1, 31);
				if (newDay > 0) {
					if (newDay > maxDayInMonth( displayedTime.month,displayedTime.year)){
						 displayedTime.day = maxDayInMonth(  displayedTime.month,displayedTime.year);
					} else {
						displayedTime.day = newDay;
					}
					
				}
				createFrame();
				setDay.isReleased = 0;
			}
			if (setYear.isReleased == 1){
				int32_t newYear = ShowKeyboardFrame(2020, 2050);
				if (newYear > 0) {
					displayedTime.year = newYear;
					if (displayedTime.day > maxDayInMonth( displayedTime.month,displayedTime.year)){
						 displayedTime.day = maxDayInMonth(  displayedTime.month,displayedTime.year);
					}
					
				}
				createFrame();
				setYear.isReleased = 0;
			}
			if (retBut.isReleased == 1){
				
				retBut.isReleased = 0;
				return (wtc_time_t){0};
			}
			if (okBut.isReleased == true){
				okBut.isReleased = false;
				return displayedTime;
			}
			if (cancelBut.isReleased == true){
				cancelBut.isReleased = false;
				return (wtc_time_t){0};
			}
    }
}

void createFrame (void){
	enableClockDraw = false;

	TC_clearButtons();
	BSP_LCD_Clear(MID_COLOR);
	drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_MENU[0]);
	
	drawStatusBarOkCancel();
	
	drawDay();
	drawMonth();
	drawYear();
	TC_addButton(&setDay);
	TC_addButton(&setMonth);
	TC_addButton(&setYear);
	TC_addButton(&retBut);
	TC_addButton(&cancelBut);
	TC_addButton(&okBut);
}

void drawMonth(){
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 - 120,BSP_LCD_GetYSize()/2 - 10, ITEM_CALENDAR_FRAME[1], LEFT_MODE);
	setMonth = drawTextLabel(BSP_LCD_GetXSize()/2 + GAP, BSP_LCD_GetYSize()/2 - 10, 150, 40,getFormatedTimeFromSource("MM",&displayedTime));	
}
void drawYear(){
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 - 120,BSP_LCD_GetYSize()/2 - 10 - 60, ITEM_CALENDAR_FRAME[0], LEFT_MODE);
	setDay = drawTextLabel(BSP_LCD_GetXSize()/2 + GAP, BSP_LCD_GetYSize()/2 - 10 - 60, 150, 40,getFormatedTimeFromSource("DD",&displayedTime));	
}
void drawDay(){
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 - 120,BSP_LCD_GetYSize()/2 - 10 + 60, ITEM_CALENDAR_FRAME[2], LEFT_MODE);
	setYear = drawTextLabel(BSP_LCD_GetXSize()/2 + GAP, BSP_LCD_GetYSize()/2 - 10 + 60, 150, 40,getFormatedTimeFromSource("YYYY",&displayedTime));	
}

//void drawMonth (void){
//	TC_clearButtons();
//	prevMonth = drawFillButton(50,LINE_1,40,40,"",false);  
//	nextMonth = drawFillButton(50,LINE_3,40,40,"",false);
//	
//	  
//	setYear = drawTextLabel(50,LINE_4+20,100,40,getFormatedTimeFromSource("YYYY",&displayedTime));
//	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//	BSP_LCD_DisplayStringAt(GAP, LINE_2, getFormatedTimeFromSource("MMM",&displayedTime),CENTER_MODE);
//	//BSP_LCD_DisplayStringAt(GAP, LINE_5, getFormatedTimeFromSource("YYYY",&displayedTime),CENTER_MODE);
//	uint8_t col = 0, row = 0, day = 0;
//	
//	while (day != maxDayInMonth(displayedTime.month,displayedTime.year)){
//		 //uint8_t ch = intToStr(day + 1);
//		 daysBut[day] = drawFillButton(190 + col*(BUT_WIDTH + 5), lineCoord[row],BUT_WIDTH, BSP_LCD_GetFont()->height + 2, intToStr(day + 1), false);
//		day++;
//		col++;
//		if (day > 0 && day%7 == 0) {
//			col = 0;
//			row++;
//		}
//	}
//	
//	
//}