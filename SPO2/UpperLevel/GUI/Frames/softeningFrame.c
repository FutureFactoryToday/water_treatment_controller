#include "softeningFrame.h"
#define MIN_KEYBOARD_RESULT 0
#define MAX_KEYBOARD_RESULT 999

uint8_t softening_frame_Scroll_cnt = 0;
uint8_t softening_frame_was_Scroll = 0;
int32_t qwertySoft[] = {0, 0, 0, 0, 0};
static void createFrame(void);
static void calcButParam();
static button_t menuLines[4];
static uint16_t res[4];
int ShowSofteningFrame(void)
{
    res[0] = sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[0].secPause/60;
    res[1] = sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[1].secPause/60;
    res[2] = sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[2].secPause/60;
    res[3] = sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[3].secPause/60;
    //res[4] = sysParams.consts.planerConsts.pistonTasks[SOFTENING_TASK_NUM].step[4].secPause/60;
    softening_frame_Scroll_cnt = 0;
    createFrame();
    while(1)
    {   
			if (updateFlags.sec == true){
					// drawClock(); drawMainStatusBar(144, 2305, 16);
					updateFlags.sec = false;
			}
		 if(okBut.isReleased == true){
			okBut.isReleased = false;
			sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[0].secPause = 60 * res[0];    
			sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[1].secPause = 60 * res[1];   
			sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[2].secPause = 60 * res[2];   
			sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[3].secPause = 60 * res[3];
			//sysParams.consts.planerConsts.pistonTasks[SOFTENING_TASK_NUM].step[4].secPause = 60 * res[4];

			FP_SaveParam();
			return 0;
		}
        if(cancelBut.isReleased == true){
            cancelBut.isReleased = false;
            return 0;
        }
		if(retBut.isReleased == true){
			retBut.isReleased = false;
			return 0;
		}		
		if (homeBut.isReleased == true){
			homeBut.isReleased = false;
      goHome = true;
		}
		if (goHome){
			return -1;
		}      
        if(menuLines[0].isReleased == true)
		{
            uint8_t tempRes = ShowKeyboardFrame(MIN_KEYBOARD_RESULT,MAX_KEYBOARD_RESULT);
            if (tempRes >= 0){
                res[0] = tempRes;
                createFrame();
            }
            menuLines[0].isReleased = false;
		}
		if(menuLines[1].isReleased == true)
		{
			uint8_t tempRes = ShowKeyboardFrame(MIN_KEYBOARD_RESULT,MAX_KEYBOARD_RESULT);
            if (tempRes >= 0){
                res[1] = tempRes;
                createFrame();
            }
			menuLines[1].isReleased = false;
		}   
        if(menuLines[2].isReleased == true)
		{
			uint8_t tempRes = ShowKeyboardFrame(MIN_KEYBOARD_RESULT,MAX_KEYBOARD_RESULT);
            if (tempRes >= 0){
                res[2] = tempRes;
                createFrame();
            }
			menuLines[2].isReleased = false;
		}
		if(menuLines[3].isReleased == true)
		{
			uint8_t tempRes = ShowKeyboardFrame(MIN_KEYBOARD_RESULT,MAX_KEYBOARD_RESULT);
            if (tempRes >= 0){
                res[3] = tempRes;
                createFrame();
            }
			menuLines[3].isReleased = false;
		}   
        
		if(menuLines[softening_frame_Scroll_cnt].isPressed == true){
				drawDarkTextLabel(4*GAP + 225,FIRST_CURSOR_POS_Y + 3,80,39,intToStr(res[softening_frame_Scroll_cnt]));
				menuLines[softening_frame_Scroll_cnt].isPressed = false;
		}
if(menuLines[softening_frame_Scroll_cnt + 1].isPressed == true){
				drawDarkTextLabel(4*GAP + 225,SECOND_CURSOR_POS_Y + 3,80,39,intToStr(res[softening_frame_Scroll_cnt + 1]));
				menuLines[softening_frame_Scroll_cnt + 1].isPressed = false;
		}
		if(menuLines[softening_frame_Scroll_cnt + 2].isPressed == true){
				drawDarkTextLabel(4*GAP + 225,THRID_CURSOR_POS_Y + 3,80,39,intToStr(res[softening_frame_Scroll_cnt + 2]));
				menuLines[softening_frame_Scroll_cnt + 2].isPressed = false;
		}
		if(menuLines[softening_frame_Scroll_cnt + 3].isPressed == true){
				drawDarkTextLabel(4*GAP + 225,FOURTH_CURSOR_POS_Y + 3,80,39,intToStr(res[softening_frame_Scroll_cnt + 3]));
				menuLines[softening_frame_Scroll_cnt + 3].isPressed = false;
		}
	}
}

