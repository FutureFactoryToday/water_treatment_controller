#include "adjustmentFrame.h"

static void createFrame(void);
static button_t playBut[7], menuLine[7];
//int32_t pistonPositions.[] = {0, 0, 0, 0, 0, 0, 0};
uint32_t *firstEl;
//char* ITEM_STEPS[] = { "ЗАКРЫТОЕ ПОЛ.", "ОБРАТНАЯ ПРОМЫВКА", "РЕГЕНЕРАЦИЯ", "ЗАПОЛНЕНИЕ", "УМЯГЧЕНИЕ", "ПРОМЫВКА", "ФИЛЬТРАЦИЯ" };
uint8_t adjustment_frame_Scroll_cnt;
void ShowAdjustmentFrame(void)
{
	adjustment_frame_Scroll_cnt = 0;
	PC_Restart();
	createFrame();
	#ifndef newPositions
	firstEl = &pistonPositions.closedPosition;
	#else
	firstEl = &pistonPositions.rabPoz;	
	#endif
	while(1)
	{
		if (updateFlags.sec == true){
				drawClock();
				updateFlags.sec = false;
		}
		if (updateFlags.optic){
			 AnimatePosMenuFrame();
			updateFlags.optic = false;
		}
		
		if(retBut.isReleased == true) {
			retBut.isReleased = false;
			return;
		}
    if (okBut.isReleased == true){
			fp->needToSave = true;
			#ifndef newPositions
			fp->params.pistonPositions.closedPosition = pistonPositions.closedPosition;
			fp->params.pistonPositions.backwash = pistonPositions.backwash;
			fp->params.pistonPositions.regeneration = pistonPositions.regeneration;
			fp->params.pistonPositions.filling = pistonPositions.filling;
			fp->params.pistonPositions.softening = pistonPositions.softening;
			fp->params.pistonPositions.flushing = pistonPositions.flushing;
			fp->params.pistonPositions.rabPoz = pistonPositions.rabPoz; 
#else
			fp->params.pistonPositions.rabPoz = pistonPositions.rabPoz;
			fp->params.pistonPositions.forwardWash = pistonPositions.forwardWash;
			fp->params.pistonPositions.backwash = pistonPositions.backwash;
			fp->params.pistonPositions.saltering = pistonPositions.saltering;
			fp->params.pistonPositions.filling = pistonPositions.filling;

#endif			
			FP_SaveParam(); 
			okBut.isReleased = false;
		}
		if (scrollUpBut.isReleased == true){
			
			RefreshScrollBarAdjustmentFrame();
			scrollUpBut.isReleased = false;
		}
		if (scrollDwnBut.isReleased == true){
			
			RefreshScrollBarAdjustmentFrame();
			scrollDwnBut.isReleased = false;
		}
        
		#ifdef newPositions
        if(menuLine[0].isReleased == true)
        {
					pistonPositions.rabPoz = ShowKeyboardFrame(0,99999);
					createFrame();
					menuLine[0].isReleased = false;
        }
        if(menuLine[1].isReleased == true)
        {
					pistonPositions.forwardWash = ShowKeyboardFrame(0,99999);
					createFrame();
					menuLine[1].isReleased = false;
        }
        if(menuLine[2].isReleased == true)
        {
					pistonPositions.backwash = ShowKeyboardFrame(0,99999);
					createFrame();
					menuLine[2].isReleased = false;
        }
        if(menuLine[3].isReleased == true)
        {
					pistonPositions.saltering = ShowKeyboardFrame(0,99999);
					createFrame();
					menuLine[3].isReleased = false;
        }
        if(menuLine[4].isReleased == true)
        {
					pistonPositions.filling = ShowKeyboardFrame(0,99999);
					createFrame();
					menuLine[4].isReleased = false;
        }
				//cycle start
        if(playBut[0].isReleased == true)
        {
					PC_GoToPoz(pistonPositions.rabPoz);

					playBut[0].isReleased = false;
					createFrame();
        }
        if(playBut[1].isReleased == true)
        {
					PC_GoToPoz(pistonPositions.backwash);

					playBut[1].isReleased = false;
					createFrame();
        }
        if(playBut[2].isReleased == true)
        {
					PC_GoToPoz(pistonPositions.forwardWash);

					playBut[2].isReleased = false;
					createFrame();
        }
        if(playBut[3].isReleased == true)
        {
					PC_GoToPoz(pistonPositions.saltering);
					playBut[3].isReleased = false;
					createFrame();
        }
        if(playBut[4].isReleased == true)
        {
					PC_GoToPoz(pistonPositions.filling);

					playBut[4].isReleased = false;
					createFrame();
        }
       
				#else 
        if(menuLine[0].isReleased == true)
        {
					pistonPositions.closedPosition = ShowKeyboardFrame(0,99999);
					createFrame();
					menuLine[0].isReleased = false;
        }
        if(menuLine[1].isReleased == true)
        {
					pistonPositions.backwash = ShowKeyboardFrame(0,99999);
					createFrame();
					menuLine[1].isReleased = false;
        }
        if(menuLine[2].isReleased == true)
        {
					pistonPositions.regeneration = ShowKeyboardFrame(0,99999);
					createFrame();
					menuLine[2].isReleased = false;
        }
        if(menuLine[3].isReleased == true)
        {
					pistonPositions.filling = ShowKeyboardFrame(0,99999);
					createFrame();
					menuLine[3].isReleased = false;
        }
        if(menuLine[4].isReleased == true)
        {
					pistonPositions.softening = ShowKeyboardFrame(0,99999);
					createFrame();
					menuLine[4].isReleased = false;
        }
        if(menuLine[5].isReleased == true)
        {
					pistonPositions.flushing = ShowKeyboardFrame(0,99999);
					createFrame();
					menuLine[5].isReleased = false;
        }
        if(menuLine[6].isReleased == true)
        {
					pistonPositions.rabPoz = ShowKeyboardFrame(0,99999);
					createFrame();
					menuLine[6].isReleased = false;
        }
				
       
        //cycle start
        if(playBut[0].isReleased == true)
        {
					PC_GoToPoz(pistonPositions.closedPosition);

					playBut[0].isReleased = false;
					createFrame();
        }
        if(playBut[1].isReleased == true)
        {
					PC_GoToPoz(pistonPositions.backwash);

					playBut[1].isReleased = false;
					createFrame();
        }
        if(playBut[2].isReleased == true)
        {
					PC_GoToPoz(pistonPositions.regeneration);

					playBut[2].isReleased = false;
					createFrame();
        }
        if(playBut[3].isReleased == true)
        {
					PC_GoToPoz(pistonPositions.filling);
					playBut[3].isReleased = false;
					createFrame();
        }
        if(playBut[4].isReleased == true)
        {
					PC_GoToPoz(pistonPositions.softening);

					playBut[4].isReleased = false;
					createFrame();
        }
        if(playBut[5].isReleased == true)
        {
					PC_GoToPoz(pistonPositions.flushing);
					
					playBut[5].isReleased = false;
					createFrame();
        }
        if(playBut[6].isReleased == true)
        {
					PC_GoToPoz(pistonPositions.rabPoz);
					
					playBut[6].isReleased = false;
					createFrame();
        }
				 #endif
    }
}

