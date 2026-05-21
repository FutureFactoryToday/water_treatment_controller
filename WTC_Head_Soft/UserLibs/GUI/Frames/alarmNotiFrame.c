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
        if (updateFlags.sec == true){
            drawClock();
            updateFlags.sec = false;
        }
        if (retBut.isReleased == true){
					 retBut.isReleased = false;
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
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_ALARM_NOTI);
	
	drawStatusBarEmpty();
	
	//BSP_LCD_DrawBitmap(LIST_X, LIST_Y, &list);
	
	//plug
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, 100, NOTI_STRING_1, CENTER_MODE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, 130, NOTI_STRING_2, CENTER_MODE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, 160, NOTI_STRING_3, CENTER_MODE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, 190, NOTI_STRING_4, CENTER_MODE);
	
	BSP_LCD_SetFont(&Oxygen_Mono_24);
	
	/*Add buttons settings*/
	
	
	/*Add Buttons*/
	TC_addButton(&retBut);
	//TC_addButton(&alarmListBut);
	
	//enableClockDraw = true;
}
