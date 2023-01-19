#include "main.h"

//#define MODE_CUSTOMER "SERVICE"
#define MODE_CUSTOMER "ÑÅÐÂÈÑ"
extern char* ITEM_SERVICE_MENU[];

//Public defines sizers
#define TOP_BOT_LINE_WIDTH 60
#define MED_LINE_WIDTH 200


//Public defines mainbar sizers
#define MAINBAR_POS_X 0
#define MAINBAR_POS_Y 0
#define MAINBAR_SIZE_X BSP_LCD_GetXSize()
#define MAINBAR_SIZE_Y TOP_BOT_LINE_WIDTH

#define RETURN_BUT_POS_X 0
#define RETURN_BUT_POS_Y 0
#define RETURN_BUT_SIZE_X TOP_BOT_LINE_WIDTH
#define RETURN_BUT_SIZE_Y 100

#define MODE_STATUS_TEXT_X 65
#define MODE_STATUS_TEXT_Y 13


//Public defines statusbar sizers
#define STATUSBAR_POS_X 0
#define STATUSBAR_POS_Y BSP_LCD_GetYSize() - TOP_BOT_LINE_WIDTH
#define STATUSBAR_SIZE_X BSP_LCD_GetXSize()
#define STATUSBAR_SIZE_Y TOP_BOT_LINE_WIDTH

#define TIME_X 370
#define TIME_Y TOP_BOT_LINE_WIDTH + MED_LINE_WIDTH + 13


//Public defines main window sizers
#define MAIN_WINDOW_POS_X 0
#define MAIN_WINDOW_POS_Y BSP_LCD_GetYSize() - TOP_BOT_LINE_WIDTH - MED_LINE_WIDTH
#define MAIN_WINDOW_SIZE_X BSP_LCD_GetXSize()
#define MAIN_WINDOW_SIZE_Y MED_LINE_WIDTH


//Public defines lists sizers
#define FIRST_CURSOR_POS_X 0
#define FIRST_CURSOR_POS_Y TOP_BOT_LINE_WIDTH - 1                   /////////////
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
#define FOURTH_CURSOR_SIZE_Y FIRST_CURSOR_SIZE_Y + 2                /////////////


//Public defines scroll sizers
#define UP_ARROW_POS_X 420
#define UP_ARROW_POS_Y TOP_BOT_LINE_WIDTH + 1
#define UP_ARROW_SIZE_X TOP_BOT_LINE_WIDTH
#define UP_ARROW_SIZE_Y TOP_BOT_LINE_WIDTH - 9

#define DOWN_ARROW_POS_X 420
#define DOWN_ARROW_POS_Y 320 - 2*TOP_BOT_LINE_WIDTH + 10
#define DOWN_ARROW_SIZE_X TOP_BOT_LINE_WIDTH
#define DOWN_ARROW_SIZE_Y UP_ARROW_SIZE_Y - 2

#define SCROLLBAR_POS_X 420
#define SCROLLBAR_POS_Y TOP_BOT_LINE_WIDTH - 1                      /////////////
#define SCROLLBAR_SIZE_X TOP_BOT_LINE_WIDTH
#define SCROLLBAR_SIZE_Y 202                                        /////////////

#define SCROLLBAR_CURSOR_POS_X 420
#define SCROLLBAR_CURSOR_POS_Y TOP_BOT_LINE_WIDTH + UP_ARROW_SIZE_Y - 2
#define SCROLLBAR_CURSOR_SIZE_X TOP_BOT_LINE_WIDTH
#define SCROLLBAR_CURSOR_SIZE_Y 102

#define SCROLLBAR_CURSOR_SLIDER_POS_X SCROLLBAR_CURSOR_POS_X + 5
#define SCROLLBAR_CURSOR_SLIDER_POS_Y SCROLLBAR_CURSOR_POS_Y + 5
#define SCROLLBAR_CURSOR_SLIDER_SIZE_X TOP_BOT_LINE_WIDTH - 10
#define SCROLLBAR_CURSOR_SLIDER_SIZE_Y 5

void ShowServiceFrame(void);

void RefreshServiceMenuFrame(void);

void RefreshScrollBarServiceMenuFrame(void);

void AnimateScrollBarKeysServiceMenuFrame(void);

void AnimateTimeServiceMenuFrame(void);

void TranslateServiceMenuFrameMSG(void);