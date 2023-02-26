#include "filterSelectionFrame.h"

uint8_t filter_selection_frame_Scroll_cnt = 0;
uint8_t filter_selection_frame_was_Scroll = 0;

int8_t markItem = 0;
static void createFrame(void);
static button_t menuLine[3], checkBox[3];
static void markLine(uint8_t markNum);
//char* ITEM_FILTER_SELECTION[] = { "ФИЛЬТРАЦИЯ", "УМЯГЧЕНИЕ" };

void ShowFilterSelectionFrame(void)
{
    filter_selection_frame_Scroll_cnt = 0;

		if(chosenTask == pistonTasks) {
			markItem = 1;
		} else {
			markItem = 2;
		}
    while(1)
    {
        if(okBut.isReleased == true){
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
					ShowFilteringFrame();
					createFrame();
					menuLine[0].isReleased = false;
        }
				if(menuLine[1].isReleased == true)
        {
					ShowSofteningFrame();
					createFrame();
					menuLine[1].isReleased = false;
        }
        if (checkBox[0].isReleased == true){
					chosenTask = &pistonTasks[0];
					fp->params.chosenTaskNum = 0;
					fp->needToSave = 1;
					checkBox[0].isReleased = false;
					markLine(0);
				}
				if (checkBox[1].isReleased == true){
					chosenTask = &pistonTasks[1];
					fp->params.chosenTaskNum = 1;
					fp->needToSave = 1;
					checkBox[1].isReleased = false;
					markLine(1);
				}					
        if(scrollUpBut.isReleased == true){
					if (filter_selection_frame_Scroll_cnt > 0){
						 filter_selection_frame_Scroll_cnt--;
					}
					RefreshScrollBarMenuFrame();
					scrollUpBut.isReleased = false;
			 }
			 if(scrollDwnBut.isReleased == true){
					filter_selection_frame_Scroll_cnt++;
					RefreshScrollBarMenuFrame();
					scrollDwnBut.isReleased = false;
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
	
	BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
	
	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y,MODE_FILTER_SELECTION,LEFT_MODE);
			
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_DrawRect(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y);
	BSP_LCD_DrawRect(SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y);
	BSP_LCD_DrawRect(THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y);
	BSP_LCD_DrawRect(FOURTH_CURSOR_POS_X,FOURTH_CURSOR_POS_Y,FOURTH_CURSOR_SIZE_X,FOURTH_CURSOR_SIZE_Y);
	BSP_LCD_DrawRect(SCROLLBAR_POS_X,SCROLLBAR_POS_Y,SCROLLBAR_SIZE_X,SCROLLBAR_SIZE_Y);
					
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt],LEFT_MODE);
	BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt + 1],LEFT_MODE);   
	//BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt + 2],LEFT_MODE);    
	//BSP_LCD_DisplayStringAt(16,FOURTH_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt + 3],LEFT_MODE);    
				 

	BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
	BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
	
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (filter_selection_frame_Scroll_cnt == 0 ? 0 : filter_selection_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (filter_selection_frame_Scroll_cnt == 0 ? 0 : filter_selection_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (filter_selection_frame_Scroll_cnt == 0 ? 0 : filter_selection_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawRect(FIRST_CURSOR_POS_X + 339,FIRST_CURSOR_POS_Y + 3,77,FIRST_CURSOR_SIZE_Y - 7);
	BSP_LCD_DrawRect(SECOND_CURSOR_POS_X + 339,SECOND_CURSOR_POS_Y + 3,77,SECOND_CURSOR_SIZE_Y - 7);
	
	markLine(markItem);
	
	/*Add buttons parameters*/
	
	/*Add buttons to Touch Controller*/
	for (uint8_t i = 0; i < sizeof(menuLine); i++){
			TC_addButton(&menuLine[i]);
	}
	for (uint8_t i = 0; i < sizeof(checkBox); i++){
			TC_addButton(&checkBox[i]);
	}
	TC_addButton(&retBut);
	TC_addButton(&okBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);
	
	enableClockDraw = true;
 
}

void RefreshScrollBarFilterSelectionFrame(void)
{
    AnimateScrollBarKeysFilterSelectionFrame();
    
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_FillRect(FIRST_CURSOR_POS_X + 1,FIRST_CURSOR_POS_Y + 1,FIRST_CURSOR_SIZE_X - 2,FIRST_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(SECOND_CURSOR_POS_X + 1,SECOND_CURSOR_POS_Y + 1,SECOND_CURSOR_SIZE_X - 2,SECOND_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(THRID_CURSOR_POS_X + 1,THRID_CURSOR_POS_Y + 1,THRID_CURSOR_SIZE_X - 2,THRID_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(FOURTH_CURSOR_POS_X + 1,FOURTH_CURSOR_POS_Y + 1,FOURTH_CURSOR_SIZE_X - 2,FOURTH_CURSOR_SIZE_Y - 2);
    
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt],LEFT_MODE);
    BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt + 1],LEFT_MODE);
    //BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt + 2],LEFT_MODE);
    //BSP_LCD_DisplayStringAt(16,FOURTH_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt + 3],LEFT_MODE);
}

void AnimateScrollBarKeysFilterSelectionFrame(void)
{
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);     
    BSP_LCD_FillRect(SCROLLBAR_POS_X + 1,SCROLLBAR_POS_Y + 51,SCROLLBAR_SIZE_X - 2,SCROLLBAR_SIZE_Y - 99);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (filter_selection_frame_was_Scroll == 0 ? 0 : filter_selection_frame_was_Scroll * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (filter_selection_frame_was_Scroll == 0 ? 0 : filter_selection_frame_was_Scroll * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (filter_selection_frame_was_Scroll == 0 ? 0 : filter_selection_frame_was_Scroll * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    
    filter_selection_frame_was_Scroll = 0;
}

void AnimateTimeFilterSelectionFrame(void)
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

void markLine(uint8_t markNum){
	 if(markNum == 1)
    {
			BSP_LCD_DrawBitmap(360, FIRST_CURSOR_POS_Y + 9, &gImage_CHECKMARK);
			
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
			BSP_LCD_FillRect(SECOND_CURSOR_POS_X + 340, SECOND_CURSOR_POS_Y + 2, 76, SECOND_CURSOR_SIZE_Y - 8);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_DrawRect(SECOND_CURSOR_POS_X + 339,SECOND_CURSOR_POS_Y + 3,77,SECOND_CURSOR_SIZE_Y - 7);

    }
    if(markNum == 2)
    {
			BSP_LCD_DrawBitmap(360, SECOND_CURSOR_POS_Y + 9, &gImage_CHECKMARK);

			BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
			BSP_LCD_FillRect(FIRST_CURSOR_POS_X + 340, FIRST_CURSOR_POS_Y + 2, 76, FIRST_CURSOR_SIZE_Y - 8);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_DrawRect(FIRST_CURSOR_POS_X + 339,FIRST_CURSOR_POS_Y + 3,77,FIRST_CURSOR_SIZE_Y - 7);  

    }
}