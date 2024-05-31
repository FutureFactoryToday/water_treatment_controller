#include "waterCountBeforeRegen.h"

static void createFrame(void);
static button_t waterBut;
static uint32_t waterVal;
static uint8_t* text;
void ShowWaterCountBeforeRegenFrame(void)
{
	
	waterVal = sysParams.consts.planerConsts.waterBeforeRegen;

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
			if (waterBut.isReleased == true){
				uint32_t tempRes = ShowKeyboardFrame(1,999);
				if (tempRes > 0){
						waterVal = tempRes;
						createFrame();
					}
				
				waterBut.isReleased = false;
			}
			if (waterBut.isPressed == true){
				if (sysParams.vars.planer.currentTask != NULL){
					drawDarkTextLabel(waterBut.x, waterBut.y, waterBut.xSize, waterBut.ySize, text);
				}
					waterBut.isPressed = false;
			}
			if (okBut.isReleased == true){
				sysParams.consts.planerConsts.waterBeforeRegen = waterVal;
				
				FP_SaveParam();
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
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_WATER_BR[0]);
	
	drawStatusBarOkCancel();
	
	waterBut = drawTextLabel(BSP_LCD_GetXSize()/2 - 110, BSP_LCD_GetYSize()/2 - 40, 100, 40, intToStr(waterVal));
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 + 10, BSP_LCD_GetYSize()/2 - 40,ITEM_WATER_BR[1], LEFT_MODE);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 + 30, BSP_LCD_GetYSize()/2 - 50,"3", LEFT_MODE);
	enableClockDraw = true;
	
  TC_addButton(&waterBut);
	TC_addButton(&okBut);
	TC_addButton(&retBut);	
	TC_addButton(&cancelBut);

}
