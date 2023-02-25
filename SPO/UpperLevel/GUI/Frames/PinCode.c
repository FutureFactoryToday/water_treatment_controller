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
	"Пароль для сервиса",
	"Введите пароль",
	"ВВОД",
	"Введите число"
};
char* pinEnText[] = {
	"SERVICE PASSWORD",
	"Enter password",
	"ENTER",
	"Enter number"
};

uint8_t** pinFrameText;
uint32_t enteredPin = {0};
static button_t pinTextArea;

/* Private function prototypes -----------------------------------------------*/
int8_t refreshPinFrame();
uint8_t pinTouchHandler();
void createPinFrame();
void drawPinBoxes(uint8_t* pin);
int32_t callKeyboardFromPin(uint32_t min, uint32_t max, uint8_t* text);
/* Private user code ---------------------------------------------------------*/
int8_t PIN_showFrame(){

	createPinFrame();
	
	while(1)
    { 
			if(pinTextArea.isPressed == true){
				enteredPin = callKeyboardFromPin(0,999999,"Введите ПИН код");
				createPinFrame();
				pinTextArea.isPressed = false;
			}
			if (okBut.isPressed == true){
				 okBut.isPressed = false;
			}
			if (okBut.isReleased == true){
				okBut.isReleased = false;
				if (enteredPin == sysParam.SERVICE_CODE){
					return 1;
				} else {
					 return -1;
				}
			}			
    }
}

int32_t callKeyboardFromPin(uint32_t min, uint32_t max, uint8_t* text){
	return ShowKeyboardFrame();
}

void createPinFrame(){
	//Static refresh
	TC_clearButtons();
	enteredPin = 1234;
	
	pinFrameText = &pinRuText;
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
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, MAINBAR_SIZE_Y + 5, (*(pinFrameText + ENTER_PIN_TEXT)), CENTER_MODE);
	
	//drawPinBoxes(enteredPin);
	
	DrawButton(ENTER_BUT_X, ENTER_BUT_Y, 10*15, PIN_TEXT.height+20,0,(*(pinFrameText + BUT_PIN_TEXT)),&PIN_TEXT);
	
	enableClockDraw = true;
}

void drawPinBoxes(uint8_t* pin){
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(PIN_BOX_X,PIN_BOX_Y,PIN_BOX_X + PIN_LENGTH* (PIN_BOX_X_LENGTH + PIN_BOX_SPACE), PIN_BOX_Y_LENGTH);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	
}


