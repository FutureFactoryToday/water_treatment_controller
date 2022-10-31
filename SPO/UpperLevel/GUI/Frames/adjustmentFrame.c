#include "adjustmentFrame.h"

uint8_t adjustment_frame_Scroll_cnt = 0;
uint8_t adjustment_frame_was_Scroll = 0;
int32_t qwertyAdj[] = {0, 0, 0, 0, 0};
int8_t hwndAdjustmentFrameControl = 0;
int8_t startAdjustmentFrame = 0;
//char* ITEM_SOFTENING[] = { "BWASH", "REAWASH", "SBWASH", "DFLUSH", "FILLING" };
char* ITEM_ADJUSTMENT[] = { "ÇÀÊÐÛÒÎÅ ÏÎË.", "ÎÁÐÀÒ.ÏÐÎÌ.", "ÐÅÃÅÍ.", "ÇÀÏÎËÍÅÍÈÅ", "ÓÌßÃ×ÅÍÈÅ", "ÏÐÎÌÛÂÊÀ", "ÔÈËÜÒÐÀÖÈß" };

void ShowAdjustmentFrame(void)
{
    hwndAdjustmentFrameControl = -1;
    adjustment_frame_Scroll_cnt = 0;
    startAdjustmentFrame = 1;
    while(1)
    {
        if(redraw)
        {
            RefreshAdjustmentFrame();
            redraw = 0;
        }
        TranslateMenuAdjustmentMSG();
        
        if(hwndAdjustmentFrameControl == 20) return;
        
        
        if(hwndAdjustmentFrameControl == 0)
        {
            qwertyAdj[hwndAdjustmentFrameControl] = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 1)
        {
            qwertyAdj[hwndAdjustmentFrameControl] = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 2)
        {
            qwertyAdj[hwndAdjustmentFrameControl] = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 3)
        {
            qwertyAdj[hwndAdjustmentFrameControl] = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 4)
        {
            qwertyAdj[hwndAdjustmentFrameControl] = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 5)
        {
            qwertyAdj[hwndAdjustmentFrameControl] = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 6)
        {
            qwertyAdj[hwndAdjustmentFrameControl] = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        
        hwndAdjustmentFrameControl = -1;
    }
}

void RefreshAdjustmentFrame(void)
{
    //Static refresh
    if(hwndAdjustmentFrameControl == -1 && startAdjustmentFrame == 1)
    {
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
        BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
        
        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
        BSP_LCD_FillRect(MAIN_WINDOW_POS_X,MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
        
        BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
        
        BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
        
        BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_ADJUSTMENT,LEFT_MODE);
        BSP_LCD_DisplayStringAt(SAVE_X,SAVE_Y,"ÑÎÕÐ.",LEFT_MODE);
        BSP_LCD_DisplayStringAt(200,SAVE_Y,"ÑÁÐÎÑ",LEFT_MODE);
            
        BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_DrawRect(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y);
        BSP_LCD_DrawRect(SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y);
        BSP_LCD_DrawRect(THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y);
        BSP_LCD_DrawRect(SCROLLBAR_POS_X,SCROLLBAR_POS_Y,SCROLLBAR_SIZE_X,SCROLLBAR_SIZE_Y);
        
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillRect(FIRST_CURSOR_VALUE_BOX_X,FIRST_CURSOR_VALUE_BOX_Y, FIRST_CURSOR_VALUE_BOX_SIZE_X, FIRST_CURSOR_VALUE_BOX_SIZE_Y);
        BSP_LCD_FillRect(SECOND_CURSOR_VALUE_BOX_X,SECOND_CURSOR_VALUE_BOX_Y, SECOND_CURSOR_VALUE_BOX_SIZE_X, SECOND_CURSOR_VALUE_BOX_SIZE_Y);
        BSP_LCD_FillRect(THRID_CURSOR_VALUE_BOX_X,THRID_CURSOR_VALUE_BOX_Y, THRID_CURSOR_VALUE_BOX_SIZE_X, THRID_CURSOR_VALUE_BOX_SIZE_Y);
        
        BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 17,ITEM_ADJUSTMENT[adjustment_frame_Scroll_cnt],LEFT_MODE);
        BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 17,ITEM_ADJUSTMENT[adjustment_frame_Scroll_cnt + 1],LEFT_MODE);
        BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 17,ITEM_ADJUSTMENT[adjustment_frame_Scroll_cnt + 2],LEFT_MODE);
        
        BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
        BSP_LCD_DisplayStringAt(330,FIRST_CURSOR_POS_Y + 17,"ÑÒÀÐÒ",LEFT_MODE);
        BSP_LCD_DisplayStringAt(330,SECOND_CURSOR_POS_Y + 17,"ÑÒÀÐÒ",LEFT_MODE);
        BSP_LCD_DisplayStringAt(330,THRID_CURSOR_POS_Y + 17,"ÑÒÀÐÒ",LEFT_MODE);

        BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
        BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
        
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (adjustment_frame_Scroll_cnt == 0 ? 0 : adjustment_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (adjustment_frame_Scroll_cnt == 0 ? 0 : adjustment_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (adjustment_frame_Scroll_cnt == 0 ? 0 : adjustment_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(FIRST_CURSOR_VALUE_BOX_X + 16,FIRST_CURSOR_VALUE_BOX_Y + 17,intToStr(qwertyAdj[adjustment_frame_Scroll_cnt]),LEFT_MODE);
        BSP_LCD_DisplayStringAt(SECOND_CURSOR_VALUE_BOX_X + 16,SECOND_CURSOR_VALUE_BOX_Y + 17,intToStr(qwertyAdj[adjustment_frame_Scroll_cnt + 1]),LEFT_MODE);
        BSP_LCD_DisplayStringAt(THRID_CURSOR_VALUE_BOX_X + 16,THRID_CURSOR_VALUE_BOX_Y + 17,intToStr(qwertyAdj[adjustment_frame_Scroll_cnt + 2]),LEFT_MODE);
        

        
        startAdjustmentFrame = 0;
    }
    if(adjustment_frame_was_Scroll == 1 || adjustment_frame_was_Scroll == 2)
        RefreshScrollBarAdjustmentFrame();
}

void RefreshScrollBarAdjustmentFrame()
{       
    AnimateScrollBarKeysAdjustmentFrame();
    
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_FillRect(FIRST_CURSOR_POS_X + 1,FIRST_CURSOR_POS_Y + 1,FIRST_CURSOR_SIZE_X - 2,FIRST_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(SECOND_CURSOR_POS_X + 1,SECOND_CURSOR_POS_Y + 1,SECOND_CURSOR_SIZE_X - 2,SECOND_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(THRID_CURSOR_POS_X + 1,THRID_CURSOR_POS_Y + 1,THRID_CURSOR_SIZE_X - 2,THRID_CURSOR_SIZE_Y - 4);
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(FIRST_CURSOR_VALUE_BOX_X,FIRST_CURSOR_VALUE_BOX_Y, FIRST_CURSOR_VALUE_BOX_SIZE_X, FIRST_CURSOR_VALUE_BOX_SIZE_Y);
    BSP_LCD_FillRect(SECOND_CURSOR_VALUE_BOX_X,SECOND_CURSOR_VALUE_BOX_Y, SECOND_CURSOR_VALUE_BOX_SIZE_X, SECOND_CURSOR_VALUE_BOX_SIZE_Y);
    BSP_LCD_FillRect(THRID_CURSOR_VALUE_BOX_X,THRID_CURSOR_VALUE_BOX_Y, THRID_CURSOR_VALUE_BOX_SIZE_X, THRID_CURSOR_VALUE_BOX_SIZE_Y);
        
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 17,ITEM_ADJUSTMENT[adjustment_frame_Scroll_cnt],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 17,ITEM_ADJUSTMENT[adjustment_frame_Scroll_cnt + 1],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 17,ITEM_ADJUSTMENT[adjustment_frame_Scroll_cnt + 2],LEFT_MODE);
    
    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
    BSP_LCD_DisplayStringAt(330,FIRST_CURSOR_POS_Y + 17,"ÑÒÀÐÒ",LEFT_MODE);
    BSP_LCD_DisplayStringAt(330,SECOND_CURSOR_POS_Y + 17,"ÑÒÀÐÒ",LEFT_MODE);
    BSP_LCD_DisplayStringAt(330,THRID_CURSOR_POS_Y + 17,"ÑÒÀÐÒ",LEFT_MODE);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(FIRST_CURSOR_VALUE_BOX_X + 16,FIRST_CURSOR_VALUE_BOX_Y + 17,intToStr(qwertyAdj[adjustment_frame_Scroll_cnt]),LEFT_MODE);
    BSP_LCD_DisplayStringAt(SECOND_CURSOR_VALUE_BOX_X + 16,SECOND_CURSOR_VALUE_BOX_Y + 17,intToStr(qwertyAdj[adjustment_frame_Scroll_cnt + 1]),LEFT_MODE);
    BSP_LCD_DisplayStringAt(THRID_CURSOR_VALUE_BOX_X + 16,THRID_CURSOR_VALUE_BOX_Y + 17,intToStr(qwertyAdj[adjustment_frame_Scroll_cnt + 2]),LEFT_MODE);
    
    
}

void AnimateScrollBarKeysAdjustmentFrame(void)
{
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);      
    BSP_LCD_FillRect(SCROLLBAR_POS_X + 1,SCROLLBAR_POS_Y + 51,SCROLLBAR_SIZE_X - 2,SCROLLBAR_SIZE_Y - 98);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (adjustment_frame_Scroll_cnt == 0 ? 0 : adjustment_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (adjustment_frame_Scroll_cnt == 0 ? 0 : adjustment_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (adjustment_frame_Scroll_cnt == 0 ? 0 : adjustment_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);

    adjustment_frame_was_Scroll = 0;
}

void TranslateMenuAdjustmentMSG(void)
{
    BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
        {
           hwndAdjustmentFrameControl = 20;
        }     
        if (isInRectangle(tsState.X,tsState.Y,STATUSBAR_POS_X,STATUSBAR_POS_Y,100,TOP_BOT_LINE_WIDTH) )
        {
           hwndAdjustmentFrameControl = 10;
        }       
        if (isInRectangle(tsState.X,tsState.Y,UP_ARROW_POS_X,UP_ARROW_POS_Y,UP_ARROW_SIZE_X,UP_ARROW_SIZE_Y))
        {
            if(adjustment_frame_Scroll_cnt > 0) adjustment_frame_Scroll_cnt--;
            adjustment_frame_was_Scroll = 1;
        }
        if (isInRectangle(tsState.X,tsState.Y,DOWN_ARROW_POS_X,DOWN_ARROW_POS_Y,DOWN_ARROW_SIZE_X,DOWN_ARROW_SIZE_Y))
        {
            if(adjustment_frame_Scroll_cnt < 4) adjustment_frame_Scroll_cnt++;
            adjustment_frame_was_Scroll = 2;
        }
        
        //process list
        if (isInRectangle(tsState.X,tsState.Y,FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y))
        {
            hwndAdjustmentFrameControl = adjustment_frame_Scroll_cnt;
        }   
        if (isInRectangle(tsState.X,tsState.Y,SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y))
        {
            hwndAdjustmentFrameControl = adjustment_frame_Scroll_cnt + 1;
        }   
        if (isInRectangle(tsState.X,tsState.Y,THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y))
        {
            hwndAdjustmentFrameControl = adjustment_frame_Scroll_cnt + 2;
        }
    }
}