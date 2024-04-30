#include "quantityCountServiceFrame.h"

static void createFrame(void);
static void updateData (void);

void ShowQuantityCountServiceFrame(void)
{
	createFrame();
	while(1)
	{
		if (updateFlags.sec == true){
             drawClock(); drawMainStatusBar(144, 2305, 16);
            updateFlags.sec = false;
        }	
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
	
	//BSP_LCD_DisplayStringAt(QUANTITY_COUNT_VALUE_X, QUANTITY_COUNT_VALUE_Y, intToStr((uint32_t)FM_getFlowMeterVal()), LEFT_MODE);
	drawTextLabel(BSP_LCD_GetXSize()/2 - 100, QUANTITY_COUNT_VALUE_Y, 100, BSP_LCD_GetFont()->height + 20, intToStr((uint32_t)FM_getFlowMeterVal()));  

}
void createFrame(void)
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_QUANTITY_COUNT);
	
	drawStatusBarEmpty();
	
	updateData();
	
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 + GAP, QUANTITY_COUNT_VALUE_Y+10, QUANTITY_COUNT, LEFT_MODE);
	
	TC_addButton(&retBut);
	//enableClockDraw = true;
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
