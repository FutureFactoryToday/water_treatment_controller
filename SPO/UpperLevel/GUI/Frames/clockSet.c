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

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
 	#define FIRST_LINE_Y MAINBAR_POS_Y
	#define GAP 20
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static wtc_time_t displayedTime = {0}, nullTime = {0};
static button_t hourBut, minBut;
/* Private function prototypes -----------------------------------------------*/
static void 	createFrame();
/* Private user code ---------------------------------------------------------*/
wtc_time_t CSF_showFrame(){
	
	displayedTime = *getTime();
	
	createFrame();
	
	while(1)
    {
			
			if (updateFlags.sec){
				updateFlags.sec = false;
			} 
			if (hourBut.isPressed == true){
				
				hourBut.isPressed = false;
			}
			
			if (minBut.isPressed == true){
				
				minBut.isPressed = false;
			}
			
			if (hourBut.isReleased == 1){
				int16_t time = ShowKeyboardFrame(0,24);
				if (time > 0){
					displayedTime.hour = time;
				}
				hourBut.isReleased = 0;
				createFrame();
			}
			
			if (minBut.isReleased == 1){
				int16_t time = ShowKeyboardFrame(0,24);
				if (time > 0){
					displayedTime.minute = time;
				}
				minBut.isReleased = 0;
				createFrame();
			}
			
			if (retBut.isReleased == 1){
				retBut.isReleased = 0;
				return displayedTime;
			}
			if (okBut.isReleased == 1){
				okBut.isReleased = 0;
				return nullTime;
			}
			if (cancelBut.isReleased == 1){
				cancelBut.isReleased = 0;
				return nullTime;
			}
    }
}


void createFrame(){
	//Static refresh
	enableClockDraw = false;

	TC_clearButtons();
	BSP_LCD_Clear(MID_COLOR);
	drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_MENU[0]);
	
	drawStatusBarOkCancel();

	
	
//	uint16_t dateTextLength = BSP_LCD_DisplayStringAt(GAP, FIRST_LINE_Y,ITEM_CLOCKSET_FRAME[0],LEFT);
//	BSP_LCD_DrawBitmap(BSP_LCD_GetXSize()/2 + dateTextLength/2,MID_CLOCK_Y + BSP_LCD_GetFont()->height + (BSP_LCD_GetFont()->height - rightArowImg.infoHeader.biHeight)/2,&rightArowImg);
//	dateSetButton.x = BSP_LCD_GetXSize()/2 + dateTextLength/2;
//	dateSetButton.y = MID_CLOCK_Y + BSP_LCD_GetFont()->height;
//	dateSetButton.xSize = rightArowImg.infoHeader.biWidth;
//	dateSetButton.ySize = rightArowImg.infoHeader.biHeight;
//	
//	timeSetButton.x = BSP_LCD_GetXSize()/2 - timeLength/2;
//	timeSetButton.y = MID_CLOCK_Y;
//	timeSetButton.xSize = timeLength + 10;
//	timeSetButton.ySize = MID_CLOCK_Y + BSP_LCD_GetFont()->height;
	
	TC_addButton(&okBut);
	TC_addButton(&cancelBut);
	TC_addButton(&retBut);
	TC_addButton(&minBut);
	TC_addButton(&hourBut);
}
