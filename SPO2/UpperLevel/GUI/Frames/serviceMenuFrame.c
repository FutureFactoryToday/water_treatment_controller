#include "serviceMenuFrame.h"

uint8_t service_menu_frame_Scroll_cnt = 0;
uint8_t service_menu_frame_was_Scroll = 0;

int8_t hwndServiceMenuFrameControl = 0;
int8_t startServiceMenuFrame = 0;

static button_t menuLines[8];
static void createFrame();
static void calcButParam();

void RefreshServiceMenuFrame(void);

void RefreshScrollBarServiceMenuFrame(void);

void AnimateScrollBarKeysServiceMenuFrame(void);

int ShowServiceMenuFrame(void)
{
  service_menu_frame_Scroll_cnt = 0;
	/*Static create*/
	createFrame();
	while(1)
	{
		 if(updateFlags.sec == true){
				 drawClock(); drawMainStatusBar(144, 2305, 16);
				updateFlags.sec = false; sysParams.vars.frameWDTTim = SOFT_WDT_TIM_VAL_DEF; 
		 }
		/*Buttons pressed*/
		 if(retBut.isPressed == true){
				retBut.isPressed = false;
				//return 0;
		 }
		 if(menuLines[0].isPressed == true){
				//Make it blue
			 #if defined (KEB)
			 	drawFillArcRec(menuLines[0].x, menuLines[0].y, menuLines[0].xSize, menuLines[0].ySize, LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetBackColor(LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				BSP_LCD_DisplayStringAt(FIRST_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_LONG_BUTTON_SIZE_X/2, FIRST_SERVICE_MENU_BUTTON_POS_Y + 4, ITEM_SERVICE_MENU[0], CENTER_MODE);
			 #else
				drawFillArcRec(menuLines[0].x, menuLines[0].y, menuLines[0].xSize, menuLines[0].ySize, LCD_COLOR_BLUE);
				BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[0].y + 9,ITEM_SERVICE_MENU[0],LEFT_MODE);
			 #endif
				menuLines[0].isPressed = false;
		 }
		 if(menuLines[1].isPressed == true){
				//Make it blue
			 #if defined (KEB)
			 	drawFillArcRec(menuLines[1].x, menuLines[1].y, menuLines[1].xSize, menuLines[1].ySize, LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetBackColor(LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				BSP_LCD_DisplayStringAt(SECOND_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_LONG_BUTTON_SIZE_X/2, SECOND_SERVICE_MENU_BUTTON_POS_Y + 4, ITEM_SERVICE_MENU[1], CENTER_MODE);
			 #else
				drawFillArcRec(menuLines[1].x, menuLines[1].y, menuLines[1].xSize, menuLines[1].ySize, LCD_COLOR_BLUE);
				BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[1].y + 9,ITEM_SERVICE_MENU[1],LEFT_MODE);
			 #endif
				menuLines[1].isPressed = false;
		 }
		 if(menuLines[2].isPressed == true){
				//Make it blue
			 #if defined (KEB)
			 	drawFillArcRec(menuLines[2].x, menuLines[2].y, menuLines[2].xSize, menuLines[2].ySize, LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetBackColor(LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				BSP_LCD_DisplayStringAt(THRID_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X/2, THRID_SERVICE_MENU_BUTTON_POS_Y + 4, ITEM_SERVICE_MENU[2], CENTER_MODE);
			 #else
				drawFillArcRec(menuLines[3].x, menuLines[2].y, menuLines[2].xSize, menuLines[2].ySize, LCD_COLOR_BLUE);
				BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[2].y + 9,ITEM_SERVICE_MENU[2],LEFT_MODE);
			 #endif
				menuLines[2].isPressed = false;
		 }
		 if(menuLines[3].isPressed == true){
				//Make it blue
			 #if defined (KEB)
			 	drawFillArcRec(menuLines[3].x, menuLines[3].y, menuLines[3].xSize, menuLines[3].ySize, LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetBackColor(LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				BSP_LCD_DisplayStringAt(FOURTH_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X/2, FOURTH_SERVICE_MENU_BUTTON_POS_Y + 4, ITEM_SERVICE_MENU[3], CENTER_MODE);
			 #else
				drawFillArcRec(menuLines[3].x, menuLines[3].y, menuLines[3].xSize, menuLines[3].ySize, LCD_COLOR_BLUE);
				BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[3].y + 9,ITEM_SERVICE_MENU[3],LEFT_MODE);
			 #endif
				menuLines[3].isPressed = false;
		 }
		 if(menuLines[4].isPressed == true){
				//Make it blue
			 #if defined (KEB)
			 	drawFillArcRec(menuLines[4].x, menuLines[4].y, menuLines[4].xSize, menuLines[4].ySize, LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetBackColor(LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				BSP_LCD_DisplayStringAt(FIVE_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X/2, FIVE_SERVICE_MENU_BUTTON_POS_Y + 4, ITEM_SERVICE_MENU[4], CENTER_MODE);
			 #else
				drawFillArcRec(menuLines[4].x, menuLines[4].y, menuLines[4].xSize, menuLines[4].ySize, LCD_COLOR_BLUE);
				BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[4].y + 9,ITEM_SERVICE_MENU[4],LEFT_MODE);
			 #endif
				menuLines[4].isPressed = false;
		 }
		 if(menuLines[5].isPressed == true){
				//Make it blue
			 #if defined (KEB)
			 	drawFillArcRec(menuLines[5].x, menuLines[5].y, menuLines[5].xSize, menuLines[5].ySize, LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetBackColor(LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				BSP_LCD_DisplayStringAt(SIX_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X/2, SIX_SERVICE_MENU_BUTTON_POS_Y + 4, ITEM_SERVICE_MENU[5], CENTER_MODE);
			 #else
				drawFillArcRec(menuLines[5].x, menuLines[5].y, menuLines[5].xSize, menuLines[5].ySize, LCD_COLOR_BLUE);
				BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[5].y + 9,ITEM_SERVICE_MENU[5],LEFT_MODE);
			 #endif
				menuLines[5].isPressed = false;
		 }
		 if(menuLines[6].isPressed == true){
				//Make it blue
			 #if defined (KEB)
			 	drawFillArcRec(menuLines[6].x, menuLines[6].y, menuLines[6].xSize, menuLines[6].ySize, LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetBackColor(LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				BSP_LCD_DisplayStringAt(SEVEN_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_SHORT_BUTTON_SIZE_X/2, SEVEN_SERVICE_MENU_BUTTON_POS_Y + 4, ITEM_SERVICE_MENU[6], CENTER_MODE);
			 #else
				drawFillArcRec(menuLines[6].x, menuLines[6].y, menuLines[6].xSize, menuLines[6].ySize, LCD_COLOR_BLUE);
				BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[6].y + 9,ITEM_SERVICE_MENU[6],LEFT_MODE);
			 #endif
				menuLines[6].isPressed = false;
		 }
		 if(menuLines[7].isPressed == true){
				//Make it blue
			 #if defined (KEB)
			 	drawFillArcRec(menuLines[7].x, menuLines[7].y, menuLines[7].xSize, menuLines[7].ySize, LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetBackColor(LCD_COLOR_KEB_ALPFA_GREEN);
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				BSP_LCD_DisplayStringAt(EIGHT_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_LONG_BUTTON_SIZE_X/2, EIGHT_SERVICE_MENU_BUTTON_POS_Y + 4, ITEM_SERVICE_MENU[7], CENTER_MODE);
			 #else
				drawFillArcRec(menuLines[7].x, menuLines[7].y, menuLines[7].xSize, menuLines[7].ySize, LCD_COLOR_BLUE);
				BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[7].y + 9,ITEM_SERVICE_MENU[7],LEFT_MODE);
			 #endif
				menuLines[7].isPressed = false;
		 }
//		 if(menuLines[8].isPressed == true){
//                        //Make it blue
//            drawFillArcRec(menuLines[8].x, menuLines[8].y, menuLines[8].xSize, menuLines[8].ySize, LCD_COLOR_BLUE);
//            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[8].y + 9,ITEM_SERVICE_MENU[8],LEFT_MODE);
//            menuLines[8].isPressed = false;
//         }
//         if(menuLines[9].isPressed == true){
//                        //Make it blue
//            drawFillArcRec(menuLines[9].x, menuLines[9].y, menuLines[9].xSize, menuLines[9].ySize, LCD_COLOR_BLUE);
//            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[9].y + 9,ITEM_SERVICE_MENU[9],LEFT_MODE);
//            menuLines[9].isPressed = false;
//         }
		 #if !defined (KEB)
		 if(scrollUpBut.isPressed == true){
						//Make it blue
				scrollUpBut.isPressed = false;
		 }
		 if(scrollDwnBut.isPressed == true){
						//Make it blue
				scrollDwnBut.isPressed = false;
		 }
		 #endif
		/*Buttons released*/
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
			showInputOneFrame();
			menuLines[2].isReleased = false;
			createFrame();
	 }
	 if(menuLines[3].isReleased == true){
			ShowUniversalOutputFrame(); 
			menuLines[3].isReleased = false;
			createFrame();
	 }
	 if(menuLines[4].isReleased == true){
			ShowACOutputFrame();
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
	//       if(menuLines[7].isReleased == true){
	//            ShowAdjustmentFrame();   
	//            menuLines[7].isReleased = false;
	//            createFrame();
	//         } 
	//		 if(menuLines[8].isReleased == true){
	//            ShowMotorSettings();   
	//            menuLines[8].isReleased = false;
	//            createFrame();
	//         }
		 if(menuLines[7].isReleased == true){ //[9]
				showChangePinCodeFrame();   
				menuLines[7].isReleased = false;
				createFrame();
		 }
		 #if !defined (KEB)
		 if(scrollUpBut.isReleased == true){
				if(service_menu_frame_Scroll_cnt > 0){ service_menu_frame_Scroll_cnt--;
						service_menu_frame_was_Scroll = 1;
						RefreshScrollBarServiceMenuFrame();
				}
				scrollUpBut.isReleased = false;
		 }
		 if(scrollDwnBut.isReleased == true){
				if(service_menu_frame_Scroll_cnt < 4){ service_menu_frame_Scroll_cnt++;
						service_menu_frame_was_Scroll = 2;
						RefreshScrollBarServiceMenuFrame();
				}
				scrollDwnBut.isReleased = false;
		 }   
		 #endif
  }
}

void createFrame(void){
	if (goHome) return;
	//TC_clearButtons();
    
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_SERVICE);
	
	drawMainWindow();
	
	#if !defined (KEB)
	drawScrollButton(service_menu_frame_Scroll_cnt == 0 ? 0 : (service_menu_frame_Scroll_cnt == 3 ? 2 : 1));
	#endif
	
	//drawStatusBarEmpty();
	drawMainStatusBar(144, 2305, 16);
	
	drawClock(); 
		
	#if !defined (KEB)
	drawStaticLines();	
	#endif
	
	#if defined (KEB)
	drawFillArcRec(FIRST_SERVICE_MENU_LONG_BUTTON_POS_X, FIRST_SERVICE_MENU_BUTTON_POS_Y, SERVICE_MENU_LONG_BUTTON_SIZE_X, SERVICE_MENU_BUTTON_SIZE_Y, LCD_COLOR_KEB_GREEN);
	drawFillArcRec(SECOND_SERVICE_MENU_LONG_BUTTON_POS_X, SECOND_SERVICE_MENU_BUTTON_POS_Y, SERVICE_MENU_LONG_BUTTON_SIZE_X, SERVICE_MENU_BUTTON_SIZE_Y, LCD_COLOR_KEB_GREEN);
	drawFillArcRec(THRID_SERVICE_MENU_LONG_BUTTON_POS_X, THRID_SERVICE_MENU_BUTTON_POS_Y, SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X, SERVICE_MENU_BUTTON_SIZE_Y, LCD_COLOR_KEB_GREEN);
	drawFillArcRec(FOURTH_SERVICE_MENU_LONG_BUTTON_POS_X, FOURTH_SERVICE_MENU_BUTTON_POS_Y, SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X, SERVICE_MENU_BUTTON_SIZE_Y, LCD_COLOR_KEB_GREEN);
	drawFillArcRec(FIVE_SERVICE_MENU_LONG_BUTTON_POS_X, FIVE_SERVICE_MENU_BUTTON_POS_Y, SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X, SERVICE_MENU_BUTTON_SIZE_Y, LCD_COLOR_KEB_GREEN);
	drawFillArcRec(SIX_SERVICE_MENU_LONG_BUTTON_POS_X, SIX_SERVICE_MENU_BUTTON_POS_Y, SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X, SERVICE_MENU_BUTTON_SIZE_Y, LCD_COLOR_KEB_GREEN);
	drawFillArcRec(SEVEN_SERVICE_MENU_LONG_BUTTON_POS_X, SEVEN_SERVICE_MENU_BUTTON_POS_Y, SERVICE_MENU_SHORT_BUTTON_SIZE_X, SERVICE_MENU_BUTTON_SIZE_Y, LCD_COLOR_KEB_GREEN);
	drawFillArcRec(EIGHT_SERVICE_MENU_LONG_BUTTON_POS_X, EIGHT_SERVICE_MENU_BUTTON_POS_Y, SERVICE_MENU_LONG_BUTTON_SIZE_X, SERVICE_MENU_BUTTON_SIZE_Y, LCD_COLOR_KEB_GREEN);
	
	BSP_LCD_SetBackColor(LCD_COLOR_KEB_GREEN);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	BSP_LCD_DisplayStringAt(FIRST_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_LONG_BUTTON_SIZE_X/2, FIRST_SERVICE_MENU_BUTTON_POS_Y + 4,ITEM_SERVICE_MENU[0],CENTER_MODE);
	BSP_LCD_DisplayStringAt(SECOND_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_LONG_BUTTON_SIZE_X/2, SECOND_SERVICE_MENU_BUTTON_POS_Y + 4,ITEM_SERVICE_MENU[1],CENTER_MODE);
	BSP_LCD_DisplayStringAt(THRID_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X/2, THRID_SERVICE_MENU_BUTTON_POS_Y + 4,ITEM_SERVICE_MENU[2],CENTER_MODE);
	BSP_LCD_DisplayStringAt(FOURTH_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X/2, FOURTH_SERVICE_MENU_BUTTON_POS_Y + 4,ITEM_SERVICE_MENU[3],CENTER_MODE);
	BSP_LCD_DisplayStringAt(FIVE_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X/2, FIVE_SERVICE_MENU_BUTTON_POS_Y + 4,ITEM_SERVICE_MENU[4],CENTER_MODE);
	BSP_LCD_DisplayStringAt(SIX_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X/2, SIX_SERVICE_MENU_BUTTON_POS_Y + 4,ITEM_SERVICE_MENU[5],CENTER_MODE);
	BSP_LCD_DisplayStringAt(SEVEN_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_SHORT_BUTTON_SIZE_X/2, SEVEN_SERVICE_MENU_BUTTON_POS_Y + 4,ITEM_SERVICE_MENU[6],CENTER_MODE);
	BSP_LCD_DisplayStringAt(EIGHT_SERVICE_MENU_LONG_BUTTON_POS_X + SERVICE_MENU_LONG_BUTTON_SIZE_X/2, EIGHT_SERVICE_MENU_BUTTON_POS_Y + 4,ITEM_SERVICE_MENU[7],CENTER_MODE);
	#else
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FIRST_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,SECOND_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 1],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,THRID_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 2],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FOURTH_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 3],LEFT_MODE);
	#endif
    
	/*Add buttons parameters*/
	calcButParam();

}

void RefreshScrollBarServiceMenuFrame(void)
{
	if(service_menu_frame_was_Scroll == 1 || service_menu_frame_was_Scroll == 2){
		calcButParam();
		
		//drawScrollButton(service_menu_frame_Scroll_cnt == 0 ? 0 : (service_menu_frame_Scroll_cnt == 3 ? 2 : 1));
		
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
 
	#if defined (KEB)
	//Setting for key "0"
	menuLines[0].x = FIRST_SERVICE_MENU_LONG_BUTTON_POS_X;
	menuLines[0].y = FIRST_SERVICE_MENU_BUTTON_POS_Y;
	menuLines[0].xSize = SERVICE_MENU_LONG_BUTTON_SIZE_X;
	menuLines[0].ySize = SERVICE_MENU_BUTTON_SIZE_Y;
	
	//Setting for key "1"
	menuLines[1].x = SECOND_SERVICE_MENU_LONG_BUTTON_POS_X;
	menuLines[1].y = SECOND_SERVICE_MENU_BUTTON_POS_Y;
	menuLines[1].xSize = SERVICE_MENU_LONG_BUTTON_SIZE_X;
	menuLines[1].ySize = SERVICE_MENU_BUTTON_SIZE_Y;
	
	//Setting for key "2"
	menuLines[2].x = THRID_SERVICE_MENU_LONG_BUTTON_POS_X;
	menuLines[2].y = THRID_SERVICE_MENU_BUTTON_POS_Y;
	menuLines[2].xSize = SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X;
	menuLines[2].ySize = SERVICE_MENU_BUTTON_SIZE_Y;
	
	//Setting for key "3"
	menuLines[3].x = FOURTH_SERVICE_MENU_LONG_BUTTON_POS_X;
	menuLines[3].y = FOURTH_SERVICE_MENU_BUTTON_POS_Y;
	menuLines[3].xSize = SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X;
	menuLines[3].ySize = SERVICE_MENU_BUTTON_SIZE_Y;
	
	//Setting for key "4"
	menuLines[4].x = FIVE_SERVICE_MENU_LONG_BUTTON_POS_X;
	menuLines[4].y = FIVE_SERVICE_MENU_BUTTON_POS_Y;
	menuLines[4].xSize = SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X;
	menuLines[4].ySize = SERVICE_MENU_BUTTON_SIZE_Y;
	
	//Setting for key "5"
	menuLines[5].x = SIX_SERVICE_MENU_LONG_BUTTON_POS_X;
	menuLines[5].y = SIX_SERVICE_MENU_BUTTON_POS_Y;
	menuLines[5].xSize = SERVICE_MENU_SUPER_SHORT_BUTTON_SIZE_X;
	menuLines[5].ySize = SERVICE_MENU_BUTTON_SIZE_Y;
	
	//Setting for key "6"
	menuLines[6].x = SEVEN_SERVICE_MENU_LONG_BUTTON_POS_X;
	menuLines[6].y = SEVEN_SERVICE_MENU_BUTTON_POS_Y;
	menuLines[6].xSize = SERVICE_MENU_SHORT_BUTTON_SIZE_X;
	menuLines[6].ySize = SERVICE_MENU_BUTTON_SIZE_Y;
	
	//Setting for key "7"
	menuLines[7].x = EIGHT_SERVICE_MENU_LONG_BUTTON_POS_X;
	menuLines[7].y = EIGHT_SERVICE_MENU_BUTTON_POS_Y;
	menuLines[7].xSize = SERVICE_MENU_LONG_BUTTON_SIZE_X;
	menuLines[7].ySize = SERVICE_MENU_BUTTON_SIZE_Y;
	
	for (uint8_t i = 0; i < 8; i++){
		TC_addButton(&menuLines[i]);
	}
	TC_addButton(&retBut);
  TC_addButton(&homeBut);
	#else
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
  TC_addButton(&homeBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);
	#endif
}