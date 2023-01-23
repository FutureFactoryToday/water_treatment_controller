#include "main.h"

//#define MODE_FORCED_REGEN "œ–»Õ”ƒ»“≈À‹Õ¿ﬂ –≈√≈Õ."

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

#define KEY_REGEN_FAST_X 30
#define KEY_REGEN_FAST_Y TOP_BOT_LINE_WIDTH + 25 
#define KEY_REGEN_FAST_SIZE_X 150
#define KEY_REGEN_FAST_SIZE_Y 150

#define KEY_REGEN_FAST_TEXT_X KEY_REGEN_FAST_X + 38
#define KEY_REGEN_FAST_TEXT_Y KEY_REGEN_FAST_Y + 58

#define KEY_REGEN_DELAY_X KEY_REGEN_FAST_X+KEY_REGEN_FAST_SIZE_X+30
#define KEY_REGEN_DELAY_Y TOP_BOT_LINE_WIDTH + 25 
#define KEY_REGEN_DELAY_SIZE_X 150
#define KEY_REGEN_DELAY_SIZE_Y 150

#define KEY_REGEN_DELAY_TEXT_X KEY_REGEN_DELAY_X + 38
#define KEY_REGEN_DELAY_TEXT_Y KEY_REGEN_DELAY_Y + 58

#define PL_STATUS_X KEY_REGEN_DELAY_X+KEY_REGEN_DELAY_SIZE_X+30
#define PL_STATUS_Y TOP_BOT_LINE_WIDTH + 25 
#define PL_STATUS_SIZE_X 30
#define PL_STATUS_SIZE_Y 30
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

void ShowForcedRegenCustFrame(void);

void RefreshForcedRegenCustFrame(void);

void AnimateTimeForcedRegenCustFrame(void);

void TranslateForcedRegenCustFrameMSG(void);