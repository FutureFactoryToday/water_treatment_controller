#include "quantityCountServiceFrame.h"

static void createFrame(void);
static void updateData (void);

void ShowQuantityCountServiceFrame(void)
{
	createFrame();
	while(1)
	{
			
		if (updateFlags.sec == true){ 
			updateData();
			updateFlags.sec = false;
		}	
		if(retBut.isPressed == true){
			return;
    }
	}
}
void updateData (void){
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(QUANTITY_COUNT_BOX_X,QUANTITY_COUNT_BOX_Y, QUANTITY_COUNT_BOX_SIZE_X, QUANTITY_COUNT_BOX_SIZE_Y);
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_DrawRect(QUANTITY_COUNT_BOX_X, QUANTITY_COUNT_BOX_Y, QUANTITY_COUNT_BOX_SIZE_X, QUANTITY_COUNT_BOX_SIZE_Y);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(QUANTITY_COUNT_VALUE_X, QUANTITY_COUNT_VALUE_Y, intToStr((uint32_t)FM_getFlowMeterVal()), LEFT_MODE);
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
	BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_QUANTITY_COUNT,LEFT_MODE);
	
	updateData();
	
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(QUANTITY_COUNT_VALUE_X + 80, QUANTITY_COUNT_VALUE_Y, QUANTITY_COUNT, LEFT_MODE);
	BSP_LCD_SetFont(&Oxygen_Mono_24);
	
	TC_addButton(&retBut);
	enableClockDraw = true;
}

//void AnimateTimeQuantityCountServiceFrame(void)
//{
//    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//    BSP_LCD_DisplayStringAt(TIME_X, TIME_Y, getFormatedTime(hour), LEFT_MODE);

//    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//    BSP_LCD_DisplayStringAt(TIME_X + 40, TIME_Y, getFormatedTime(minute), LEFT_MODE);
//    
//    if(getTime()->second%2 == 0)
//    {
//        BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(TIME_X + 30, TIME_Y - 2, ":", LEFT_MODE);
//    }
//    else
//    {
//        BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//        BSP_LCD_DisplayStringAt(TIME_X + 30, TIME_Y - 2, ":", LEFT_MODE);
//    }
//}
