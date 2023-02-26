#include "stepsFrame.h"

uint8_t steps_frame_Scroll_cnt = 0;
uint8_t steps_frame_was_Scroll = 0;

int8_t startStepsFrame = 0;

int8_t stepsFrameResult = 0;
int8_t stepResult = -1;

static void createFrame(void);
static button_t menuLine[6];
int8_t ShowStepsFrame(void)
{
	steps_frame_Scroll_cnt = 0;
	startStepsFrame = 1;
	stepsFrameResult = 0;
	stepResult = 0;
	while(1)
	{
		if (scrollUpBut.isReleased == true){
			steps_frame_Scroll_cnt--;
			RefreshScrollBarStepsFrame();
			scrollUpBut.isReleased = false;
		}
		if (scrollDwnBut.isReleased == true){
			steps_frame_Scroll_cnt++;
			RefreshScrollBarStepsFrame();
			scrollDwnBut.isReleased = false;
		} 
        
		if(retBut.isReleased == true)
		{
			retBut.isReleased == false;
			return 0;
		}
		if(okBut.isReleased == true)
		{
			okBut.isReleased == false;
			return stepResult;
		}
		 if(menuLine[0].isReleased == true)
		{
			stepResult = 1;
			menuLine[0].isReleased = false;
		}
		if(menuLine[1].isReleased == true)
		{
			stepResult = 2;
			menuLine[1].isReleased = false;
		}
		if(menuLine[2].isReleased == true)
		{
			stepResult = 3;
			menuLine[2].isReleased = false;
		}
		if(menuLine[3].isReleased == true)
		{
			stepResult = 4;
			menuLine[3].isReleased = false;
		}
		if(menuLine[4].isReleased == true)
		{
			stepResult = 5;
			menuLine[4].isReleased = false;
		}
		if(menuLine[5].isReleased == true)
		{
			stepResult = 6;
			menuLine[5].isReleased = false;
		}
   }
}

void createFrame(void)
{
	TC_clearButtons(); 
	//Static refresh

	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
	BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_FillRect(MAIN_WINDOW_POS_X,MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
	
	BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
	
	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,STEPS_LIST,LEFT_MODE);
			
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_DrawRect(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y);
	BSP_LCD_DrawRect(SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y);
	BSP_LCD_DrawRect(THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y);
	BSP_LCD_DrawRect(FOURTH_CURSOR_POS_X,FOURTH_CURSOR_POS_Y,FOURTH_CURSOR_SIZE_X,FOURTH_CURSOR_SIZE_Y);
	
	BSP_LCD_DrawRect(SCROLLBAR_POS_X,SCROLLBAR_POS_Y,SCROLLBAR_SIZE_X,SCROLLBAR_SIZE_Y);
	
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt],LEFT_MODE);
	BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt + 1],LEFT_MODE);
	BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt + 2],LEFT_MODE);
	BSP_LCD_DisplayStringAt(16,FOURTH_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt + 3],LEFT_MODE);
	
				 
	BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
	BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
	
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (steps_frame_Scroll_cnt == 0 ? 0 : steps_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (steps_frame_Scroll_cnt == 0 ? 0 : steps_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (steps_frame_Scroll_cnt == 0 ? 0 : steps_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
	
	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	
	BSP_LCD_DisplayStringAt(CANCEL_X, CANCEL_Y, CANCEL, LEFT_MODE);
	
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	
	BSP_LCD_DisplayStringAt(OK_X, OK_Y, OK, LEFT_MODE);
	
	/*Add Buttons Data*/
	
	/*Add Buttons*/
	for(uint8_t i = 0; i < sizeof (menuLine); i++){
		 TC_addButton(&menuLine[i]);
	}

	TC_addButton(&retBut);
	TC_addButton(&okBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);

	enableClockDraw = true;
}

void RefreshScrollBarStepsFrame()
{       
    AnimateScrollBarKeysStepsFrame();
    

    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_FillRect(FIRST_CURSOR_POS_X + 1,FIRST_CURSOR_POS_Y + 1,FIRST_CURSOR_SIZE_X - 2,FIRST_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(SECOND_CURSOR_POS_X + 1,SECOND_CURSOR_POS_Y + 1,SECOND_CURSOR_SIZE_X - 2,SECOND_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(THRID_CURSOR_POS_X + 1,THRID_CURSOR_POS_Y + 1,THRID_CURSOR_SIZE_X - 2,THRID_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(FOURTH_CURSOR_POS_X + 1,FOURTH_CURSOR_POS_Y + 1,FOURTH_CURSOR_SIZE_X - 2,FOURTH_CURSOR_SIZE_Y - 2);
    
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt + 1],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt + 2],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,FOURTH_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt + 3],LEFT_MODE);
    
}

void AnimateScrollBarKeysStepsFrame(void)
{
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);      
    BSP_LCD_FillRect(SCROLLBAR_POS_X + 1,SCROLLBAR_POS_Y + 51,SCROLLBAR_SIZE_X - 2,SCROLLBAR_SIZE_Y - 98);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (steps_frame_Scroll_cnt == 0 ? 0 : steps_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (steps_frame_Scroll_cnt == 0 ? 0 : steps_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (steps_frame_Scroll_cnt == 0 ? 0 : steps_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);

    steps_frame_was_Scroll = 0;
}
