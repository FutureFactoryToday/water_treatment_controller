/**
  ******************************************************************************
  * @file           : timeSetFrame.c
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
#include "timeSetFrame.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define TIME_STR_WD "DD.MM.YYYY hh:mm:ss"
#define TIME_STR_WOD "DD.MM.YYYY hh:mm:ss"

#define MAIN_TEXT 0
#define SETTINGS_UP_TEXT 1
#define YEAR_TEXT 2
#define MONTH_TEXT 3
#define DAY_TEXT 4
#define HOUR_TEXT 5
#define MIN_TEXT 6
#define SAVE_TEXT 7
#define BACK_TEXT 8
#define EDIT_TEXT 9
#define CH_YEAR_TEXT 10
#define CH_MONTH_TEXT 11
#define CH_DAY_TEXT 12
#define CH_HOUR_TEXT 13
#define CH_MINUTE_TEXT 14

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
//uint8_t* ITEM_TIME_enText[] = {
//	"Date and time",
//	"Set date and time",
//	"YEAR",
//	"MONTH",
//	"DAY",
//	"HOUR",
//	"MINUTE",
//	"SAVE",
//	"DISCARD",
//	"Set date and time",
//	"Enter year",
//	"Enter month",
//	"Enter day",
//	"Enter hour",
//	"Enter minute"
//};

uint8_t** frameText;
uint8_t* timeStr = TIME_STR_WD;

char monthTable[7][7];
wtc_time_t displayedTime;
wtc_time_t editedTime;
extern date_name_t* dateName;

uint16_t setTimeButtonLength;
bool editBoxesShow = 0;
uint32_t rightButX;
button_t timeSetButton, dateSetButton;

/* Private function prototypes -----------------------------------------------*/
uint8_t refreshFrame();
uint8_t touchHandler();
void createFrame();
void drawMonth(void);
uint16_t drawMidClock(bool checked);
void drawEditBoxes(wtc_time_t editTime);
bool timeSetPressed = false;
/* Private user code ---------------------------------------------------------*/

void TSF_showFrame(){
	

	frameText = &ITEM_TIME_ruText;
	uint8_t memSec = getTime()->second;
	
	wtc_time_t *sysTimePtr = getTime();
	displayedTime = *sysTimePtr;
	
	createFrame();
	
	while(1)
    {
			
			if (updateFlags.sec){
				displayedTime = *addSec(&displayedTime,1);
				drawMidClock(timeSetPressed);
				updateFlags.sec = false;
			} 
			if (timeSetButton.isPressed == true){
				timeSetPressed = true;
				drawMidClock(timeSetPressed);
				timeSetButton.isPressed = false;
			}
			if (timeSetButton.isReleased == 1){
				int16_t time = ShowKeyboardFrame(0,2400);
				if (time > 0){
				uint8_t hour = time/100;
				uint8_t minutes = time - hour*100;
				displayedTime.hour = hour;
				displayedTime.minute = minutes;
				
				
				}
				timeSetPressed = false;
				drawMidClock(timeSetPressed);
				timeSetButton.isReleased = 0;
				createFrame();
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


void createFrame(){
	//Static refresh
	enableClockDraw = false;

	TC_clearButtons();
	BSP_LCD_Clear(MID_COLOR);
	drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_MENU[0]);
	
	drawStatusBarOkCancel();
	uint16_t timeLength = drawMidClock(false);
	
	uint16_t dateTextLength = BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, MID_CLOCK_Y + BSP_LCD_GetFont()->height,getFormatedTimeFromSource("DD MMM YYYY ", &displayedTime),CENTER_MODE);
	BSP_LCD_DrawBitmap(BSP_LCD_GetXSize()/2 + dateTextLength/2,MID_CLOCK_Y + BSP_LCD_GetFont()->height + (BSP_LCD_GetFont()->height - rightArowImg.infoHeader.biHeight)/2,&rightArowImg);
	dateSetButton.x = BSP_LCD_GetXSize()/2 + dateTextLength/2;
	dateSetButton.y = MID_CLOCK_Y + BSP_LCD_GetFont()->height;
	dateSetButton.xSize = rightArowImg.infoHeader.biWidth;
	dateSetButton.ySize = rightArowImg.infoHeader.biHeight;
	
	timeSetButton.x = BSP_LCD_GetXSize()/2 - timeLength/2;
	timeSetButton.y = MID_CLOCK_Y;
	timeSetButton.xSize = timeLength + 10;
	timeSetButton.ySize = MID_CLOCK_Y + BSP_LCD_GetFont()->height;
	
	TC_addButton(&okBut);
	TC_addButton(&timeSetButton);
	TC_addButton(&dateSetButton);
}
uint16_t drawMidClock (bool checked){
	BSP_LCD_SetFont(&Oxygen_Mono_24);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(0,MID_CLOCK_Y,BSP_LCD_GetXSize(),BSP_LCD_GetFont()->height);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	uint8_t* formatter = (getTime()->second % 2)? "hh:mm " : "hh mm ";
	uint16_t timeLength = BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,MID_CLOCK_Y,getFormatedTimeFromSource(formatter, &displayedTime), CENTER_MODE);
	
	if (!checked){
		BSP_LCD_SetTextColor(DARK_COLOR);
		//BSP_LCD_DrawBitmap(BSP_LCD_GetXSize()/2 + timeLength/2,MID_CLOCK_Y + (BSP_LCD_GetFont()->height - rightArowImg.infoHeader.biHeight)/2,&rightArowImg);
		BSP_LCD_FillTriangle(BSP_LCD_GetXSize()/2 + timeLength/2 + 5, MID_CLOCK_Y + 10, 
													BSP_LCD_GetXSize()/2 + timeLength/2 + 5, MID_CLOCK_Y + 20, 
													BSP_LCD_GetXSize()/2 + timeLength/2 + 5 + 5, MID_CLOCK_Y + 15); 
				
	} else {
		//BSP_LCD_DrawBitmap(BSP_LCD_GetXSize()/2 + timeLength/2,MID_CLOCK_Y + (BSP_LCD_GetFont()->height - rightArowImg.infoHeader.biHeight)/2,&rightArowImg);
		BSP_LCD_SetTextColor(LIGHT_COLOR);
		//BSP_LCD_DrawBitmap(BSP_LCD_GetXSize()/2 + timeLength/2,MID_CLOCK_Y + (BSP_LCD_GetFont()->height - rightArowImg.infoHeader.biHeight)/2,&rightArowImg);
		BSP_LCD_FillTriangle(BSP_LCD_GetXSize()/2 + timeLength/2 + 5, MID_CLOCK_Y + BSP_LCD_GetFont()->height/2 - 5, 
													BSP_LCD_GetXSize()/2 + timeLength/2 + 15, MID_CLOCK_Y + BSP_LCD_GetFont()->height/2 - 5, 
													BSP_LCD_GetXSize()/2 + timeLength/2 + 10, MID_CLOCK_Y + BSP_LCD_GetFont()->height/2 + 5); 

	}
	return timeLength;
}


