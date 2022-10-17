#include "keyboardFrame.h"

uint8_t qwertyResult = 0;

uint8_t ShowKeyboardFrame(void)
{
    qwertyResult= 0;
    while(1)
    {
        if(redraw)
        {
            RefreshKeyboardFrame();
            redraw = 0;
        }
        TranslateKeyboardFrameMSG();
        
        if(qwertyResult != 0)return qwertyResult;
    }
}

void RefreshKeyboardFrame(void)
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
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    
    BSP_LCD_DisplayStringAt(CANCEL_X, CANCEL_Y, CANCEL, LEFT_MODE);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    
    BSP_LCD_DisplayStringAt(OK_X, OK_Y, OK, LEFT_MODE);
}

void TranslateKeyboardFrameMSG()
{
    
}