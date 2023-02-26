#include "alarmNotiFrame.h"

int8_t hwndAlarmNotiServiceFrameControl = 0;
int8_t startAlarmNotiFrame = 0;
static void createFrame (void);
static button_t alarmListBut;

void ShowAlarmNotiServiceFrame(void)
{
		createFrame();
    while(1)
    {
        if (retBut.isPressed == true){
					 retBut.isPressed = false;
					return;
				}
 
        if(alarmListBut.isPressed == true){
					alarmListBut.isPressed = false;
				}
				if (alarmListBut.isReleased == true)
        {
          ShowAlarmListFrame();
					alarmListBut.isReleased = false;
					createFrame();
        }
    }
}

void createFrame (void){
	TC_clearButtons();
 //Static refresh
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
	BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_FillRect(MAIN_WINDOW_POS_X,MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
	
	BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
	
	BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
	
	BSP_LCD_DrawBitmap(LIST_X, LIST_Y, &list);
	
	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_ALARM_NOTI,LEFT_MODE);
	
	//plug
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(85, 100, NOTI_STRING_1, LEFT_MODE);
	BSP_LCD_DisplayStringAt(105, 130, NOTI_STRING_2, LEFT_MODE);
	BSP_LCD_DisplayStringAt(135, 160, NOTI_STRING_3, LEFT_MODE);
	BSP_LCD_DisplayStringAt(140, 190, NOTI_STRING_4, LEFT_MODE);
	
	BSP_LCD_SetFont(&Oxygen_Mono_24);
	
	/*Add buttons settings*/
	
	
	/*Add Buttons*/
	TC_addButton(&retBut);
	TC_addButton(&alarmListBut);
	
	enableClockDraw = true;
}
