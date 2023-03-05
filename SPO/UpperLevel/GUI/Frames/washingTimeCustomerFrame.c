#include "washingTimeCustomerFrame.h"

static void createFrame();
static uint8_t* text;

void ShowWashTimCustFrame(void)
{
	createFrame();
	while(1)
	{
        if (updateFlags.sec == true){
            if (chosenTask == NULL){
                text = &PL_NOT_INITED;
              } else {
                text = getFormatedTimeFromSource("hh:mm", &chosenTask->restartDateTime);
              }
            uint8_t remainingDays = countDaysBetween(getTime(), &chosenTask->startDateTime);
            BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_DisplayStringAt(WASHING_TIME_CUST_VALUE_BOX_X + 32, WASHING_TIME_CUST_VALUE_BOX_Y + 12, text ,LEFT_MODE);         
            updateFlags.sec = false;
        }
		if(retBut.isPressed == true){
            retBut.isPressed = false;
            return;
        }
    }

}

void createFrame()
{
    TC_clearButtons();
    
    drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_WASHING_TIME);
    
    drawMainWindow();
    
    drawTextLabel(WASHING_TIME_CUST_VALUE_BOX_X, WASHING_TIME_CUST_VALUE_BOX_Y, WASHING_TIME_CUST_VALUE_BOX_SIZE_X, WASHING_TIME_CUST_VALUE_BOX_SIZE_Y,"");
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    //BSP_LCD_DisplayStringAt(250, WASHING_TIME_CUST_VALUE_BOX_Y + 10, "Время" ,LEFT_MODE);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    
    drawStatusBarEmpty();
    
    drawClock();
    
    /*Add buttons parameters*/
   
	/*Add buttons to Touch Controller*/
	
	TC_addButton(&retBut);
    
    enableClockDraw = true;
    
//	TC_clearButtons();
//	//Static refresh
//	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//	BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
//	BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
//	
//	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//	BSP_LCD_FillRect(MAIN_WINDOW_POS_X, MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
//	
//	BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
//	
//	BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
//					
//	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//	BSP_LCD_DisplayStringAt(MODE_WASH_TIME_X, MODE_WASH_TIME_Y ,MODE_WASHING_TIME,LEFT_MODE);
//	
//	//uint8_t picPtr;
//	if(equalTime(&pistonTasks[REGENERATION_TASK_NUM].restartDateTime,&pl_dayWashTime))
//	//if(FP_GetParam()->params.washTime == 1)
//	{
//			BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//			BSP_LCD_DisplayStringAt(WASHING_TIME_CUST_VALUE_X, WASHING_TIME_CUST_VALUE_Y, DAY, LEFT_MODE);
//			//picPtr = &day;
//			//BSP_LCD_DrawBitmap(190, 90, &day);
//	}
//	if(equalTime(&pistonTasks[REGENERATION_TASK_NUM].restartDateTime,&pl_nightWashTime))
//	//if(FP_GetParam()->params.washTime == 2)
//	{
//			BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//			BSP_LCD_DisplayStringAt(WASHING_TIME_CUST_VALUE_X, WASHING_TIME_CUST_VALUE_Y, NIGHT, LEFT_MODE);
//			//picPtr = &night;
//			//BSP_LCD_DrawBitmap(190, 90, &night);
//	}
//	//BSP_LCD_DrawBitmap(190, 90, &picPtr);
//    enableClockDraw = true;
//	TC_addButton(&retBut);  
}
