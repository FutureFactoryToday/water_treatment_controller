#include "mainMenuFrame.h"


static button_t customerBut, serviceBut, historyBut; 
static void createFrame (void);

int ShowMainMenuFrame(void){
    createFrame();
	
	while(1)
	{		
        if (updateFlags.sec == true){
            drawClock();
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
			if(ShowMenuFrame() == 1) return 1;
			customerBut.isReleased = false;
			createFrame();
		}
		if (serviceBut.isReleased == true){
			if (PIN_showFrame() == 1){
				if(ShowServiceMenuFrame() == 1) return 1;
			}	
            //ShowMenuFrame(); 
			serviceBut.isReleased = false;
			createFrame();
		}
        if (historyBut.isReleased == true){
            //ShowAlarmNotiServiceFrame();   
			historyBut.isReleased = false;
            createFrame();
		}
        if (homeBut.isReleased == true){
            //ShowAlarmNotiServiceFrame();   
			homeBut.isReleased = false;
            return 1;
            //createFrame();
		}
	}
}

void createFrame (void){
	TC_clearButtons();
    
    drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, "");
	
	drawMainWindow();
	
	customerBut = drawFillButton(140, 70, 200, 60, "ПОЛЬЗОВАТЕЛЬ", false);
	serviceBut = drawFillButton(140, 140, 200, 60, "ИНЖЕНЕР", false);
	historyBut = drawFillButton(140, 210, 200, 60, "ИСТОРИЯ", false);
	
	drawMainStatusBar(144, 2305, 15);
	
	drawClock();
	
	/*Add buttons settings*/
	
	/*Add Buttons*/
	TC_addButton(&customerBut);
	TC_addButton(&serviceBut);
    TC_addButton(&historyBut);
    TC_addButton(&retBut);
    TC_addButton(&homeBut);
	
	enableClockDraw = true;
}