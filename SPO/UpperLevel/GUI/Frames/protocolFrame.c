#include "protocolFrame.h"

uint8_t protocol_frame_Scroll_cnt = 0;
uint8_t protocol_frame_was_Scroll = 0;
//int32_t qwertyAdj[] = {0, 0, 0, 0, 0, 0, 0};
int8_t hwndProtocolFrameControl = 0;
int8_t startProtocolFrame = 0;
char* ITEM_PROTOCOL[] = { "111", "222", "333", "444", "555", "666", "NNN" };

void ShowProtocolFrame(void)
{
    hwndProtocolFrameControl = -1;
    protocol_frame_Scroll_cnt = 0;
    startProtocolFrame = 1;
    while(1)
    {
        if(redraw)
        {
            RefreshAdjustmentFrame();
            redraw = 0;
        }
        AnimatePosMenuFrame();
        TranslateMenuAdjustmentMSG();
        
        if(hwndProtocolFrameControl == 20) return;
        
        if(hwndProtocolFrameControl == 40)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 30)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 0)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 1)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 2)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 3)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 4)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 5)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 6)
        {
            startProtocolFrame = 1;
        }
        
        //cycle start
        if(hwndProtocolFrameControl == 10)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 11)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 12)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 13)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 14)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 15)
        {
            startProtocolFrame = 1;
        }
        if(hwndProtocolFrameControl == 16)
        {
            startProtocolFrame = 1;
        }
        
        hwndProtocolFrameControl = -1;
    }
}

void RefreshProtocolFrame(void)
{
    //Static refresh
    if(hwndProtocolFrameControl == -1 && startProtocolFrame == 1)
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
        BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_PROTOCOL,LEFT_MODE);
        BSP_LCD_DisplayStringAt(SAVE_X,SAVE_Y,"ÑÎÕÐ.",LEFT_MODE);
        BSP_LCD_DisplayStringAt(RESET_X,RESET_Y,"ÑÁÐÎÑ",LEFT_MODE);
        BSP_LCD_DisplayStringAt(POS_VALUE_LABEL_X,POS_VALUE_LABEL_Y,"ÏÎÇ:",LEFT_MODE);
            
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
        BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 17,ITEM_PROTOCOL[protocol_frame_Scroll_cnt],LEFT_MODE);
        BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 17,ITEM_PROTOCOL[protocol_frame_Scroll_cnt + 1],LEFT_MODE);
        BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 17,ITEM_PROTOCOL[protocol_frame_Scroll_cnt + 2],LEFT_MODE);
        
        BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
        BSP_LCD_DisplayStringAt(330,FIRST_CURSOR_POS_Y + 17,"ÑÒÀÐÒ",LEFT_MODE);
        BSP_LCD_DisplayStringAt(330,SECOND_CURSOR_POS_Y + 17,"ÑÒÀÐÒ",LEFT_MODE);
        BSP_LCD_DisplayStringAt(330,THRID_CURSOR_POS_Y + 17,"ÑÒÀÐÒ",LEFT_MODE);

        BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
        BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
        
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (protocol_frame_Scroll_cnt == 0 ? 0 : protocol_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (protocol_frame_Scroll_cnt == 0 ? 0 : protocol_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (protocol_frame_Scroll_cnt == 0 ? 0 : protocol_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        //BSP_LCD_DisplayStringAt(FIRST_CURSOR_VALUE_BOX_X + 16,FIRST_CURSOR_VALUE_BOX_Y + 17,intToStr(qwertyAdj[protocol_frame_Scroll_cnt]),LEFT_MODE);
        //BSP_LCD_DisplayStringAt(SECOND_CURSOR_VALUE_BOX_X + 16,SECOND_CURSOR_VALUE_BOX_Y + 17,intToStr(qwertyAdj[protocol_frame_Scroll_cnt + 1]),LEFT_MODE);
        //BSP_LCD_DisplayStringAt(THRID_CURSOR_VALUE_BOX_X + 16,THRID_CURSOR_VALUE_BOX_Y + 17,intToStr(qwertyAdj[protocol_frame_Scroll_cnt + 2]),LEFT_MODE);
        

        
        startProtocolFrame = 0;
    }
    if(protocol_frame_was_Scroll == 1 || protocol_frame_was_Scroll == 2)
        RefreshScrollBarAdjustmentFrame();
}

void RefreshScrollBarProtocolFrame()
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
    BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 17,ITEM_PROTOCOL[protocol_frame_Scroll_cnt],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 17,ITEM_PROTOCOL[protocol_frame_Scroll_cnt + 1],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 17,ITEM_PROTOCOL[protocol_frame_Scroll_cnt + 2],LEFT_MODE);
    
    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
    BSP_LCD_DisplayStringAt(330,FIRST_CURSOR_POS_Y + 17,"ÑÒÀÐÒ",LEFT_MODE);
    BSP_LCD_DisplayStringAt(330,SECOND_CURSOR_POS_Y + 17,"ÑÒÀÐÒ",LEFT_MODE);
    BSP_LCD_DisplayStringAt(330,THRID_CURSOR_POS_Y + 17,"ÑÒÀÐÒ",LEFT_MODE);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    //BSP_LCD_DisplayStringAt(FIRST_CURSOR_VALUE_BOX_X + 16,FIRST_CURSOR_VALUE_BOX_Y + 17,intToStr(qwertyAdj[protocol_frame_Scroll_cnt]),LEFT_MODE);
    //BSP_LCD_DisplayStringAt(SECOND_CURSOR_VALUE_BOX_X + 16,SECOND_CURSOR_VALUE_BOX_Y + 17,intToStr(qwertyAdj[protocol_frame_Scroll_cnt + 1]),LEFT_MODE);
    //BSP_LCD_DisplayStringAt(THRID_CURSOR_VALUE_BOX_X + 16,THRID_CURSOR_VALUE_BOX_Y + 17,intToStr(qwertyAdj[protocol_frame_Scroll_cnt + 2]),LEFT_MODE);
    
    
}

