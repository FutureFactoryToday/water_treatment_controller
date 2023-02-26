#include "filteringFrame.h"

uint8_t fitlering_frame_Scroll_cnt = 0;
uint8_t fitlering_frame_was_Scroll = 0;
int32_t qwertyFilBWASH = 0;
int32_t qwertyFilDFLUSH = 0;
int8_t hwndFilteringFrameControl = 0;
int8_t startFilteringFrame = 0;

int8_t step = 0;
//char* ITEM_FILTERING[] = { "ОБР.ПРОМ.", "ПРЯМ.ПРОМ."};


void ShowFilteringFrame(void)
{
    hwndFilteringFrameControl = -1;
    fitlering_frame_Scroll_cnt = 0;
    startFilteringFrame = 1;
    while(1)
    {
        if(redraw)
        {
            RefreshFilteringFrame();
            RefreshCreateBox();
            redraw = 0;
        }
        TranslateMenuFilteringMSG();
        
        if(hwndFilteringFrameControl == 20)
        {
           copyTasksToFlash();
              fp->needToSave = 1;
            FP_SaveParam();
            return;
        }
        
        
        if(hwndFilteringFrameControl == 0)
        {
            pistonTasks[REGENERATION_TASK_NUM].step[0].secPause = 60 * ShowKeyboardFrame(1, 150);
            startFilteringFrame = 1;
        }
        if(hwndFilteringFrameControl == 1)
        {
            pistonTasks[REGENERATION_TASK_NUM].step[1].secPause = 60 * ShowKeyboardFrame(1, 150);
            startFilteringFrame = 1;
        }
        if(hwndFilteringFrameControl == 2)
        {
            step = ShowStepsFrame();
            startFilteringFrame = 1;
        }
        hwndFilteringFrameControl = -1;
    }
}

void RefreshFilteringFrame(void)
{
    //Static refresh
    if(hwndFilteringFrameControl == -1 && startFilteringFrame == 1)
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
        BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_FILTERING,LEFT_MODE);
        BSP_LCD_DisplayStringAt(SAVE_X - 200,SAVE_Y,intToStr(step),LEFT_MODE);
        BSP_LCD_DisplayStringAt(SAVE_X,SAVE_Y,SAVE,LEFT_MODE);
        
        RefreshItem();        
        BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//        BSP_LCD_DrawRect(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y);
        BSP_LCD_DrawRect(SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y);
        BSP_LCD_DrawRect(THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y);
        BSP_LCD_DrawRect(SCROLLBAR_POS_X,SCROLLBAR_POS_Y,SCROLLBAR_SIZE_X,SCROLLBAR_SIZE_Y);
        
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(FIRST_CURSOR_VALUE_BOX_X,FIRST_CURSOR_VALUE_BOX_Y, FIRST_CURSOR_VALUE_BOX_SIZE_X, FIRST_CURSOR_VALUE_BOX_SIZE_Y);
        BSP_LCD_FillRect(SECOND_CURSOR_VALUE_BOX_X,SECOND_CURSOR_VALUE_BOX_Y, SECOND_CURSOR_VALUE_BOX_SIZE_X, SECOND_CURSOR_VALUE_BOX_SIZE_Y);
        //BSP_LCD_FillRect(THRID_CURSOR_VALUE_BOX_X,THRID_CURSOR_VALUE_BOX_Y, THRID_CURSOR_VALUE_BOX_SIZE_X, THRID_CURSOR_VALUE_BOX_SIZE_Y);
        
        BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 17,ITEM_FILTERING[fitlering_frame_Scroll_cnt],LEFT_MODE);
        BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 17,ITEM_FILTERING[fitlering_frame_Scroll_cnt + 1],LEFT_MODE);
        //BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 17,ITEM_FILTERING[fitlering_frame_Scroll_cnt + 2],LEFT_MODE);
        
//        BSP_LCD_DisplayStringAt(300,FIRST_CURSOR_POS_Y + 17,"���",LEFT_MODE);
        BSP_LCD_DisplayStringAt(300,SECOND_CURSOR_POS_Y + 17,MINUTE,LEFT_MODE);
        
//        BSP_LCD_DrawBitmap(372, FIRST_CURSOR_POS_Y + 8,&gImage_TRASH);
        BSP_LCD_DrawBitmap(372, SECOND_CURSOR_POS_Y + 8,&gImage_TRASH);

        BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
        BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
        
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (fitlering_frame_Scroll_cnt == 0 ? 0 : fitlering_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (fitlering_frame_Scroll_cnt == 0 ? 0 : fitlering_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (fitlering_frame_Scroll_cnt == 0 ? 0 : fitlering_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(FIRST_CURSOR_VALUE_BOX_X + 14,FIRST_CURSOR_VALUE_BOX_Y + 17,intToStr(qwertyFilBWASH),LEFT_MODE);
        BSP_LCD_DisplayStringAt(SECOND_CURSOR_VALUE_BOX_X + 14,SECOND_CURSOR_VALUE_BOX_Y + 17,intToStr(pistonTasks[REGENERATION_TASK_NUM].step[1].secPause/60),LEFT_MODE);
        

        
        startFilteringFrame = 0;
    }
    if(fitlering_frame_was_Scroll == 1 || fitlering_frame_was_Scroll == 2)
        RefreshScrollBarFilteringFrame();
}

void RefreshItem(void)
{
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_DrawRect(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y);
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(FIRST_CURSOR_VALUE_BOX_X,FIRST_CURSOR_VALUE_BOX_Y, FIRST_CURSOR_VALUE_BOX_SIZE_X, FIRST_CURSOR_VALUE_BOX_SIZE_Y);
    
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 17,ITEM_FILTERING[fitlering_frame_Scroll_cnt],LEFT_MODE);
    
    BSP_LCD_DisplayStringAt(300,FIRST_CURSOR_POS_Y + 17,MINUTE,LEFT_MODE);
    
    BSP_LCD_DrawBitmap(372, FIRST_CURSOR_POS_Y + 8,&gImage_TRASH);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(FIRST_CURSOR_VALUE_BOX_X + 14,FIRST_CURSOR_VALUE_BOX_Y + 17,intToStr(pistonTasks[REGENERATION_TASK_NUM].step[0].secPause/60),LEFT_MODE);
}

