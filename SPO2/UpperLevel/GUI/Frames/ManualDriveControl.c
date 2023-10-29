#include "ManualDriveControl.h"
#define motStartBut 	20,150,100,50, "Старт"
#define motStopBut		20,220,100,50, "Стоп"
#define curPozBut 	 	270,70,  100,50
#define setPozBut 	 	270,150,  100, 50
#define goPozBut		 	270,220,  100, 50, "GO"
#define changeDirBut 	20,70,100, 50
#define addPozBut 	 	380,150,  100, 50, "+5"
#define decPozBut		 	380,220,  100, 50, "-5"
static button_t motStart, motStop, changeDir, curPoz, goPoz, setPoz, addPoz, decPoz; 
static void createFrame (void);
uint16_t poz ;
uint8_t dir;
int16_t dispPoz = 0;
void ShowManualDriveControl(void)
{
	poz = PC_GetParams()->curPoz;
	createFrame();
	
	while(1)
	{		
		if (updateFlags.sec == true){
				drawClock();
				updateFlags.sec = false;
		}
		if (updateFlags.optic == true || dispPoz != PC_GetParams()->curPoz){
			dispPoz = PC_GetParams()->curPoz;
			drawTextLabel(curPozBut,intToStr(dispPoz));
			updateFlags.optic = false;
		}
		/*Button pressed*/
		if (retBut.isReleased){
			PC_GoToPoz(pistonPositions.rabPoz);
			return;
		}
		if (motStart.isPressed == true){
			drawFillButton(motStartBut, true);
			motStart.isPressed = false;
		}
		if (motStop.isPressed == true){
			drawFillButton(motStopBut, true);
			motStop.isPressed = false;
		}
		if (goPoz.isPressed == true){
			drawFillButton(goPozBut, true);
			goPoz.isPressed = false;
		}
    if (changeDir.isPressed == true){
			if (dir == IN){
				drawFillButton(changeDirBut,"IN", false);
			}
			else {
				drawFillButton(changeDirBut,"OUT", false);
			}
			changeDir.isPressed = false;
		}   
    if (setPoz.isPressed == true){
			poz = ShowKeyboardFrame(-1000,1000);
			createFrame();
		} 
		/*Buttons releases*/
		if (motStart.isReleased == true){
			MOT_Start();
			motStart.isReleased = false;
			drawFillButton(motStartBut, false);
		}
		if (motStop.isReleased == true){
			MOT_Stop();
			motStop.isReleased = false;
			drawFillButton(motStopBut, false);
		}
		if (goPoz.isReleased == true){
			PC_GoToPoz(poz); 
			goPoz.isReleased = false;
			drawFillButton(goPozBut, false);
		}
		if (changeDir.isReleased == true){
			if (dir == OUT){
				dir = IN;
				drawFillButton(changeDirBut,"IN", false);
			}
			else {
				dir = OUT;
				drawFillButton(changeDirBut,"OUT", false);
			}
			MOT_SetDir(dir);   
			changeDir.isReleased = false;
		}
		if (addPoz.isReleased == true){
			if (poz < 650) {
				poz += 5;
			}
			PC_GoToPoz(poz);
			LL_mDelay(100);
			addPoz.isReleased = false;
		}
		if (decPoz.isReleased == true){
			if (poz >= 5) {
				poz -= 5;
			}
			PC_GoToPoz(poz);
			LL_mDelay(100);
			decPoz.isReleased = false;
		}
	}
}

void createFrame (void){
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	TC_clearButtons();
	
	dir = IN;
	
	drawMainBar(true, 190, 5, " ");
	
	drawMainWindow();
	
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawVLine(240,60,220);
	motStart = drawFillButton(motStartBut, false);
	motStop = drawFillButton(motStopBut, false);
	drawTextLabel(curPozBut,intToStr(PC_GetParams()->curPoz));
	goPoz = drawFillButton(goPozBut, false);
	if (dir == IN){
				dir = 0;
				changeDir=drawFillButton(changeDirBut,"IN", false);
			}
			else {
				dir = 1;
				changeDir=drawFillButton(changeDirBut,"OUT", false);
			}
	
	setPoz= drawFillButton(setPozBut,intToStr(poz), false);
	
	addPoz = drawFillButton(addPozBut, false);
	decPoz = drawFillButton(decPozBut, false);					
	drawStatusBarEmpty();
	
	drawClock();
	
	/*Add buttons settings*/
	
	/*Add Buttons*/
			TC_addButton(&retBut);
	TC_addButton(&motStart);
	TC_addButton(&motStop);
	TC_addButton(&goPoz);
  TC_addButton(&changeDir);
	TC_addButton(&setPoz);
	TC_addButton(&addPoz);
	TC_addButton(&decPoz);
	enableClockDraw = true;
}
