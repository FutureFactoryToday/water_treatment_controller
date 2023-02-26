#include "washingTimeServiceFrame.h"

static void createFrame(void);
static button_t dayBut, nightBut;
void ShowWashingTimeServiceFrame(void)
{
   createFrame();
    while(1)
    {
       
			
			if(retBut.isReleased == true) {
				retBut.isReleased = false;
				FP_SaveParam();
				return;
			}
			if (dayBut.isReleased == true){
				pistonTasks[REGENERATION_TASK_NUM].restartDateTime.hour = pl_nightWashTime.hour;  
				pistonTasks[REGENERATION_TASK_NUM].restartDateTime.minute = pl_nightWashTime.minute; 
				pistonTasks[REGENERATION_TASK_NUM].restartDateTime.second = pl_nightWashTime.second;
				copyOneTaskToFlash(REGENERATION_TASK_NUM);
			
				FP_GetParam()->needToSave = 1;
				
				dayBut.isReleased = false;
			}
			
			if (nightBut.isReleased == true){
				pistonTasks[REGENERATION_TASK_NUM].restartDateTime.hour = pl_dayWashTime.hour;  
				pistonTasks[REGENERATION_TASK_NUM].restartDateTime.minute = pl_dayWashTime.minute; 
				pistonTasks[REGENERATION_TASK_NUM].restartDateTime.second = pl_dayWashTime.second;
				copyOneTaskToFlash(REGENERATION_TASK_NUM);
				//FP_GetParam()->params.washTime = 1;
				FP_GetParam()->needToSave = 1;
				
				nightBut.isReleased = false;
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
	BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_WASHING_TIME_SET,LEFT_MODE);
	
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(WASHING_TIME_VALUE_BOX_X,WASHING_TIME_VALUE_BOX_Y, WASHING_TIME_VALUE_BOX_SIZE_X, WASHING_TIME_VALUE_BOX_SIZE_Y);
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_DrawRect(WASHING_TIME_VALUE_BOX_X, WASHING_TIME_VALUE_BOX_Y, WASHING_TIME_VALUE_BOX_SIZE_X, WASHING_TIME_VALUE_BOX_SIZE_Y);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(WASHING_TIME_VALUE_BOX_X,WASHING_TIME_VALUE_BOX_Y, WASHING_TIME_VALUE_BOX_SIZE_X, WASHING_TIME_VALUE_BOX_SIZE_Y);
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_DrawRect(WASHING_TIME_VALUE_BOX_X, WASHING_TIME_VALUE_BOX_Y, WASHING_TIME_VALUE_BOX_SIZE_X, WASHING_TIME_VALUE_BOX_SIZE_Y);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	if(equalTime(&pistonTasks[REGENERATION_TASK_NUM].restartDateTime,&pl_dayWashTime))
	//if(FP_GetParam()->params.washTime == 1)
	{
		BSP_LCD_DisplayStringAt(WASHING_TIME_VALUE_X, WASHING_TIME_VALUE_Y, DAY, LEFT_MODE);
	}
	if(equalTime(&pistonTasks[REGENERATION_TASK_NUM].restartDateTime,&pl_nightWashTime))
	//if(FP_GetParam()->params.washTime == 2)
	{
		BSP_LCD_DisplayStringAt(WASHING_TIME_VALUE_X, WASHING_TIME_VALUE_Y, NIGHT, LEFT_MODE);
	}
	
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	dayBut.xSize = BSP_LCD_DisplayStringAt(WASHING_TIME_VALUE_X + 150, WASHING_TIME_VALUE_Y, DAY, LEFT_MODE);
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	nightBut.xSize = BSP_LCD_DisplayStringAt(WASHING_TIME_VALUE_X + 250, WASHING_TIME_VALUE_Y, NIGHT, LEFT_MODE);
	
	dayBut.x = WASHING_TIME_VALUE_X + 150;
	dayBut.y = WASHING_TIME_VALUE_Y; 
	dayBut.ySize = BSP_LCD_GetFont()->height;

	nightBut.x = WASHING_TIME_VALUE_X + 250;
	nightBut.y = WASHING_TIME_VALUE_Y;
	nightBut.ySize = BSP_LCD_GetFont()->height;
	
	enableClockDraw = true;
	TC_addButton(&retBut);
	TC_addButton(&dayBut);
	TC_addButton(&nightBut);	
}
