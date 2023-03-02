#include "keyboardFrame.h"

int32_t qwertyResult = 0;
uint8_t dx = 0;
int8_t hwndKeyboardFrameControl = 0;
int32_t result_keyboard = 0;

int32_t _min = 0;

int32_t _max = 0;

int32_t result = 144;

button_t _0,_1,_2,_3,_4,_5,_6,_7,_8,_9, delBut;

void staticCreate(void);

void RefreshKeyboardFrame(void);

uint8_t KeyClick(void);

void PrintResultFromKeyboard(int32_t result);

void RefreshCursor(uint8_t dx);
	
int32_t ShowKeyboardFrame(int32_t min, int32_t max)
{
    _min = min;
    _max = max;
    dx = 0;
    qwertyResult = 0;
    result_keyboard = 0;
	
	
	staticCreate();
	
    while(1)
    {
			//Секундное обновление
			if (updateFlags.sec == 1){
				RefreshCursor(dx);
				updateFlags.sec = 0;
			}
			
			//Обработка кнопок
			if(_0.isReleased == 1){
				 PrintResultFromKeyboard(0);
				_0.isReleased = 0;
			}
			if(_1.isReleased == 1){
				PrintResultFromKeyboard(1);
				_1.isReleased = 0;
			}
			if(_2.isReleased == 1){
				PrintResultFromKeyboard(2);
				_2.isReleased = 0;
			}
			if(_3.isReleased == 1){
				PrintResultFromKeyboard(3);
				_3.isReleased = 0;
			}
			if(_4.isReleased == 1){
				PrintResultFromKeyboard(4);
				_4.isReleased = 0;
			}
			if(_5.isReleased == 1){
				PrintResultFromKeyboard(5);
				_5.isReleased = 0;
			}
			if(_6.isReleased == 1){
				PrintResultFromKeyboard(6);
				_6.isReleased = 0;
			}
			if(_7.isReleased == 1){
				PrintResultFromKeyboard(7);
				_7.isReleased = 0;
			}
			if(_8.isReleased == 1){
				PrintResultFromKeyboard(8);
				_8.isReleased = 0;
			}
			if(_9.isReleased == 1){
				PrintResultFromKeyboard(9);
				_9.isReleased = 0;
			}
			if(retBut.isReleased == 1){
				
				retBut.isReleased = 0;
				return -1;
			}
			if(okBut.isReleased == 1){
				
				okBut.isReleased = 0;
				return result_keyboard;
			}
			if(delBut.isReleased == 1){
				PrintResultFromKeyboard(10);
				delBut.isReleased = 0;
			}
    }
    
}

