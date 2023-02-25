#include "alarmListFrame.h" 

uint8_t alarm_list_frame_Scroll_cnt = 0;
uint8_t alarm_list_frame_was_Scroll = 0;

int8_t hwndAlarmListFrameControl = 0;
int8_t startAlarmListFrame = 0;

//char* ITEM_ALARM_LIST[];
static button_t menuLines[5], scrollUpBut, scrollDwnBut; 
static void createFrame();

void ShowAlarmListFrame(void)
{
    
    alarm_list_frame_Scroll_cnt = 0;
    startAlarmListFrame = 1;
    while(1)
    {
        createFrame();
    while(1)
    {
		
		/*Buttons pressed*/
		 if (retBut.isPressed == true){
			 
			 retBut.isPressed = false;
			 return;
		 }
		 if(menuLines[0].isPressed == true){
				//Make it blue
				menuLines[0].isPressed = false;
		 }
		 if(menuLines[1].isPressed == true){
				//Make it blue
				menuLines[1].isPressed = false;
		 }
		 if(menuLines[2].isPressed == true){
				//Make it blue
				menuLines[2].isPressed = false;
		 }
		 if(menuLines[3].isPressed == true){
				//Make it blue
				menuLines[3].isPressed = false;
		 }
		 if(menuLines[4].isPressed == true){
				//Make it blue
				menuLines[4].isPressed = false;
		 }
		 if(scrollUpBut.isPressed == true){
				//Make it blue
				scrollUpBut.isPressed = false;
		 }
		 if(scrollDwnBut.isPressed == true){
				//Make it blue
				scrollDwnBut.isPressed = false;
		 }
		/*Buttons released*/
		 if (retBut.isReleased == true){
			 
			 retBut.isReleased = false;
		 }
		 if(menuLines[0].isReleased == true){
				TSF_showFrame();
				menuLines[0].isReleased = false;
				createFrame();
		 }
		 if(menuLines[1].isReleased == true){
				ShowWashTimCustFrame();
				menuLines[1].isReleased = false;
			 createFrame();
		 }
		 if(menuLines[2].isReleased == true){
				ShowForcedRegenCustFrame();
				menuLines[2].isReleased = false;
			 createFrame();
		 }
		 if(menuLines[3].isReleased == true){
				ShowDelayedRegenCustFrame();
				menuLines[3].isReleased = false;
			 createFrame();
		 }
		 if(menuLines[4].isReleased == true){
				ShowDaysBetweenRegenCustFrame();
				menuLines[4].isReleased = false;
			 createFrame();
		 }
		 if(scrollUpBut.isReleased == true){
				
				scrollUpBut.isReleased = false;
		 }
		 if(scrollDwnBut.isReleased == true){
				
				scrollDwnBut.isReleased = false;
		 }
		}
	}
}
void createFrame(void){
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
	BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y, MODE_ALARM_LIST, LEFT_MODE);
			
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_DrawRect(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y);
	BSP_LCD_DrawRect(SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y);
	BSP_LCD_DrawRect(THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y);
	BSP_LCD_DrawRect(FOURTH_CURSOR_POS_X,FOURTH_CURSOR_POS_Y,FOURTH_CURSOR_SIZE_X,FOURTH_CURSOR_SIZE_Y);
	BSP_LCD_DrawRect(SCROLLBAR_POS_X,SCROLLBAR_POS_Y,SCROLLBAR_SIZE_X,SCROLLBAR_SIZE_Y);
					
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	//BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 9,ITEM_ALARM_LIST[alarm_list_frame_Scroll_cnt],LEFT_MODE);
	//BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 9,ITEM_ALARM_LIST[alarm_list_frame_Scroll_cnt + 1],LEFT_MODE);   
	//BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 9,ITEM_ALARM_LIST[alarm_list_frame_Scroll_cnt + 2],LEFT_MODE);    
	//BSP_LCD_DisplayStringAt(16,FOURTH_CURSOR_POS_Y + 9,ITEM_ALARM_LIST[alarm_list_frame_Scroll_cnt + 3],LEFT_MODE);    
				 

	BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
	BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);

	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (alarm_list_frame_Scroll_cnt == 0 ? 0 : alarm_list_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (alarm_list_frame_Scroll_cnt == 0 ? 0 : alarm_list_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
	BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (alarm_list_frame_Scroll_cnt == 0 ? 0 : alarm_list_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
  
	/*Add buttons parameters*/
	
	/*Add buttons to Touch Controller*/
	for (uint8_t i = 0; i < sizeof(menuLines); i++){
			TC_addButton(&menuLines[i]);
	}
	TC_addButton(&retBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);
	
	enableClockDraw = true;	
}
void RefreshAlarmListFrame(void)
{
  
    if(alarm_list_frame_was_Scroll == 1 || alarm_list_frame_was_Scroll == 2)
        RefreshScrollBarAlarmListFrame();
}

void RefreshScrollBarAlarmListFrame(void)
{
    AnimateScrollBarKeysAlarmListFrame();
    
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_FillRect(FIRST_CURSOR_POS_X + 1,FIRST_CURSOR_POS_Y + 1,FIRST_CURSOR_SIZE_X - 2,FIRST_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(SECOND_CURSOR_POS_X + 1,SECOND_CURSOR_POS_Y + 1,SECOND_CURSOR_SIZE_X - 2,SECOND_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(THRID_CURSOR_POS_X + 1,THRID_CURSOR_POS_Y + 1,THRID_CURSOR_SIZE_X - 2,THRID_CURSOR_SIZE_Y - 2);
    BSP_LCD_FillRect(FOURTH_CURSOR_POS_X + 1,FOURTH_CURSOR_POS_Y + 1,FOURTH_CURSOR_SIZE_X - 2,FOURTH_CURSOR_SIZE_Y - 2);
    
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    //BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 9,ITEM_ALARM_LIST[alarm_list_frame_Scroll_cnt],LEFT_MODE);
    //BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 9,ITEM_ALARM_LIST[alarm_list_frame_Scroll_cnt + 1],LEFT_MODE);
    //BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 9,ITEM_ALARM_LIST[alarm_list_frame_Scroll_cnt + 2],LEFT_MODE);
    //BSP_LCD_DisplayStringAt(16,FOURTH_CURSOR_POS_Y + 9,ITEM_ALARM_LIST[alarm_list_frame_Scroll_cnt + 3],LEFT_MODE);
}

void AnimateScrollBarKeysAlarmListFrame(void)
{
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);     
    BSP_LCD_FillRect(SCROLLBAR_POS_X + 1,SCROLLBAR_POS_Y + 51,SCROLLBAR_SIZE_X - 2,SCROLLBAR_SIZE_Y - 99);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (alarm_list_frame_Scroll_cnt == 0 ? 0 : alarm_list_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 7) + (alarm_list_frame_Scroll_cnt == 0 ? 0 : alarm_list_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 14) + (alarm_list_frame_Scroll_cnt == 0 ? 0 : alarm_list_frame_Scroll_cnt * 36), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
    
    alarm_list_frame_was_Scroll = 0;
}


