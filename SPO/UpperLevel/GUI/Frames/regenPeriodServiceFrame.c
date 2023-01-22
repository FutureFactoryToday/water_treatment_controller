#include "regenPeriodServiceFrame.h"

int8_t hwndRegenPeriodServiceFrameControl = 0;
//int8_t regenPeriod = 0;
int8_t startRegenPeriodServiceFrame = 0;

void ShowRegenPeriodServiceFrame(void)
{
    hwndRegenPeriodServiceFrameControl = 0;
    startRegenPeriodServiceFrame = 1;
    while(1)
    {
        if(redraw)
        {
            RefreshRegenPeriodServiceFrame();
            redraw = 0;
        }
        AnimateTimeRegenPeriodServiceFrame();
        TranslateRegenPeriodServiceFrameMSG();
        
        if(hwndRegenPeriodServiceFrameControl == 20) return;
        
        if(hwndRegenPeriodServiceFrameControl == 1)
        {
            regenPeriod = ShowKeyboardFrame();
            startRegenPeriodServiceFrame = 1;
        }
        
        hwndRegenPeriodServiceFrameControl = 0;
    }
}

void RefreshRegenPeriodServiceFrame(void)
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
    BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_REGEN_PERIOD,LEFT_MODE);
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(REGEN_PERIOD_VALUE_BOX_X,REGEN_PERIOD_VALUE_BOX_Y, REGEN_PERIOD_VALUE_BOX_SIZE_X, REGEN_PERIOD_VALUE_BOX_SIZE_Y);
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_DrawRect(REGEN_PERIOD_VALUE_BOX_X, REGEN_PERIOD_VALUE_BOX_Y, REGEN_PERIOD_VALUE_BOX_SIZE_X, REGEN_PERIOD_VALUE_BOX_SIZE_Y);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(REGEN_PERIOD_VALUE_X, REGEN_PERIOD_VALUE_Y, intToStr(regenPeriod), LEFT_MODE);
    
    BSP_LCD_SetFont(&Oxygen_Mono_20);
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(REGEN_PERIOD_VALUE_X + 80, REGEN_PERIOD_VALUE_Y, "���� ����� �������������", LEFT_MODE);
    BSP_LCD_SetFont(&Oxygen_Mono_24);
}

void AnimateTimeRegenPeriodServiceFrame(void)
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

void TranslateRegenPeriodServiceFrameMSG(void)
{
    BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && wasTouch())
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
        {
            hwndRegenPeriodServiceFrameControl = 20;
        }
        if (isInRectangle(tsState.X,tsState.Y,REGEN_PERIOD_VALUE_BOX_X,REGEN_PERIOD_VALUE_BOX_Y,REGEN_PERIOD_VALUE_BOX_SIZE_X,REGEN_PERIOD_VALUE_BOX_SIZE_Y)) 
        {
            hwndRegenPeriodServiceFrameControl = 1;
        }
    }
}