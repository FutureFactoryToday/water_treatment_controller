#include "softeningFrame.h"


uint8_t softening_frame_Scroll_cnt = 0;
uint8_t softening_frame_was_Scroll = 0;
int32_t qwertySoft[] = {0, 0, 0, 0, 0};

//char* ITEM_SOFTENING[] = { "ОБР.ПРОМ.", "РЕАГ.ПРОМ.", "ВТОРАЯ.ПРОМ.", "ПРЯМАЯ.ПРОМ.", "ЗАЛИВКА" };
static void createFrame(void);
static button_t menuLine[5];
void ShowSofteningFrame(void)
{

    softening_frame_Scroll_cnt = 0;
    createFrame();
    while(1)
    {   
		 if(okBut.isReleased == true){
			copyTasksToFlash();
			fp->needToSave = 1;
			FP_SaveParam();
			okBut.isReleased = false;
			return;
		}
		if(retBut.isReleased == true){
			retBut.isReleased = false;
			return;
		}			
    if(menuLine[0].isReleased == true)
		{
			pistonTasks[SOFTENING_TASK_NUM].step[0].secPause = 60 * ShowKeyboardFrame(1,150);      
			createFrame();
			menuLine[0].isReleased = false;
		}
		if(menuLine[1].isReleased == true)
		{
			pistonTasks[SOFTENING_TASK_NUM].step[1].secPause = 60 * ShowKeyboardFrame(1,150);
			createFrame();
			menuLine[1].isReleased = false;
		}   
    if(menuLine[2].isReleased == true)
		{
			pistonTasks[SOFTENING_TASK_NUM].step[2].secPause = 60 * ShowKeyboardFrame(1,150);  
			createFrame();
			menuLine[2].isReleased = false;
		}
		if(menuLine[3].isReleased == true)
		{
			pistonTasks[SOFTENING_TASK_NUM].step[3].secPause = 60 * ShowKeyboardFrame(1,150);
			createFrame();
			menuLine[3].isReleased = false;
		}   
    if(menuLine[4].isReleased == true)
		{
			pistonTasks[SOFTENING_TASK_NUM].step[4].secPause = 60 * ShowKeyboardFrame(1,150);
			createFrame();
			menuLine[4].isReleased = false;
		}
		if(scrollUpBut.isReleased == true){
			if (softening_frame_Scroll_cnt > 0){
				 softening_frame_Scroll_cnt--;
			}
			RefreshScrollBarSofteningFrame();
			scrollUpBut.isReleased = false;
	 }
	 if(scrollDwnBut.isReleased == true){
			softening_frame_Scroll_cnt++;
			RefreshScrollBarSofteningFrame();
			scrollDwnBut.isReleased = false;     
	 }     
	}
}

