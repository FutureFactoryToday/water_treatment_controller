#include "menuFrame.h"

uint8_t menu_frame_Scroll_cnt = 0;
uint8_t menu_frame_was_Scroll = 0;
int32_t qwerty = 0;
int8_t hwndMenuFrameControl = 0;
int8_t startMenuFrame = 0;
//char* ITEM_MENU[] = { "TIME/DATE", "WASHING TIME", "FORCED REGEN", "DELAYED REGEN", "DBR", "SERVICE" };
char* ITEM_MENU[] = { "ÂÐÅÌß/ÄÀÒÀ", "ÂÐÅÌß ÏÐÎÌÛÂÊÈ", "ÏÐÈÍÓÄÈÒÅËÜÍÀß ÐÅÃ.", "ÎÒËÎÆÅÍÍÀß ÐÅÃ.", "ÄÍÅÉ ÌÅÆÄÓ ÐÅÃ.", "ÑÅÐÂÈÑ" };

void ShowMenuFrame(void)
{
    hwndMenuFrameControl = -1;
    menu_frame_Scroll_cnt = 0;
    startMenuFrame = 1;
    while(1)
    {
        if(redraw)
        {
            RefreshMenuFrame();
            redraw = 0;
        }
        AnimateTimeMenuFrame();
        TranslateMenuFrameMSG();
        
        if(hwndMenuFrameControl == 20) return;
        
        if(hwndMenuFrameControl == 0)
        {
            TSF_showFrame();
            BSP_LCD_SetFont(&Oxygen_Mono_24);
            startMenuFrame = 1;
        }
        if(hwndMenuFrameControl == 1)
        {
            ShowWashTimCustFrame();
            startMenuFrame = 1;
        }
        if(hwndMenuFrameControl == 2)
        {
            ShowForcedRegenCustFrame();
            startMenuFrame = 1;
        }
        if(hwndMenuFrameControl == 3)
        {
            ShowDelayedRegenCustFrame();
            startMenuFrame = 1;
        }
        if(hwndMenuFrameControl == 4)
        {
            ShowDaysBetweenRegenCustFrame();
            startMenuFrame = 1;
        }
        if(hwndMenuFrameControl == 5)
        {
            if(PIN_showFrame() == 1)
            {
                BSP_LCD_SetFont(&Oxygen_Mono_24);
                ShowServiceFrame();
            }
            BSP_LCD_SetFont(&Oxygen_Mono_24);
            startMenuFrame = 1;
        }
        
        hwndMenuFrameControl = -1;
    }
}

