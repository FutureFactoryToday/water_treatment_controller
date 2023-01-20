/**
  ******************************************************************************
  * @file           : PinCode.c
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
#include "PinCode.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define MAIN_TEXT 0
#define ENTER_PIN_TEXT 1
#define BUT_PIN_TEXT 2
#define PIN_KB_TEXT 3
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
char* pinRuText[] = {
	"ÑÅÐÂÈÑÍÛÉ ÊÎÄ ÄÎÑÒÓÏÀ",
	"Ââåäèòå êîä",
	"ÂÂÎÄ",
	"Ââåäèòå ÷èñëî"
};
char* pinEnText[] = {
	"SERVICE PASSWORD",
	"Enter password",
	"ENTER",
	"Enter number"
};

uint8_t** pinFrameText;
uint8_t enteredPin[PIN_LENGTH] = {0};

/* Private function prototypes -----------------------------------------------*/
int8_t refreshPinFrame();
uint8_t pinTouchHandler();
void createPinFrame();
void drawPinBoxes(uint8_t* pin);
int32_t callKeyboardFromPin(uint32_t min, uint32_t max, uint8_t* text);
/* Private user code ---------------------------------------------------------*/
int8_t PIN_showFrame(){
    enteredPin[0] = 1;
    enteredPin[1] = 2;
    enteredPin[2] = 3;
    enteredPin[3] = 4;
	if (sysParam.lang == ENGLISH){
		pinFrameText = &pinEnText;
	} else {
		pinFrameText = &pinRuText;
	}
	uint8_t memSec = getTime()->second;
	createPinFrame();
	
	while(1)
    {
			if (memSec != getTime()->second){
				drawClock();
			} 
			if (pinTouchHandler()){
				int8_t refRes = refreshPinFrame();
					if (refRes != 0){
						return refRes;
					}
			}		
    }
}

int8_t refreshPinFrame(){
	/*?????? ?????*/
	if (isInRectangle(tsState.X,tsState.Y,10, 10,gImage_RETURNARROW.infoHeader.biWidth,gImage_RETURNARROW.infoHeader.biHeight))
  {
		return -1;
	}
	for (uint8_t i = 0; i< PIN_LENGTH; i++){
		if (isInRectangle(tsState.X,tsState.Y,PIN_BOX_X + i* (PIN_BOX_X_LENGTH + PIN_BOX_SPACE),PIN_BOX_Y,PIN_BOX_X_LENGTH,PIN_BOX_Y_LENGTH))
		{
			uint8_t kbResult = callKeyboardFromPin(0,9,(*(pinFrameText + PIN_KB_TEXT)));
			if (kbResult >= 0){
				enteredPin[i] = kbResult;
				createPinFrame();
			}
		}
	}
	if (isInRectangle(tsState.X,tsState.Y,ENTER_BUT_X, ENTER_BUT_Y,5*15, PIN_TEXT.height+4))
  {
		uint32_t pin = 0;
		for(uint8_t i = 0; i < PIN_LENGTH; i++){
			pin += enteredPin[PIN_LENGTH - i - 1]*POWC(10,i);
		}
		if (pin == sysParam.SERVICE_CODE){
			return 1;
		} else {
			return -1;
		}
	}
	return 0;
}
int32_t callKeyboardFromPin(uint32_t min, uint32_t max, uint8_t* text){
	return ShowKeyboardFrame();
}
uint8_t pinTouchHandler(){
	//BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && wasTouch())
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

void createPinFrame(){
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
	BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
			
	BSP_LCD_DrawBitmap(10, 10, &gImage_RETURNARROW);
	
	BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
		

	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

	BSP_LCD_SetFont(&Oxygen_Mono_24);
	BSP_LCD_DisplayStringAt(FRAME_NAME_TEXT_X, FRAME_NAME_TEXT_Y, (*(pinFrameText + MAIN_TEXT)), LEFT_MODE);
	
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, MAINBAR_SIZE_Y, (*(pinFrameText + ENTER_PIN_TEXT)), CENTER_MODE);
	
	drawPinBoxes(enteredPin);
	
	DrawButton(ENTER_BUT_X, ENTER_BUT_Y, 5*15, PIN_TEXT.height+8,0,(*(pinFrameText + BUT_PIN_TEXT)),&PIN_TEXT);
	
}

void drawPinBoxes(uint8_t* pin){
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(PIN_BOX_X,PIN_BOX_Y,PIN_BOX_X + PIN_LENGTH* (PIN_BOX_X_LENGTH + PIN_BOX_SPACE), PIN_BOX_Y_LENGTH);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	for(uint8_t i = 0; i < PIN_LENGTH; i++){
		BSP_LCD_DrawRect(PIN_BOX_X + i* (PIN_BOX_X_LENGTH + PIN_BOX_SPACE),PIN_BOX_Y,PIN_BOX_X_LENGTH,PIN_BOX_Y_LENGTH);
		BSP_LCD_DisplayStringAt(PIN_BOX_X + i* (PIN_BOX_X_LENGTH + PIN_BOX_SPACE)+6,PIN_BOX_Y+5,intToStr(enteredPin[i]), CENTER_MODE);
	}
	
}


