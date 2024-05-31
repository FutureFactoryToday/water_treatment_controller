#include "filterSelectionFrame.h"

#define MARK_GAP MARK_BOX + 20
#define MARK_BOX 330
static int8_t markItem = 0;
static void createFrame(void);
static button_t menuLine[3], checkBox[3];
static void markLines();
static void calcButParam();
int ShowFilterSelectionFrame(void) {
	if(sysParams.vars.planer.currentTask == & sysParams.consts.planerConsts.planerTasks[0]) {
		markItem = 1;
	}
	if(sysParams.vars.planer.currentTask == & sysParams.consts.planerConsts.planerTasks[1]) {
		markItem = 2;
	}
	if(sysParams.vars.planer.currentTask == & sysParams.consts.planerConsts.planerTasks[2]) {
		markItem = 3;
	}
	createFrame();
	while(1) {
		if(updateFlags.sec == true) {
			// drawClock(); drawMainStatusBar(144, 2305, 16);
			updateFlags.sec = false;
		}
		if(okBut.isReleased == true) {
			if(markItem > 0) {
				if(markItem - 1 != sysParams.consts.planerConsts.currentTaskNum) {
					sysParams.consts.planerConsts.status = PL_NOT_SET;
				}
				sysParams.vars.planer.currentTask = & sysParams.consts.planerConsts.planerTasks[markItem - 1];
				sysParams.consts.planerConsts.currentTaskNum = markItem - 1;
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
		if(menuLine[0].isReleased == true) {
			ShowManualFilterSettings(&sysParams.consts.planerConsts.planerTasks[REGENERATION_TASK_NUM], ITEM_FILTER_SELECTION[0], false);
			createFrame();
			menuLine[0].isReleased = false;
		}
		if(menuLine[1].isReleased == true) {
			ShowManualFilterSettings(&sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM], ITEM_FILTER_SELECTION[1], false);
			createFrame();
			menuLine[1].isReleased = false;
		}
		if(menuLine[2].isReleased == true) {
			ShowManualFilterSettings(&sysParams.consts.planerConsts.planerTasks[MAN_TASK_NUM], ITEM_FILTER_SELECTION[2], true);
			createFrame();
			menuLine[2].isReleased = false;
		}
		if(checkBox[0].isReleased == true) {
			markItem = 1;
			checkBox[0].isReleased = false;
			markLines();
		}
		if(checkBox[1].isReleased == true) {
			markItem = 2;
			checkBox[1].isReleased = false;
			markLines();
		}
		if(checkBox[2].isReleased == true) {
			markItem = 3;
			checkBox[2].isReleased = false;
			markLines();
		}
		for(uint8_t i = 0; i < sizeof(menuLine) / sizeof(menuLine[0]); i++) {
			if(menuLine[i].isPressed) {
				drawFillArcRec(menuLine[i].x - 9, menuLine[i].y - 9, menuLine[i].xSize, menuLine[i].ySize + 4, LCD_COLOR_BLUE);
				BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				BSP_LCD_DisplayStringAt(menuLine[i].x, menuLine[i].y, ITEM_FILTER_SELECTION[i], LEFT_MODE);
				//drawDarkTextLabel(3*GAP + 40 + GAP, BSP_LCD_GetYSize()/2 - 80 + i*50, 250, 40, ITEM_FILTER_SELECTION[i]);
				menuLine[i].isPressed = false;
			}
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
		menuLine[i].xSize = 18 + BSP_LCD_DisplayStringAt(menuLine[i].x, menuLine[i].y, ITEM_FILTER_SELECTION[i], LEFT_MODE);
	}
	markLines();
	/*Add buttons parameters*/
	drawStaticLines();
}
void markLines() {
	bool checked;
	char * status;
	for(uint8_t i = 0; i < sizeof(menuLine) / sizeof(menuLine[0]); i++) {
		checked = (markItem - 1 == i) ? true : false;
		status = (markItem - 1 == i) ? "X" : "";
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