void RefreshKeyboardFrame(void)
{
    //Static refresh
    if(qwertyResult == 0)
    {
        BSP_LCD_SetFont(&Oxygen_Mono_24);
        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
        BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
        
        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
        BSP_LCD_FillRect(MAIN_WINDOW_POS_X,MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
        
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillRect(TEXT_CTRL_POS_X,TEXT_CTRL_POS_Y, TEXT_CTRL_SIZE_X, TEXT_CTRL_SIZE_Y);
        
        BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
        
        BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
        
        BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        
        BSP_LCD_DisplayStringAt(CANCEL_X, CANCEL_Y, CANCEL, LEFT_MODE);
        
        BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
        
        BSP_LCD_DisplayStringAt(OK_X, OK_Y, OK, LEFT_MODE);
        
        //RefreshKeys();
    }
    //PrintResultFromKeyboard();
}

void RefreshCursor(uint8_t dx)
{
    uint16_t oldTextColor = BSP_LCD_GetTextColor();
    
    if(getTime()->second%2 == 0)
    {
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_FillRect(CURSOR_POS_X + dx,CURSOR_POS_Y, CURSOR_SIZE_X, CURSOR_SIZE_Y);
    }
    else
    {
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillRect(CURSOR_POS_X + dx,CURSOR_POS_Y, CURSOR_SIZE_X, CURSOR_SIZE_Y);
    }
    
    BSP_LCD_SetTextColor(oldTextColor);
}

void staticCreate(void)
{
	TC_clearButtons();

    drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, " ");
    
    drawMainWindow();
    
    drawTextLabel(TEXT_CTRL_POS_X, TEXT_CTRL_POS_Y, TEXT_CTRL_SIZE_X, TEXT_CTRL_SIZE_Y, "          ");

    drawStatusBarOkCancel();
    
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);	
    ////uint32_t dy = (BSP_LCD_GetYSize() - LINE_KEYS_POS_Y - 40);   //////// 
    BSP_LCD_FillRect(0, LINE_KEYS_POS_Y, BSP_LCD_GetXSize(),91);
    //Horizontal lines
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_DrawLine(0, LINE_KEYS_POS_Y, BSP_LCD_GetXSize(), LINE_KEYS_POS_Y);
    BSP_LCD_DrawLine(0, LINE_KEYS_POS_Y + 45, BSP_LCD_GetXSize(), LINE_KEYS_POS_Y + 45);
    BSP_LCD_DrawLine(0, LINE_KEYS_POS_Y + 91, BSP_LCD_GetXSize(), LINE_KEYS_POS_Y + 91);
    
    //Vertical lines
    BSP_LCD_DrawLine(0, LINE_KEYS_POS_Y, 0, LINE_KEYS_POS_Y + 91);
    BSP_LCD_DrawLine(60, LINE_KEYS_POS_Y, 60, LINE_KEYS_POS_Y + 91);
    BSP_LCD_DrawLine(120, LINE_KEYS_POS_Y, 120, LINE_KEYS_POS_Y + 91);
    BSP_LCD_DrawLine(180, LINE_KEYS_POS_Y, 180, LINE_KEYS_POS_Y + 91);
    BSP_LCD_DrawLine(240, LINE_KEYS_POS_Y, 240, LINE_KEYS_POS_Y + 91);
    BSP_LCD_DrawLine(300, LINE_KEYS_POS_Y, 300, LINE_KEYS_POS_Y + 91);
    BSP_LCD_DrawLine(360, LINE_KEYS_POS_Y, 360, LINE_KEYS_POS_Y + 91);
    BSP_LCD_DrawLine(420, LINE_KEYS_POS_Y, 420, LINE_KEYS_POS_Y + 91);
    BSP_LCD_DrawLine(479, LINE_KEYS_POS_Y, 479, LINE_KEYS_POS_Y + 91);
    
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X, NUM_KEYS_POS_Y, "0", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 60, NUM_KEYS_POS_Y, "1", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 120, NUM_KEYS_POS_Y, "2", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 180, NUM_KEYS_POS_Y, "3", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 240, NUM_KEYS_POS_Y, "4", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 300, NUM_KEYS_POS_Y, "5", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 360, NUM_KEYS_POS_Y, "6", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 420, NUM_KEYS_POS_Y, "7", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X, NUM_KEYS_POS_Y + 46, "8", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 60, NUM_KEYS_POS_Y + 46, "9", LEFT_MODE);
    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 116, NUM_KEYS_POS_Y + 46, "<", LEFT_MODE);
    
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    
		//Setting for key "0"
    _0.xSize = 60;//
    _0.x = NUM_KEYS_POS_X;
    _0.y = NUM_KEYS_POS_Y;
    _0.ySize = BSP_LCD_GetFont()->height;
		
		//Setting for key "1"
    _1.xSize = 60;//
    _1.x = NUM_KEYS_POS_X + 60;
    _1.y = NUM_KEYS_POS_Y;
    _1.ySize = BSP_LCD_GetFont()->height;
    
		//Setting for key "2"
    _2.xSize = 60;//
    _2.x = NUM_KEYS_POS_X + 120;
    _2.y = NUM_KEYS_POS_Y;
    _2.ySize = BSP_LCD_GetFont()->height;
    
		//Setting for key "3"
    _3.xSize = 60;//
    _3.x = NUM_KEYS_POS_X + 180;
    _3.y = NUM_KEYS_POS_Y;
    _3.ySize = BSP_LCD_GetFont()->height;
    
		//Setting for key "4"
    _4.xSize = 60;//
    _4.x = NUM_KEYS_POS_X + 240;
    _4.y = NUM_KEYS_POS_Y;
    _4.ySize = BSP_LCD_GetFont()->height;
    
		//Setting for key "5"
    _5.xSize = 60;//
    _5.x = NUM_KEYS_POS_X + 300;
    _5.y = NUM_KEYS_POS_Y;
    _5.ySize = BSP_LCD_GetFont()->height;
    
		//Setting for key "6"
    _6.xSize = 60;//
    _6.x = NUM_KEYS_POS_X + 360;
    _6.y = NUM_KEYS_POS_Y;
    _6.ySize = BSP_LCD_GetFont()->height;
    
		//Setting for key "7"
    _7.xSize = 60;//
    _7.x = NUM_KEYS_POS_X + 420;
    _7.y = NUM_KEYS_POS_Y;
    _7.ySize = BSP_LCD_GetFont()->height;
    
		//Setting for key "8"
    _8.xSize = 60;//
    _8.x = NUM_KEYS_POS_X;
    _8.y = NUM_KEYS_POS_Y + 46;
    _8.ySize = BSP_LCD_GetFont()->height;
    
		//Setting for key "9"
    _9.xSize = 60;//
    _9.x = NUM_KEYS_POS_X + 60;
    _9.y = NUM_KEYS_POS_Y + 46;
    _9.ySize = BSP_LCD_GetFont()->height;
    
		//Setting for key "delete"
    delBut.xSize = 60;//
    delBut.x = NUM_KEYS_POS_X + 116;
    delBut.y = NUM_KEYS_POS_Y + 46;
    delBut.ySize = BSP_LCD_GetFont()->height;
    
	TC_addButton(&_0);
	TC_addButton(&_1);
	TC_addButton(&_2);
	TC_addButton(&_3);
	TC_addButton(&_4);
	TC_addButton(&_5);
	TC_addButton(&_6);
	TC_addButton(&_7);
	TC_addButton(&_8);
	TC_addButton(&_9);
	TC_addButton(&delBut);
	TC_addButton(&okBut);
	TC_addButton(&retBut);
	
	//PrintResultFromKeyboard();
	
	enableClockDraw = false;
}

void PrintResultFromKeyboard(int32_t result)
{
    int32_t pre_result = result;
    
    if((pre_result >= 1 && pre_result <= 9) || (pre_result == 0 && result_keyboard != 0))
    {
        result_keyboard = (result_keyboard * 10) + pre_result;
        if(result_keyboard > _max)
            result_keyboard = result_keyboard / 10;
        else
            dx += 13;
    }
        
    if(pre_result == 10)
    {
        result_keyboard = result_keyboard / 10;
        if(dx != 0) 
            dx -= 13;
    }

    if(result_keyboard != 0)
    {       
        drawFillArcRec (TEXT_CTRL_POS_X + 1, TEXT_CTRL_POS_Y + 2, TEXT_CTRL_SIZE_X - 2,  TEXT_CTRL_SIZE_Y - 3, LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(CURSOR_POS_X, CURSOR_POS_Y + 4, intToStr(result_keyboard), LEFT_MODE);        
    }
    if(result_keyboard == 0)
    {
        drawFillArcRec (TEXT_CTRL_POS_X + 1, TEXT_CTRL_POS_Y + 2, TEXT_CTRL_SIZE_X - 2,  TEXT_CTRL_SIZE_Y - 3, LCD_COLOR_WHITE);
    }
    result = 144;
}