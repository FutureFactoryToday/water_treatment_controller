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
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
void TC_Init (void){
	buttonList.butNum = 0;
}
void TC_addButton (button_t* but){
	if (buttonList.butNum < MAX_BUT_NUM){
	 buttonList.buttons[buttonList.butNum++] = but;
	} else {
		 Error_Handler();
	}
}
void TC_clearButtons(void){
	 buttonList.butNum = 0;
}
void TC_Interrupt(void){
	 if (buttonList.butNum > 0 && tsState.TouchDetected == 1){
				 for (uint8_t i = 0; i < buttonList.butNum; i++){
						if (isInRectangle(tsState.X,tsState.Y,buttonList.buttons[i]->x,buttonList.buttons[i]->y,buttonList.buttons[i]->xSize,buttonList.buttons[i]->ySize)){
							 buttonList.buttons[i]->isPressed = 1;
						}
				 }
	 }
}