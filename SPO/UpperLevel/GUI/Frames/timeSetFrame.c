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
char* ruText[] = {
	"ВРЕМЯ/ДАТА",
	"Настройка времени и даты",
	"ГОД",
	"МЕСЯЦ",
	"ДЕНЬ",
	"ЧАС",
	"МИНУТА",
	"ЗАПИСАТЬ",
	"ОТМЕНА",
	"Настройка времени и даты",
	"Введите год",
	"Введите месяц",
	"Введите день",
	"Введите час",
	"Введите минуты"
};
char* enText[] = {
	"Date and time",
	"Set date and time",
	"YEAR",
	"MONTH",
	"DAY",
	"HOUR",
	"MINUTE",
	"SAVE",
	"DISCARD",
	"Set date and time",
	"Enter year",
	"Enter month",
	"Enter day",
	"Enter hour",
	"Enter minute"
};

uint8_t** frameText;
uint8_t* timeStr = TIME_STR_WD;

char monthTable[7][7];
wtc_time_t displayedTime;
wtc_time_t editedTime;
extern date_name_t* dateName;

uint16_t setTimeButtonLength;
bool editBoxesShow = 0;
uint32_t rightButX;
/* Private function prototypes -----------------------------------------------*/
uint8_t refreshFrame();
uint8_t touchHandler();
void createFrame();
void drawMonth(void);
void drawClock(void);
void drawEditBoxes(wtc_time_t editTime);
int32_t callKeyboard(uint32_t min, uint32_t max, uint8_t* text);
/* Private user code ---------------------------------------------------------*/

void TSF_showFrame(){
	if (sysParam.lang == ENGLISH){
		frameText = &enText;
	} else {
		frameText = &ruText;
	}
	uint8_t memSec = getTime()->second;
	
	wtc_time_t *sysTimePtr = getTime();
	displayedTime = *sysTimePtr;
	
	createFrame();
	
	while(1)
    {
			if (memSec != getTime()->second){
				drawClock();
			} 
			if (touchHandler()){
					if (refreshFrame()){
						return;
					}
			}		
    }
}

