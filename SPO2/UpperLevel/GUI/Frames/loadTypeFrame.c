#include "loadTypeFrame.h"


static void createFrame(void);
static button_t loadBut[4];
void  showLoadTypeFrame()
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
				
				return;
			}
			for(uint8_t i = 0; i < 4; i ++){
				if (loadBut[i].isPressed){
					drawDarkTextLabel(FIRST_CURSOR_POS_X, STATIC_LINE_Y + STATIC_LINE_SPASER*i+3, 300, 40, ITEM_LOAD_TYPE[i]);
					loadBut[i].isPressed = false;
				}
				if (loadBut[i].isReleased){
					fp->params.planner.loadType = planner.loadType = i;
					fp->needToSave = 1;
					FP_SaveParam();
					return;
				}
			}
		}  
}

void createFrame(void)
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_LOAD_TYPE[4]);
	drawStaticLines();
	drawStatusBarEmpty();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	for(uint8_t i = 0; i < 4; i ++){
		BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + GAP, STATIC_LINE_Y + STATIC_LINE_SPASER*i +9,ITEM_LOAD_TYPE[i], LEFT_MODE);
		loadBut[i].x = FIRST_CURSOR_POS_X;
		loadBut[i].y = STATIC_LINE_Y + STATIC_LINE_SPASER*i;
		loadBut[i].xSize = 300;
		loadBut[i].ySize = 40;
		TC_addButton(&loadBut[i]);
	}

//	TC_addButton(&okBut);
//	TC_addButton(&cancelBut);
	TC_addButton(&retBut);	
	drawClock();
}