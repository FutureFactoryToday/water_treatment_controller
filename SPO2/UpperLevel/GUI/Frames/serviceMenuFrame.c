#include "serviceMenuFrame.h"

uint8_t service_menu_frame_Scroll_cnt = 0;
uint8_t service_menu_frame_was_Scroll = 0;

int8_t hwndServiceMenuFrameControl = 0;
int8_t startServiceMenuFrame = 0;

static button_t menuLines[7];
static void createFrame();
static void calcButParam();

void RefreshServiceMenuFrame(void);

void RefreshScrollBarServiceMenuFrame(void);

void AnimateScrollBarKeysServiceMenuFrame(void);

void ShowServiceMenuFrame(void)
{
    service_menu_frame_Scroll_cnt = 0;

		/*Static create*/
		createFrame();
    while(1)
    {
        if (updateFlags.sec == true){
            drawClock();
            updateFlags.sec = false;
        }
			/*Buttons pressed*/
         if(retBut.isPressed == true){
             
            retBut.isPressed = false;
            return;
         }
         if(menuLines[0].isPressed == true){
                //Make it blue
            drawFillArcRec(menuLines[0].x, menuLines[0].y, menuLines[0].xSize, menuLines[0].ySize, LCD_COLOR_BLUE);
            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[0].y + 9,ITEM_SERVICE_MENU[0],LEFT_MODE);
            menuLines[0].isPressed = false;
         }
         if(menuLines[1].isPressed == true){
                //Make it blue
            drawFillArcRec(menuLines[1].x, menuLines[1].y, menuLines[1].xSize, menuLines[1].ySize, LCD_COLOR_BLUE);
            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[1].y + 9,ITEM_SERVICE_MENU[1],LEFT_MODE);
            menuLines[1].isPressed = false;
         }
         if(menuLines[2].isPressed == true){
                //Make it blue
            drawFillArcRec(menuLines[3].x, menuLines[2].y, menuLines[2].xSize, menuLines[2].ySize, LCD_COLOR_BLUE);
            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[2].y + 9,ITEM_SERVICE_MENU[2],LEFT_MODE);
            menuLines[2].isPressed = false;
         }
         if(menuLines[3].isPressed == true){
                //Make it blue
            drawFillArcRec(menuLines[3].x, menuLines[3].y, menuLines[3].xSize, menuLines[3].ySize, LCD_COLOR_BLUE);
            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[3].y + 9,ITEM_SERVICE_MENU[3],LEFT_MODE);
            menuLines[3].isPressed = false;
         }
         if(menuLines[4].isPressed == true){
                //Make it blue
            drawFillArcRec(menuLines[4].x, menuLines[4].y, menuLines[4].xSize, menuLines[4].ySize, LCD_COLOR_BLUE);
            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[4].y + 9,ITEM_SERVICE_MENU[4],LEFT_MODE);
            menuLines[4].isPressed = false;
         }
         if(menuLines[5].isPressed == true){
                //Make it blue
            drawFillArcRec(menuLines[5].x, menuLines[5].y, menuLines[5].xSize, menuLines[5].ySize, LCD_COLOR_BLUE);
            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[5].y + 9,ITEM_SERVICE_MENU[5],LEFT_MODE);
            menuLines[5].isPressed = false;
         }
         if(menuLines[6].isPressed == true){
                //Make it blue
            drawFillArcRec(menuLines[6].x, menuLines[6].y, menuLines[6].xSize, menuLines[6].ySize, LCD_COLOR_BLUE);
            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[6].y + 9,ITEM_SERVICE_MENU[6],LEFT_MODE);
            menuLines[6].isPressed = false;
         }
         if(scrollUpBut.isPressed == true){
                //Make it blue
            scrollUpBut.isPressed = false;
         }
         if(scrollDwnBut.isPressed == true){
                //Make it blue
            scrollDwnBut.isPressed = false;
         }
        /*Buttons released*/
         if(retBut.isReleased == true){
            retBut.isReleased = false;
            return;
         }
         if(menuLines[0].isReleased == true){
            ShowFilterSelectionFrame();
            menuLines[0].isReleased = false;
            createFrame();
         }
         if(menuLines[1].isReleased == true){
            showLoadTypeFrame(); 
            menuLines[1].isReleased = false;
            createFrame();
         }
         if(menuLines[2].isReleased == true){
            ShowWashingTimeServiceFrame();
            menuLines[2].isReleased = false;
            createFrame();
         }
         if(menuLines[3].isReleased == true){
            ShowRegenPeriodServiceFrame(); 
            menuLines[3].isReleased = false;
            createFrame();
         }
         if(menuLines[4].isReleased == true){
            ShowWaterCountBeforeRegenFrame();
            menuLines[4].isReleased = false;
            createFrame();
         }
         if(menuLines[5].isReleased == true){
            showServiceInfoFrame();                         
            menuLines[5].isReleased = false;
            createFrame();
         }
         if(menuLines[6].isReleased == true){
            ShowAlarmNotiServiceFrame();   
            menuLines[6].isReleased = false;
            createFrame();
         }
         if(scrollUpBut.isReleased == true){
            if(service_menu_frame_Scroll_cnt > 0){ service_menu_frame_Scroll_cnt--;
                service_menu_frame_was_Scroll = 1;
                RefreshScrollBarServiceMenuFrame();
            }
            scrollUpBut.isReleased = false;
         }
         if(scrollDwnBut.isReleased == true){
            if(service_menu_frame_Scroll_cnt < 3){ service_menu_frame_Scroll_cnt++;
                service_menu_frame_was_Scroll = 2;
                RefreshScrollBarServiceMenuFrame();
            }
            scrollDwnBut.isReleased = false;
         }   
    }
}