void RefreshCreateBox(void)
{
//    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//    BSP_LCD_DisplayStringAt(155,FIRST_CURSOR_POS_Y + 17,"�������",LEFT_MODE);
//    
//    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//    BSP_LCD_DisplayStringAt(155,SECOND_CURSOR_POS_Y + 17,"�������",LEFT_MODE);
    
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(155,THRID_CURSOR_POS_Y + 17, CREATE, LEFT_MODE);
    
}

void RefreshScrollBarFilteringFrame()
{       
    AnimateScrollBarKeysFilteringFrame();
    
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_FillRect(FIRST_CURSOR_POS_X + 1,FIRST_CURSOR_POS_Y + 1,FIRST_CURSOR_SIZE_X - 2,FIRST_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(SECOND_CURSOR_POS_X + 1,SECOND_CURSOR_POS_Y + 1,SECOND_CURSOR_SIZE_X - 2,SECOND_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(THRID_CURSOR_POS_X + 1,THRID_CURSOR_POS_Y + 1,THRID_CURSOR_SIZE_X - 2,THRID_CURSOR_SIZE_Y - 2);
    
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 17,ITEM_FILTERING[fitlering_frame_Scroll_cnt],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 17,ITEM_FILTERING[fitlering_frame_Scroll_cnt + 1],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 17,ITEM_FILTERING[fitlering_frame_Scroll_cnt + 2],LEFT_MODE);
}

void AnimateScrollBarKeysFilteringFrame(void)
{
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);      
    BSP_LCD_FillRect(SCROLLBAR_POS_X + 1,SCROLLBAR_POS_Y + 51,SCROLLBAR_SIZE_X - 2,SCROLLBAR_SIZE_Y - 98);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (fitlering_frame_Scroll_cnt == 0 ? 0 : fitlering_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (fitlering_frame_Scroll_cnt == 0 ? 0 : fitlering_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (fitlering_frame_Scroll_cnt == 0 ? 0 : fitlering_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);

    fitlering_frame_was_Scroll = 0;
}

void TranslateMenuFilteringMSG(void)
{
  BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
        {
           hwndFilteringFrameControl = 20;
        }     
        if (isInRectangle(tsState.X,tsState.Y,STATUSBAR_POS_X,STATUSBAR_POS_Y,100,TOP_BOT_LINE_WIDTH) )
        {
           hwndFilteringFrameControl = 10;
        }       
//        if (isInRectangle(tsState.X,tsState.Y,UP_ARROW_POS_X,UP_ARROW_POS_Y,UP_ARROW_SIZE_X,UP_ARROW_SIZE_Y))
//        {
//            if(fitlering_frame_Scroll_cnt > 0) fitlering_frame_Scroll_cnt--;
//            fitlering_frame_was_Scroll = 1;
//        }
//        if (isInRectangle(tsState.X,tsState.Y,DOWN_ARROW_POS_X,DOWN_ARROW_POS_Y,DOWN_ARROW_SIZE_X,DOWN_ARROW_SIZE_Y))
//        {
//            if(fitlering_frame_Scroll_cnt < 2) fitlering_frame_Scroll_cnt++;
//            fitlering_frame_was_Scroll = 2;
//        }
        
        //process list
        if (isInRectangle(tsState.X,tsState.Y,FIRST_CURSOR_VALUE_BOX_X,FIRST_CURSOR_VALUE_BOX_Y, FIRST_CURSOR_VALUE_BOX_SIZE_X, FIRST_CURSOR_VALUE_BOX_SIZE_Y))
        {
            hwndFilteringFrameControl = fitlering_frame_Scroll_cnt;
        }   
        if (isInRectangle(tsState.X,tsState.Y,SECOND_CURSOR_VALUE_BOX_X,SECOND_CURSOR_VALUE_BOX_Y, SECOND_CURSOR_VALUE_BOX_SIZE_X, SECOND_CURSOR_VALUE_BOX_SIZE_Y))
        {
            hwndFilteringFrameControl = fitlering_frame_Scroll_cnt + 1;
        }   
        if (isInRectangle(tsState.X,tsState.Y,THRID_CURSOR_VALUE_BOX_X,THRID_CURSOR_VALUE_BOX_Y, THRID_CURSOR_VALUE_BOX_SIZE_X, THRID_CURSOR_VALUE_BOX_SIZE_Y))
        {
            hwndFilteringFrameControl = fitlering_frame_Scroll_cnt + 2;
        }
    }
}