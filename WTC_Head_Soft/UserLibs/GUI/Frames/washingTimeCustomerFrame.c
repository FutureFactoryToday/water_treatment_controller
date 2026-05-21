#include "washingTimeCustomerFrame.h"

static void createFrame();
static uint8_t* text;
static button_t timeBut;
static wtc_time_t regTime;

int ShowWashTimCustFrame(void)
{

		regTime = planner.preferedTimeForWash;
    createFrame();
    while(1)
    {
        if (updateFlags.sec == true){
            drawClock();
            updateFlags.sec = false;
        }
        //Pressed
        if (timeBut.isPressed == true){
//            if (planner.currentTask != NULL){
//                drawDarkTextLabel(BSP_LCD_GetXSize()/2 - 80, BSP_LCD_GetYSize()/2 - 20, 140, 40, getFormatedTimeFromSource("hh:mm", &regTime));
//            }
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
        if(homeBut.isReleased == true) {
            homeBut.isReleased = false;
            return 1;
        }
        if (timeBut.isReleased == true){
            
					wtc_time_t tempTime = CSF_showFrame(&regTime);
					if( !isZeroTime(&tempTime)){
							regTime = *setTime(&regTime, &tempTime);
							//createFrame();
					}
					timeBut.isReleased = false;
					createFrame();
        }
        if (okBut.isReleased == true){
            
                planner.preferedTimeForWash = regTime;
                copyTasksToFlash();
                fp->needToSave = 1;
                FP_SaveParam();
            
            okBut.isReleased = false;
            return 0;
        }
			
			}
}

void createFrame()
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_REGEN_TIME);
	
	drawStatusBarOkCancel();
    drawClock();
	
	if (planner.currentTask == NULL){
		text = &PL_NOT_INITED;
	} else {
		text = getFormatedTimeFromSource("hh:mm", &regTime);
	}
	timeBut = drawLightTextLabel(BSP_LCD_GetXSize()/2 - 80, BSP_LCD_GetYSize()/2 - 20, 140, 40, text);
	
    TC_addButton(&timeBut);
	TC_addButton(&retBut);
    TC_addButton(&homeBut);
    TC_addButton(&okBut);	
}
