#include "serviceInfo.h"

static void createFrame(void);
static button_t serviceComplBut;
void  showServiceInfoFrame()
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
				
				return;
			}
			
			if (serviceComplBut.isReleased == true){
				int32_t res = showServiceDateSelectFrame();
				if (res > 0){
					fp->params.planner.monthBetweenService = planner.monthBetweenService = res;
					
					fp->params.planner.lastService = planner.lastService = getRTC();
					fp->needToSave = 1;
					FP_SaveParam();
				}
				createFrame();
				serviceComplBut.isReleased = false;
			}
			
			if (serviceComplBut.isPressed == true){
				
					drawFillButton(serviceComplBut.x, serviceComplBut.y, serviceComplBut.xSize, serviceComplBut.ySize, ITEM_SERVICE_INFO[2], true);
				
					serviceComplBut.isPressed = false;
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
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, FIRST_CURSOR_POS_Y, ITEM_SERVICE_INFO[1], CENTER_MODE);
	wtc_time_t tempDate = intToWTCTime(planner.lastService + planner.monthBetweenService*30*24*60*60);//*addMonth(&planner.lastService,planner.monthBetweenService);
	uint8_t* text = (compareDate(getTime(),&tempDate) < 0)? getFormatedTimeFromSource("DD MMM YYYY", &tempDate):ITEM_SERVICE_INFO[3];
	
	drawTextLabel(BSP_LCD_GetXSize()/2 - 150, SECOND_CURSOR_POS_Y, 300, 40, text);
	
	serviceComplBut = drawFillButton(BSP_LCD_GetXSize()/2 - 150, THRID_CURSOR_POS_Y, 300, 40, ITEM_SERVICE_INFO[2], false);

  TC_addButton(&serviceComplBut);
	TC_addButton(&okBut);
	TC_addButton(&retBut);	
	drawClock();
}
