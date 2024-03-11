#include "filterSelectionFrame.h"

uint8_t filter_selection_frame_Scroll_cnt = 0;
uint8_t filter_selection_frame_was_Scroll = 0;

#define MARK_GAP MARK_BOX + 20
#define MARK_BOX 330
int8_t markItem = 0;
static void createFrame(void);
static button_t menuLine[3], checkBox[3];
static void markLines();
static void calcButParam();

void RefreshFilterSelectionFrame(void);

void RefreshScrollBarFilterSelectionFrame(void);



int ShowFilterSelectionFrame(void)
{
    filter_selection_frame_Scroll_cnt = 0;

		if(planner.currentTask == &planner.pistonTasks[0]){
			markItem = 1;
		} 
		if(planner.currentTask == &planner.pistonTasks[1]){
			markItem = 2;
		}
		if(planner.currentTask == &planner.pistonTasks[2]){
			markItem = 3;
		}
		
		createFrame();
    while(1)
    {
        if (updateFlags.sec == true){
            //drawClock();
            updateFlags.sec = false;
        }
        if(okBut.isReleased == true){
            if (markItem > 0){
                fp->params.planner.currentTask = planner.currentTask = &planner.pistonTasks[markItem - 1];
                
                fp->needToSave = 1;
                FP_SaveParam();
            }
                okBut.isReleased = false;
                return 0;
		}
        if(retBut.isReleased == true){
            retBut.isReleased = false;
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
        if(menuLine[0].isReleased == true)
        {
            if(ShowFilteringFrame() == 1) return 1;
            createFrame();
            menuLine[0].isReleased = false;
        }
		if(menuLine[1].isReleased == true)
        {
            if(ShowSofteningFrame() == 1) return 1;
            createFrame();
            menuLine[1].isReleased = false;
        }
		if(menuLine[2].isReleased == true)
        {
            if(ShowManualFilterSettings() == 1) return 1;
            createFrame();
            menuLine[2].isReleased = false;
        }
        if (checkBox[0].isReleased == true){
            markItem = 1;
            checkBox[0].isReleased = false;
            markLines();
		}
		if (checkBox[1].isReleased == true){
            markItem = 2;
            checkBox[1].isReleased = false;
            markLines();
		}		
		if (checkBox[2].isReleased == true){
            markItem = 3;
            checkBox[2].isReleased = false;
            markLines();
		}		
        for (uint8_t i = 0; i < sizeof(menuLine)/sizeof(menuLine[0]); i++){
            if (menuLine[i].isPressed){
                drawDarkTextLabel(3*GAP + 40 + GAP, BSP_LCD_GetYSize()/2 - 80 + i*50, 250, 40, ITEM_FILTER_SELECTION[i]);
                menuLine[i].isPressed = false;
            } 
            if (checkBox[i].isPressed){
                drawFillButton(3*GAP, BSP_LCD_GetYSize()/2 - 80 + i*50, 40, 40,"", true);
                checkBox[i].isPressed = false;
            }
        }
    }
}

void createFrame(void)
{
	TC_clearButtons();
  //Static refresh
	
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_FILTER_SELECTION);
	
	drawStatusBarOkCancel();
	
	for (uint8_t i = 0; i < sizeof(menuLine)/sizeof(menuLine[0]); i++){
		menuLine[i] = drawTextLabel(3*GAP + 40 + GAP, BSP_LCD_GetYSize()/2 - 80 + i*50, 250, 40, ITEM_FILTER_SELECTION[i]);
	}
	markLines();	
	/*Add buttons parameters*/
    calcButParam();
}

void markLines(){
	bool checked;
    char* status;
	for (uint8_t i = 0; i < sizeof(menuLine)/sizeof(menuLine[0]); i++){
		checked = (markItem - 1 == i)? true: false;
        status = (markItem - 1 == i)? "C": "";
		checkBox[i] = drawFillButton(3*GAP, BSP_LCD_GetYSize()/2 - 80 + i*50, 40, 40,status, checked);
	}
}

void calcButParam()
{
    TC_clearButtons();
    for (uint8_t i = 0; i < sizeof(menuLine)/sizeof(menuLine[0]); i++){
			TC_addButton(&menuLine[i]);
	}
	for (uint8_t i = 0; i < sizeof(checkBox)/sizeof(checkBox[0]); i++){
			TC_addButton(&checkBox[i]);
	}
	TC_addButton(&retBut);
	TC_addButton(&okBut);
    TC_addButton(&cancelBut);
    TC_addButton(&homeBut);
    
}