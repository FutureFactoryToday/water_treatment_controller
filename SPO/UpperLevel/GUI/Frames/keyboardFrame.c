#include "keyboardFrame.h"

int32_t qwertyResult = 0;

uint8_t dx = 0;

int8_t hwndKeyboardFrameControl = 0;

int32_t result_keyboard = 0;

int32_t ShowKeyboardFrame(void)
{
    dx = 0;
    qwertyResult= 0;
    result_keyboard = 0;
    while(1)
    {
        if(redraw)
        {
            RefreshKeyboardFrame();
            redraw = 0;
        }
        TranslateKeyboardFrameMSG();
        
        if(qwertyResult == 1)return result_keyboard;
        
        if(qwertyResult == 0)return qwertyResult;
        
        RefreshCursor(dx);
    }
    
}

void RefreshKeyboardFrame(void)
{
    //Static refresh
    if(qwertyResult == 0)
    {
        BSP_LCD_SetFont(&Oxygen_Mono_24);
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
        BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
        
        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
        BSP_LCD_FillRect(MAIN_WINDOW_POS_X,MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
        
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillRect(TEXT_CTRL_POS_X,TEXT_CTRL_POS_Y, TEXT_CTRL_SIZE_X, TEXT_CTRL_SIZE_Y);
        
        BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
        
        BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
        
        BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        
        BSP_LCD_DisplayStringAt(CANCEL_X, CANCEL_Y, CANCEL, LEFT_MODE);
        
        BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
        
        BSP_LCD_DisplayStringAt(OK_X, OK_Y, OK, LEFT_MODE);
        
        RefreshKeys();
        qwertyResult = 2;
    }
    PrintResultFromKeyboard();
}

void RefreshCursor(uint8_t dx)
{
    if(getTime()->second%2 == 0)
    {
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_FillRect(CURSOR_POS_X + dx,CURSOR_POS_Y, CURSOR_SIZE_X, CURSOR_SIZE_Y);
    }
    else
    {
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillRect(CURSOR_POS_X + dx,CURSOR_POS_Y, CURSOR_SIZE_X, CURSOR_SIZE_Y);
    }
}

void RefreshKeys(void)
{
    //Horizontal lines
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_DrawLine(0, 121, BSP_LCD_GetXSize(), 121);
    BSP_LCD_DrawLine(0, 166, BSP_LCD_GetXSize(), 166);
    BSP_LCD_DrawLine(0, 212, BSP_LCD_GetXSize(), 212);
    BSP_LCD_DrawLine(0, 259, BSP_LCD_GetXSize(), 259);
    
    //Vertical lines
    BSP_LCD_DrawLine(0, 120, 0, 260);
    BSP_LCD_DrawLine(60, 120, 60, 260);
    BSP_LCD_DrawLine(120, 120, 120, 260);
    BSP_LCD_DrawLine(180, 120, 180, 260);
    BSP_LCD_DrawLine(240, 120, 240, 260);
    BSP_LCD_DrawLine(300, 120, 300, 260);
    BSP_LCD_DrawLine(360, 120, 360, 260);
    BSP_LCD_DrawLine(420, 120, 420, 260);
    BSP_LCD_DrawLine(480, 120, 480, 260);
    
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X, NUM_KEYS_POS_Y, "0", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 60, NUM_KEYS_POS_Y, "1", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 120, NUM_KEYS_POS_Y, "2", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 180, NUM_KEYS_POS_Y, "3", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 240, NUM_KEYS_POS_Y, "4", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 300, NUM_KEYS_POS_Y, "5", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 360, NUM_KEYS_POS_Y, "6", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 420, NUM_KEYS_POS_Y, "7", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X, NUM_KEYS_POS_Y + 46, "8", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 60, NUM_KEYS_POS_Y + 46, "9", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 116, NUM_KEYS_POS_Y + 46, "<", LEFT_MODE);
}

uint8_t KeyClick()
{
    int32_t result = 144;
    BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
        touchDelay = 100;
        if(result_keyboard < 99999999)
        {
            if (isInRectangle(tsState.X,tsState.Y, 0, 121, 60, 46)) 
            {
               result = 0;
            }  
            if (isInRectangle(tsState.X,tsState.Y, 60, 121, 60, 46)) 
            {
               result = 1;
            }
            if (isInRectangle(tsState.X,tsState.Y, 120, 121, 60, 46)) 
            {
               result = 2;
            }
            if (isInRectangle(tsState.X,tsState.Y, 180, 121, 60, 46)) 
            {
               result = 3;
            }
            if (isInRectangle(tsState.X,tsState.Y, 240, 121, 60, 46)) 
            {
               result = 4;
            }
            if (isInRectangle(tsState.X,tsState.Y, 300, 121, 60, 46)) 
            {
               result = 5;
            }   
            if (isInRectangle(tsState.X,tsState.Y, 360, 121, 60, 46)) 
            {
               result = 6;
            }
            if (isInRectangle(tsState.X,tsState.Y, 420, 121, 60, 46)) 
            {
               result = 7;
            }
            if (isInRectangle(tsState.X,tsState.Y, 0, 166, 60, 46)) 
            {
               result = 8;
            }
            if (isInRectangle(tsState.X,tsState.Y, 60, 166, 60, 46)) 
            {
               result = 9;
            }
        }
        if (isInRectangle(tsState.X,tsState.Y, 120, 166, 60, 46)) 
        {
           result = 10;
        }
    }
    return result;
}

void PrintResultFromKeyboard()
{
    int32_t pre_result = KeyClick();
    
    if((pre_result >= 1 && pre_result <= 9) || (pre_result == 0 && result_keyboard != 0))
    {
        dx += 13;
        result_keyboard = (result_keyboard * 10) + pre_result;
    }
        
    if(pre_result == 10)
    {
        result_keyboard = result_keyboard / 10;
        if(dx != 0) 
            dx -= 13;
    }
    
    if(result_keyboard != 0)
    {
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillRect(TEXT_CTRL_POS_X,TEXT_CTRL_POS_Y, TEXT_CTRL_SIZE_X, TEXT_CTRL_SIZE_Y);
        
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(CURSOR_POS_X, CURSOR_POS_Y + 6, intToStr(result_keyboard), LEFT_MODE);         
    }
    if(result_keyboard == 0)
    {
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillRect(TEXT_CTRL_POS_X, TEXT_CTRL_POS_Y, TEXT_CTRL_SIZE_X, TEXT_CTRL_SIZE_Y);
    }
}

void TranslateKeyboardFrameMSG()
{
    BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,420,260,60,60)) //OK
        {
           qwertyResult = 1;
        }  
        if (isInRectangle(tsState.X,tsState.Y,0,260,120,60))  //CANCEL
        {
           qwertyResult = 0;
        }  
        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
        {
           qwertyResult = 0;
        }     
    }
}