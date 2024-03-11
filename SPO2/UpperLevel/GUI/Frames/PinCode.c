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
#define MAX_PIN_CHAR 4 + 3 + 3 + 3 + 1
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

uint8_t** pinFrameText;
uint32_t enteredPin = {0};
static button_t pinTextArea, enterBut;
uint8_t pinString[MAX_PIN_CHAR];
/* Private function prototypes -----------------------------------------------*/
int8_t refreshPinFrame();
uint8_t pinTouchHandler();
void createPinFrame();
void drawPinBoxes(uint8_t* pin);
int32_t callKeyboardFromPin(uint32_t min, uint32_t max, uint8_t* text);
void pinToStr (uint16_t pin);
/* Private user code ---------------------------------------------------------*/
int8_t PIN_showFrame(){
    
    enteredPin = 1234;

	createPinFrame();
	
	while(1)
    { 
        if (updateFlags.sec == true){
            drawClock();
            updateFlags.sec = false;
        }
        if (pinTextArea.isReleased == true){
            int32_t newPin = callKeyboardFromPin(0,9999,"Введите ПИН код");
            if (newPin >= 0 ){
                enteredPin = newPin;
                createPinFrame();
            }
            else if(newPin == -1)
            {
                enteredPin = 0;
                createPinFrame();
            }
            pinTextArea.isReleased = false;
        }
        if (enterBut.isPressed == true){
             enterBut.isPressed = false;
        }
        if (enterBut.isReleased == true){
            enterBut.isReleased = false;
            if (enteredPin == sysParam.SERVICE_CODE){
                return 1;
            } else {
                BSP_LCD_SetTextColor(LCD_COLOR_RED);
                BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
                for(uint8_t i = 0; i < 6; i++){
                    BSP_LCD_DrawHLine(BSP_LCD_GetXSize()/2 - 100, PIN_BOX_Y + 20 + PIN_FONT.height + i, 200);
                }
                
                BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
                BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, PIN_FONT.height*5, "Неверный код!", CENTER_MODE);
            }
        }
        if (retBut.isReleased == true){
            retBut.isReleased = false;
            return -1;
        }	
    }
}

int32_t callKeyboardFromPin(uint32_t min, uint32_t max, uint8_t* text){
	return ShowKeyboardFrame(0, 9999);
}

void createPinFrame(){
	//Static refresh
	TC_clearButtons();
	
	
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	pinFrameText = &ITEM_PINCODE_FRAME;
	
	drawMainBar(true, false, SMALL_LOGO_X, SMALL_LOGO_Y, (*(pinFrameText + MAIN_TEXT)));
	
	drawStatusBarEmpty();
		
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&PIN_FONT);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, MAINBAR_SIZE_Y + 5, (*(pinFrameText + ENTER_PIN_TEXT)), CENTER_MODE);
	pinToStr(enteredPin);
	pinTextArea = drawTextLabel(BSP_LCD_GetXSize()/2 - 100, PIN_BOX_Y, 200, BSP_LCD_GetFont()->height + 10,&pinString);    
	
	enterBut = drawFillButton(BSP_LCD_GetXSize()/2 - 50, ENTER_BUT_Y, 100, BSP_LCD_GetFont()->height + 10,(*(pinFrameText + BUT_PIN_TEXT)), false);
	
	TC_addButton(&pinTextArea);
	TC_addButton(&retBut);
	TC_addButton(&cancelBut);
	TC_addButton(&okBut);
	TC_addButton(&enterBut);
	//enableClockDraw = true;
}

void drawPinBoxes(uint8_t* pin){
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(PIN_BOX_X,PIN_BOX_Y,PIN_BOX_X + PIN_LENGTH* (PIN_BOX_X_LENGTH + PIN_BOX_SPACE), PIN_BOX_Y_LENGTH);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	
}

void pinToStr (uint16_t pin){
	if (pin == 0){
		 pinString[0] = 0;
	}
	
	uint8_t i = 0;
	uint8_t* edPin = intToStr(pin);
	while (*edPin != 0){
		pinString[i++] = *edPin;
		if (i < MAX_PIN_CHAR - 1){
			pinString[i++] = ' ';
			pinString[i++] = '-';
			pinString[i++] = ' ';	
		}			
		edPin++;
	}
	if (i == MAX_PIN_CHAR - 1){
		pinString[i] = 0;
	} else {
		pinString[i - 3] = 0;
	}
}

