#include "forcedRegenCustomerFrame.h"

int8_t hwndForcedRegenCustFrameControl = 0;

void ShowForcedRegenCustFrame(void)
{
    hwndForcedRegenCustFrameControl = 0;
    while(1)
    {
        if(redraw)
        {
            RefreshForcedRegenCustFrame();
            redraw = 0;
        }
        AnimateTimeForcedRegenCustFrame();
        TranslateForcedRegenCustFrameMSG();
        
        if(hwndForcedRegenCustFrameControl == 20) return;
				if(hwndForcedRegenCustFrameControl == 30){
					hwndForcedRegenCustFrameControl = 0;
					PL_Planner(FORCE_START_NOW);
				}
				if(hwndForcedRegenCustFrameControl == 40){
					hwndForcedRegenCustFrameControl = 0;
					PL_Planner(FORCE_START_NEAREST);
				}
    }
}

void RefreshForcedRegenCustFrame(void)
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
	BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_FORCED_REGEN,LEFT_MODE);
	
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_FillRect(KEY_REGEN_FAST_X,KEY_REGEN_FAST_Y,KEY_REGEN_FAST_SIZE_X, KEY_REGEN_FAST_SIZE_Y);
	BSP_LCD_FillRect(KEY_REGEN_DELAY_X,KEY_REGEN_DELAY_Y,KEY_REGEN_DELAY_SIZE_X, KEY_REGEN_DELAY_SIZE_Y);
	
	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(KEY_REGEN_FAST_TEXT_X, KEY_REGEN_FAST_TEXT_Y, "пецем.", LEFT_MODE);
	BSP_LCD_DisplayStringAt(KEY_REGEN_DELAY_TEXT_X, KEY_REGEN_DELAY_TEXT_Y, "нрк. пецем.", LEFT_MODE);
		
	if (PL_isRunnig){
		BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	}else {
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
	}
	BSP_LCD_FillRect(PL_STATUS_X,PL_STATUS_Y,PL_STATUS_SIZE_X, PL_STATUS_SIZE_Y);
}

void AnimateTimeForcedRegenCustFrame(void)
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

void TranslateForcedRegenCustFrameMSG(void)
{
    BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
        {
            hwndForcedRegenCustFrameControl = 20;
        }
				if (isInRectangle(tsState.X,tsState.Y,KEY_REGEN_FAST_X,KEY_REGEN_FAST_Y,KEY_REGEN_FAST_SIZE_X, KEY_REGEN_FAST_SIZE_Y)) 
        {
            hwndForcedRegenCustFrameControl = 30;
        }
				if (isInRectangle(tsState.X,tsState.Y,KEY_REGEN_DELAY_X,KEY_REGEN_DELAY_Y,KEY_REGEN_DELAY_SIZE_X, KEY_REGEN_DELAY_SIZE_Y)) 
        {
            hwndForcedRegenCustFrameControl = 40;
        }
    }
}