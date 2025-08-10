#include "ScreensaverFrame.h"

static void createFrame();

void ShowScreensaverFrame(void) {
	
	while(1) {
		if (updateFlags.sec == true) {
			DrawScreensaverClock();
			updateFlags.sec = false; 
			sysParams.vars.frameWDTTim = SOFT_WDT_TIM_VAL_DEF; 
		}
	}
}

void createFrame() {
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_FillRect(0,0, 480, 320);
}


void DrawScreensaverClock(void) {
    
	uint16_t oldTextColor = BSP_LCD_GetTextColor();
	uint16_t oldBackColor = BSP_LCD_GetBackColor();
	time_t rtcTime = LL_RTC_TIME_Get(RTC);
	wtc_time_t time = intToWTCTime(rtcTime);
	BSP_LCD_SetFont(&Oxygen_Mono_24);
	
	BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
	//BSP_LCD_FillRect(HOUR_X,STATUSBAR_POS_Y,100,STATUSBAR_SIZE_Y);
	BSP_LCD_DrawBuffer_Start(HOUR_X, STATUSBAR_POS_Y, 90, STATUSBAR_SIZE_Y,LCD_COLOR_WHITEBLUE);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	if (getTime().second % 2){
		BSP_LCD_DisplayStringAt(DIV_X, CLOCK_Y, getFormatedTime(" "),LEFT_MODE);
		
	} else {
		BSP_LCD_DisplayStringAt(DIV_X, CLOCK_Y, ":",LEFT_MODE);
	}
  BSP_LCD_DisplayStringAt(DIV_X - 3, CLOCK_Y, getFormatedTimeFromSource("hh", &time),RIGHT_MODE);
	BSP_LCD_DisplayStringAt(DIV_X + 7, CLOCK_Y, getFormatedTimeFromSource("mm", &time),LEFT_MODE);
	
  BSP_LCD_SetTextColor(oldTextColor);
  BSP_LCD_SetBackColor(oldBackColor);
	BSP_LCD_DrawBuffer_Stop();
}