void createFrame(void)
{
  TC_clearButtons(); 
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
	BSP_LCD_DisplayStringAt(SAVE_X,SAVE_Y,SAVE,LEFT_MODE);
	BSP_LCD_DisplayStringAt(RESET_X,RESET_Y,RESET_TEXT,LEFT_MODE);
	BSP_LCD_DisplayStringAt(POS_VALUE_LABEL_X,POS_VALUE_LABEL_Y,POSITION,LEFT_MODE);
			
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
	BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 17,ITEM_STEPS[adjustment_frame_Scroll_cnt],LEFT_MODE);
	BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 17,ITEM_STEPS[adjustment_frame_Scroll_cnt + 1],LEFT_MODE);
	BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 17,ITEM_STEPS[adjustment_frame_Scroll_cnt + 2],LEFT_MODE);
	
	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	BSP_LCD_DisplayStringAt(330,FIRST_CURSOR_POS_Y + 17,START_ENG,LEFT_MODE);
	BSP_LCD_DisplayStringAt(330,SECOND_CURSOR_POS_Y + 17,START_ENG,LEFT_MODE);
	BSP_LCD_DisplayStringAt(330,THRID_CURSOR_POS_Y + 17,START_ENG,LEFT_MODE);

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
	
	/*Add Buttons Data*/
	
	/*Add Buttons*/
	for(uint8_t i = 0; i < sizeof (menuLine); i++){
		 TC_addButton(&menuLine[i]);
	}
	for(uint8_t i = 0; i < sizeof (playBut); i++){
		 TC_addButton(&playBut[i]);
	}
	TC_addButton(&retBut);
	TC_addButton(&okBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);

	//enableClockDraw = true;
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
    BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 17,ITEM_STEPS[adjustment_frame_Scroll_cnt],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 17,ITEM_STEPS[adjustment_frame_Scroll_cnt + 1],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 17,ITEM_STEPS[adjustment_frame_Scroll_cnt + 2],LEFT_MODE);
    
    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
    BSP_LCD_DisplayStringAt(330,FIRST_CURSOR_POS_Y + 17,START_ENG,LEFT_MODE);
    BSP_LCD_DisplayStringAt(330,SECOND_CURSOR_POS_Y + 17,START_ENG,LEFT_MODE);
    BSP_LCD_DisplayStringAt(330,THRID_CURSOR_POS_Y + 17,START_ENG,LEFT_MODE);
    
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
}

void AnimatePosMenuFrame(void)
{
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_FillRect(POS_VALUE_X, POS_VALUE_Y,RESET_BUTTON_X - POS_VALUE_X,RESET_BUTTON_SIZE_Y);
    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    BSP_LCD_DisplayStringAt(POS_VALUE_X, POS_VALUE_Y, intToStr(PC_GetCurPoz()), LEFT_MODE);
	
}
