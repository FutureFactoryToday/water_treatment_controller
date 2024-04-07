#include "elMagFrame.h"

static void createFrame(void);
static button_t elMagBut[3];
int showElMagFrame()
{
   createFrame();
    while(1)
    {
        if (updateFlags.sec == true){
            drawClock();
            updateFlags.sec = false;
        }
        if(retBut.isReleased == true) {
            retBut.isReleased = false;
            return 0;
        }
        if(homeBut.isReleased == true) {
            homeBut.isReleased = false;
            return 1;
        }
        for(uint8_t i = 0; i < 4; i ++){
            if (elMagBut[i].isPressed){
                drawFillArcRec(FIRST_CURSOR_POS_X, STATIC_LINE_Y + STATIC_LINE_SPASER*i+3, 300, 40, LCD_COLOR_BLUE);
                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + GAP, STATIC_LINE_Y + STATIC_LINE_SPASER*i + 9, ITEM_EL_MAG_FRAME[i], LEFT_MODE);
                elMagBut[i].isPressed = false;
            }
            if (elMagBut[i].isReleased){
//                fp->params.planner.loadType = planner.loadType = i;
//                fp->needToSave = 1;
//                FP_SaveParam();
                return 0;
            }
        }
    }  
}

void createFrame(void)
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_EL_MAG_FRAME[2]);
	drawStaticLines();
    drawMainStatusBar(144, 2305, 16);
	//drawStatusBarEmpty();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	for(uint8_t i = 0; i < 2; i ++){
		BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + GAP, STATIC_LINE_Y + STATIC_LINE_SPASER*i + 9,ITEM_EL_MAG_FRAME[i], LEFT_MODE);
		elMagBut[i].x = FIRST_CURSOR_POS_X;
		elMagBut[i].y = STATIC_LINE_Y + STATIC_LINE_SPASER*i;
		elMagBut[i].xSize = 300;
		elMagBut[i].ySize = 40;
		TC_addButton(&elMagBut[i]);
	}

//	TC_addButton(&okBut);
//	TC_addButton(&cancelBut);
	TC_addButton(&retBut);	
    TC_addButton(&homeBut);
	drawClock();
}
