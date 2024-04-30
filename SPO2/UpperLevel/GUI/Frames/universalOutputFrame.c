#include "universalOutputFrame.h"
#define LINE_NUM 4
static int8_t markItem = 0;
static button_t menuLines[LINE_NUM], checkBox[LINE_NUM];
static void createFrame();
static void markLines();
static void calcButParam();
int ShowUniversalOutputFrame(void) {
	switch(sysParams.consts.dcRelay.workType) {
		case (HALT): {
			markItem = 1;
			break;
		}
		case (WASH): {
			markItem = 2;
			break;
		}
		case (PULSE): {
			markItem = 3;
			break;
		}
		case (NEIGHBOR): {
			markItem = 4;
			break;
		}
	}
	/*Static create*/
	createFrame();
	while(1) {
		if(updateFlags.sec == true) {
			updateFlags.sec = false;
		}
		/*Buttons pressed*/
		if(retBut.isPressed == true) {
			retBut.isPressed = false;
		}
		for(uint8_t i = 1; i < LINE_NUM - 1; i++) {
			if(menuLines[i].isPressed == true) {
				//Make it blue
				drawFillArcRec(menuLines[i].x - 9, menuLines[i].y - 9, menuLines[i].xSize, menuLines[i].ySize + 4, LCD_COLOR_BLUE);
				BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				BSP_LCD_DisplayStringAt(menuLines[i].x, menuLines[i].y, ITEM_UNIVERSAL_OUTPUT_FRAME[i], LEFT_MODE);
				menuLines[i].isPressed = false;
			}
		}
		/*Buttons released*/
		if(retBut.isReleased == true) {
			retBut.isReleased = false;
			return 0;
		}
		if(homeBut.isReleased == true) {
			homeBut.isReleased = false;
			goHome = true;
		}
		if(okBut.isReleased == true) {
			switch(markItem) {
				case (1): {
					sysParams.consts.dcRelay.workType = HALT;
					break;
				}
				case (2): {
					sysParams.consts.dcRelay.workType = WASH;
					break;
				}
				case (3): {
					sysParams.consts.dcRelay.workType = PULSE;
					break;
				}
				case (4): {
					sysParams.consts.dcRelay.workType = NEIGHBOR;
					break;
				}
			}
			FP_SaveParam();
			okBut.isReleased = false;
			return 0;
		}
		if(goHome) {
			return -1;
		}
		if(menuLines[1].isReleased == true) {
			ShowOutputEnableChoice(ITEM_UNIVERSAL_OUTPUT_FRAME[1],&sysParams.consts.dcRelay);
			menuLines[1].isReleased = false;
			createFrame();
		}
		if(menuLines[2].isReleased == true) {
			ShowImpulseWeightChoice();
			menuLines[2].isReleased = false;
			createFrame();
		}
		for(uint8_t i = 0; i < LINE_NUM; i++) {
			if(checkBox[i].isPressed) {
				drawFillButton(checkBox[i].x, checkBox[i].y, checkBox[i].xSize, checkBox[i].ySize, "", true);
				checkBox[i].isPressed = false;
			}
			if(checkBox[i].isReleased) {
				markItem = i + 1;
				markLines();
				checkBox[i].isReleased = false;
			}
		}
	}
}
void createFrame(void) {
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_UNIVERSAL_OUTPUT_FRAME[4]);
	drawMainWindow();
	drawStatusBarOkCancel();
	drawStaticLines();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	calcButParam();
	for(uint8_t i = 0; i < LINE_NUM; i++) {
		menuLines[i].xSize = 18 + BSP_LCD_DisplayStringAt(menuLines[i].x, menuLines[i].y, ITEM_UNIVERSAL_OUTPUT_FRAME[i], LEFT_MODE);
	}
	markLines();
	/*Add buttons parameters*/
}
void markLines() {
	bool checked;
	char * status;
	for(uint8_t i = 0; i < LINE_NUM; i++) {
		checked = (markItem - 1 == i) ? true : false;
		status = (markItem - 1 == i) ? "X" : "";
		checkBox[i] = drawFillButton(SCROLLKEYUP_POS_X - 5 - 40, STATIC_LINE_Y + STATIC_LINE_SPASER * i + 3, 40, 40, status, checked);
	}
}
void calcButParam() {
	TC_clearButtons();
	TC_clearButtons();
	for(uint8_t i = 0; i < LINE_NUM; i++) {
		menuLines[i].x = FIRST_CURSOR_POS_X + 9;
		menuLines[i].y = STATIC_LINE_Y + i * STATIC_LINE_SPASER + 9;
		//menuLines[i].xSize = 250;
		menuLines[i].ySize = 40;
		TC_addButton( & menuLines[i]);
	}
	for(uint8_t i = 0; i < sizeof(checkBox) / sizeof(checkBox[0]); i++) {
		TC_addButton( & checkBox[i]);
	}
	TC_addButton( & retBut);
	TC_addButton( & okBut);
	TC_addButton( & cancelBut);
	TC_addButton( & homeBut);
}
