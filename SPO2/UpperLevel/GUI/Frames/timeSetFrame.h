/**
  ******************************************************************************
  * @file    timeSetFrame.h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TIME_SET_FRAME_H_
#define _TIME_SET_FRAME_H_

/*Includes */
#include "main.h"

/*Public defines */
#define MID_CLOCK_Y MAINBAR_SIZE_Y + 20

#define TSF_UPBAR_POS_X 0
#define TSF_UPBAR_POS_Y BSP_LCD_GetYSize() - TOP_LINE_WIDTH - MED_LINE_WIDTH
#define TSF_UPBAR_SIZE_X BSP_LCD_GetXSize()
#define TSF_UPBAR_SIZE_Y MED_LINE_WIDTH


#define MONTH_GRID_X1 10
#define MONTH_GRID_Y1 TOP_LINE_WIDTH

#define FIRST_ROW_Y MONTH_GRID_Y1
#define FIRST_COL_X MONTH_GRID_X1

#define DAY_NAME_WIDTH 40

#define COL_GAP 3

#define UP_MONTH_BUT


#define CHANGE_TEXT_X BSP_LCD_GetXSize()/2 + 10 

#define SETTINGS_FONT Oxygen_Mono_16
#define YEAR_LINE_Y FIRST_ROW_Y + SETTINGS_FONT.height + 2
#define MONTH_LINE_Y YEAR_LINE_Y + SETTINGS_FONT.height + 2
#define DAY_LINE_Y MONTH_LINE_Y + SETTINGS_FONT.height + 2
#define HOUR_LINE_Y DAY_LINE_Y + SETTINGS_FONT.height + 2
#define MINUTE_LINE_Y  HOUR_LINE_Y + SETTINGS_FONT.height + 2
#define SAVE_LINE_Y MINUTE_LINE_Y + SETTINGS_FONT.height + 5

#define BOX_X BSP_LCD_GetXSize()/2 + BSP_LCD_GetXSize()/6

#define CLOCK_EDIT_BUT_X STATUSBAR_POS_X + 10
#define CLOCK_EDIT_BUT_Y STATUSBAR_POS_Y + 20
/*Global params*/

/*Prototypes */
int TSF_showFrame();

#endif /* __TIME_SET_FRAME_H__ */

