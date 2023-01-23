#include "serviceMenuFrame.h"

uint8_t service_menu_frame_Scroll_cnt = 0;
uint8_t service_menu_frame_was_Scroll = 0;

int8_t hwndServiceMenuFrameControl = 0;
int8_t startServiceMenuFrame = 0;

//char* ITEM_SERVICE_MENU[] = { "ÂÛÁÎÐ ÔÈËÜÒÐÀ", "ÏÅÐÈÎÄ ÐÅÃÅÍ", "ÂÐÅÌß ÏÐÎÌÛÂÊÈ", "Ñ×¨Ò×ÈÊ ÂÎÄÛ", "ÐÅÃÅÍÅÐÀÖÈß", "ÐÅÃÓËÈÐÎÂÊÀ ÊËÀÏÀÍÀ", "ÓÂÅÄÎÌËÅÍÈß ÎÁÑËÓÆÈÂÀÍÈß" };

void ShowServiceFrame(void)
{
    hwndServiceMenuFrameControl = -1;
    service_menu_frame_Scroll_cnt = 0;
    startServiceMenuFrame = 1;
    while(1)
    {
        if(redraw)
        {
            RefreshServiceMenuFrame();
            redraw = 0;
        }
        AnimateTimeServiceMenuFrame();
        TranslateServiceMenuFrameMSG();
  
        if(hwndServiceMenuFrameControl == 20) return;
        
        if(hwndServiceMenuFrameControl == 0)
        {
            ShowFilterSelectionFrame();
            startServiceMenuFrame = 1;
        }
        if(hwndServiceMenuFrameControl == 1)
        {
            ShowRegenPeriodServiceFrame();
            startServiceMenuFrame = 1;
        }
        if(hwndServiceMenuFrameControl == 2)
        {
            ShowWashingTimeServiceFrame();
            startServiceMenuFrame = 1;
        }
        if(hwndServiceMenuFrameControl == 3)
        {
            ShowQuantityCountServiceFrame();
            startServiceMenuFrame = 1;
        }
        if(hwndServiceMenuFrameControl == 4)
        {
            ShowRegenServiceFrame();
            startServiceMenuFrame = 1;
        }
        if(hwndServiceMenuFrameControl == 5)
        {
            ShowAdjustmentFrame();
            startServiceMenuFrame = 1;
        }
        if(hwndServiceMenuFrameControl == 6)
        {
            ShowAlarmNotiServiceFrame();
            startServiceMenuFrame = 1;
        }
        hwndServiceMenuFrameControl = -1;
    }
}

void RefreshServiceMenuFrame(void)
{
    //Static refresh
    if(hwndServiceMenuFrameControl == -1 && startServiceMenuFrame == 1)
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
        BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt],LEFT_MODE);
        BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 1],LEFT_MODE);   
        BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 2],LEFT_MODE);    
        BSP_LCD_DisplayStringAt(16,FOURTH_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 3],LEFT_MODE);    
               
        BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
        BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
        
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (service_menu_frame_Scroll_cnt == 0 ? 0 : service_menu_frame_Scroll_cnt * 25), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (service_menu_frame_Scroll_cnt == 0 ? 0 : service_menu_frame_Scroll_cnt * 25), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (service_menu_frame_Scroll_cnt == 0 ? 0 : service_menu_frame_Scroll_cnt * 25), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        
        startServiceMenuFrame = 0;
    }
    if(service_menu_frame_was_Scroll == 1 || service_menu_frame_was_Scroll == 2)
        RefreshScrollBarServiceMenuFrame();
}

void RefreshScrollBarServiceMenuFrame(void)
{
    AnimateScrollBarKeysServiceMenuFrame();
    
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_FillRect(FIRST_CURSOR_POS_X + 1,FIRST_CURSOR_POS_Y + 1,FIRST_CURSOR_SIZE_X - 2,FIRST_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(SECOND_CURSOR_POS_X + 1,SECOND_CURSOR_POS_Y + 1,SECOND_CURSOR_SIZE_X - 2,SECOND_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(THRID_CURSOR_POS_X + 1,THRID_CURSOR_POS_Y + 1,THRID_CURSOR_SIZE_X - 2,THRID_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(FOURTH_CURSOR_POS_X + 1,FOURTH_CURSOR_POS_Y + 1,FOURTH_CURSOR_SIZE_X - 2,FOURTH_CURSOR_SIZE_Y - 2);
    
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 1],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 2],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,FOURTH_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 3],LEFT_MODE);
}

void AnimateScrollBarKeysServiceMenuFrame(void)
{
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);     
    BSP_LCD_FillRect(SCROLLBAR_POS_X + 1,SCROLLBAR_POS_Y + 51,SCROLLBAR_SIZE_X - 2,SCROLLBAR_SIZE_Y - 99);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (service_menu_frame_Scroll_cnt == 0 ? 0 : service_menu_frame_Scroll_cnt * 25), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (service_menu_frame_Scroll_cnt == 0 ? 0 : service_menu_frame_Scroll_cnt * 25), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (service_menu_frame_Scroll_cnt == 0 ? 0 : service_menu_frame_Scroll_cnt * 25), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    
    service_menu_frame_was_Scroll = 0;
}

void AnimateTimeServiceMenuFrame(void)
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

void TranslateServiceMenuFrameMSG(void)
{
    BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
        {
           hwndServiceMenuFrameControl = 20;
        }        
        if (isInRectangle(tsState.X,tsState.Y,UP_ARROW_POS_X,UP_ARROW_POS_Y,UP_ARROW_SIZE_X,UP_ARROW_SIZE_Y))
        {
            if(service_menu_frame_Scroll_cnt > 0) service_menu_frame_Scroll_cnt--;
            service_menu_frame_was_Scroll = 1;
        }
        if (isInRectangle(tsState.X,tsState.Y,DOWN_ARROW_POS_X,DOWN_ARROW_POS_Y,DOWN_ARROW_SIZE_X,DOWN_ARROW_SIZE_Y))
        {
            if(service_menu_frame_Scroll_cnt < 3) service_menu_frame_Scroll_cnt++;
            service_menu_frame_was_Scroll = 2;
        }
        
        //process list
        if (isInRectangle(tsState.X,tsState.Y,FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y))
        {
            hwndServiceMenuFrameControl = service_menu_frame_Scroll_cnt;
        }   
        if (isInRectangle(tsState.X,tsState.Y,SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y))
        {
            hwndServiceMenuFrameControl = service_menu_frame_Scroll_cnt + 1;
        }   
        if (isInRectangle(tsState.X,tsState.Y,THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y))
        {
            hwndServiceMenuFrameControl = service_menu_frame_Scroll_cnt + 2;
        }
        if (isInRectangle(tsState.X,tsState.Y,FOURTH_CURSOR_POS_X,FOURTH_CURSOR_POS_Y,FOURTH_CURSOR_SIZE_X,FOURTH_CURSOR_SIZE_Y))
        {
            hwndServiceMenuFrameControl = service_menu_frame_Scroll_cnt + 3;
        }
    }
}