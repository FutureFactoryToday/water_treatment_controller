#include "filterCycleFrame.h"

static void createFrame();
static button_t filterCycleBut;
static button_t reserveBut;
static button_t mcube;
static button_t liters;

static uint32_t filterCycle;
static uint8_t reserve;

bool quantity = false;
	
int ShowFilterCycleCustFrame(void)
{
    createFrame();
    while(1)
    {
        if (updateFlags.sec == true){
            drawClock();
            updateFlags.sec = false;
        }
        
        
        
        //Released
        if(filterCycleBut.isReleased == true){
            filterCycle = ShowKeyboardFrame(1,2000);
            createFrame();
            filterCycleBut.isReleased = false;
        }
        if(reserveBut.isReleased == true){
            reserve = ShowKeyboardFrame(1,100);
            createFrame();
            reserveBut.isReleased = false;
        }
				if(mcube.isReleased == true){
						quantity = false;
						drawLightTextLabel(BSP_LCD_GetXSize()/2 + 100, BSP_LCD_GetYSize()/2 - 65, 60, 60, "М*3");
						drawTextLabel(BSP_LCD_GetXSize()/2 + 170, BSP_LCD_GetYSize()/2 - 65, 60, 60, "Л");
            mcube.isReleased = false;
        }
				if(liters.isReleased == true){
						quantity = true;
						drawTextLabel(BSP_LCD_GetXSize()/2 + 100, BSP_LCD_GetYSize()/2 - 65, 60, 60, "М*3");
						drawLightTextLabel(BSP_LCD_GetXSize()/2 + 170, BSP_LCD_GetYSize()/2 - 65, 60, 60, "Л");
            liters.isReleased = false;
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
	filterCycleBut = drawLightTextLabel(BSP_LCD_GetXSize()/2 - 50, BSP_LCD_GetYSize()/2 - 65, 140, 60, intToStr(filterCycle));
	reserveBut = drawLightTextLabel(BSP_LCD_GetXSize()/2 - 50, BSP_LCD_GetYSize()/2 + 25, 100, 60, intToStr(reserve));
	if(quantity) {
		mcube = drawTextLabel(BSP_LCD_GetXSize()/2 + 100, BSP_LCD_GetYSize()/2 - 65, 60, 60, "М*3");
		liters = drawLightTextLabel(BSP_LCD_GetXSize()/2 + 170, BSP_LCD_GetYSize()/2 - 65, 60, 60, "Л");
	}
	else {
		mcube = drawLightTextLabel(BSP_LCD_GetXSize()/2 + 100, BSP_LCD_GetYSize()/2 - 65, 60, 60, "М*3");
		liters = drawTextLabel(BSP_LCD_GetXSize()/2 + 170, BSP_LCD_GetYSize()/2 - 65, 60, 60, "Л");
	}
	
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 + 100, BSP_LCD_GetYSize()/2 + 40, "%", LEFT_MODE);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 - 200, BSP_LCD_GetYSize()/2 - 50, "Фильтроцикл", LEFT_MODE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 - 200, BSP_LCD_GetYSize()/2 + 30, "Резерв", LEFT_MODE);

	TC_addButton(&filterCycleBut);
	TC_addButton(&reserveBut);
	TC_addButton(&mcube);
	TC_addButton(&liters);
	TC_addButton(&retBut);
	TC_addButton(&homeBut);
	TC_addButton(&okBut);	
}

