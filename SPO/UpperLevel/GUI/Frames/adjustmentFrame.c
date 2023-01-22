#include "adjustmentFrame.h"

uint8_t adjustment_frame_Scroll_cnt = 0;
uint8_t adjustment_frame_was_Scroll = 0;
//int32_t pistonPositions.[] = {0, 0, 0, 0, 0, 0, 0};
int8_t hwndAdjustmentFrameControl = 0;
int8_t startAdjustmentFrame = 0;
uint32_t *firstEl;
char* ITEM_ADJUSTMENT[] = { "�������� ���.", "�����.����.", "�����.", "����������", "���������", "��������", "����������" };

void ShowAdjustmentFrame(void)
{
	hwndAdjustmentFrameControl = -1;
	adjustment_frame_Scroll_cnt = 0;
	startAdjustmentFrame = 1;
	firstEl = &pistonPositions.closedPosition;
    while(1)
    {
        if(redraw)
        {
            RefreshAdjustmentFrame();
            redraw = 0;
        }
        AnimatePosMenuFrame();
        TranslateMenuAdjustmentMSG();
        
        if(hwndAdjustmentFrameControl == 20) return;
        
        if(hwndAdjustmentFrameControl == 40)
        {
            fp->needToSave = true;
            fp->params.pistonPositions.closedPosition = pistonPositions.closedPosition;
            fp->params.pistonPositions.backwash = pistonPositions.backwash;
            fp->params.pistonPositions.regeneration = pistonPositions.regeneration;
            fp->params.pistonPositions.filling = pistonPositions.filling;
            fp->params.pistonPositions.softening = pistonPositions.softening;
            fp->params.pistonPositions.flushing = pistonPositions.flushing;
            fp->params.pistonPositions.filtering = pistonPositions.filtering;            
            FP_SaveParam();
            
            startAdjustmentFrame = 1;
        }
        
        if(hwndAdjustmentFrameControl == 30)
        {
            pistonPositions.closedPosition = 0;
            pistonPositions.backwash = 0;
            pistonPositions.regeneration = 0;
            pistonPositions.filling = 0;
            pistonPositions.softening = 0;
            pistonPositions.flushing = 0;
            pistonPositions.filtering = 0;
            
            startAdjustmentFrame = 1;
        }
        
        if(hwndAdjustmentFrameControl == 0)
        {
            pistonPositions.closedPosition = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 1)
        {
            pistonPositions.backwash = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 2)
        {
            pistonPositions.regeneration = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 3)
        {
            pistonPositions.filling = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 4)
        {
            pistonPositions.softening = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 5)
        {
            pistonPositions.flushing = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 6)
        {
            pistonPositions.filtering = ShowKeyboardFrame();
            startAdjustmentFrame = 1;
        }
        if (hwndAdjustmentFrameControl >=10 ||
					hwndAdjustmentFrameControl <= 16)
				{
					PC_Restart();
				}
        //cycle start
        if(hwndAdjustmentFrameControl == 10)
        {
            PC_GoToPoz(pistonPositions.closedPosition);
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 11)
        {
            PC_GoToPoz(pistonPositions.backwash);
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 12)
        {
            PC_GoToPoz(pistonPositions.regeneration);
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 13)
        {
            PC_GoToPoz(pistonPositions.filling);
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 14)
        {
            PC_GoToPoz(pistonPositions.softening);
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 15)
        {
            PC_GoToPoz(pistonPositions.flushing);
            startAdjustmentFrame = 1;
        }
        if(hwndAdjustmentFrameControl == 16)
        {
            PC_GoToPoz(pistonPositions.filtering);
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
        BSP_LCD_DisplayStringAt(SAVE_X,SAVE_Y,"����.",LEFT_MODE);
        BSP_LCD_DisplayStringAt(RESET_X,RESET_Y,"�����",LEFT_MODE);
        BSP_LCD_DisplayStringAt(POS_VALUE_LABEL_X,POS_VALUE_LABEL_Y,"���:",LEFT_MODE);
            
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
        BSP_LCD_DisplayStringAt(330,FIRST_CURSOR_POS_Y + 17,"�����",LEFT_MODE);
        BSP_LCD_DisplayStringAt(330,SECOND_CURSOR_POS_Y + 17,"�����",LEFT_MODE);
        BSP_LCD_DisplayStringAt(330,THRID_CURSOR_POS_Y + 17,"�����",LEFT_MODE);

        BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
        BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
        
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (adjustment_frame_Scroll_cnt == 0 ? 0 : adjustment_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (adjustment_frame_Scroll_cnt == 0 ? 0 : adjustment_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (adjustment_frame_Scroll_cnt == 0 ? 0 : adjustment_frame_Scroll_cnt * 19), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
        
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(FIRST_CURSOR_VALUE_BOX_X + 16,FIRST_CURSOR_VALUE_BOX_Y + 17,intToStr(*(firstEl + adjustment_frame_Scroll_cnt)),LEFT_MODE);
        BSP_LCD_DisplayStringAt(SECOND_CURSOR_VALUE_BOX_X + 16,SECOND_CURSOR_VALUE_BOX_Y + 17,intToStr(*(firstEl + adjustment_frame_Scroll_cnt + 1)),LEFT_MODE);
        BSP_LCD_DisplayStringAt(THRID_CURSOR_VALUE_BOX_X + 16,THRID_CURSOR_VALUE_BOX_Y + 17,intToStr(*(firstEl + adjustment_frame_Scroll_cnt + 2)),LEFT_MODE);
        

        
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
    BSP_LCD_DisplayStringAt(330,FIRST_CURSOR_POS_Y + 17,"�����",LEFT_MODE);
    BSP_LCD_DisplayStringAt(330,SECOND_CURSOR_POS_Y + 17,"�����",LEFT_MODE);
    BSP_LCD_DisplayStringAt(330,THRID_CURSOR_POS_Y + 17,"�����",LEFT_MODE);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(FIRST_CURSOR_VALUE_BOX_X + 16,FIRST_CURSOR_VALUE_BOX_Y + 17,intToStr(*(firstEl + adjustment_frame_Scroll_cnt)),LEFT_MODE);
    BSP_LCD_DisplayStringAt(SECOND_CURSOR_VALUE_BOX_X + 16,SECOND_CURSOR_VALUE_BOX_Y + 17,intToStr(*(firstEl + adjustment_frame_Scroll_cnt + 1)),LEFT_MODE);
    BSP_LCD_DisplayStringAt(THRID_CURSOR_VALUE_BOX_X + 16,THRID_CURSOR_VALUE_BOX_Y + 17,intToStr(*(firstEl + adjustment_frame_Scroll_cnt + 2)),LEFT_MODE);
    
    
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

void AnimatePosMenuFrame(void)
{
    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    BSP_LCD_DisplayStringAt(POS_VALUE_X, POS_VALUE_Y, intToStr(PC_GetParams()->curPoz), LEFT_MODE);
}

void TranslateMenuAdjustmentMSG(void)
{
  BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && wasTouch())
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,SAVE_BUTTON_X,SAVE_BUTTON_Y,SAVE_BUTTON_SIZE_X,SAVE_BUTTON_SIZE_Y)) 
        {
           hwndAdjustmentFrameControl = 40;
        }  
        if (isInRectangle(tsState.X,tsState.Y,RESET_BUTTON_X,RESET_BUTTON_Y,RESET_BUTTON_SIZE_X,RESET_BUTTON_SIZE_Y)) 
        {
           hwndAdjustmentFrameControl = 30;
        }  
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
        if (isInRectangle(tsState.X,tsState.Y,FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,300,FIRST_CURSOR_SIZE_Y))
        {
            hwndAdjustmentFrameControl = adjustment_frame_Scroll_cnt;
        }   
        if (isInRectangle(tsState.X,tsState.Y,SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,300,SECOND_CURSOR_SIZE_Y))
        {
            hwndAdjustmentFrameControl = adjustment_frame_Scroll_cnt + 1;
        }   
        if (isInRectangle(tsState.X,tsState.Y,THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,300,THRID_CURSOR_SIZE_Y))
        {
            hwndAdjustmentFrameControl = adjustment_frame_Scroll_cnt + 2;
        }
        
        //process cycle start
        if (isInRectangle(tsState.X,tsState.Y,FIRST_CURSOR_POS_X + 300,FIRST_CURSOR_POS_Y,119,FIRST_CURSOR_SIZE_Y))
        {
            hwndAdjustmentFrameControl = 10 + adjustment_frame_Scroll_cnt;
        }   
        if (isInRectangle(tsState.X,tsState.Y,SECOND_CURSOR_POS_X + 300,SECOND_CURSOR_POS_Y,119,SECOND_CURSOR_SIZE_Y))
        {
            hwndAdjustmentFrameControl = 10 + adjustment_frame_Scroll_cnt + 1;
        }   
        if (isInRectangle(tsState.X,tsState.Y,THRID_CURSOR_POS_X + 300,THRID_CURSOR_POS_Y,119,THRID_CURSOR_SIZE_Y))
        {
            hwndAdjustmentFrameControl = 10 + adjustment_frame_Scroll_cnt + 2;
        }
    }
}