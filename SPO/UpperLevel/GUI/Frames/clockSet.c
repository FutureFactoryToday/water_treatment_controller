/**
  ******************************************************************************
  * @file           : _ClockSet_.c
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
#include "math.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
 	#define FIRST_LINE_Y MAINBAR_SIZE_Y + 10
	#define HOUR_LABEL_SIZE_X 100	
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static wtc_time_t displayedTime = {0}, nullTime = {0};
static button_t hourBut, minBut;
/* Private function prototypes -----------------------------------------------*/
static void createFrame();
/* Private user code ---------------------------------------------------------*/
wtc_time_t CSF_showFrame(){
	
	displayedTime = *getTime();
	
	createFrame();
	
	while(1)
    {
        if (updateFlags.sec == true){
            drawClock();
            updateFlags.sec = false;
        }
			
			if (updateFlags.sec){
				updateFlags.sec = false;
			} 
			if (hourBut.isPressed == true){
				drawTextLabel(BSP_LCD_GetXSize()/2 + GAP,BSP_LCD_GetYSize()/2 - GAP - BSP_LCD_GetFont()->height, HOUR_LABEL_SIZE_X, BSP_LCD_GetFont()->height + 10, getFormatedTimeFromSource("hh",&displayedTime));
				hourBut.isPressed = false;
			}
			
			if (minBut.isPressed == true){
				drawTextLabel(BSP_LCD_GetXSize()/2 + GAP,BSP_LCD_GetYSize()/2 + GAP, HOUR_LABEL_SIZE_X, BSP_LCD_GetFont()->height + 10, getFormatedTimeFromSource("mm",&displayedTime));
				minBut.isPressed = false;
			}
			
			if (hourBut.isReleased == 1){
				int16_t time = ShowKeyboardFrame(0,23);
				if (time > 0){
					displayedTime.hour = time;
				}
				hourBut.isReleased = 0;
				createFrame();
			}
			
			if (minBut.isReleased == 1){
				int16_t time = ShowKeyboardFrame(0,59);
				if (time > 0){
					displayedTime.minute = time;
				}
				minBut.isReleased = 0;
				createFrame();
			}
			
			if (retBut.isReleased == 1){
				retBut.isReleased = 0;
				return nullTime;
			}
			if (okBut.isReleased == 1){
				okBut.isReleased = 0;
				return displayedTime;
			}
			if (cancelBut.isReleased == 1){
				cancelBut.isReleased = 0;
				return nullTime;
			}
    }
}


void createFrame(){
	//Static refresh
	//enableClockDraw = false;

	TC_clearButtons();
	BSP_LCD_Clear(MID_COLOR);
	drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_MENU[0]);
	
	drawStatusBarOkCancel();

	BSP_LCD_SetBackColor(MID_COLOR);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//BSP_LCD_DrawHLine(BSP_LCD_GetXSize()/2, 0, BSP_LCD_GetYSize());
	uint8_t hourText = BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 - 100, BSP_LCD_GetYSize()/2 - GAP - BSP_LCD_GetFont()->height+5,ITEM_CLOCKSET_FRAME[0],LEFT_MODE);
	uint8_t minText = BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 - 100, BSP_LCD_GetYSize()/2 + GAP+5,ITEM_CLOCKSET_FRAME[1],LEFT_MODE);
//	uint8_t hourLength = BSP_LCD_DisplayStringAt(MAX(hourText,minText) + 2, FIRST_LINE_Y, getFormatedTimeFromSource("hh",&displayedTime),LEFT_MODE); 
//	uint8_t minLength = BSP_LCD_DisplayStringAt(MAX(hourText,minText) + 2, FIRST_LINE_Y + BSP_LCD_GetFont()->height + GAP, getFormatedTimeFromSource("mm",&displayedTime),LEFT_MODE);


	hourBut = drawTextLabel(BSP_LCD_GetXSize()/2 + GAP,BSP_LCD_GetYSize()/2 - GAP - BSP_LCD_GetFont()->height, HOUR_LABEL_SIZE_X, BSP_LCD_GetFont()->height + 10, getFormatedTimeFromSource("hh",&displayedTime));
	minBut = drawTextLabel(BSP_LCD_GetXSize()/2 + GAP,BSP_LCD_GetYSize()/2 + GAP, HOUR_LABEL_SIZE_X, BSP_LCD_GetFont()->height + 10, getFormatedTimeFromSource("mm",&displayedTime));

	
	TC_addButton(&okBut);
	TC_addButton(&cancelBut);
	TC_addButton(&retBut);
	TC_addButton(&minBut);
	TC_addButton(&hourBut);
}