uint8_t refreshFrame(){
	/*Кнопка Установки времени*/
	if (isInRectangle(tsState.X,tsState.Y,CLOCK_EDIT_BUT_X,CLOCK_EDIT_BUT_Y,setTimeButtonLength + 5,Oxygen_Mono_20.height+3))
  {
		if (!editBoxesShow)
		{
			editedTime = *getTime();
			drawEditBoxes(*getTime());
			editBoxesShow = 1;
		} else {
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			BSP_LCD_FillRect(BSP_LCD_GetXSize()/2 + 1, MAINBAR_SIZE_Y, BSP_LCD_GetXSize()/2, STATUSBAR_POS_Y - MAINBAR_SIZE_Y);
			
			editBoxesShow = 0;
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		}
		
	}
	/* Установка времени*/
	if (editBoxesShow){
		//Настраиваем год
		if (isInRectangle(tsState.X,tsState.Y,BOX_X,YEAR_LINE_Y - 1,4*15,SETTINGS_FONT.height+2))
		{
			int32_t kbResult = callKeyboard(0, 9999, (*(frameText + CH_YEAR_TEXT)));
			if (kbResult >= 0){
				editedTime.year = kbResult;
				createFrame();
			}
			
		}	
		if (isInRectangle(tsState.X,tsState.Y,BOX_X,MONTH_LINE_Y - 1,9*15,SETTINGS_FONT.height+2))
		{
			int32_t kbResult = callKeyboard(1, 12, (*(frameText + CH_MONTH_TEXT)));
			if (kbResult >= 0){
				editedTime.month = kbResult;
				if (editedTime.day > maxDayInMonth(editedTime.month, editedTime.year)) {
					editedTime.day = maxDayInMonth(editedTime.month, editedTime.year);
				}
				createFrame();
			}
			
		}	
		if (isInRectangle(tsState.X,tsState.Y,BOX_X,DAY_LINE_Y - 1,4*15,SETTINGS_FONT.height+2))
		{
			int32_t kbResult = callKeyboard(1, maxDayInMonth(editedTime.month, editedTime.year), (*(frameText + CH_DAY_TEXT)));
			if (kbResult >= 0){
				editedTime.day = kbResult;
				createFrame();
			}
		}	
		if (isInRectangle(tsState.X,tsState.Y,BOX_X,HOUR_LINE_Y - 1,4*15,SETTINGS_FONT.height+2))
		{
			int32_t kbResult = callKeyboard(0, 23, (*(frameText + CH_HOUR_TEXT)));
			if (kbResult >= 0){
				editedTime.hour = kbResult;
				createFrame();
			}
		}	
		if (isInRectangle(tsState.X,tsState.Y,BOX_X,MINUTE_LINE_Y - 1,4*15,SETTINGS_FONT.height+2))
		{
			int32_t kbResult = callKeyboard(0, 59, (*(frameText + CH_MINUTE_TEXT)));
			if (kbResult >= 0){
				editedTime.minute = kbResult;
				createFrame();
			}
		}	
		if (isInRectangle(tsState.X,tsState.Y,BSP_LCD_GetXSize() - 8*10 - 10, SAVE_LINE_Y, 8*10, SETTINGS_FONT.height + 6))
		{
			editedTime.second = 0;
			setSysTime(&editedTime);
			displayedTime = *getTime();
			createFrame();
		}	
		if (isInRectangle(tsState.X,tsState.Y,CHANGE_TEXT_X, SAVE_LINE_Y, 8*10, SETTINGS_FONT.height + 6))
		{
			editedTime = *getTime();
			drawEditBoxes(*getTime());
			editBoxesShow = 1;
		}	
		
		
	}

	if (isInRectangle(tsState.X,tsState.Y,MONTH_GRID_X1, MONTH_GRID_Y1 +  5,leftArowImg.infoHeader.biWidth,leftArowImg.infoHeader.biHeight))
		{
			displayedTime.month -= 1;
			if (displayedTime.month < 1){
				displayedTime.month = 12;
				displayedTime.year -= 1;
			}
			drawMonth();
		}
	if (isInRectangle(tsState.X,tsState.Y,rightButX - rightArowImg.infoHeader.biWidth, MONTH_GRID_Y1 + 5,rightArowImg.infoHeader.biWidth,rightArowImg.infoHeader.biHeight))
		{
			displayedTime.month += 1;
			if (displayedTime.month > 12){
				displayedTime.month = 1;
				displayedTime.year += 1;
			}
			drawMonth();
		}
		//Кнопка "Назад"
	if (isInRectangle(tsState.X,tsState.Y,10, 10,gImage_RETURNARROW.infoHeader.biWidth,gImage_RETURNARROW.infoHeader.biHeight))
  {
		return 1;
	}
	return 0;
}
int32_t callKeyboard(uint32_t min, uint32_t max, uint8_t* text){
	return ShowKeyboardFrame();
}
uint8_t touchHandler(){
	BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
      touchDelay = 100;
			tsState.TouchDetected = 0;
			return 1;
		}
		else {
			tsState.TouchDetected = 0;
			return 0;
		}
		
}

void createFrame(){
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
    BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
    
    
    BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
      
	
    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
    BSP_LCD_SetFont(&Oxygen_Mono_24);
    BSP_LCD_DisplayStringAt(FRAME_NAME_TEXT_X, FRAME_NAME_TEXT_Y, (*(frameText + MAIN_TEXT)), LEFT_MODE);
        
    
    drawMonth();
    
    drawClock();
    
    BSP_LCD_SetFont(&Oxygen_Mono_20);
    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
    setTimeButtonLength = BSP_LCD_DisplayStringAt(CLOCK_EDIT_BUT_X + 3,CLOCK_EDIT_BUT_Y + 3,(*(frameText + EDIT_TEXT)),LEFT_MODE);
    BSP_LCD_DrawRect(CLOCK_EDIT_BUT_X,CLOCK_EDIT_BUT_Y ,setTimeButtonLength + 5, Oxygen_Mono_20.height+3);
    
    BSP_LCD_DrawVLine( BSP_LCD_GetXSize()/2, MAINBAR_SIZE_Y, BSP_LCD_GetYSize() - MAINBAR_SIZE_Y - STATUSBAR_SIZE_Y);
    
    if (editBoxesShow){
        drawEditBoxes(editedTime);
    }
    
    BSP_LCD_DrawBitmap(10, 10, &gImage_RETURNARROW);
        
}

