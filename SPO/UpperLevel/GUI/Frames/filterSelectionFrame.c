#include "filterSelectionFrame.h"

uint8_t filter_selection_frame_Scroll_cnt = 0;
uint8_t filter_selection_frame_was_Scroll = 0;

#define MARK_GAP MARK_BOX + 20
#define MARK_BOX 330
int8_t markItem = 0;
static void createFrame(void);
static button_t menuLine[3], checkBox[3];
static void markLines();

void RefreshFilterSelectionFrame(void);

void RefreshScrollBarFilterSelectionFrame(void);



void ShowFilterSelectionFrame(void)
{
    filter_selection_frame_Scroll_cnt = 0;

		if(chosenTask == &pistonTasks[0]){
			markItem = 1;
		} 
		if(chosenTask == &pistonTasks[1]){
			markItem = 2;
		}
		if(chosenTask == &pistonTasks[2]){
			markItem = 3;
		}
		
		createFrame();
    while(1)
    {
        if(okBut.isReleased == true){
					if (markItem > 0){
						chosenTask = &pistonTasks[markItem - 1];
						fp->params.chosenTaskNum = markItem - 1;
						fp->needToSave = 1;
						FP_SaveParam();
					}
					okBut.isReleased = false;
					return;
				}
        if(retBut.isReleased == true){
					retBut.isReleased = false;
					return;
				}
				if (cancelBut.isReleased == true){
					cancelBut.isReleased = false;
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
				if(menuLine[2].isReleased == true)
        {
					ShowSofteningFrame();
					createFrame();
					menuLine[2].isReleased = false;
        }
        if (checkBox[0].isReleased == true){
					markItem = 1;
					checkBox[0].isReleased = false;
					markLines();
				}
				if (checkBox[1].isReleased == true){
					markItem = 2;
					checkBox[1].isReleased = false;
					markLines();
				}		
				if (checkBox[2].isReleased == true){
					markItem = 3;
					checkBox[2].isReleased = false;
					markLines();
				}		
        for (uint8_t i = 0; i < sizeof(menuLine)/sizeof(menuLine[0]); i++){
					if (menuLine[i].isPressed){
						drawDarkTextLabel(3*GAP + 40 + GAP, BSP_LCD_GetYSize()/2 - 80 + i*50, 250, 40, ITEM_FILTER_SELECTION[i]);
						menuLine[i].isPressed = false;
					} 
					if (checkBox[i].isPressed){
						drawFillButton(3*GAP, BSP_LCD_GetYSize()/2 - 80 + i*50, 40, 40,"", true);
						checkBox[i].isPressed = false;
					}
				}
    }
}

void createFrame(void)
{
	TC_clearButtons();
  //Static refresh
	
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_FILTER_SELECTION);
	
	drawStatusBarOkCancel();
	
	for (uint8_t i = 0; i < sizeof(menuLine)/sizeof(menuLine[0]); i++){
		menuLine[i] = drawTextLabel(3*GAP + 40 + GAP, BSP_LCD_GetYSize()/2 - 80 + i*50, 250, 40, ITEM_FILTER_SELECTION[i]);
	}
	markLines();	

	
//	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//	BSP_LCD_DrawRect(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y);
//	BSP_LCD_DrawRect(SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y);
//	BSP_LCD_DrawRect(THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y);
//	BSP_LCD_DrawRect(FOURTH_CURSOR_POS_X,FOURTH_CURSOR_POS_Y,FOURTH_CURSOR_SIZE_X,FOURTH_CURSOR_SIZE_Y);

//					
//	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//	BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt],LEFT_MODE);
//	BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt + 1],LEFT_MODE);   
//	BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt + 2],LEFT_MODE);    
//	//BSP_LCD_DisplayStringAt(16,FOURTH_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt + 3],LEFT_MODE);    
//				 

////	BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
////	BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
////	
////	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
////	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (filter_selection_frame_Scroll_cnt == 0 ? 0 : filter_selection_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
////	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (filter_selection_frame_Scroll_cnt == 0 ? 0 : filter_selection_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
////	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (filter_selection_frame_Scroll_cnt == 0 ? 0 : filter_selection_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
////	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//	BSP_LCD_DrawRect(FIRST_CURSOR_POS_X + MARK_BOX,FIRST_CURSOR_POS_Y + 3,77,FIRST_CURSOR_SIZE_Y - 7);
//	BSP_LCD_DrawRect(SECOND_CURSOR_POS_X + MARK_BOX,SECOND_CURSOR_POS_Y + 3,77,SECOND_CURSOR_SIZE_Y - 7);
//	BSP_LCD_DrawRect(THRID_CURSOR_POS_X + MARK_BOX,THRID_CURSOR_POS_Y + 3,77,THRID_CURSOR_SIZE_Y - 7);
//	markLine(markItem);
	
	/*Add buttons parameters*/
	
	/*Add buttons to Touch Controller*/
	for (uint8_t i = 0; i < sizeof(menuLine)/sizeof(menuLine[0]); i++){
			TC_addButton(&menuLine[i]);
	}
	for (uint8_t i = 0; i < sizeof(checkBox)/sizeof(checkBox[0]); i++){
			TC_addButton(&checkBox[i]);
	}
	TC_addButton(&retBut);
	TC_addButton(&okBut);
//	TC_addButton(&scrollUpBut);
//	TC_addButton(&scrollDwnBut);
	
	enableClockDraw = true;
 
}