void createFrame(void)
{
	//Static refresh
    TC_clearButtons();
    
    drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_CUSTOMER);
    
    drawMainWindow();
    
    //drawScrollButton(softening_frame_Scroll_cnt == 0 ? 0 : (softening_frame_Scroll_cnt == 1 ? 2 : 1));
    
    drawStatusBarOkCancel();
    
    // drawClock(); drawMainStatusBar(144, 2305, 16);
    
    drawStaticLines();
    
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FIRST_CURSOR_POS_Y + 9,ITEM_SOFTENING[softening_frame_Scroll_cnt],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,SECOND_CURSOR_POS_Y + 9,ITEM_SOFTENING[softening_frame_Scroll_cnt + 1],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,THRID_CURSOR_POS_Y + 9,ITEM_SOFTENING[softening_frame_Scroll_cnt + 2],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FOURTH_CURSOR_POS_Y + 9,ITEM_SOFTENING[softening_frame_Scroll_cnt + 3],LEFT_MODE);
    
    drawTextLabel(4*GAP + 225,FIRST_CURSOR_POS_Y + 3, 80, 39,intToStr((res[softening_frame_Scroll_cnt])));
    drawTextLabel(4*GAP + 225,SECOND_CURSOR_POS_Y + 3, 80, 39,intToStr((res[softening_frame_Scroll_cnt + 1])));
    drawTextLabel(4*GAP + 225,THRID_CURSOR_POS_Y + 3, 80, 39,intToStr((res[softening_frame_Scroll_cnt + 2])));
    drawTextLabel(4*GAP + 225,FOURTH_CURSOR_POS_Y + 3, 80, 39,intToStr((res[softening_frame_Scroll_cnt + 3])));
    
    BSP_LCD_DisplayStringAt(400,FIRST_CURSOR_POS_Y + 9, MINUTE,LEFT_MODE);
    BSP_LCD_DisplayStringAt(400,SECOND_CURSOR_POS_Y + 9, MINUTE,LEFT_MODE);
    BSP_LCD_DisplayStringAt(400,THRID_CURSOR_POS_Y + 9, MINUTE,LEFT_MODE);
    BSP_LCD_DisplayStringAt(400,FOURTH_CURSOR_POS_Y + 9, MINUTE,LEFT_MODE);
			
	/*Add buttons parameters*/
	calcButParam();
}


