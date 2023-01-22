/**
  ******************************************************************************
  * @file    PinCode.h
  * @brief   This file contains all the function prototypes for
  *          the PinCode.c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _PINCODE_H_
#define _PINCODE_H_

/*Includes */
#include "main.h"

/*Public defines */
#define PIN_LENGTH 4

#define PIN_TEXT Oxygen_Mono_24

#define PIN_BOX_SPACE 30
#define PIN_BOX_X_LENGTH 55 + 6
#define PIN_BOX_Y_LENGTH PIN_TEXT.height + 25

#define PIN_BOX_Y MAINBAR_SIZE_Y + PIN_TEXT.height*2 - 18

#define PIN_BOX_X (BSP_LCD_GetXSize() - (PIN_LENGTH*PIN_BOX_X_LENGTH + (PIN_LENGTH-1)*PIN_BOX_SPACE))/2 - 10

#define ENTER_BUT_X (BSP_LCD_GetXSize() - 10*15 - 1)/2
#define ENTER_BUT_Y PIN_TEXT.height*5+13

/*Global params*/

/*Prototypes */
int8_t PIN_showFrame();

#endif /* __PINCODE_H__ */

