#include "mainFrame.h"
uint8_t* FormatTime = "hh:mm";
uint8_t* TimeStr;

uint8_t hwndMainFrameControl = 0;
int8_t startMainFrame = 1;

void ShowMainFrame(void)
{
    hwndMainFrameControl = 0;
    startMainFrame = 1;
    while(1)
    {
        if(redraw)
        {
            RefreshMainFrame();
            redraw = 0;
        }
        AnimateTimeMainFrame();
        TranslateMainFrameMSG();
        
        if(hwndMainFrameControl == 1)
        {
            ShowMenuFrame();
            startMainFrame = 1;
        }
        hwndMainFrameControl = 0;
    }
}

void RefreshMainFrame(void)
{
    //Static refresh
    if(hwndMainFrameControl == 0 && startMainFrame== 1)
    {
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
    BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
    
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_FillRect(MAIN_WINDOW_POS_X,MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
    
    BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(DELAY_REGEN_VALUE_BOX_X,DELAY_REGEN_VALUE_BOX_Y, DELAY_REGEN_VALUE_BOX_SIZE_X, DELAY_REGEN_VALUE_BOX_SIZE_Y * 3);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_DrawRect(DELAY_REGEN_VALUE_BOX_X, DELAY_REGEN_VALUE_BOX_Y, DELAY_REGEN_VALUE_BOX_SIZE_X, DELAY_REGEN_VALUE_BOX_SIZE_Y);
    BSP_LCD_DrawRect(SPEED_VALUE_BOX_X, SPEED_VALUE_BOX_Y, SPEED_VALUE_BOX_SIZE_X, SPEED_VALUE_BOX_SIZE_Y);
    BSP_LCD_DrawRect(TIME_VALUE_BOX_X, TIME_VALUE_BOX_Y, TIME_VALUE_BOX_SIZE_X, TIME_VALUE_BOX_SIZE_Y);
    BSP_LCD_DrawRect(DELAY_REGEN_VALUE_BOX_X - 1, DELAY_REGEN_VALUE_BOX_Y - 1, DELAY_REGEN_VALUE_BOX_SIZE_X + 2, TIME_VALUE_BOX_SIZE_Y*3+2);
    
    
    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    
    BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y, MODE_SOFTENING_CYCLE, LEFT_MODE);
    BSP_LCD_DisplayStringAt(MODE_MENU_X, MODE_MENU_Y, MODE_MENU, LEFT_MODE);
    
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_TEXT_X, DELAY_REGEN_STATUS_TEXT_Y, DELAY_REGEN, LEFT_MODE);
    BSP_LCD_DisplayStringAt(SPEED_STATUS_TEXT_X, SPEED_STATUS_TEXT_Y, SPEED, LEFT_MODE);
    BSP_LCD_DisplayStringAt(TIME_STATUS_TEXT_X, TIME_STATUS_TEXT_Y, TIME, LEFT_MODE);
    
    BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_UNITS_X, DELAY_REGEN_STATUS_UNITS_Y, DELAY_REGEN_UNITS, LEFT_MODE);
    BSP_LCD_DisplayStringAt(SPEED_STATUS_UNITS_X, SPEED_STATUS_UNITS_Y, SPEED_UNITS, LEFT_MODE);
    BSP_LCD_DisplayStringAt(TIME_STATUS_UNITS_X , TIME_STATUS_UNITS_Y, TIME_UNITS, LEFT_MODE);

    //Dinamic refresh

	TimeStr = getFormatedTime(FormatTime);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_VALUE_X, DELAY_REGEN_STATUS_VALUE_Y, DELAY_REGEN_VALUE, LEFT_MODE);
    BSP_LCD_DisplayStringAt(SPEED_STATUS_VALUE_X, SPEED_STATUS_VALUE_Y, SPEED_VALUE, LEFT_MODE); 
    startMainFrame = 0;
    }    
}

void AnimateTimeMainFrame(void)
{
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(TIME_STATUS_VALUE_X, TIME_STATUS_VALUE_Y, getFormatedTime(hour), LEFT_MODE);

    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(TIME_STATUS_VALUE_X + 40, TIME_STATUS_VALUE_Y, getFormatedTime(minute), LEFT_MODE);
    
    if(getTime()->second%2 == 0)
    {
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(TIME_STATUS_VALUE_X + 30, TIME_STATUS_VALUE_Y - 2, ":", LEFT_MODE);
    }
    else
    {
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(TIME_STATUS_VALUE_X + 30, TIME_STATUS_VALUE_Y - 2, ":", LEFT_MODE);
    }
}

void TranslateMainFrameMSG (void)
{
    BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,STATUSBAR_POS_X,STATUSBAR_POS_Y,100,TOP_BOT_LINE_WIDTH) )
        {
           hwndMainFrameControl = 1;
        }        
    }
}