#include "changePinCodeFrame.h"

static void createFrame(void);
static button_t oldPinCodeBut;
static button_t newPinCodeBut;
static button_t saveNewPinCodeBut;

int32_t oldPinCode;
int32_t newPinCode;

int showChangePinCodeFrame()
{
    oldPinCode = -1;
    newPinCode = -1;
	
    createFrame();
    while(1)
    {
			if (updateFlags.sec == true){
				drawClock();
                drawMainStatusBar(144, 2305, 16);
				updateFlags.sec = false; sysParams.vars.frameWDTTim = SOFT_WDT_TIM_VAL_DEF; 
			}
			if (retBut.isReleased == true) {
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
            
            /*Buttons pressed*/

			if (oldPinCodeBut.isPressed == true){			
				drawFillButton(oldPinCodeBut.x, oldPinCodeBut.y, oldPinCodeBut.xSize, oldPinCodeBut.ySize, ITEM_CHANGE_PINCODE_FRAME[0], true);
                oldPinCodeBut.isPressed = false;
			}
            if (newPinCodeBut.isPressed == true){			
				drawFillButton(newPinCodeBut.x, newPinCodeBut.y, newPinCodeBut.xSize, newPinCodeBut.ySize, ITEM_CHANGE_PINCODE_FRAME[1], true);
                newPinCodeBut.isPressed = false;
			}
            if (saveNewPinCodeBut.isPressed == true){			
				drawFillButton(saveNewPinCodeBut.x, saveNewPinCodeBut.y, saveNewPinCodeBut.xSize, saveNewPinCodeBut.ySize, ITEM_CHANGE_PINCODE_FRAME[2], true);
                saveNewPinCodeBut.isPressed = false;
			}
            
            /*Buttons released*/
            			
			if (oldPinCodeBut.isReleased == true){
                oldPinCode = ShowKeyboardFrame(0, 9999);
				createFrame();
				oldPinCodeBut.isReleased = false;
			}
            if (newPinCodeBut.isReleased == true){
                newPinCode = ShowKeyboardFrame(0, 9999);
				createFrame();
				newPinCodeBut.isReleased = false;
			}
            if (saveNewPinCodeBut.isReleased == true){
                if(oldPinCode == sysParams.consts.ServicePinCode)
                {
                    if(newPinCode != -1) {
                        BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
                        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
                        BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, MAINBAR_SIZE_Y + 3, "        Пароль успешно изменен!        ", CENTER_MODE);
                        sysParams.consts.ServicePinCode = newPinCode;
                        FP_SaveParam();
                    }
                    else {
                        BSP_LCD_SetTextColor(LCD_COLOR_RED);
                        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
                        BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, MAINBAR_SIZE_Y + 3, "        Введите новый пароль!        ", CENTER_MODE);
                    }
                }
                else
                {
                    BSP_LCD_SetTextColor(LCD_COLOR_RED);
                    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
                    BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, MAINBAR_SIZE_Y + 3, "        Неверный старый пароль!        ", CENTER_MODE);
                }
				//createFrame();
                drawFillButton(BSP_LCD_GetXSize()/2 - 150, 220, 300, 50, ITEM_CHANGE_PINCODE_FRAME[2], false);
				saveNewPinCodeBut.isReleased = false;
			}
		}
    
}

void createFrame(void)
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_SERVICE_MENU[9]);
	
	drawStatusBarEmpty();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
    if(oldPinCode == -1)
        oldPinCodeBut = drawTextLabel(BSP_LCD_GetXSize()/2 - 150, 100, 300, 50, ITEM_CHANGE_PINCODE_FRAME[0]);
    else
        oldPinCodeBut = drawTextLabel(BSP_LCD_GetXSize()/2 - 150, 100, 300, 50, intToStr(oldPinCode));
    
    if(newPinCode == -1)
        newPinCodeBut = drawTextLabel(BSP_LCD_GetXSize()/2 - 150, 160, 300, 50, ITEM_CHANGE_PINCODE_FRAME[1]);
    else
        newPinCodeBut = drawTextLabel(BSP_LCD_GetXSize()/2 - 150, 160, 300, 50, intToStr(newPinCode));
    
    
    saveNewPinCodeBut = drawFillButton(BSP_LCD_GetXSize()/2 - 150, 220, 300, 50, ITEM_CHANGE_PINCODE_FRAME[2], false);
    

    TC_addButton(&oldPinCodeBut);
    TC_addButton(&newPinCodeBut);
    TC_addButton(&saveNewPinCodeBut);
	TC_addButton(&okBut);
	TC_addButton(&retBut);	
	TC_addButton(&homeBut);
	drawClock(); 
    drawMainStatusBar(144, 2305, 16);
}
