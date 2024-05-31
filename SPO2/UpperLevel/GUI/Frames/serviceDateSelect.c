#include "serviceDateSelect.h"


static void createFrame(void);
static button_t dateBut[5];
int32_t  showServiceDateSelectFrame()
{
	
   createFrame();
    while(1)
    {
			if (updateFlags.sec == true){
				 drawClock(); drawMainStatusBar(144, 2305, 16);
				updateFlags.sec = false;
			}
			if(retBut.isReleased == true) {
				retBut.isReleased = false;
				
				return -1;
			}
			for(uint8_t i = 0; i < 5; i ++){
//				if (dateBut[i].isPressed){
//				 drawFillButton(BSP_LCD_GetXSize()/2 - 140 - GAP + (70 + GAP)*i, THRID_CURSOR_POS_Y, 70, 40, ITEM_SERVICE_INFO[7+i], true);
//					dateBut[i].isPressed = false;
//				}
				if (dateBut[i].isReleased){
					return 3*i;
				}
			}
		}  
}

void createFrame(void)
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, false, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_SERVICE_INFO[0]);
	
	drawStatusBarEmpty();
	
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, FIRST_CURSOR_POS_Y, ITEM_SERVICE_INFO[5], CENTER_MODE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, FIRST_CURSOR_POS_Y + 30, ITEM_SERVICE_INFO[6], CENTER_MODE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, FOURTH_CURSOR_POS_Y + 15, ITEM_SERVICE_INFO[12], CENTER_MODE);
	for(uint8_t i = 0; i < 5; i ++){
		dateBut[i] = drawFillButton(BSP_LCD_GetXSize()/2 - 165 - GAP - GAP + (70 + GAP)*i, THRID_CURSOR_POS_Y, 70, 40, ITEM_SERVICE_INFO[7+i], false);
		TC_addButton(&dateBut[i]);
	}


	TC_addButton(&retBut);	
	 drawClock(); drawMainStatusBar(144, 2305, 16);
}