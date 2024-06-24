#include "historyErrorsFrame.h"

static uint32_t firstEl;
static uint8_t *errorText;
static void createFrame();
static void calcButParam();
static uint32_t errorsNum;
static void RefreshScreen();

int ShowHistoryMaxWaterFrame(void) {
	firstEl = 0;
	
  /*Static create*/
  createFrame();
  while (1) {
    if (updateFlags.sec == true) {
      drawClock();
      drawMainStatusBar(144, 2305, 16);
      updateFlags.sec = false;
    }
    /*Buttons pressed*/
    if (retBut.isPressed == true) {
      retBut.isPressed = false;
    }
    if (scrollUpBut.isPressed == true) {
      // Make it blue
      scrollUpBut.isPressed = false;
    }
    if (scrollDwnBut.isPressed == true) {
      // Make it blue
      scrollDwnBut.isPressed = false;
    }
    /*Buttons released*/
    if (retBut.isReleased == true) {
      retBut.isReleased = false;
      return 0;
    }
    if (homeBut.isReleased == true) {
      homeBut.isReleased = false;
      goHome = true;
    }
    if (goHome) {
      return -1;
    }
		if (scrollUpBut.isReleased == true) {
      // Make it blue
			if (firstEl)
				firstEl--;
			RefreshScreen();
      scrollUpBut.isReleased = false;
    }
    if (scrollDwnBut.isReleased == true) {
      // Make it blue
			if (firstEl < errorsNum - 4)
				firstEl++;
			RefreshScreen();
      scrollDwnBut.isReleased = false;
    }
  }
}
void createFrame(void) {
  drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_HISTORY_MAX_WATER);
	
  drawMainStatusBar(144, 2305, 16);

  drawClock();

	RefreshScreen();

  /*Add buttons parameters*/
  calcButParam();
}

 void RefreshScreen()
{
	drawMainWindow();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	uint8_t offset = FIRST_CURSOR_POS_X + 9;
	BSP_LCD_DisplayStringAt(offset,STATIC_LINE_Y + STATIC_LINE_SPASER + 9, ITEM_HISTORY_ERROR[0],LEFT_MODE);
	errorsNum = LOG_GetWaterUsage(firstEl);
	drawMainWindow();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	if (errorsNum){
		drawScrollButton(0);
		uint8_t max = MIN(errorsNum,4);
		for(uint8_t i = 0; i < max; i++){
			offset = FIRST_CURSOR_POS_X + 9;
						wtc_time_t time = intToWTCTime(displayData[max - i - 1].timeStamp);
			
			offset += BSP_LCD_DisplayStringAt(offset,STATIC_LINE_Y + i*STATIC_LINE_SPASER + 9, getFormatedTimeFromSource("YYYY.MM.DD - ",&time),LEFT_MODE);
			offset += BSP_LCD_DisplayStringAt(offset,STATIC_LINE_Y + i*STATIC_LINE_SPASER + 9, intToStr(displayData[i*2].cause) ,LEFT_MODE);
			offset += BSP_LCD_DisplayStringAt(offset,STATIC_LINE_Y + i*STATIC_LINE_SPASER + 9, ITEM_HISTORY_ERROR[5] ,LEFT_MODE);
			
		}
		drawStaticLines();
	} else {
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_DisplayStringAt(offset,STATIC_LINE_Y + STATIC_LINE_SPASER + 9, ITEM_HISTORY_ERROR[2],LEFT_MODE);
	}
}

void calcButParam() {
  TC_clearButtons();

  TC_addButton(&retBut);
  TC_addButton(&scrollUpBut);
  TC_addButton(&scrollDwnBut);
  TC_addButton(&homeBut);
}