void RefreshMenuFrame(void)
{
    //Static refresh
    if(hwndMenuFrameControl == -1 && startMenuFrame == 1)
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
        BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_CUSTOMER,LEFT_MODE);
            
        BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_DrawRect(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y);
        BSP_LCD_DrawRect(SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y);
        BSP_LCD_DrawRect(THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y);
        BSP_LCD_DrawRect(FOURTH_CURSOR_POS_X,FOURTH_CURSOR_POS_Y,FOURTH_CURSOR_SIZE_X,FOURTH_CURSOR_SIZE_Y);
        BSP_LCD_DrawRect(SCROLLBAR_POS_X,SCROLLBAR_POS_Y,SCROLLBAR_SIZE_X,SCROLLBAR_SIZE_Y);
        
        BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 9,ITEM_MENU[menu_frame_Scroll_cnt],LEFT_MODE);
        BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 9,ITEM_MENU[menu_frame_Scroll_cnt + 1],LEFT_MODE);
        BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 9,ITEM_MENU[menu_frame_Scroll_cnt + 2],LEFT_MODE);
        BSP_LCD_DisplayStringAt(16,FOURTH_CURSOR_POS_Y + 9,ITEM_MENU[menu_frame_Scroll_cnt + 3],LEFT_MODE);
               
        BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
        BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
        
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (menu_frame_Scroll_cnt == 0 ? 0 : menu_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (menu_frame_Scroll_cnt == 0 ? 0 : menu_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (menu_frame_Scroll_cnt == 0 ? 0 : menu_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        
        startMenuFrame = 0;
    }
    if(menu_frame_was_Scroll == 1 || menu_frame_was_Scroll == 2)
        RefreshScrollBarMenuFrame();
}

void RefreshScrollBarMenuFrame()
{       
    AnimateScrollBarKeysMenuFrame();
    
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_FillRect(FIRST_CURSOR_POS_X + 1,FIRST_CURSOR_POS_Y + 1,FIRST_CURSOR_SIZE_X - 2,FIRST_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(SECOND_CURSOR_POS_X + 1,SECOND_CURSOR_POS_Y + 1,SECOND_CURSOR_SIZE_X - 2,SECOND_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(THRID_CURSOR_POS_X + 1,THRID_CURSOR_POS_Y + 1,THRID_CURSOR_SIZE_X - 2,THRID_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(FOURTH_CURSOR_POS_X + 1,FOURTH_CURSOR_POS_Y + 1,FOURTH_CURSOR_SIZE_X - 2,FOURTH_CURSOR_SIZE_Y - 2);
    
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 9,ITEM_MENU[menu_frame_Scroll_cnt],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 9,ITEM_MENU[menu_frame_Scroll_cnt + 1],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 9,ITEM_MENU[menu_frame_Scroll_cnt + 2],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,FOURTH_CURSOR_POS_Y + 9,ITEM_MENU[menu_frame_Scroll_cnt + 3],LEFT_MODE);
}

void AnimateScrollBarKeysMenuFrame(void)
{
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);      
    BSP_LCD_FillRect(SCROLLBAR_POS_X + 1,SCROLLBAR_POS_Y + 51,SCROLLBAR_SIZE_X - 2,SCROLLBAR_SIZE_Y - 98);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (menu_frame_Scroll_cnt == 0 ? 0 : menu_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (menu_frame_Scroll_cnt == 0 ? 0 : menu_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (menu_frame_Scroll_cnt == 0 ? 0 : menu_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);

    menu_frame_was_Scroll = 0;
}

void AnimateTimeMenuFrame(void)
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

void TranslateMenuFrameMSG(void)
{
    //BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && wasTouch())
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
        {
           hwndMenuFrameControl = 20;
        }     
        if (isInRectangle(tsState.X,tsState.Y,STATUSBAR_POS_X,STATUSBAR_POS_Y,100,TOP_BOT_LINE_WIDTH) )
        {
           hwndMenuFrameControl = 10;
        }       
        if (isInRectangle(tsState.X,tsState.Y,UP_ARROW_POS_X,UP_ARROW_POS_Y,UP_ARROW_SIZE_X,UP_ARROW_SIZE_Y))
        {
            if(menu_frame_Scroll_cnt > 0) menu_frame_Scroll_cnt--;
            menu_frame_was_Scroll = 1;
        }
        if (isInRectangle(tsState.X,tsState.Y,DOWN_ARROW_POS_X,DOWN_ARROW_POS_Y,DOWN_ARROW_SIZE_X,DOWN_ARROW_SIZE_Y))
        {
            if(menu_frame_Scroll_cnt < 2) menu_frame_Scroll_cnt++;
            menu_frame_was_Scroll = 2;
        }
        
        //process list
        if (isInRectangle(tsState.X,tsState.Y,FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y))
        {
            hwndMenuFrameControl = menu_frame_Scroll_cnt;
        }   
        if (isInRectangle(tsState.X,tsState.Y,SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y))
        {
            hwndMenuFrameControl = menu_frame_Scroll_cnt + 1;
        }   
        if (isInRectangle(tsState.X,tsState.Y,THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y))
        {
            hwndMenuFrameControl = menu_frame_Scroll_cnt + 2;
        }
        if (isInRectangle(tsState.X,tsState.Y,FOURTH_CURSOR_POS_X,FOURTH_CURSOR_POS_Y,FOURTH_CURSOR_SIZE_X,FOURTH_CURSOR_SIZE_Y))
        {
            hwndMenuFrameControl = menu_frame_Scroll_cnt + 3;
        }
    }
}