///**
//  ******************************************************************************
//  * @file    GUI.h
//  * @brief   This file contains all the function prototypes for
//  *          the .c file
//  ******************************************************************************
//  
//  ******************************************************************************
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

#define DROP_BUT_X 20
#define DROP_BUT_Y TOP_BOT_LINE_WIDTH + 32
#define DROP_BUT_X_SIZE 134
#define DROP_BUT_Y_SIZE DROP_BUT_X_SIZE

#define WRENCH_BUT_X DROP_BUT_X + 134 + DROP_BUT_X
#define WRENCH_BUT_Y DROP_BUT_Y

#define PAGE_BUT_X DROP_BUT_X + 134 + DROP_BUT_X + 134 + DROP_BUT_X
#define PAGE_BUT_Y DROP_BUT_Y

//Public defines lists sizers

#define FIRST_CURSOR_POS_X 0
#define FIRST_CURSOR_POS_Y TOP_BOT_LINE_WIDTH
#define FIRST_CURSOR_SIZE_X 420
#define FIRST_CURSOR_SIZE_Y 50

#define SECOND_CURSOR_POS_X 0
#define SECOND_CURSOR_POS_Y FIRST_CURSOR_POS_Y + 50
#define SECOND_CURSOR_SIZE_X FIRST_CURSOR_SIZE_X
#define SECOND_CURSOR_SIZE_Y FIRST_CURSOR_SIZE_Y

#define THRID_CURSOR_POS_X 0
#define THRID_CURSOR_POS_Y SECOND_CURSOR_POS_Y + 50
#define THRID_CURSOR_SIZE_X FIRST_CURSOR_SIZE_X
#define THRID_CURSOR_SIZE_Y FIRST_CURSOR_SIZE_Y

#define FOURTH_CURSOR_POS_X 0
#define FOURTH_CURSOR_POS_Y THRID_CURSOR_POS_Y + 50
#define FOURTH_CURSOR_SIZE_X FIRST_CURSOR_SIZE_X
#define FOURTH_CURSOR_SIZE_Y FIRST_CURSOR_SIZE_Y

//Public defines scroll sizers
#define UP_ARROW_POS_X 421
#define UP_ARROW_POS_Y TOP_BOT_LINE_WIDTH + 1
#define UP_ARROW_SIZE_X TOP_BOT_LINE_WIDTH
#define UP_ARROW_SIZE_Y TOP_BOT_LINE_WIDTH - 9

#define DOWN_ARROW_POS_X 421
#define DOWN_ARROW_POS_Y 320 - 2*TOP_BOT_LINE_WIDTH + 10
#define DOWN_ARROW_SIZE_X TOP_BOT_LINE_WIDTH
#define DOWN_ARROW_SIZE_Y UP_ARROW_SIZE_Y - 2

#define SCROLLBAR_POS_X 420
#define SCROLLBAR_POS_Y TOP_BOT_LINE_WIDTH
#define SCROLLBAR_SIZE_X TOP_BOT_LINE_WIDTH
#define SCROLLBAR_SIZE_Y 200

#define SCROLLBAR_CURSOR_POS_X 420
#define SCROLLBAR_CURSOR_POS_Y TOP_BOT_LINE_WIDTH + UP_ARROW_SIZE_Y - 2
#define SCROLLBAR_CURSOR_SIZE_X TOP_BOT_LINE_WIDTH
#define SCROLLBAR_CURSOR_SIZE_Y 102

#define SCROLLBAR_CURSOR_SLIDER_POS_X SCROLLBAR_CURSOR_POS_X + 5
#define SCROLLBAR_CURSOR_SLIDER_POS_Y SCROLLBAR_CURSOR_POS_Y + 5
#define SCROLLBAR_CURSOR_SLIDER_SIZE_X TOP_BOT_LINE_WIDTH - 10
#define SCROLLBAR_CURSOR_SLIDER_SIZE_Y 3

//Public defines statusbar sizers
#define STATUSBAR_POS_X 0
#define STATUSBAR_POS_Y BSP_LCD_GetYSize() - TOP_BOT_LINE_WIDTH
#define STATUSBAR_SIZE_X BSP_LCD_GetXSize()
#define STATUSBAR_SIZE_Y TOP_BOT_LINE_WIDTH

#define TIME_POS_X BSP_LCD_GetXSize() - 100
#define TIME_POS_Y BSP_LCD_GetYSize() - TOP_BOT_LINE_WIDTH
#define TIME_SIZE_X 100
#define TIME_SIZE_Y TOP_BOT_LINE_WIDTH

//Public defines mainbar sizers
#define MAINBAR_POS_X 0
#define MAINBAR_POS_Y 0
#define MAINBAR_SIZE_X BSP_LCD_GetXSize()
#define MAINBAR_SIZE_Y TOP_BOT_LINE_WIDTH

#define RETURN_BUT_POS_X 0
#define RETURN_BUT_POS_Y 0
#define RETURN_BUT_SIZE_X TOP_BOT_LINE_WIDTH
#define RETURN_BUT_SIZE_Y TOP_BOT_LINE_WIDTH * 2

//Public defines control sizers

//New GUI
#define MODE_TEXT_X 16
#define MODE_TEXT_Y 18

//Public defines items menu



/*Global params*/
extern const BITMAPSTRUCT LOGO;
extern const BITMAPSTRUCT gImage_SMALL_LOGO;
extern const BITMAPSTRUCT gImage_ARROWUP;
extern const BITMAPSTRUCT gImage_ARROWDOWN;
extern const BITMAPSTRUCT gImage_RETURNARROW;

extern const BITMAPSTRUCT gImage_DROPBUT;
extern const BITMAPSTRUCT gImage_WRENCHBUT;
extern const BITMAPSTRUCT gImage_PAGEBUT;

extern const BITMAPSTRUCT leftArowImg;
extern const BITMAPSTRUCT rightArowImg;
extern uint32_t touchDelay;
extern uint8_t redraw;
extern uint8_t frame;
extern TS_StateTypeDef tsState;

extern char* ITEM_MENU_DROP[];
extern char* ITEM_MENU_WRENCH[];
extern char* ITEM_MENU_PAGE[];

extern char* ITEM_MENU_SERVICE[];
extern char* ITEM_MENU_REGENERATION[];
extern char* ITEM_MENU_FILERING[];


//struct message
//{
//    uint8_t frame = 0;
//    Point *isFocus = {0,0};
//}msg;
/*Prototypes */
void initGUI(void);
void translateMessage(void);
void refresh(void);
void DrawButton(uint16_t x, uint16_t y, uint16_t xSize, uint16_t ySize, uint8_t isPushed, uint8_t* text, WTC_FONT_t* font);
uint8_t isInRectangle (uint16_t x, uint16_t y, uint16_t xS, uint16_t yS, uint16_t xE, uint16_t yE);
#endif /* __GUI_H__ */