void createFrame(void)
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
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_SOFTENING,LEFT_MODE);
	BSP_LCD_DisplayStringAt(SAVE_X,SAVE_Y,SAVE,LEFT_MODE);
			
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
	BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 17,ITEM_SOFTENING[softening_frame_Scroll_cnt],LEFT_MODE);
	BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 17,ITEM_SOFTENING[softening_frame_Scroll_cnt + 1],LEFT_MODE);
	BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 17,ITEM_SOFTENING[softening_frame_Scroll_cnt + 2],LEFT_MODE);
	
	BSP_LCD_DisplayStringAt(300,FIRST_CURSOR_POS_Y + 17,MINUTE,LEFT_MODE);
	BSP_LCD_DisplayStringAt(300,SECOND_CURSOR_POS_Y + 17,MINUTE,LEFT_MODE);
	BSP_LCD_DisplayStringAt(300,THRID_CURSOR_POS_Y + 17,MINUTE,LEFT_MODE);
	
	BSP_LCD_DrawBitmap(372, FIRST_CURSOR_POS_Y + 8,&gImage_TRASH);
	BSP_LCD_DrawBitmap(372, SECOND_CURSOR_POS_Y + 8,&gImage_TRASH);
	BSP_LCD_DrawBitmap(372, THRID_CURSOR_POS_Y + 8,&gImage_TRASH);

	BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
	BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
	
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (softening_frame_Scroll_cnt == 0 ? 0 : softening_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (softening_frame_Scroll_cnt == 0 ? 0 : softening_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (softening_frame_Scroll_cnt == 0 ? 0 : softening_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
	
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_VALUE_BOX_X + 14,FIRST_CURSOR_VALUE_BOX_Y + 17,intToStr(pistonTasks[SOFTENING_TASK_NUM].step[softening_frame_Scroll_cnt].secPause/60),LEFT_MODE);
	BSP_LCD_DisplayStringAt(SECOND_CURSOR_VALUE_BOX_X + 14,SECOND_CURSOR_VALUE_BOX_Y + 17,intToStr(pistonTasks[SOFTENING_TASK_NUM].step[softening_frame_Scroll_cnt + 1].secPause/60),LEFT_MODE);
	BSP_LCD_DisplayStringAt(THRID_CURSOR_VALUE_BOX_X + 14,THRID_CURSOR_VALUE_BOX_Y + 17,intToStr(pistonTasks[SOFTENING_TASK_NUM].step[softening_frame_Scroll_cnt + 2].secPause/60),LEFT_MODE);
			
	/*Add buttons parameters*/
	
	/*Add buttons to Touch Controller*/
	for (uint8_t i = 0; i < sizeof(menuLine); i++){
			TC_addButton(&menuLine[i]);
	}

	TC_addButton(&retBut);
	TC_addButton(&okBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);
	
	enableClockDraw = true;
          
}

void RefreshScrollBarSofteningFrame()
{       
    AnimateScrollBarKeysSofteningFrame();
    
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
    BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 17,ITEM_SOFTENING[softening_frame_Scroll_cnt],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 17,ITEM_SOFTENING[softening_frame_Scroll_cnt + 1],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 17,ITEM_SOFTENING[softening_frame_Scroll_cnt + 2],LEFT_MODE);
    
    BSP_LCD_DisplayStringAt(300,FIRST_CURSOR_POS_Y + 17,MINUTE,LEFT_MODE);
    BSP_LCD_DisplayStringAt(300,SECOND_CURSOR_POS_Y + 17,MINUTE,LEFT_MODE);
    BSP_LCD_DisplayStringAt(300,THRID_CURSOR_POS_Y + 17,MINUTE,LEFT_MODE);
    
    BSP_LCD_DrawBitmap(372, FIRST_CURSOR_POS_Y + 8,&gImage_TRASH);
    BSP_LCD_DrawBitmap(372, SECOND_CURSOR_POS_Y + 8,&gImage_TRASH);
    BSP_LCD_DrawBitmap(372, THRID_CURSOR_POS_Y + 8,&gImage_TRASH);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(FIRST_CURSOR_VALUE_BOX_X + 14,FIRST_CURSOR_VALUE_BOX_Y + 17,intToStr(pistonTasks[SOFTENING_TASK_NUM].step[softening_frame_Scroll_cnt].secPause/60),LEFT_MODE);
        BSP_LCD_DisplayStringAt(SECOND_CURSOR_VALUE_BOX_X + 14,SECOND_CURSOR_VALUE_BOX_Y + 17,intToStr(pistonTasks[SOFTENING_TASK_NUM].step[softening_frame_Scroll_cnt + 1].secPause/60),LEFT_MODE);
        BSP_LCD_DisplayStringAt(THRID_CURSOR_VALUE_BOX_X + 14,THRID_CURSOR_VALUE_BOX_Y + 17,intToStr(pistonTasks[SOFTENING_TASK_NUM].step[softening_frame_Scroll_cnt + 2].secPause/60),LEFT_MODE);
    
    
}

void AnimateScrollBarKeysSofteningFrame(void)
{
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);      
    BSP_LCD_FillRect(SCROLLBAR_POS_X + 1,SCROLLBAR_POS_Y + 51,SCROLLBAR_SIZE_X - 2,SCROLLBAR_SIZE_Y - 98);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (softening_frame_Scroll_cnt == 0 ? 0 : softening_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (softening_frame_Scroll_cnt == 0 ? 0 : softening_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (softening_frame_Scroll_cnt == 0 ? 0 : softening_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);

    softening_frame_was_Scroll = 0;
}