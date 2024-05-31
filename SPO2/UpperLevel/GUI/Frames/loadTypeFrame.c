#include "loadTypeFrame.h"

#define MARK_GAP MARK_BOX + 20
#define MARK_BOX 330
static int8_t markItem = 0;
static void createFrame(void);
static button_t menuLine[4], checkBox[4];
static void markLines();
static void calcButParam();
int showLoadTypeFrame()
{
	markItem = sysParams.consts.planerConsts.startType;
	createFrame();
	while(1) {
		if(updateFlags.sec == true) {
			// drawClock(); drawMainStatusBar(144, 2305, 16);
			updateFlags.sec = false;
		}
		if(okBut.isReleased == true) {
			if(markItem >= 0) {
				sysParams.consts.planerConsts.startType = markItem;
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
		
		if(checkBox[0].isReleased == true) {
			markItem = 0;
			checkBox[0].isReleased = false;
			markLines();
		}
		if(checkBox[1].isReleased == true) {
			markItem = 1;
			checkBox[1].isReleased = false;
			markLines();
		}
		if(checkBox[2].isReleased == true) {
			markItem = 2;
			checkBox[2].isReleased = false;
			markLines();
		}
		if(checkBox[3].isReleased == true) {
			markItem = 3;
			checkBox[3].isReleased = false;
			markLines();
		}
		for(uint8_t i = 0; i < sizeof(menuLine) / sizeof(menuLine[0]); i++) {
			if(checkBox[i].isPressed) {
				drawFillButton(checkBox[i].x, checkBox[i].y, checkBox[i].xSize, checkBox[i].ySize, "", true);
				checkBox[i].isPressed = false;
			}
		}
	}
}
void createFrame(void) {
	if(goHome) return;
	TC_clearButtons();
	//Static refresh
	calcButParam();
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_FILTER_SELECTION);
	drawStatusBarOkCancel();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	calcButParam();
	for(uint8_t i = 0; i < sizeof(menuLine) / sizeof(menuLine[0]); i++) {
		menuLine[i].xSize = 18 + BSP_LCD_DisplayStringAt(menuLine[i].x, menuLine[i].y, ITEM_LOAD_TYPE[i], LEFT_MODE);
	}
	markLines();
	/*Add buttons parameters*/
	drawStaticLines();
}
void markLines() {
	bool checked;
	char * status;
	for(uint8_t i = 0; i < sizeof(menuLine) / sizeof(menuLine[0]); i++) {
		checked = (markItem == i) ? true : false;
		status = (markItem == i) ? "X" : "";
		checkBox[i] = drawFillButton(SCROLLKEYUP_POS_X - 5 - 40, STATIC_LINE_Y + STATIC_LINE_SPASER * i + 3, 40, 40, status, checked);
	}
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
	TC_addButton( & retBut);
	TC_addButton( & okBut);
	TC_addButton( & cancelBut);
	TC_addButton( & homeBut);
}