void drawEditBoxes(wtc_time_t editTime){
	BSP_LCD_SetFont(&Oxygen_Mono_16);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(CHANGE_TEXT_X, FIRST_ROW_Y, (*(frameText + SETTINGS_UP_TEXT)), LEFT_MODE);
	
	BSP_LCD_SetFont(&SETTINGS_FONT);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(CHANGE_TEXT_X, YEAR_LINE_Y, (*(frameText + YEAR_TEXT)), LEFT_MODE);
	BSP_LCD_DisplayStringAt(CHANGE_TEXT_X, MONTH_LINE_Y, (*(frameText + MONTH_TEXT)), LEFT_MODE);
	BSP_LCD_DisplayStringAt(CHANGE_TEXT_X, DAY_LINE_Y, (*(frameText + DAY_TEXT)), LEFT_MODE);
	BSP_LCD_DisplayStringAt(CHANGE_TEXT_X, HOUR_LINE_Y, (*(frameText + HOUR_TEXT)), LEFT_MODE);
	BSP_LCD_DisplayStringAt(CHANGE_TEXT_X, MINUTE_LINE_Y, (*(frameText + MIN_TEXT)), LEFT_MODE);
	
	BSP_LCD_DrawRect(BOX_X,YEAR_LINE_Y - 1,4*15,SETTINGS_FONT.height+2);
	BSP_LCD_DisplayStringAt(BOX_X+10,YEAR_LINE_Y,getFormatedTimeFromSource("YYYY", &editTime),LEFT_MODE);
	
	BSP_LCD_DrawRect(BOX_X,MONTH_LINE_Y - 1,9*15,SETTINGS_FONT.height+2);
	BSP_LCD_DisplayStringAt(BOX_X + 10,MONTH_LINE_Y,getFormatedTimeFromSource("MMM", &editTime),LEFT_MODE);
	
	BSP_LCD_DrawRect(BOX_X,DAY_LINE_Y - 1,4*15,SETTINGS_FONT.height+2);
	BSP_LCD_DisplayStringAt(BOX_X+10,DAY_LINE_Y,getFormatedTimeFromSource("DD", &editTime),LEFT_MODE);
	
	BSP_LCD_DrawRect(BOX_X,HOUR_LINE_Y - 1,4*15,SETTINGS_FONT.height+2);
	BSP_LCD_DisplayStringAt(BOX_X+10,HOUR_LINE_Y,getFormatedTimeFromSource("hh" ,&editTime),LEFT_MODE);
	
	BSP_LCD_DrawRect(BOX_X,MINUTE_LINE_Y - 1,4*15,SETTINGS_FONT.height+2);
	BSP_LCD_DisplayStringAt(BOX_X+10,MINUTE_LINE_Y,getFormatedTimeFromSource("mm", &editTime),LEFT_MODE);
	
	DrawButton(BSP_LCD_GetXSize() - 8*12 - 10, SAVE_LINE_Y, 8*12, SETTINGS_FONT.height + 6, 0, (*(frameText + SAVE_TEXT)),&SETTINGS_FONT);
	DrawButton(CHANGE_TEXT_X, SAVE_LINE_Y, 8*10, SETTINGS_FONT.height + 6, 0, (*(frameText + BACK_TEXT)),&SETTINGS_FONT);
	

}

void drawMonth(void){
	uint32_t tableLength = 0;
	uint32_t curY = MONTH_GRID_Y1;
	uint32_t rowMid[DAYS_NUM];
	BSP_LCD_SetFont(&Oxygen_Mono_16);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	
	
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(BSP_LCD_GetXSize(), MAINBAR_SIZE_Y, BSP_LCD_GetXSize()/2 - 1, STATUSBAR_POS_Y - MAINBAR_SIZE_Y);
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
