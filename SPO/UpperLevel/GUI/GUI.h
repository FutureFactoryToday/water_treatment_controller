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

#define DROP_BUT_X 15
#define DROP_BUT_Y TOP_BOT_LINE_WIDTH + 30

#define DROP_BUT_X_SIZE 320 - 3*TOP_BOT_LINE_WIDTH
#define DROP_BUT_Y_SIZE DROP_BUT_X_SIZE
#define DROP_BUT_FIRST_TEXT "DROP"
#define DROP_BUT_SECOND_TEXT "STOP"

#define WRENCH_BUT_X DROP_BUT_X + DROP_BUT_X_SIZE + DROP_BUT_X
#define WRENCH_BUT_Y DROP_BUT_Y
#define WRENCH_BUT_FIRST_TEXT "WRENCH"
#define WRENCH_BUT_SECOND_TEXT "CCW"

#define PAGE_BUT_X DROP_BUT_X + DROP_BUT_X_SIZE + DROP_BUT_X + DROP_BUT_X_SIZE + DROP_BUT_X
#define PAGE_BUT_Y DROP_BUT_Y
#define PAGE_BUT_TEXT "PAGE"
#define PAGE_BUT_NEXT_TEXT "CLICK"


#define SENS_STATUS_TEXT_X (DROP_BUT_X + DROP_BUT_X_SIZE)*2 + 15
#define SENS_STATUS_TEXT_Y DROP_BUT_Y

#define SENS_STATUS_CIRC_X (DROP_BUT_X + DROP_BUT_X_SIZE)*2 + 30
#define SENS_STATUS_CIRC_Y DROP_BUT_Y + 25


#define SENS_CNT_X (DROP_BUT_X + DROP_BUT_X_SIZE)*2 + 15
#define SENS_CNT_Y SENS_STATUS_CIRC_Y + 25

#define SENS_CNT_TEXT_X (DROP_BUT_X + DROP_BUT_X_SIZE)*2 + 15
#define SENS_CNT_TEXT_Y SENS_CNT_Y + 25

//New GUI
#define MODE_TEXT_X 16
#define MODE_TEXT_Y 18
#define MODE_SOFTENING_CYCLE "SOFTENING CYCLE"


/*Global params*/
extern const BITMAPSTRUCT gImage_LOGO_MAIN;
extern const BITMAPSTRUCT gImage_SMALL_LOGO;
extern uint32_t touchDelay;
extern uint8_t redraw;
/*Prototypes */
void initGUI(void);
void redrawGUI(void);

#endif /* __GUI_H__ */