//void RefreshScrollBarSofteningFrame()
//{
//    calcButParam();
//    
//    if(softening_frame_was_Scroll == 1 || softening_frame_was_Scroll == 2){
//        drawScrollButton(softening_frame_Scroll_cnt == 0 ? 0 : (softening_frame_Scroll_cnt == 1 ? 2 : 1));
//        
//        drawFillArcRec(menuLines[softening_frame_Scroll_cnt].x, menuLines[softening_frame_Scroll_cnt].y, menuLines[softening_frame_Scroll_cnt].xSize, menuLines[softening_frame_Scroll_cnt].ySize, LCD_COLOR_WHITE);
//        drawFillArcRec(menuLines[softening_frame_Scroll_cnt + 1].x, menuLines[softening_frame_Scroll_cnt + 1].y, menuLines[softening_frame_Scroll_cnt + 1].xSize, menuLines[softening_frame_Scroll_cnt + 1].ySize, LCD_COLOR_WHITE);
//        drawFillArcRec(menuLines[softening_frame_Scroll_cnt + 2].x, menuLines[softening_frame_Scroll_cnt + 2].y, menuLines[softening_frame_Scroll_cnt + 2].xSize, menuLines[softening_frame_Scroll_cnt + 2].ySize, LCD_COLOR_WHITE);
//        drawFillArcRec(menuLines[softening_frame_Scroll_cnt + 3].x, menuLines[softening_frame_Scroll_cnt + 3].y, menuLines[softening_frame_Scroll_cnt + 3].xSize, menuLines[softening_frame_Scroll_cnt + 3].ySize, LCD_COLOR_WHITE);
//        
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(FIRST_CURSOR_POS_X, FIRST_CURSOR_POS_Y, 300, 200);
//        
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FIRST_CURSOR_POS_Y + 3,ITEM_STEPS[softening_frame_Scroll_cnt],LEFT_MODE);
//        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,SECOND_CURSOR_POS_Y + 3,ITEM_STEPS[softening_frame_Scroll_cnt + 1],LEFT_MODE);
//        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,THRID_CURSOR_POS_Y + 3,ITEM_STEPS[softening_frame_Scroll_cnt + 2],LEFT_MODE);
//        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FOURTH_CURSOR_POS_Y + 3,ITEM_STEPS[softening_frame_Scroll_cnt + 3],LEFT_MODE);
//        
//        drawTextLabel(4*GAP + 125,FIRST_CURSOR_POS_Y + 3, 80, 39,intToStr((res[softening_frame_Scroll_cnt])));
//        drawTextLabel(4*GAP + 125,SECOND_CURSOR_POS_Y + 3, 80, 39,intToStr((res[softening_frame_Scroll_cnt + 1])));
//        drawTextLabel(4*GAP + 125,THRID_CURSOR_POS_Y + 3, 80, 39,intToStr((res[softening_frame_Scroll_cnt + 2])));
//        drawTextLabel(4*GAP + 125,FOURTH_CURSOR_POS_Y + 3, 80, 39,intToStr((res[softening_frame_Scroll_cnt + 3])));
//        
//        BSP_LCD_DisplayStringAt(300,FIRST_CURSOR_POS_Y + 9,MINUTE,LEFT_MODE);
//        BSP_LCD_DisplayStringAt(300,SECOND_CURSOR_POS_Y + 9,MINUTE,LEFT_MODE);
//        BSP_LCD_DisplayStringAt(300,THRID_CURSOR_POS_Y + 9,MINUTE,LEFT_MODE);
//        BSP_LCD_DisplayStringAt(300,FOURTH_CURSOR_POS_Y + 9,MINUTE,LEFT_MODE);
//        
//        drawStaticLines();
//        
//        softening_frame_was_Scroll = 0;
//    }
//}


void calcButParam()
{
    TC_clearButtons();
    
        //Setting for key "0"
    menuLines[softening_frame_Scroll_cnt].x = 4*GAP + 225;
    menuLines[softening_frame_Scroll_cnt].y = FIRST_CURSOR_POS_Y + 3;
    menuLines[softening_frame_Scroll_cnt].xSize = 80;
    menuLines[softening_frame_Scroll_cnt].ySize = 39;
		
		//Setting for key "1"
    menuLines[softening_frame_Scroll_cnt + 1].x = 4*GAP + 225;
    menuLines[softening_frame_Scroll_cnt + 1].y = SECOND_CURSOR_POS_Y + 3;
    menuLines[softening_frame_Scroll_cnt + 1].xSize = 80;
    menuLines[softening_frame_Scroll_cnt + 1].ySize = 39;
    
		//Setting for key "2"
    menuLines[softening_frame_Scroll_cnt + 2].x = 4*GAP + 225;
    menuLines[softening_frame_Scroll_cnt + 2].y = THRID_CURSOR_POS_Y + 3;
    menuLines[softening_frame_Scroll_cnt + 2].xSize = 80;
    menuLines[softening_frame_Scroll_cnt + 2].ySize = 39;
    
		//Setting for key "3"
    menuLines[softening_frame_Scroll_cnt + 3].x = 4*GAP + 225;
    menuLines[softening_frame_Scroll_cnt + 3].y = FOURTH_CURSOR_POS_Y + 3;
    menuLines[softening_frame_Scroll_cnt + 3].xSize = 80;
    menuLines[softening_frame_Scroll_cnt + 3].ySize = 39;
    
    
    
    for (uint8_t i = softening_frame_Scroll_cnt; i < softening_frame_Scroll_cnt + 3; i++){
			TC_addButton(&menuLines[i]);
	}
	TC_addButton(&retBut);
    TC_addButton(&homeBut);
	TC_addButton(&okBut);   
    TC_addButton(&cancelBut);    
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);
}