#include "washingTimeCustomerFrame.h"

int8_t hwndWashTimCustFrameControl = 0;
int8_t startWashTimCustFrame = 0;

void ShowWashTimCustFrame(void)
{
    hwndWashTimCustFrameControl = 0;
    startWashTimCustFrame = 1;
    while(1)
    {
        if(redraw)
        {
            RefreshWashTimCustFrame();
            redraw = 0;
        }
        AnimateTimeWashTimCustFrame();
        TranslateWashTimCustFrameMSG();
        
        if(hwndWashTimCustFrameControl == 20) return;
        hwndWashTimCustFrameControl = 0;
    }
}

void RefreshWashTimCustFrame(void)
{
    //Static refresh
    if(hwndWashTimCustFrameControl == 0 && startWashTimCustFrame == 1)
    {
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
        BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
        
        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
        BSP_LCD_FillRect(MAIN_WINDOW_POS_X, MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
        
        BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
        
        BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
                
        BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(MODE_WASH_TIME_X, MODE_WASH_TIME_Y ,MODE_WASHING_TIME,LEFT_MODE);
        
        //uint8_t picPtr;
				if(equalTime(&pistonTasks[REGENERATION_TASK_NUM].restartDateTime,&pl_dayWashTime))
        //if(FP_GetParam()->params.washTime == 1)
        {
            BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_DisplayStringAt(WASHING_TIME_CUST_VALUE_X, WASHING_TIME_CUST_VALUE_Y, "ÄÅÍÜ", LEFT_MODE);
            //picPtr = &day;
            //BSP_LCD_DrawBitmap(190, 90, &day);
        }
				if(equalTime(&pistonTasks[REGENERATION_TASK_NUM].restartDateTime,&pl_nightWashTime))
        //if(FP_GetParam()->params.washTime == 2)
        {
            BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_DisplayStringAt(WASHING_TIME_CUST_VALUE_X, WASHING_TIME_CUST_VALUE_Y, "ÍÎ×Ü", LEFT_MODE);
            //picPtr = &night;
            //BSP_LCD_DrawBitmap(190, 90, &night);
        }
        //BSP_LCD_DrawBitmap(190, 90, &picPtr);
        startWashTimCustFrame = 0;
    }
}

void AnimateTimeWashTimCustFrame(void)
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

void TranslateWashTimCustFrameMSG(void)
{
    //BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && wasTouch())
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
        {
            hwndWashTimCustFrameControl = 20;
        }
    }
}