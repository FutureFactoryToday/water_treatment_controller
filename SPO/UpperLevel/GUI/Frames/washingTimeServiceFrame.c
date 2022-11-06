#include "washingTimeServiceFrame.h"

int8_t hwndWashingTimeServiceFrameControl = 0;

void ShowWashingTimeServiceFrame(void)
{
    hwndWashingTimeServiceFrameControl = 0;
    while(1)
    {
        if(redraw)
        {
            RefreshWashingTimeServiceFrame();
            redraw = 0;
        }
        AnimateTimeWashingTimeServiceFrame();
        TranslateWashingTimeServiceFrameMSG();
        
        if(hwndWashingTimeServiceFrameControl == 20) return;
    }
}

void RefreshWashingTimeServiceFrame(void)
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
    BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_WASHING_TIME_SET,LEFT_MODE);
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(WASHING_TIME_VALUE_BOX_X,WASHING_TIME_VALUE_BOX_Y, WASHING_TIME_VALUE_BOX_SIZE_X, WASHING_TIME_VALUE_BOX_SIZE_Y);
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_DrawRect(WASHING_TIME_VALUE_BOX_X, WASHING_TIME_VALUE_BOX_Y, WASHING_TIME_VALUE_BOX_SIZE_X, WASHING_TIME_VALUE_BOX_SIZE_Y);
    

    if(FP_GetParam()->params.washTime == 1)
    {
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillRect(WASHING_TIME_VALUE_BOX_X,WASHING_TIME_VALUE_BOX_Y, WASHING_TIME_VALUE_BOX_SIZE_X, WASHING_TIME_VALUE_BOX_SIZE_Y);
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_DrawRect(WASHING_TIME_VALUE_BOX_X, WASHING_TIME_VALUE_BOX_Y, WASHING_TIME_VALUE_BOX_SIZE_X, WASHING_TIME_VALUE_BOX_SIZE_Y);
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(WASHING_TIME_VALUE_X, WASHING_TIME_VALUE_Y, "ÄÅÍÜ", LEFT_MODE);
    }
    if(FP_GetParam()->params.washTime == 2)
    {
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillRect(WASHING_TIME_VALUE_BOX_X,WASHING_TIME_VALUE_BOX_Y, WASHING_TIME_VALUE_BOX_SIZE_X, WASHING_TIME_VALUE_BOX_SIZE_Y);
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_DrawRect(WASHING_TIME_VALUE_BOX_X, WASHING_TIME_VALUE_BOX_Y, WASHING_TIME_VALUE_BOX_SIZE_X, WASHING_TIME_VALUE_BOX_SIZE_Y);
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(WASHING_TIME_VALUE_X, WASHING_TIME_VALUE_Y, "ÍÎ×Ü", LEFT_MODE);
    }
    
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(WASHING_TIME_VALUE_X + 150, WASHING_TIME_VALUE_Y, "ÄÅÍÜ", LEFT_MODE);
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(WASHING_TIME_VALUE_X + 250, WASHING_TIME_VALUE_Y, "ÍÎ×Ü", LEFT_MODE);
    

    //BSP_LCD_SetFont(&Oxygen_Mono_24);
}

void AnimateTimeWashingTimeServiceFrame(void)
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

void TranslateWashingTimeServiceFrameMSG(void)
{
    BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
        {
            hwndWashingTimeServiceFrameControl = 20;
        }
        if (isInRectangle(tsState.X,tsState.Y,WASHING_TIME_VALUE_X + 100,WASHING_TIME_VALUE_Y, WASHING_TIME_VALUE_X + 250,WASHING_TIME_VALUE_Y + 50)) 
        {
            FP_GetParam()->params.washTime = 2;
            FP_GetParam()->needToSave = 1;
        }
        if (isInRectangle(tsState.X,tsState.Y,WASHING_TIME_VALUE_X, WASHING_TIME_VALUE_Y, WASHING_TIME_VALUE_X + 150,WASHING_TIME_VALUE_Y + 50)) 
        {
            FP_GetParam()->params.washTime = 1;
            FP_GetParam()->needToSave = 1;
        }
    }
}