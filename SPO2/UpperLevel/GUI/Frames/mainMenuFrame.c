#include "mainMenuFrame.h"


static button_t customerBut, serviceBut, historyBut; 
static void createFrame (void);

int ShowMainMenuFrame(void){
    createFrame();
	
	while(1)
	{		
		if (updateFlags.sec == true){
				 drawClock(); drawMainStatusBar(144, 2305, 16);
				updateFlags.sec = false;
		}
		/*Button pressed*/
    if (customerBut.isPressed == true){
			//drawFillCustomButton(25, 80, 200, 60, "ПРОМЫВКА", &gImage_DROPBUT, true);
			customerBut.isPressed = false;
		}
		if (serviceBut.isPressed == true){
			//drawFillCustomButton(255, 80, 200, 60, "МЕНЮ", &gImage_DROPBUT, true);
			serviceBut.isPressed = false;
		}
        if (historyBut.isPressed == true){
			//drawFillButton(260, 200, 200, 60, "Контакты", true);
			historyBut.isPressed = false;
		}
       
        
		/*Buttons releases*/
		if (retBut.isReleased == true){
				retBut.isReleased = false;
				return 0;
		}
		if (customerBut.isReleased == true){
			ShowMenuFrame();
			customerBut.isReleased = false;
			createFrame();
		}
		if (serviceBut.isReleased == true){
			if (PIN_showFrame() == 1){
				ShowServiceMenuFrame();
			}	
			serviceBut.isReleased = false;
			createFrame();
		}
    if (historyBut.isReleased == true){
      ShowHistoryMenuFrame();
			historyBut.isReleased = false;
            createFrame();
		}
    if (homeBut.isReleased == true){
			homeBut.isReleased = false;
      goHome = true;
		}
		if (goHome){
			return -1;
		}
	}
}

void createFrame (void){
	if (goHome) return;
	TC_clearButtons();
    
  drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, "");
	
	drawMainWindow();
	
	customerBut = drawFillButton(140, 70, 200, 60, "ПОЛЬЗОВАТЕЛЬ", false);
	serviceBut = drawFillButton(140, 140, 200, 60, "ИНЖЕНЕР", false);
	historyBut = drawFillButton(140, 210, 200, 60, "ИСТОРИЯ", false);
	
	drawMainStatusBar(144, 2305, 15);
	
	drawClock(); drawMainStatusBar(144, 2305, 16);
	
	/*Add buttons settings*/
	
	/*Add Buttons*/
	TC_addButton(&customerBut);
	TC_addButton(&serviceBut);
    TC_addButton(&historyBut);
    TC_addButton(&retBut);
    TC_addButton(&homeBut);
	
	enableClockDraw = true;
}