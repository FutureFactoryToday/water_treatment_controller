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

int32_t ShowKeyboardFrame(int32_t min, int32_t max);

void RefreshKeyboardFrame(void);

void RefreshCursor(uint8_t dx);

void PrintResultFromKeyboard();

uint8_t KeyClick(void);

void TranslateKeyboardFrameMSG(void);

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
			if(_0.isPressed == 1){
				 PrintResultFromKeyboard(0);
				_0.isPressed = 0;
			}
			if(_1.isPressed == 1){
				PrintResultFromKeyboard(1);
				_1.isPressed = 0;
			}
			if(_2.isPressed == 1){
				PrintResultFromKeyboard(2);
				_2.isPressed = 0;
			}
			if(_3.isPressed == 1){
				PrintResultFromKeyboard(3);
				_3.isPressed = 0;
			}
			if(_4.isPressed == 1){
				PrintResultFromKeyboard(4);
				_4.isPressed = 0;
			}
			if(_5.isPressed == 1){
				PrintResultFromKeyboard(5);
				_5.isPressed = 0;
			}
			if(_6.isPressed == 1){
				PrintResultFromKeyboard(6);
				_6.isPressed = 0;
			}
			if(_7.isPressed == 1){
				PrintResultFromKeyboard(7);
				_7.isPressed = 0;
			}
			if(_8.isPressed == 1){
				PrintResultFromKeyboard(8);
				_8.isPressed = 0;
			}
			if(_9.isPressed == 1){
				PrintResultFromKeyboard(9);
				_9.isPressed = 0;
			}
			if(retBut.isPressed == 1){
				
				retBut.isPressed = 0;
				return -1;
			}
			if(okBut.isPressed == 1){
				
				okBut.isPressed = 0;
				return result_keyboard;
			}
			if(delBut.isPressed == 1){
				PrintResultFromKeyboard(10);
				delBut.isPressed = 0;
			}
			
//        if(redraw)
//        {
//            RefreshKeyboardFrame();
//            redraw = 0;
//        }
//        TranslateKeyboardFrameMSG();
//        
//        if(qwertyResult == 1)return result_keyboard;
//        
//        if(qwertyResult == 0)return qwertyResult;
        
        
        RefreshCursor(dx);
        
        qwertyResult = 2;
    }
    
}

//void RefreshKeyboardFrame(void)
//{
//    //Static refresh
//    if(qwertyResult == 0)
//    {      
//        RefreshKeys();
//        qwertyResult = 2;
//    }
//    PrintResultFromKeyboard();
//}
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
    PrintResultFromKeyboard();
}

void RefreshCursor(uint8_t dx)
{
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
}

void staticCreate(void)
{
	TC_clearButtons();

	enableClockDraw = false;
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
				
    //Horizontal lines
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_DrawLine(0, 121, BSP_LCD_GetXSize(), 121);
    BSP_LCD_DrawLine(0, 166, BSP_LCD_GetXSize(), 166);
    BSP_LCD_DrawLine(0, 212, BSP_LCD_GetXSize(), 212);
    BSP_LCD_DrawLine(0, 259, BSP_LCD_GetXSize(), 259);
    
    //Vertical lines
    BSP_LCD_DrawLine(0, 120, 0, 260);
    BSP_LCD_DrawLine(60, 121, 60, 260);
    BSP_LCD_DrawLine(120, 121, 120, 260);
    BSP_LCD_DrawLine(180, 121, 180, 260);
    BSP_LCD_DrawLine(240, 121, 240, 260);
    BSP_LCD_DrawLine(300, 121, 300, 260);
    BSP_LCD_DrawLine(360, 121, 360, 260);
    BSP_LCD_DrawLine(420, 121, 420, 260);
    BSP_LCD_DrawLine(479, 121, 479, 260);
    
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    //Setting for key "0"
    _0.xSize = BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X, NUM_KEYS_POS_Y, "0", LEFT_MODE);
		_0.x = NUM_KEYS_POS_X;
		_0.y = NUM_KEYS_POS_Y;
		_0.ySize = BSP_LCD_GetFont()->height;
		
		//Setting for key "1"
    _1.xSize = BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 60, NUM_KEYS_POS_Y, "1", LEFT_MODE);
		_1.x = NUM_KEYS_POS_X + 60;
		_1.y = NUM_KEYS_POS_Y;
		_1.ySize = BSP_LCD_GetFont()->height;
		
		//Setting for key "2"
    _2.xSize = BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 120, NUM_KEYS_POS_Y, "2", LEFT_MODE);
		_2.x = NUM_KEYS_POS_X + 120;
		_2.y = NUM_KEYS_POS_Y;
		_2.ySize = BSP_LCD_GetFont()->height;
		
		//Setting for key "3"
    _3.xSize = BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 180, NUM_KEYS_POS_Y, "3", LEFT_MODE);
		_3.x = NUM_KEYS_POS_X + 180;
		_3.y = NUM_KEYS_POS_Y;
		_3.ySize = BSP_LCD_GetFont()->height;
		
		//Setting for key "4"
    _4.xSize = BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 240, NUM_KEYS_POS_Y, "4", LEFT_MODE);
		_4.x = NUM_KEYS_POS_X + 240;
		_4.y = NUM_KEYS_POS_Y;
		_4.ySize = BSP_LCD_GetFont()->height;
		
		//Setting for key "5"
    _5.xSize = BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 300, NUM_KEYS_POS_Y, "5", LEFT_MODE);
		_5.x = NUM_KEYS_POS_X +300;
		_5.y = NUM_KEYS_POS_Y;
		_5.ySize = BSP_LCD_GetFont()->height;
		
		//Setting for key "6"
    _6.xSize = BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 360, NUM_KEYS_POS_Y, "6", LEFT_MODE);
		_6.x = NUM_KEYS_POS_X + 360;
		_6.y = NUM_KEYS_POS_Y;
		_6.ySize = BSP_LCD_GetFont()->height;
		
		//Setting for key "7"
    _7.xSize = BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 420, NUM_KEYS_POS_Y, "7", LEFT_MODE);
		_7.x = NUM_KEYS_POS_X + 420;
		_7.y = NUM_KEYS_POS_Y;
		_7.ySize = BSP_LCD_GetFont()->height;
		
		//Setting for key "8"
    _8.xSize = BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X, NUM_KEYS_POS_Y + 46, "8", LEFT_MODE);
		_8.x = NUM_KEYS_POS_X;
		_8.y = NUM_KEYS_POS_Y + 46;
		_8.ySize = BSP_LCD_GetFont()->height;
		
		//Setting for key "9"
    _9.xSize = BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 60, NUM_KEYS_POS_Y + 46, "9", LEFT_MODE);
		_9.x = NUM_KEYS_POS_X + 60;
		_9.y = NUM_KEYS_POS_Y + 46;
		_9.ySize = BSP_LCD_GetFont()->height;
		
		//Setting for key "delete"
    delBut.xSize = BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 116, NUM_KEYS_POS_Y + 46, "<", LEFT_MODE);
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
	
	PrintResultFromKeyboard();
    enableClockDraw = false;
}