//void RefreshScrollBarFilterSelectionFrame(void)
//{
//    //AnimateScrollBarKeysFilterSelectionFrame();
//    
//    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//    BSP_LCD_FillRect(FIRST_CURSOR_POS_X + 1,FIRST_CURSOR_POS_Y + 1,FIRST_CURSOR_SIZE_X - 2,FIRST_CURSOR_SIZE_Y - 2);
//    BSP_LCD_FillRect(SECOND_CURSOR_POS_X + 1,SECOND_CURSOR_POS_Y + 1,SECOND_CURSOR_SIZE_X - 2,SECOND_CURSOR_SIZE_Y - 2);
//    BSP_LCD_FillRect(THRID_CURSOR_POS_X + 1,THRID_CURSOR_POS_Y + 1,THRID_CURSOR_SIZE_X - 2,THRID_CURSOR_SIZE_Y - 2);
//    BSP_LCD_FillRect(FOURTH_CURSOR_POS_X + 1,FOURTH_CURSOR_POS_Y + 1,FOURTH_CURSOR_SIZE_X - 2,FOURTH_CURSOR_SIZE_Y - 2);
//    
//    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//    BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt],LEFT_MODE);
//    BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt + 1],LEFT_MODE);
//    //BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt + 2],LEFT_MODE);
//    //BSP_LCD_DisplayStringAt(16,FOURTH_CURSOR_POS_Y + 9,ITEM_FILTER_SELECTION[filter_selection_frame_Scroll_cnt + 3],LEFT_MODE);
//}

//void AnimateScrollBarKeysFilterSelectionFrame(void)
//{
//    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);     
//    BSP_LCD_FillRect(SCROLLBAR_POS_X + 1,SCROLLBAR_POS_Y + 51,SCROLLBAR_SIZE_X - 2,SCROLLBAR_SIZE_Y - 99);
//    
//    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (filter_selection_frame_was_Scroll == 0 ? 0 : filter_selection_frame_was_Scroll * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
//    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (filter_selection_frame_was_Scroll == 0 ? 0 : filter_selection_frame_was_Scroll * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
//    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (filter_selection_frame_was_Scroll == 0 ? 0 : filter_selection_frame_was_Scroll * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
//    
//    filter_selection_frame_was_Scroll = 0;
//}

void markLines(){
	bool checked;
	for (uint8_t i = 0; i < sizeof(menuLine)/sizeof(menuLine[0]); i++){
		checked = (markItem - 1 == i)? true: false;
		checkBox[i] = drawFillButton(3*GAP, BSP_LCD_GetYSize()/2 - 80 + i*50, 40, 40,"", checked);
	}
		
}