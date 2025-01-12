#include "loadTypeFrame.h"

#define MARK_GAP MARK_BOX + 20
#define MARK_BOX 330
static uint8_t firstEl;
static int8_t markItem = 0;
static void createFrame(void);
static button_t menuLine[5], checkBox[5];
static void markLines();
static void calcButParam();
static void RefreshScrollBar(void);
int showLoadTypeFrame()
{
	markItem = sysParams.consts.planerConsts.startType;
	createFrame();
	while(1) {
		if(updateFlags.sec == true) {
			updateFlags.sec = false; 
			sysParams.vars.frameWDTTim = SOFT_WDT_TIM_VAL_DEF; 
		}
		if(okBut.isReleased == true) {
			if(markItem >= 0) {
				sysParams.consts.planerConsts.startType = markItem;
				//sysParams.consts.planerConsts.status = PL_WAIT_MANUAL;
				switch (sysParams.consts.planerConsts.startType) {
					case BY_DAY: {
						sysParams.vars.planer.currentTask -> restartDateTime = DEF_BY_DAY_RESTART;
						break;
					}
					case BY_HOUR: {
						sysParams.vars.planer.currentTask -> restartDateTime = DEF_BY_HOUR_RESTART;
						break;
					}
					case UNIVERSAL: {
						sysParams.vars.planer.currentTask -> restartDateTime = DEF_UNIVERSAL_TIME_RESTART;
						sysParams.consts.planerConsts.filtroCycle = DEF_UNIVERSAL_WATER_RESTART;
						break;
					}
					case IMMEDIATELY: {
						sysParams.consts.planerConsts.filtroCycle = DEF_IMMEDIATELY_WATER_RESTART;
						break;
					}
				}
				sysParams.consts.planerConsts.status = PL_NOT_SET;
				FP_SaveParam();
			}
			okBut.isReleased = false;
			return 0;
		}
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
			goHome = true;
		}
		if(goHome) {
			return -1;
		}
		
		for(uint8_t i = 0; i < 4; i++){
			if(checkBox[i].isReleased == true) {
				markItem = i + firstEl;
				checkBox[i].isReleased = false;
				markLines();
			}
		}
		
		for(uint8_t i = 0; i < 4; i++) {
			if(checkBox[i].isPressed) {
				drawFillButton(checkBox[i].x, checkBox[i].y, checkBox[i].xSize, checkBox[i].ySize, "", true);
				checkBox[i].isPressed = false;
			}
		}
		if(scrollUpBut.isReleased == true) {
			if(firstEl > 0) {
				firstEl--;
				RefreshScrollBar();
			}
			scrollUpBut.isReleased = false;
		}
		if(scrollDwnBut.isReleased == true) {
			if(firstEl < (sizeof(menuLine)/sizeof(menuLine[0]))) {
				firstEl++;
				RefreshScrollBar();
			}
			scrollDwnBut.isReleased = false;
		}
	}
}
void createFrame(void) {
	if(goHome) return;
	TC_clearButtons();
	//Static refresh
	calcButParam();
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_LOAD_TYPE[0]);
	drawStatusBarOkCancel();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	drawScrollButton(0);
	calcButParam();
	for(uint8_t i = 0; i < 4; i++) {
		menuLine[i].xSize = 18 + BSP_LCD_DisplayStringAt(menuLine[i].x, menuLine[i].y, ITEM_LOAD_TYPE[i+1], LEFT_MODE);
	}
	markLines();
	/*Add buttons parameters*/
	drawStaticLines();
}
void markLines() {
	bool checked;
	char * status;
	for(uint8_t i = 0; i < 4; i++) {
		checked = (markItem == i + firstEl) ? true : false;
		status = (markItem == i + firstEl) ? "X" : "";
		checkBox[i] = drawFillButton(SCROLLKEYUP_POS_X - 5 - 40, STATIC_LINE_Y + STATIC_LINE_SPASER * i + 3, 40, 40, status, checked);
	}
}
void RefreshScrollBar(void) {
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	drawMainWindow();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	WTC_FONT_t *oldFont = BSP_LCD_GetFont();
	BSP_LCD_SetFont( &Oxygen_Mono_20);
	for(uint8_t i = 0; i < 4; i++) {
		int8_t pozNum = i + firstEl;
		
		menuLine[i].xSize = 18 + BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9, STATIC_LINE_Y + STATIC_LINE_SPASER * i + 3, ITEM_LOAD_TYPE[pozNum], LEFT_MODE);
		//menuLines[i].xSize = 18 + BSP_LCD_DisplayStringAt(menuLines[i].x, menuLines[i].y, ITEM_STEPS[i + firstEl], LEFT_MODE);
		markLines(i);
	}
	drawScrollButton(0);
	BSP_LCD_SetFont(oldFont);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	
	drawStaticLines();
	
}
void calcButParam() {
	TC_clearButtons();
	for(uint8_t i = 0; i < sizeof(menuLine) / sizeof(menuLine[0]); i++) {
		menuLine[i].x = FIRST_CURSOR_POS_X + 9;
		menuLine[i].y = STATIC_LINE_Y + i * STATIC_LINE_SPASER + 9;
		//menuLine[i].xSize = 250;
		menuLine[i].ySize = 40;
		TC_addButton( & menuLine[i]);
	}
	for(uint8_t i = 0; i < sizeof(checkBox) / sizeof(checkBox[0]); i++) {
		TC_addButton( & checkBox[i]);
	}
	  TC_addButton(&scrollUpBut);
  TC_addButton(&scrollDwnBut);
	TC_addButton( &retBut);
	TC_addButton( &okBut);
	TC_addButton( &cancelBut);
	TC_addButton( &homeBut);
}