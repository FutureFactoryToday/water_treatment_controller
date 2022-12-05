#include "main.h"

//#define MODE_DAYS_BETWEEN_REGEN "DAYS BETWEEN REGEN"
#define MODE_DAYS_BETWEEN_REGEN "ƒÕ» Ã≈∆ƒ” –≈√≈Õ≈–¿÷»ﬂÃ»"

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

#define DBR_VALUE_BOX_X 30
#define DBR_VALUE_BOX_Y TOP_BOT_LINE_WIDTH + 70 
#define DBR_VALUE_BOX_SIZE_X 80
#define DBR_VALUE_BOX_SIZE_Y 60

#define DBR_VALUE_X DBR_VALUE_BOX_X + 14
#define DBR_VALUE_Y DBR_VALUE_BOX_Y + 13

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

void ShowDaysBetweenRegenCustFrame(void);

void RefreshDaysBetweenRegenCustFrame(void);

void AnimateTimeDaysBetweenRegenCustFrame(void);

void TranslateDaysBetweenRegenCustFrameMSG(void);