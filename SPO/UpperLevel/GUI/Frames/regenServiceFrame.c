#include "regenServiceFrame.h"

int8_t hwndRegenServiceFrameControl = 0;

void ShowRegenServiceFrame(void)
{
    hwndRegenServiceFrameControl = 0;
    while(1)
    {
        if(redraw)
        {
            RefreshRegenServiceFrame();
            redraw = 0;
        }
        //AnimateTimeRegenServiceFrame();
        TranslateRegenServiceFrameMSG();
        
        if(hwndRegenServiceFrameControl == 20) return;
    }
}

void RefreshRegenServiceFrame(void)
{
    drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_REGEN);
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(MAIN_WINDOW_POS_X,MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y + 20);
    
    drawStatusBarSave("Обезжелезивание");

    drawFillButton(60, 70, 300, 50, 15, "ВКЛ", LCD_COLOR_WHITEBLUE, false);
    drawFillButton(60, 145, 300, 50, 15, "ВЫКЛ", LCD_COLOR_WHITEBLUE, false);
    drawTextLabel(60, 220, 300, 50, 15, "Ввод", LCD_COLOR_WHITEBLUE, LCD_COLOR_WHITE);
    
    drawScrollButton(1);
}

void AnimateTimeRegenServiceFrame(void)
{
    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(TIME_X, TIME_Y, getFormatedTime(hour), LEFT_MODE);

    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(TIME_X + 40, TIME_Y, getFormatedTime(minute), LEFT_MODE);
    
    if(getTime()->second%2 == 0)
    {
        BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(TIME_X + 30, TIME_Y - 2, ":", LEFT_MODE);
    }
    else
    {
        BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_DisplayStringAt(TIME_X + 30, TIME_Y - 2, ":", LEFT_MODE);
    }
}

void TranslateRegenServiceFrameMSG(void)
{
    BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
        {
            hwndRegenServiceFrameControl = 20;
        }
    }
}