void drawMonth(void){
	uint32_t tableLength = 0;
	uint32_t curY = MONTH_GRID_Y1;
	uint32_t rowMid[DAYS_NUM];
	BSP_LCD_SetFont(&Oxygen_Mono_16);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	
	
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(BSP_LCD_GetXSize(), MID_CLOCK_Y, BSP_LCD_GetXSize()/2 - 1, STATUSBAR_POS_Y - MID_CLOCK_Y);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	curY+=BSP_LCD_GetFont()->height;
	uint32_t rowS, rowE;
	
	for( uint8_t i = 0; i < DAYS_NUM; i++){
		BSP_LCD_DrawVLine(FIRST_COL_X + tableLength, curY ,7 * BSP_LCD_GetFont()->height);
		tableLength += COL_GAP;
		rowS = FIRST_COL_X + tableLength;
		tableLength += BSP_LCD_DisplayStringAt (FIRST_COL_X + tableLength, curY, dateName->dayShortName[i], LEFT_MODE);
		tableLength += COL_GAP;
		rowE = FIRST_COL_X + tableLength;
		rowMid[i] = rowS + (rowE - rowS)/2;
	}
	BSP_LCD_DrawVLine(FIRST_COL_X + tableLength,curY,7 * BSP_LCD_GetFont()->height);
	
	
	BSP_LCD_DisplayStringAt (tableLength/2, MONTH_GRID_Y1, getFormatedTimeFromSource("MMM YYYY", &displayedTime), CENTER_MODE);
	BSP_LCD_DrawBitmap(MONTH_GRID_X1, MONTH_GRID_Y1 +  5, &leftArowImg);
	BSP_LCD_DrawBitmap(tableLength - rightArowImg.infoHeader.biWidth, MONTH_GRID_Y1 + 5, &rightArowImg);
	rightButX = tableLength;
	uint8_t firstDay = getDayNameByDate(&displayedTime);
	uint8_t dispDayOfMonthNum = 1;
	curY = MONTH_GRID_Y1 + 2 * BSP_LCD_GetFont()->height;
	for (uint8_t row = 0; row < 6; row++){
		for (uint8_t col = 0; col < 7; col++){
			if (displayedTime.year == getTime()->year && 
				displayedTime.month == getTime()->month && 
				dispDayOfMonthNum == getTime()->day){
					BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
				} else {
					BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
				}
			if (row == 0){
				if (col >= firstDay){
					BSP_LCD_DisplayStringAt (rowMid[col], curY, intToStr(dispDayOfMonthNum++), CENTER_MODE);
				}
			} else {
				BSP_LCD_DisplayStringAt (rowMid[col], curY, intToStr(dispDayOfMonthNum++), CENTER_MODE);
			}
			if (dispDayOfMonthNum > maxDayInMonth(displayedTime.month, displayedTime.year)){
				row = 7;
				break;
			}
		}
		curY+=BSP_LCD_GetFont()->height;
	}
	curY = MONTH_GRID_Y1 + BSP_LCD_GetFont()->height;
	for (uint8_t i = 0; i < 8; i++){
		BSP_LCD_DrawHLine(MONTH_GRID_X1, curY, tableLength);
		curY+=BSP_LCD_GetFont()->height;
	}
	
	
}
