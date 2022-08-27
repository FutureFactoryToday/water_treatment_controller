/**
  ******************************************************************************
  * @file    GUI.h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _GUI_H_
#define _GUI_H_

/*Includes */
#include "main.h"

/*Public defines */
#define SMALL_LOGO_X  480 - 55
#define SMALL_LOGO_Y  5

#define TOP_BOT_LINE_WIDTH 60

#define START_BUT_X 10
#define START_BUT_Y TOP_BOT_LINE_WIDTH + 10

#define START_BUT_X_SIZE 320 - 2*TOP_BOT_LINE_WIDTH - 20
#define START_BUT_Y_SIZE START_BUT_X_SIZE
#define START_BUT_FIRST_TEXT "START"
#define START_BUT_SECOND_TEXT "STOP"

#define DIR_BUT_X START_BUT_X + START_BUT_X_SIZE + START_BUT_X
#define DIR_BUT_Y START_BUT_Y
#define DIR_BUT_FIRST_TEXT "CW"
#define DIR_BUT_SECOND_TEXT "CCW"


#define SENS_STATUS_TEXT_X (START_BUT_X + START_BUT_X_SIZE)*2 + 15
#define SENS_STATUS_TEXT_Y START_BUT_Y

#define SENS_STATUS_CIRC_X (START_BUT_X + START_BUT_X_SIZE)*2 + 30
#define SENS_STATUS_CIRC_Y START_BUT_Y + 25


#define SENS_CNT_X (START_BUT_X + START_BUT_X_SIZE)*2 + 15
#define SENS_CNT_Y SENS_STATUS_CIRC_Y + 25

#define SENS_CNT_TEXT_X (START_BUT_X + START_BUT_X_SIZE)*2 + 15
#define SENS_CNT_TEXT_Y SENS_CNT_Y + 25


/*Global params*/
extern const BITMAPSTRUCT gImage_LOGO_MAIN;
extern const BITMAPSTRUCT gImage_SMALL_LOGO;
extern uint32_t touchDelay;
extern uint8_t redraw;
/*Prototypes */
void initGUI(void);
void redrawGUI(void);

#endif /* __GUI_H__ */