void AnimateScrollBarKeysProtocolFrame(void)
{
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);      
    BSP_LCD_FillRect(SCROLLBAR_POS_X + 1,SCROLLBAR_POS_Y + 51,SCROLLBAR_SIZE_X - 2,SCROLLBAR_SIZE_Y - 98);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (protocol_frame_Scroll_cnt == 0 ? 0 : protocol_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (protocol_frame_Scroll_cnt == 0 ? 0 : protocol_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (protocol_frame_Scroll_cnt == 0 ? 0 : protocol_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);

    protocol_frame_was_Scroll = 0;
}

void TranslateMenuProtocolMSG(void)
{
    BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,SAVE_BUTTON_X,SAVE_BUTTON_Y,SAVE_BUTTON_SIZE_X,SAVE_BUTTON_SIZE_Y)) 
        {
           hwndProtocolFrameControl = 40;
        }  
        if (isInRectangle(tsState.X,tsState.Y,RESET_BUTTON_X,RESET_BUTTON_Y,RESET_BUTTON_SIZE_X,RESET_BUTTON_SIZE_Y)) 
        {
           hwndProtocolFrameControl = 30;
        }  
        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
        {
           hwndProtocolFrameControl = 20;
        }     
        if (isInRectangle(tsState.X,tsState.Y,STATUSBAR_POS_X,STATUSBAR_POS_Y,100,TOP_BOT_LINE_WIDTH) )
        {
           hwndProtocolFrameControl = 10;
        }       
        if (isInRectangle(tsState.X,tsState.Y,UP_ARROW_POS_X,UP_ARROW_POS_Y,UP_ARROW_SIZE_X,UP_ARROW_SIZE_Y))
        {
            if(protocol_frame_Scroll_cnt > 0) protocol_frame_Scroll_cnt--;
            protocol_frame_was_Scroll = 1;
        }
        if (isInRectangle(tsState.X,tsState.Y,DOWN_ARROW_POS_X,DOWN_ARROW_POS_Y,DOWN_ARROW_SIZE_X,DOWN_ARROW_SIZE_Y))
        {
            if(protocol_frame_Scroll_cnt < 4) protocol_frame_Scroll_cnt++;
            protocol_frame_was_Scroll = 2;
        }
        
        //process list
        if (isInRectangle(tsState.X,tsState.Y,FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,300,FIRST_CURSOR_SIZE_Y))
        {
            hwndProtocolFrameControl = protocol_frame_Scroll_cnt;
        }   
        if (isInRectangle(tsState.X,tsState.Y,SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,300,SECOND_CURSOR_SIZE_Y))
        {
            hwndProtocolFrameControl = protocol_frame_Scroll_cnt + 1;
        }   
        if (isInRectangle(tsState.X,tsState.Y,THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,300,THRID_CURSOR_SIZE_Y))
        {
            hwndProtocolFrameControl = protocol_frame_Scroll_cnt + 2;
        }
        
        //process cycle start
        if (isInRectangle(tsState.X,tsState.Y,FIRST_CURSOR_POS_X + 300,FIRST_CURSOR_POS_Y,119,FIRST_CURSOR_SIZE_Y))
        {
            hwndProtocolFrameControl = 10 + protocol_frame_Scroll_cnt;
        }   
        if (isInRectangle(tsState.X,tsState.Y,SECOND_CURSOR_POS_X + 300,SECOND_CURSOR_POS_Y,119,SECOND_CURSOR_SIZE_Y))
        {
            hwndProtocolFrameControl = 10 + protocol_frame_Scroll_cnt + 1;
        }   
        if (isInRectangle(tsState.X,tsState.Y,THRID_CURSOR_POS_X + 300,THRID_CURSOR_POS_Y,119,THRID_CURSOR_SIZE_Y))
        {
            hwndProtocolFrameControl = 10 + protocol_frame_Scroll_cnt + 2;
        }
    }
}