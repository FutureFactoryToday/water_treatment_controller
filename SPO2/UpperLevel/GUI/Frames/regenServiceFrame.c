#include "regenServiceFrame.h"


static void createFrame();

void ShowRegenServiceFrame(void)
{
  createFrame();
	while(1)
	{
        if (updateFlags.sec == true){
             drawClock(); drawMainStatusBar(144, 2305, 16);
            updateFlags.sec = false;
        }
		if(retBut.isPressed == true){
			return;
    }
	}
}

void createFrame(void)
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
	BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_FillRect(MAIN_WINDOW_POS_X,MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
	
	BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
	
	BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
	
	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_REGEN,LEFT_MODE);
	
	//plug
//    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//    BSP_LCD_DisplayStringAt(218, 142, "???", LEFT_MODE);
//	drawFillButton(120, 80, 200, 50, "ВКЛ", LCD_COLOR_BLUE, false);
//	drawFillButton(120, 200, 200, 50, "ВЫКЛ", LCD_COLOR_BLUE, false);
	
	TC_addButton(&retBut);
	//enableClockDraw = true;
}

