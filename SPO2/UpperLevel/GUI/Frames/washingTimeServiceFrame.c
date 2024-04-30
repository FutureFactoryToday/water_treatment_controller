#include "washingTimeServiceFrame.h"

static void createFrame(void);
static button_t timeBut;
static wtc_time_t regTime;
static uint8_t* text;
int ShowWashingTimeServiceFrame(void)
{
	if (sysParams.vars.planer.currentTask != NULL){
		regTime = intToWTCTime(sysParams.vars.planer.currentTask->restartDateTime);
	}
    createFrame();
    while(1)
    {
        if (updateFlags.sec == true){
             drawClock(); drawMainStatusBar(144, 2305, 16);
            updateFlags.sec = false;
        }
        //Pressed
        if (timeBut.isPressed == true){
            if (sysParams.vars.planer.currentTask != NULL){
                drawDarkTextLabel(BSP_LCD_GetXSize()/2 - 80, BSP_LCD_GetYSize()/2 - 20, 140, 40, getFormatedTimeFromSource("hh:mm", &regTime));
            }
            timeBut.isPressed = false;
        }
        //Released
        if(retBut.isReleased == true) {
            retBut.isReleased = false;
            return 0;
        }
        if(cancelBut.isReleased == true) {
            cancelBut.isReleased = false;
            return 0;
        }
        if (homeBut.isReleased == true){
			homeBut.isReleased = false;
      goHome = true;
		}
		if (goHome){
			return -1;
		}
        if (timeBut.isReleased == true){
            if (sysParams.vars.planer.currentTask != NULL){
                wtc_time_t tempTime = CSF_showFrame(&regTime);
                if( !isZeroTime(&tempTime)){
                    regTime = setTime(&regTime, &tempTime);
                    //createFrame();
                }
            }
            timeBut.isReleased = false;
            createFrame();
        }
        if (okBut.isReleased == true){
            if (sysParams.vars.planer.currentTask != NULL){
                sysParams.vars.planer.currentTask->restartDateTime = wtcTimeToInt(&regTime); 
                FP_SaveParam();
            }
            okBut.isReleased = false;
            return 0;
        }
			
    }
}

void createFrame(void)
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_REGEN_TIME);
	
	drawStatusBarOkCancel();
     
	
	if (sysParams.vars.planer.currentTask == NULL){
		text = &PL_NOT_INITED;
	} else {
		text = getFormatedTimeFromSource("hh:mm", &regTime);
	}
	timeBut = drawTextLabel(BSP_LCD_GetXSize()/2 - 80, BSP_LCD_GetYSize()/2 - 20, 140, 40, text);
	
    TC_addButton(&timeBut);
	TC_addButton(&retBut);
    TC_addButton(&homeBut);
    TC_addButton(&okBut);	
	TC_addButton(&cancelBut);
}