//uint8_t KeyClick()
//{
//    int32_t result = 144;
//  BSP_TS_GetState(&tsState);
//	if (touchDelay == 0 && tsState.TouchDetected == 1)
//    {
//        touchDelay = 100;
//        if(result_keyboard < 99999999)
//        {
//            if (isInRectangle(tsState.X,tsState.Y, 0, 121, 60, 46)) 
//            {
//               result = 0;
//            }  
//            if (isInRectangle(tsState.X,tsState.Y, 60, 121, 60, 46)) 
//            {
//               result = 1;
//            }
//            if (isInRectangle(tsState.X,tsState.Y, 120, 121, 60, 46)) 
//            {
//               result = 2;
//            }
//            if (isInRectangle(tsState.X,tsState.Y, 180, 121, 60, 46)) 
//            {
//               result = 3;
//            }
//            if (isInRectangle(tsState.X,tsState.Y, 240, 121, 60, 46)) 
//            {
//               result = 4;
//            }
//            if (isInRectangle(tsState.X,tsState.Y, 300, 121, 60, 46)) 
//            {
//               result = 5;
//            }   
//            if (isInRectangle(tsState.X,tsState.Y, 360, 121, 60, 46)) 
//            {
//               result = 6;
//            }
//            if (isInRectangle(tsState.X,tsState.Y, 420, 121, 60, 46)) 
//            {
//               result = 7;
//            }
//            if (isInRectangle(tsState.X,tsState.Y, 0, 166, 60, 46)) 
//            {
//               result = 8;
//            }
//            if (isInRectangle(tsState.X,tsState.Y, 60, 166, 60, 46)) 
//            {
//               result = 9;
//            }
//        }
//        if (isInRectangle(tsState.X,tsState.Y, 120, 166, 60, 46)) 
//        {
//           result = 10;
//        }
//    }
//    return result;
//}

void PrintResultFromKeyboard()
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
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillRect(TEXT_CTRL_POS_X,TEXT_CTRL_POS_Y, TEXT_CTRL_SIZE_X, TEXT_CTRL_SIZE_Y);
        
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(CURSOR_POS_X, CURSOR_POS_Y + 6, intToStr(result_keyboard), LEFT_MODE);         
    }
    if(result_keyboard == 0)
    {
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillRect(TEXT_CTRL_POS_X, TEXT_CTRL_POS_Y, TEXT_CTRL_SIZE_X, TEXT_CTRL_SIZE_Y);
    }
    result = 144;
}

//void TranslateKeyboardFrameMSG()
//{
//  BSP_TS_GetState(&tsState);
//	if (touchDelay == 0 && tsState.TouchDetected == 1)
//    {
//        touchDelay = 100;
//        if (isInRectangle(tsState.X,tsState.Y,420,260,60,60)) //OK
//        {
//           qwertyResult = 1;
//        }  
//        if (isInRectangle(tsState.X,tsState.Y,0,260,120,60))  //CANCEL
//        {
//           qwertyResult = -1;
//        }  
//        if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y)) 
//        {
//           qwertyResult = -1;
//        }     
//    }
//}