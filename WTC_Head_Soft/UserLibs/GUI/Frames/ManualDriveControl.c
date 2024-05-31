#include "ManualDriveControl.h"
#define motStartBut 	20,150,100,50, "Старт"
#define motStopBut		20,220,100,50, "Стоп"
#define curPozBut 	 	270,70,  100,50
#define setPozBut 	 	270,150,  100, 50
#define goPozBut		 	270,220,  100, 50, "GO"
#define changeDirBut 	20,70,100, 50
#define addPozBut 	 	380,150,  100, 50, "+5"
#define decPozBut		 	380,220,  100, 50, "-5"
#define dcOnOffBut		140, 110, 100, 50, "DC"
#define acOnOffBut		140, 220, 100, 50, "AC"
#define dcIsOnCirc		190, 80, 16
#define acIsOnCirc		190, 195, 16
static button_t motStart, motStop, changeDir, curPoz, goPoz, setPoz, addPoz, decPoz, dcOnOff, acOnOff;
bool acIsOn, dcIsOn;
static void createFrame (void);
uint16_t poz, manualPoz = 0;
uint8_t dir;
int16_t dispPoz = 0;
uint8_t Speed = 100;
void ShowManualDriveControl(void)
{
	//poz = PC_GetParams()->curPoz;
	createFrame();
	
	while(1)
	{		
		LL_mDelay(10);
		
		if (updateFlags.sec == true){
				drawClock();
			
				//drawTextLabel(curPozBut,intToStr(dispPoz));
				updateFlags.sec = false;
		}
		
		if (dispPoz != PC_GetCurPoz()){
			dispPoz = PC_GetCurPoz();
//			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//			BSP_LCD_DisplayStringAt(270,100, intToStr(dispPoz), LEFT_MODE);
			drawTextLabel(curPozBut,intToStr(dispPoz));
			updateFlags.optic = false;
		}
		/*Button pressed*/
		if (retBut.isReleased){
			PC_GetParams()->autoControl = true;
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
			manualPoz = ShowKeyboardFrame(-1000,1000);
			createFrame();
			//drawFillButton(setPozBut,intToStr(manualPoz), false);
		} 
		if (dcOnOff.isPressed == true){
			drawFillButton(dcOnOffBut, true);
		} 
		if (acOnOff.isPressed == true){
			drawFillButton(acOnOffBut, true);
		} 
		/*Buttons releases*/
		if (motStart.isReleased == true){
			PC_GetParams()->autoControl = false;
			MOT_SetSpeed(Speed);
			MOT_Start();
			motStart.isReleased = false;
			drawFillButton(motStartBut, false);
		}
		if (motStop.isReleased == true){
			MOT_Stop();
			motStop.isReleased = false;
			drawFillButton(motStopBut, false);
			PC_GetParams()->destPoz = PC_GetParams()->curPoz;
			PC_GetParams()->autoControl = true;
		}
		if (goPoz.isReleased == true){
			PC_GoToPoz(manualPoz); 
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
			poz = PC_GetCurPoz();
			if (poz < 650) {
				poz += 5;
			}
			PC_GoToPoz(poz);
			LL_mDelay(100);
			addPoz.isReleased = false;
		}
		if (decPoz.isReleased == true){
			poz = PC_GetCurPoz();
			if (poz >= 5) {
				poz -= 5;
			}
			PC_GoToPoz(poz);
			LL_mDelay(100);
			decPoz.isReleased = false;
		}
		if (dcOnOff.isReleased == true){
			LL_GPIO_TogglePin(REL1_ON_GPIO_Port,REL1_ON_Pin);
			if (!LL_GPIO_IsInputPinSet(REL1_CNTR_GPIO_Port,REL1_CNTR_Pin)){
				BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
			} else {
				BSP_LCD_SetTextColor(LCD_COLOR_RED);
			}
			BSP_LCD_FillCircle(dcIsOnCirc);
			drawFillButton(dcOnOffBut, false);
			dcOnOff.isReleased = false;
		} 
		if (acOnOff.isReleased == true){
			LL_GPIO_TogglePin(REL2_ON_GPIO_Port,REL2_ON_Pin);
			if (!LL_GPIO_IsInputPinSet(REL2_CNTR_GPIO_Port,REL2_CNTR_Pin)){
				BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
			} else {
				BSP_LCD_SetTextColor(LCD_COLOR_RED);
			}
			BSP_LCD_FillCircle(acIsOnCirc);

			drawFillButton(acOnOffBut, false);
			acOnOff.isReleased = false;
		} 
	}
}

void createFrame (void){
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	TC_clearButtons();
	
	dir = IN;
	
	drawMainBar(true, true, 190, 5, " ");
	
	drawMainWindow();
	
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawVLine(240,60,220);
	motStart = drawFillButton(motStartBut, false);
	motStop = drawFillButton(motStopBut, false);
	drawTextLabel(curPozBut,intToStr(PC_GetCurPoz()));
	goPoz = drawFillButton(goPozBut, false);
	if (dir == IN){
				dir = 0;
				changeDir=drawFillButton(changeDirBut,"IN", false);
			}
			else {
				dir = 1;
				changeDir=drawFillButton(changeDirBut,"OUT", false);
			}
	
	setPoz= drawFillButton(setPozBut,intToStr(manualPoz), false);
	
	addPoz = drawFillButton(addPozBut, false);
	decPoz = drawFillButton(decPozBut, false);		

	acOnOff = drawFillButton(acOnOffBut, false);
	dcOnOff = drawFillButton(dcOnOffBut, false);
	
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillCircle(dcIsOnCirc);
	BSP_LCD_FillCircle(acIsOnCirc);
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
	TC_addButton(&acOnOff);
	TC_addButton(&dcOnOff);
	enableClockDraw = true;
}
