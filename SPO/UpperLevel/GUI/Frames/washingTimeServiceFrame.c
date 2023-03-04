#include "washingTimeServiceFrame.h"

static void createFrame(void);
static button_t timeBut;
static wtc_time_t regTime;
static uint8_t* text;
void ShowWashingTimeServiceFrame(void)
{
	if (chosenTask != NULL){
		regTime = chosenTask->restartDateTime;
	}
   createFrame();
    while(1)
    {
			if(retBut.isReleased == true) {
				retBut.isReleased = false;
				
				return;
			}
			if(cancelBut.isReleased == true) {
				cancelBut.isReleased = false;
				
				return;
			}
			if (timeBut.isReleased == true){
				if (chosenTask != NULL){
					wtc_time_t tempTime = CSF_showFrame();
					if( !isZeroTime(&tempTime)){
						regTime = *setTime(&regTime, &tempTime);
						createFrame();
					}
				}
				timeBut.isReleased = false;
			}
			if (timeBut.isPressed == true){
				if (chosenTask != NULL){
					drawDarkTextLabel(BSP_LCD_GetXSize()/2 - 50, BSP_LCD_GetYSize()/2 - 40, 100, 40, text);
				}
					timeBut.isPressed = false;
			}
			if (okBut.isReleased == true){
				if (chosenTask != NULL){
					chosenTask->restartDateTime = *setTime(&chosenTask->restartDateTime, &regTime);
					FP_SaveParam();
				}
				okBut.isReleased = false;
				return;
			}
			
    }
}

void createFrame(void)
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_REGEN_TIME);
	
	drawStatusBarOkCancel();
	
	if (chosenTask == NULL){
		text = &PL_NOT_INITED;
	} else {
		text = getFormatedTimeFromSource("hh:mm", &chosenTask->restartDateTime);
	}
	timeBut = drawTextLabel(BSP_LCD_GetXSize()/2 - 50, BSP_LCD_GetYSize()/2 - 40, 100, 40, text);
	
	enableClockDraw = true;
	TC_addButton(&retBut);	
	drawClock();
}
