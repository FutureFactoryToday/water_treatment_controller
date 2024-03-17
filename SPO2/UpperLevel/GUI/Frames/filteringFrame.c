#include "filteringFrame.h"

uint8_t fitlering_frame_Scroll_cnt = 0;
uint8_t fitlering_frame_was_Scroll = 0;
int32_t qwertyFilBWASH = 0;
int32_t qwertyFilDFLUSH = 0;
int8_t hwndFilteringFrameControl = 0;
int8_t startFilteringFrame = 0;

int8_t step = 0;
static button_t menuLine[2];
static void createFrame();
static uint8_t res[2];
int ShowFilteringFrame(void)
{
    res[0] = planner.pistonTasks[REGENERATION_TASK_NUM].step[0].secPause/60;
    res[1] = planner.pistonTasks[REGENERATION_TASK_NUM].step[1].secPause/60;
    fitlering_frame_Scroll_cnt = 0;
    createFrame();

    while(1)
    {
        if (updateFlags.sec == true){
            //drawClock();
            updateFlags.sec = false;
        }

        /*Buttons released*/
        if (retBut.isReleased == true){
            retBut.isReleased = false;
            return 0;
        }
        if (okBut.isReleased == true){
            okBut.isReleased = false;
            planner.pistonTasks[REGENERATION_TASK_NUM].step[0].secPause = 60 * res[0];
            planner.pistonTasks[REGENERATION_TASK_NUM].step[1].secPause = 60 * res[1];
            copyTasksToFlash();
            fp->needToSave = 1;
            FP_SaveParam();
            return 0;
        }
        if (cancelBut.isReleased == true){
            cancelBut.isReleased = false;
            return 0;
        }
        if (homeBut.isReleased == true){
            homeBut.isReleased = false;
            return 1;
        }
        if(menuLine[0].isReleased == true){
            uint8_t tempRes = ShowKeyboardFrame(1,150);
            if (tempRes > 0){
                res[0] = tempRes;
                createFrame();
            }
            menuLine[0].isReleased = false;
        }
        if(menuLine[1].isReleased == true){
            uint8_t tempRes = ShowKeyboardFrame(1,150);
            if (tempRes > 0){
                res[1] = tempRes;
                createFrame();
            }
            menuLine[1].isReleased = false;
        }
        if(menuLine[0].isPressed == true){
            drawDarkTextLabel(4*GAP + 225,BSP_LCD_GetYSize()/2 - 70,80,40,intToStr(res[0]));
            menuLine[0].isPressed = false;
        }
        if(menuLine[1].isPressed == true){
            drawDarkTextLabel(4*GAP + 225,BSP_LCD_GetYSize()/2 - 10,80,40,intToStr(res[1]));
            menuLine[1].isPressed = false;
        }
    }
}

void createFrame(void)
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_FILTERING);
	
	drawStatusBarOkCancel();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    
	BSP_LCD_DisplayStringAt(2*GAP,BSP_LCD_GetYSize()/2 - 65,ITEM_FILTERING[0],LEFT_MODE);
	menuLine[0] = drawTextLabel(4*GAP + 225,BSP_LCD_GetYSize()/2 - 70,80,40,intToStr(res[0]));
	BSP_LCD_DisplayStringAt(400,BSP_LCD_GetYSize()/2 - 65,MINUTE,LEFT_MODE);
	
	BSP_LCD_DisplayStringAt(2*GAP,BSP_LCD_GetYSize()/2 - 5,ITEM_FILTERING[1],LEFT_MODE);
    menuLine[1] = drawTextLabel(4*GAP + 225,BSP_LCD_GetYSize()/2 - 10,80,40,intToStr(res[1]));
	BSP_LCD_DisplayStringAt(400,BSP_LCD_GetYSize()/2 - 5,MINUTE,LEFT_MODE);
	
	/*Add buttons parameters*/
	
	/*Add buttons to Touch Controller*/
	for (uint8_t i = 0; i < sizeof(menuLine)/sizeof(menuLine[0]); i++){
			TC_addButton(&menuLine[i]);
	}
	TC_addButton(&retBut);
    TC_addButton(&homeBut);
	TC_addButton(&okBut);
    TC_addButton(&cancelBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);
	
	//enableClockDraw = true; 
}

