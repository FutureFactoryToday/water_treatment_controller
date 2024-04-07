#include "periodRegenFrame.h"

static void createFrame();
static button_t periodRegenBut;
static button_t timeBeforeRegenBut;

static uint8_t periodRegen, timeBeforeRegen;

int ShowPeriodRegenCustFrame(void)
{
	 
    createFrame();
    while(1)
    {
        if (updateFlags.sec == true){
            drawClock();
            updateFlags.sec = false;
        }
        
        
        
        //Released
        if(periodRegenBut.isReleased == true){
					int32_t tempData = ShowKeyboardFrame(1,250);
            if (tempData >= 0) {
							planner.currentTask->restartDateTime = tempData*60*60;
						}
            createFrame();
            periodRegenBut.isReleased = false;
        }
        if(timeBeforeRegenBut.isReleased == true){
            int32_t tempData = ShowKeyboardFrame(1,250);
            if (tempData >= 0) {
							planner.currentTask->startDateTime = getRTC() + tempData*60*60;
						}
					
            createFrame();
            timeBeforeRegenBut.isReleased = false;
        }
        if(retBut.isReleased == true) {
            retBut.isReleased = false;
            return 0;
        }
        if(homeBut.isReleased == true) {
            homeBut.isReleased = false;
            return 1;
        }
        if (okBut.isReleased == true){
            okBut.isReleased = false;
            return 0;
        }
        if(cancelBut.isReleased == true) {
            cancelBut.isReleased = false;
            return 0;
        }
    }
}

void createFrame()
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, PERIOD_REGEN);
	
	drawStatusBarOkCancel();
	drawClock();

	BSP_LCD_SetFont(&Oxygen_Mono_24);
	periodRegenBut = drawLightTextLabel(BSP_LCD_GetXSize()/2 + 50, BSP_LCD_GetYSize()/2 - 65, 100, 60, intToStr(planner.currentTask->restartDateTime/(60*60)));
	int32_t deltTime = planner.currentTask->startDateTime - getRTC();
	uint32_t remHours = 0;
	if (deltTime >= 0){
		remHours = deltTime/(60*60);
		timeBeforeRegenBut = drawLightTextLabel(BSP_LCD_GetXSize()/2 + 50, BSP_LCD_GetYSize()/2 + 25, 100, 60, intToStr(remHours));
	} else {
		timeBeforeRegenBut = drawLightTextLabel(BSP_LCD_GetXSize()/2 + 50, BSP_LCD_GetYSize()/2 + 25, 100, 60, "NaN");
	
	}
	
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 + 180, BSP_LCD_GetYSize()/2 - 50, "Ч", LEFT_MODE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 + 180, BSP_LCD_GetYSize()/2 + 40, "Ч", LEFT_MODE);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 - 190, BSP_LCD_GetYSize()/2 - 60, "Период проведения", LEFT_MODE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 - 190, BSP_LCD_GetYSize()/2 - 36, "промывки", LEFT_MODE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 - 190, BSP_LCD_GetYSize()/2 + 30, "Оставшееся время", LEFT_MODE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 - 190, BSP_LCD_GetYSize()/2 + 54, "до начала промывки", LEFT_MODE);

	TC_addButton(&periodRegenBut);
	TC_addButton(&timeBeforeRegenBut);
	TC_addButton(&retBut);
	TC_addButton(&homeBut);
	TC_addButton(&okBut);	
}
