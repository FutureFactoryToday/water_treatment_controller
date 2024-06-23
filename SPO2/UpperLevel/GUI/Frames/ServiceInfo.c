#include "serviceInfo.h"

static void createFrame(void);
static button_t serviceComplBut;
int showServiceInfoFrame()
{
	
   createFrame();
    while(1)
    {
			if (updateFlags.sec == true){
				drawClock();
                drawMainStatusBar(144, 2305, 16);
				updateFlags.sec = false;
			}
			if (retBut.isReleased == true) {
				retBut.isReleased = false;
				return 0;
			}
            if (homeBut.isReleased == true){
                homeBut.isReleased = false;
                goHome = true;
            }
            if (goHome){
                return -1;
            }
			
			if (serviceComplBut.isReleased == true){
				int32_t res = showServiceDateSelectFrame();
				if (res >= 0){
					sysParams.consts.planerConsts.monthBetweenService = res;
					sysParams.consts.planerConsts.lastService = getRTC();
					sysParams.vars.status.flags.NeedService = 0;
					FP_SaveParam();
				}
				createFrame();
				serviceComplBut.isReleased = false;
			}
			if (serviceComplBut.isPressed == true){
				
					drawFillButton(serviceComplBut.x, serviceComplBut.y, serviceComplBut.xSize, serviceComplBut.ySize, ITEM_SERVICE_INFO[3], true);
				
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
  BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, FIRST_CURSOR_POS_Y + 30, ITEM_SERVICE_INFO[2], CENTER_MODE);
	wtc_time_t tempDate = intToWTCTime(sysParams.consts.planerConsts.lastService + sysParams.consts.planerConsts.monthBetweenService*30*24*60*60);//*addMonth(&sysParams.consts.planerConsts.lastService,sysParams.consts.planerConsts.monthBetweenService);
	uint8_t* text = (compareDate(&sysParams.vars.sysTime,&tempDate) < 0)? getFormatedTimeFromSource("DD MMM YYYY", &tempDate):ITEM_SERVICE_INFO[4];
	
	drawTextLabel(BSP_LCD_GetXSize()/2 - 150, SECOND_CURSOR_POS_Y + 30, 300, 40, text);
	
	serviceComplBut = drawFillButton(BSP_LCD_GetXSize()/2 - 150, THRID_CURSOR_POS_Y + 50, 300, 40, ITEM_SERVICE_INFO[3], false);

    TC_addButton(&serviceComplBut);
	TC_addButton(&okBut);
	TC_addButton(&retBut);	
	TC_addButton(&homeBut);
	 drawClock(); drawMainStatusBar(144, 2305, 16);
}
