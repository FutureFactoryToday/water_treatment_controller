#include "serviceDateSelect.h"


static void createFrame(void);
static button_t dateBut[4];
int32_t  showServiceDateSelectFrame()
{
	
   createFrame();
    while(1)
    {
			if (updateFlags.sec == true){
				drawClock();
				updateFlags.sec = false;
			}
			if(retBut.isReleased == true) {
				retBut.isReleased = false;
				
				return -1;
			}
			for(uint8_t i = 0; i < 4; i ++){
				if (dateBut[i].isPressed){
				 drawFillButton(BSP_LCD_GetXSize()/2 - 140 - GAP - GAP/2 + (70 + GAP)*i, THRID_CURSOR_POS_Y, 70, 40, ITEM_SERVICE_INFO[6+i], true);
					dateBut[i].isPressed = false;
				}
				if (dateBut[i].isReleased){
					return 3+3*i;
				}
			}
		}  
}

void createFrame(void)
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_SERVICE_INFO[0]);
	
	drawStatusBarEmpty();
	
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, FIRST_CURSOR_POS_Y, ITEM_SERVICE_INFO[4], CENTER_MODE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, SECOND_CURSOR_POS_Y, ITEM_SERVICE_INFO[5], CENTER_MODE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, FOURTH_CURSOR_POS_Y, ITEM_SERVICE_INFO[10], CENTER_MODE);
	for(uint8_t i = 0; i < 4; i ++){
		dateBut[i] = drawFillButton(BSP_LCD_GetXSize()/2 - 140 - GAP - GAP/2 + (70 + GAP)*i, THRID_CURSOR_POS_Y, 70, 40, ITEM_SERVICE_INFO[6+i], false);
		TC_addButton(&dateBut[i]);
	}


	TC_addButton(&retBut);	
	drawClock();
}