void createFrame(void){
	//TC_clearButtons();
    
    drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_SERVICE);
    
    drawMainWindow();
    
    drawScrollButton(service_menu_frame_Scroll_cnt == 0 ? 0 : (service_menu_frame_Scroll_cnt == 3 ? 2 : 1));
    
    drawStatusBarEmpty();
    
    drawClock();
    
    drawStaticLines();	
	
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FIRST_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,SECOND_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 1],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,THRID_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 2],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FOURTH_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 3],LEFT_MODE);
    
	/*Add buttons parameters*/
	calcButParam();

}

void RefreshScrollBarServiceMenuFrame(void)
{
    if(service_menu_frame_was_Scroll == 1 || service_menu_frame_was_Scroll == 2){
        calcButParam();
        
        drawScrollButton(service_menu_frame_Scroll_cnt == 0 ? 0 : (service_menu_frame_Scroll_cnt == 3 ? 2 : 1));
        
        drawFillArcRec(menuLines[service_menu_frame_Scroll_cnt].x, menuLines[service_menu_frame_Scroll_cnt].y, menuLines[service_menu_frame_Scroll_cnt].xSize, menuLines[service_menu_frame_Scroll_cnt].ySize, LCD_COLOR_WHITE);
        drawFillArcRec(menuLines[service_menu_frame_Scroll_cnt + 1].x, menuLines[service_menu_frame_Scroll_cnt + 1].y, menuLines[service_menu_frame_Scroll_cnt + 1].xSize, menuLines[service_menu_frame_Scroll_cnt + 1].ySize, LCD_COLOR_WHITE);
        drawFillArcRec(menuLines[service_menu_frame_Scroll_cnt + 2].x, menuLines[service_menu_frame_Scroll_cnt + 2].y, menuLines[service_menu_frame_Scroll_cnt + 2].xSize, menuLines[service_menu_frame_Scroll_cnt + 2].ySize, LCD_COLOR_WHITE);
        drawFillArcRec(menuLines[service_menu_frame_Scroll_cnt + 3].x, menuLines[service_menu_frame_Scroll_cnt + 3].y, menuLines[service_menu_frame_Scroll_cnt + 3].xSize, menuLines[service_menu_frame_Scroll_cnt + 3].ySize, LCD_COLOR_WHITE);
        
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FIRST_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt],LEFT_MODE);
        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,SECOND_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 1],LEFT_MODE);
        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,THRID_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 2],LEFT_MODE);
        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FOURTH_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 3],LEFT_MODE);
        
        drawStaticLines();
        
        service_menu_frame_was_Scroll = 0;
    }
}

void calcButParam()
{    
    TC_clearButtons();
   
        //Setting for key "0"
    menuLines[service_menu_frame_Scroll_cnt].x = FIRST_CURSOR_POS_X;
    menuLines[service_menu_frame_Scroll_cnt].y = FIRST_CURSOR_POS_Y;
    menuLines[service_menu_frame_Scroll_cnt].xSize = FIRST_CURSOR_SIZE_X;
    menuLines[service_menu_frame_Scroll_cnt].ySize = FIRST_CURSOR_SIZE_Y;
		
		//Setting for key "1"
    menuLines[service_menu_frame_Scroll_cnt + 1].x = SECOND_CURSOR_POS_X;
    menuLines[service_menu_frame_Scroll_cnt + 1].y = SECOND_CURSOR_POS_Y;
    menuLines[service_menu_frame_Scroll_cnt + 1].xSize = SECOND_CURSOR_SIZE_X;
    menuLines[service_menu_frame_Scroll_cnt + 1].ySize = SECOND_CURSOR_SIZE_Y;
    
		//Setting for key "2"
    menuLines[service_menu_frame_Scroll_cnt + 2].x = THRID_CURSOR_POS_X;
    menuLines[service_menu_frame_Scroll_cnt + 2].y = THRID_CURSOR_POS_Y;
    menuLines[service_menu_frame_Scroll_cnt + 2].xSize = THRID_CURSOR_SIZE_X;
    menuLines[service_menu_frame_Scroll_cnt + 2].ySize = THRID_CURSOR_SIZE_Y;
    
		//Setting for key "3"
    menuLines[service_menu_frame_Scroll_cnt + 3].x = FOURTH_CURSOR_POS_X;
    menuLines[service_menu_frame_Scroll_cnt + 3].y = FOURTH_CURSOR_POS_Y;
    menuLines[service_menu_frame_Scroll_cnt + 3].xSize = FOURTH_CURSOR_SIZE_X;
    menuLines[service_menu_frame_Scroll_cnt + 3].ySize = FOURTH_CURSOR_SIZE_Y;
    
    for (uint8_t i = service_menu_frame_Scroll_cnt; i < service_menu_frame_Scroll_cnt + 4; i++){
			TC_addButton(&menuLines[i]);
	}
	TC_addButton(&retBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);
}