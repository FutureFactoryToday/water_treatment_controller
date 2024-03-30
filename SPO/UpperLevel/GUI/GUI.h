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


////Public defines control sizers

//New GUI
#define MODE_TEXT_X 16
#define MODE_TEXT_Y 18

//Public defines items menu


typedef struct {
	bool optic;
	bool sec;
	bool touch;
	bool TFT;
} update_flag_t;

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t xSize;
	uint16_t ySize;
	bool isPressed;
	bool isReleased;
	bool wasPressed;
	uint32_t pressCnt;
} button_t;

extern button_t retBut, okBut, scrollUpBut, scrollDwnBut, cancelBut;
extern bool enableClockDraw;
/*Global params*/
extern const BITMAPSTRUCT LOGO;
extern const BITMAPSTRUCT Logo;
extern const BITMAPSTRUCT gImage_SMALL_LOGO;
extern const BITMAPSTRUCT gImage_ARROWUP;
//extern const BITMAPSTRUCT gImage_ARROWUP_ghost;
extern const BITMAPSTRUCT gImage_ARROWDOWN;
extern const BITMAPSTRUCT gImage_RETURNARROW;
extern const BITMAPSTRUCT day;
extern const BITMAPSTRUCT night;
extern const BITMAPSTRUCT list;

extern const BITMAPSTRUCT gImage_DROPBUT;
extern const BITMAPSTRUCT gImage_WRENCHBUT;
extern const BITMAPSTRUCT gImage_PAGEBUT;

extern const BITMAPSTRUCT leftArowImg;
extern const BITMAPSTRUCT rightArowImg;

extern const BITMAPSTRUCT gImage_TRASH;
extern const BITMAPSTRUCT gImage_CHECKMARK;

extern uint32_t touchDelay;
extern uint8_t redraw;
extern uint8_t frame;
extern TS_StateTypeDef tsState;

extern uint8_t* hour;
extern uint8_t* minute;

extern char* ITEM_MENU_DROP[];
extern char* ITEM_MENU_WRENCH[];
extern char* ITEM_MENU_PAGE[];

extern char* ITEM_MENU_SERVICE[];
extern char* ITEM_MENU_REGENERATION[];
extern char* ITEM_MENU_FILERING[];

extern update_flag_t updateFlags;

//struct message
//{
//    uint8_t frame = 0;
//    Point *isFocus = {0,0};
//}msg;
/*Prototypes */
void initGUI(void);
//void translateMessage(void);
void refresh(void);

uint8_t isInRectangle (uint16_t x, uint16_t y, uint16_t xS, uint16_t yS, uint16_t xE, uint16_t yE);
void drawClock(void);
#endif /* __GUI_H__ */

