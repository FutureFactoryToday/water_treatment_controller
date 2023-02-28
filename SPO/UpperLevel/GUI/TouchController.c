/**
  ******************************************************************************
  * @file           : TouchController.c
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
#include "Gui/TouchController.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
tc_button_list_t buttonList;
bool TC_isTouched;
uint32_t TC_touchCnt;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
void TC_Init (void){
	buttonList.butNum = 0;
	TC_touchCnt = 0;
	TC_isTouched = false;
}
void TC_addButton (button_t* but){
	if (buttonList.butNum < MAX_BUT_NUM){
	 buttonList.buttons[buttonList.butNum++] = but;
	} else {
		 Error_Handler();
	}
}
void TC_clearButtons(void){
	if ( buttonList.butNum > 0){
	 for (uint8_t i = 0; i < buttonList.butNum; i++){
		 buttonList.buttons[i]->isPressed = 0;
		 buttonList.buttons[i]->isReleased = 0;
		 buttonList.buttons[i]->wasPressed = 0;
		 buttonList.buttons[i]->pressCnt = 0;
	 }
	 buttonList.butNum = 0;
 }
}
void TC_checkButtons(void){
	
	 if (TC_isTouched == false && buttonList.butNum > 0 && tsState.TouchDetected == 1){
		 for (uint8_t i = 0; i < buttonList.butNum; i++){
				if (isInRectangle(tsState.X,tsState.Y,buttonList.buttons[i]->x,buttonList.buttons[i]->y,buttonList.buttons[i]->xSize,buttonList.buttons[i]->ySize)){
					buttonList.buttons[i]->isPressed = true;
					buttonList.buttons[i]->wasPressed = true;
					buttonList.buttons[i]->pressCnt++;
					buttonList.buttons[i]->isReleased = false;
					TC_isTouched = true;
				}
		 }
	 }
	 if (TC_isTouched == true){
			for (uint8_t i = 0; i < buttonList.butNum; i++){
				if (buttonList.buttons[i]->pressCnt > 0){
					buttonList.buttons[i]->pressCnt++;
					if (buttonList.buttons[i]->pressCnt == BUT_MAX_PRESS){
						 buttonList.buttons[i]->pressCnt--;
					}
				}
		 }
	 }
}
void TC_releaseButtons(void) {
	for (uint8_t i = 0; i < buttonList.butNum; i++){
		buttonList.buttons[i]->pressCnt = 0;
		if (buttonList.buttons[i]->wasPressed == true){
			 buttonList.buttons[i]->isReleased = true;
		}
		buttonList.buttons[i]->isPressed = false;
		buttonList.buttons[i]->wasPressed = false;
	}

}
