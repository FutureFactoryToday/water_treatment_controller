#include "ManualDriveControl.h"
#define motStartBut 	20,150,100,50, "Старт"
#define motStopBut		20,220,100,50, "Стоп"
#define curPozBut 	 	270,70,  100,50
#define setPozBut 	 	270,150,  100, 50
#define goPozBut		 	270,220,  100, 50, "GO"
#define changeDirBut 	20,70,100, 50

static button_t motStart, motStop, changeDir, curPoz, goPoz, setPoz; 
static void createFrame (void);
uint16_t poz;
uint8_t dir;
void ShowManualDriveControl(void)
{
	
	createFrame();
	
	while(1)
	{		
		if (updateFlags.sec == true){
				drawClock();
				updateFlags.sec = false;
		}
		if (updateFlags.optic == true){
			drawTextLabel(curPozBut,intToStr(PC_GetParams()->curPoz));
			updateFlags.optic = false;
		}
		/*Button pressed*/
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
	
	}
}

void createFrame (void){
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	TC_clearButtons();
	
	dir = IN;
	
	drawMainBar(false, 190, 5, " ");
	
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
	
	drawStatusBarEmpty();
	
	drawClock();
	
	/*Add buttons settings*/
	
	/*Add Buttons*/
	TC_addButton(&motStart);
	TC_addButton(&motStop);
	TC_addButton(&goPoz);
  TC_addButton(&changeDir);
	TC_addButton(&setPoz);
	
	enableClockDraw = true;
}
