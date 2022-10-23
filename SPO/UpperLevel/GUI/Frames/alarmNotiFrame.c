#include "alarmNotiFrame.h"

int8_t hwndAlarmNotiServiceFrameControl = 0;
int8_t startAlarmNotiFrame = 0;

void ShowAlarmNotiServiceFrame(void)
{
    hwndAlarmNotiServiceFrameControl = 0;
    startAlarmNotiFrame = 1;
    while(1)
    {
        if(redraw)
        {
            RefreshAlarmNotiServiceFrame();
            redraw = 0;
        }
        AnimateTimeAlarmNotiServiceFrame();
        TranslateAlarmNotiServiceFrameMSG();
        
        if(hwndAlarmNotiServiceFrameControl == 20) return;
        
        if(hwndAlarmNotiServiceFrameControl == 1)
        {
            ShowAlarmListFrame();
            startAlarmNotiFrame = 1;
        }
        hwndAlarmNotiServiceFrameControl = 0;
    }
}

void RefreshAlarmNotiServiceFrame(void)
{
    //Static refresh
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
    BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
    
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_FillRect(MAIN_WINDOW_POS_X,MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
    
    BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
    
    BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
    
    BSP_LCD_DrawBitmap(LIST_X, LIST_Y, &list);
    
    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_ALARM_NOTI,LEFT_MODE);
    
    //plug
    BSP_LCD_SetFont(&Oxygen_Mono_20);
    
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(75, 100, "For service, you need to contact the", LEFT_MODE);
    BSP_LCD_DisplayStringAt(85, 130, "service department of LLC Sarmat", LEFT_MODE);
    BSP_LCD_DisplayStringAt(135, 160, "+7 (495) 189 - 71 - 78", LEFT_MODE);
    BSP_LCD_DisplayStringAt(140, 190, "info@sarmatwater.ru", LEFT_MODE);
    
    BSP_LCD_SetFont(&Oxygen_Mono_24);
    
    
}

void AnimateTimeAlarmNotiServiceFrame(void)
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

void TranslateAlarmNotiServiceFrameMSG(void)
{
    BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
        {
            hwndAlarmNotiServiceFrameControl = 20;
        }
        if (isInRectangle(tsState.X,tsState.Y,LIST_X - 10,LIST_Y - 7,100,60)) 
        {
            hwndAlarmNotiServiceFrameControl = 1;
        }
    }
}