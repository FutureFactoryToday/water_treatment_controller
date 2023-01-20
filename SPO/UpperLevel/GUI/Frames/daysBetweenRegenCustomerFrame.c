#include "daysBetweenRegenCustomerFrame.h"

int8_t hwndDaysBetweenRegenCustFrameControl = 0;

void ShowDaysBetweenRegenCustFrame(void)
{
    hwndDaysBetweenRegenCustFrameControl = 0;
    while(1)
    {
        if(redraw)
        {
            RefreshDaysBetweenRegenCustFrame();
            redraw = 0;
        }
        AnimateTimeDaysBetweenRegenCustFrame();
        TranslateDaysBetweenRegenCustFrameMSG();
        
        if(hwndDaysBetweenRegenCustFrameControl == 20) return;
    }
}

void RefreshDaysBetweenRegenCustFrame(void)
{
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
    BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_DAYS_BETWEEN_REGEN,LEFT_MODE);
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(DBR_VALUE_BOX_X,DBR_VALUE_BOX_Y, DBR_VALUE_BOX_SIZE_X, DBR_VALUE_BOX_SIZE_Y);
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_DrawRect(DBR_VALUE_BOX_X, DBR_VALUE_BOX_Y, DBR_VALUE_BOX_SIZE_X, DBR_VALUE_BOX_SIZE_Y);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(DBR_VALUE_X, DBR_VALUE_Y, intToStr(regenPeriod), LEFT_MODE);
    
    BSP_LCD_SetFont(&Oxygen_Mono_20);
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(DBR_VALUE_X + 80, DBR_VALUE_Y, "ÄÍÅÉ ÌÅÆÄÓ ÐÅÃÅÍÅÐÀÖÈßÌÈ", LEFT_MODE);
    BSP_LCD_SetFont(&Oxygen_Mono_24);
}

void AnimateTimeDaysBetweenRegenCustFrame(void)
{
    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(TIME_X, TIME_Y, getFormatedTime(hour), LEFT_MODE);

    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(TIME_X + 40, TIME_Y, getFormatedTime(minute), LEFT_MODE);
    
    if(getTime()->second%2 == 0)
    {
        BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(TIME_X + 30, TIME_Y - 2, ":", LEFT_MODE);
    }
    else
    {
        BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_DisplayStringAt(TIME_X + 30, TIME_Y - 2, ":", LEFT_MODE);
    }
}

void TranslateDaysBetweenRegenCustFrameMSG(void)
{
  //BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && wasTouch())
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
        {
            hwndDaysBetweenRegenCustFrameControl = 20;
        }
    }
}