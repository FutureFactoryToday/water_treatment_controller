/**
  ******************************************************************************
  * @file           : GUI.c
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
TS_StateTypeDef tsState;
uint32_t touchDelay;
uint8_t startBut;
uint8_t dirBut;
uint8_t numBuf[11] = {0};
uint8_t redraw = 0;
/* Private function prototypes -----------------------------------------------*/
void DrawButton(uint16_t x, uint16_t y, uint16_t xSize, uint16_t ySize, uint8_t isPushed, uint8_t* text);
uint8_t isInRectangle (uint16_t x, uint16_t y, uint16_t xS, uint16_t yS, uint16_t xE, uint16_t yE);
uint8_t* intToStr (uint32_t num);
void DrawOpticStatus(void);
/* Private user code ---------------------------------------------------------*/
void initGUI(void){
	
	redraw = 0;
	BSP_LCD_Init();
	BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
	//BSP_LCD_FillRect(0,0,10,10);
	//BSP_LCD_FillRect(100,50,10,10);
	BSP_LCD_DrawBitmap((ILI9486_LCD_PIXEL_HEIGHT-150)/2,(ILI9486_LCD_PIXEL_WIDTH-150)/2,&gImage_LOGO_MAIN);
	LL_mDelay(2000);
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_FillRect(0,0,BSP_LCD_GetXSize(),TOP_BOT_LINE_WIDTH);
	BSP_LCD_FillRect(0,BSP_LCD_GetYSize() - TOP_BOT_LINE_WIDTH,BSP_LCD_GetXSize(),TOP_BOT_LINE_WIDTH);
	BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
	
	DrawButton(START_BUT_X, START_BUT_Y, START_BUT_X_SIZE, START_BUT_Y_SIZE, 1, START_BUT_FIRST_TEXT);
	startBut = 0;
	
	DrawButton(DIR_BUT_X, DIR_BUT_Y, START_BUT_X_SIZE, START_BUT_Y_SIZE, 1, DIR_BUT_FIRST_TEXT);
	dirBut = 0;
	
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	
	BSP_LCD_DisplayStringAt(SENS_STATUS_TEXT_X,SENS_STATUS_TEXT_Y,"Sensor",LEFT_MODE);
	
	DrawOpticStatus();
	 
	BSP_LCD_DisplayStringAt(SENS_CNT_X,SENS_CNT_Y,"Cnt",LEFT_MODE);
	
	intToStr(opticCnt);
	BSP_LCD_DisplayStringAt(SENS_CNT_TEXT_X,SENS_CNT_TEXT_Y,numBuf,LEFT_MODE);
	
}

void redrawGUI(void){
	BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1){
		touchDelay = 300;
		if (isInRectangle(tsState.X,tsState.Y,START_BUT_X,START_BUT_Y,START_BUT_X + START_BUT_X_SIZE,START_BUT_Y + START_BUT_Y_SIZE) ){
			if (startBut == 0)
			{
				MOT_START();
				DrawButton(START_BUT_X, START_BUT_Y, START_BUT_X_SIZE, START_BUT_Y_SIZE, 1, START_BUT_SECOND_TEXT);
				startBut = 1;
			} else {
				MOT_STOP();
				DrawButton(START_BUT_X, START_BUT_Y, START_BUT_X_SIZE, START_BUT_Y_SIZE, 1, START_BUT_FIRST_TEXT);
				startBut = 0;
			}
		}
		if (isInRectangle(tsState.X,tsState.Y,DIR_BUT_X,DIR_BUT_Y,DIR_BUT_X + START_BUT_X_SIZE,DIR_BUT_Y + START_BUT_Y_SIZE) ){
			
				MOT_CHANGE_DIR();
				if (!dirBut) {
					DrawButton(DIR_BUT_X, DIR_BUT_Y, START_BUT_X_SIZE, START_BUT_Y_SIZE, 1, DIR_BUT_SECOND_TEXT);
				} else {
					DrawButton(DIR_BUT_X, DIR_BUT_Y, START_BUT_X_SIZE, START_BUT_Y_SIZE, 1, DIR_BUT_FIRST_TEXT);
				}
					dirBut = !dirBut;
			}
		}
	
	intToStr(opticCnt);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(SENS_CNT_TEXT_X, SENS_CNT_TEXT_Y,100, 25);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(SENS_CNT_TEXT_X, SENS_CNT_TEXT_Y, numBuf,LEFT_MODE);
	
	DrawOpticStatus();
}

void DrawOpticStatus(void){
	if (opticStatus == 1){
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
	} else {
		BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	}
	BSP_LCD_FillCircle(SENS_STATUS_CIRC_X, SENS_STATUS_CIRC_Y,10);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
}

uint8_t* intToStr (uint32_t num){
	for(int i = 0; i <sizeof(numBuf); i++){
		numBuf[i] = 0;
	}
	uint32_t modNum = num;
	uint8_t ch = 0;
	uint32_t mod = 1000000000;
	if (num == 0){
		numBuf[0] = 48;
		return numBuf;
	}
	uint8_t i = 0;
	while(modNum < mod){
		mod /= 10;
	}
	if (mod == 0) {
		mod = 1;
	}
	
	while (modNum > 0 || mod > 0){
		while (modNum>=mod){
			ch++;
			modNum -= mod;
		}
		numBuf[i++] = ch + 48;
		ch = 0;
		mod /= 10;
//		if (mod == 0) {
//		mod = 1;
//		}
	}
	return numBuf;
}

uint8_t isInRectangle (uint16_t x, uint16_t y, uint16_t xS, uint16_t yS, uint16_t xE, uint16_t yE){
	
	return x < xE && x > xS && y < yE && y > yS;
}
void DrawButton(uint16_t x, uint16_t y, uint16_t xSize, uint16_t ySize, uint8_t isPushed, uint8_t* text){
	if (isPushed == 1)
	{
		BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
		BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	}
	else {
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
		BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	}
	BSP_LCD_FillRect(x,y,xSize,ySize);
	
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font24);
	
	uint32_t size = 0, xsize = 0; 
  uint8_t  *ptr = text;
  
  /* Get the text size */
  while (*ptr++) size ++ ;
	
	uint16_t xTextStart = xSize/2+x;
	uint16_t yTextStart = ySize/2+y;
	
	BSP_LCD_DrawPixel(xTextStart, yTextStart, LCD_COLOR_RED);
	BSP_LCD_DrawPixel(xSize/2+x, ySize/2+y, LCD_COLOR_RED);
	
	BSP_LCD_DisplayStringAt(xSize/2+x ,ySize/2+y,text,CENTER_MODE);
}