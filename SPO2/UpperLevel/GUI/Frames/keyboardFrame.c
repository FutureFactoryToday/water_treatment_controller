#include "keyboardFrame.h"

int32_t qwertyResult = 0;
uint8_t dx = 0;
int8_t hwndKeyboardFrameControl = 0;
int32_t result_keyboard = 0;

int32_t _min = 0;

int32_t _max = 0;

int32_t result = 0;

button_t _0,_1,_2,_3,_4,_5,_6,_7,_8,_9, delBut;

static void createFrame(void);

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
	
	
	createFrame();
	
    while(1)
    {
			//Секундное обновление
        if (updateFlags.sec){
            RefreshCursor(dx);
            updateFlags.sec = false;
        }
        //Удержание кнопки с индикацией
        if(_0.isPressed){
            _0.isPressed = false;
//                BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//                BSP_LCD_FillRect(0, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X, NUM_KEYS_POS_Y, "0", LEFT_MODE);
        }
        if(_1.isPressed){
            _1.isPressed = false;
//                BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//                BSP_LCD_FillRect(60, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 60, NUM_KEYS_POS_Y, "1", LEFT_MODE);
        }
        if(_2.isPressed){
            _2.isPressed = false;
//                BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//                BSP_LCD_FillRect(120, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 120, NUM_KEYS_POS_Y, "2", LEFT_MODE);
        }
        if(_3.isPressed){
            _3.isPressed = false;
//                BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//                BSP_LCD_FillRect(180, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 180, NUM_KEYS_POS_Y, "3", LEFT_MODE);
        }
        if(_4.isPressed){
            _4.isPressed = false;
//                BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//                BSP_LCD_FillRect(240, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 240, NUM_KEYS_POS_Y, "4", LEFT_MODE);
        }
        if(_5.isPressed){
            _5.isPressed = false;
//                BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//                BSP_LCD_FillRect(300, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 300, NUM_KEYS_POS_Y, "5", LEFT_MODE);
        }
        if(_6.isPressed){
            _6.isPressed = false;
//                BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//                BSP_LCD_FillRect(360, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 360, NUM_KEYS_POS_Y, "6", LEFT_MODE);
        }
        if(_7.isPressed){
            _7.isPressed = false;
//                BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//                BSP_LCD_FillRect(420, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 420, NUM_KEYS_POS_Y, "7", LEFT_MODE);
        }
        if(_8.isPressed){
            _8.isPressed = false;
//                BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//                BSP_LCD_FillRect(0, LINE_KEYS_POS_Y + 45, 60, 46);
//                BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X, NUM_KEYS_POS_Y + 45, "8", LEFT_MODE);
        }
        if(_9.isPressed){
            _9.isPressed = false;
//                BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//                BSP_LCD_FillRect(60, LINE_KEYS_POS_Y + 45, 60, 46);
//                BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 60, NUM_KEYS_POS_Y + 45, "9", LEFT_MODE);
        }
        if(delBut.isPressed){
            delBut.isPressed = false;
//                BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//                BSP_LCD_FillRect(120, LINE_KEYS_POS_Y + 45, 60, 46);
//                BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 120, NUM_KEYS_POS_Y + 45, "<", LEFT_MODE);
        }
        
        //Обработка кнопок
        if(_0.isReleased){
            _0.isReleased = false;
            PrintResultFromKeyboard(0);
//                BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//                BSP_LCD_FillRect(0, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X, NUM_KEYS_POS_Y, "0", LEFT_MODE);
        }
        if(_1.isReleased){
            _1.isReleased = false;
            PrintResultFromKeyboard(1);
//                BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//                BSP_LCD_FillRect(60, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 60, NUM_KEYS_POS_Y, "1", LEFT_MODE);
        }
        if(_2.isReleased){
            _2.isReleased = false;
            PrintResultFromKeyboard(2);
//                BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//                BSP_LCD_FillRect(120, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 120, NUM_KEYS_POS_Y, "2", LEFT_MODE);  
        }
        if(_3.isReleased){
            _3.isReleased = false;
            PrintResultFromKeyboard(3);
//                BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//                BSP_LCD_FillRect(180, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 180, NUM_KEYS_POS_Y, "3", LEFT_MODE);
        }
        if(_4.isReleased){
            _4.isReleased = false;
            PrintResultFromKeyboard(4);
//                BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//                BSP_LCD_FillRect(240, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 240, NUM_KEYS_POS_Y, "4", LEFT_MODE);
        }
        if(_5.isReleased){
            _5.isReleased = false;
            PrintResultFromKeyboard(5);
//                BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//                BSP_LCD_FillRect(300, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 300, NUM_KEYS_POS_Y, "5", LEFT_MODE);
        }
        if(_6.isReleased){
            _6.isReleased = false;
            PrintResultFromKeyboard(6);
//                BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//                BSP_LCD_FillRect(360, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 360, NUM_KEYS_POS_Y, "6", LEFT_MODE);
        }
        if(_7.isReleased){
            _7.isReleased = false;
            PrintResultFromKeyboard(7);
//                BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//                BSP_LCD_FillRect(420, LINE_KEYS_POS_Y, 60, 45);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 420, NUM_KEYS_POS_Y, "7", LEFT_MODE);
        }
        if(_8.isReleased){
            _8.isReleased = false;
            PrintResultFromKeyboard(8);
//                BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//                BSP_LCD_FillRect(0, LINE_KEYS_POS_Y + 45, 60, 46);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X, NUM_KEYS_POS_Y + 45, "8", LEFT_MODE);
        }
        if(_9.isReleased){
            _9.isReleased = false;
            PrintResultFromKeyboard(9);
//                BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//                BSP_LCD_FillRect(60, LINE_KEYS_POS_Y + 45, 60, 46);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 60, NUM_KEYS_POS_Y + 45, "9", LEFT_MODE);
        }
        if(delBut.isReleased){
            delBut.isReleased = false;
            PrintResultFromKeyboard(10);
//                BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//                BSP_LCD_FillRect(120, LINE_KEYS_POS_Y + 45, 60, 46);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 120, NUM_KEYS_POS_Y + 45, "<", LEFT_MODE);
        }
        if(retBut.isReleased == true){
            retBut.isReleased = false;
            return -1;
        }
        if(okBut.isReleased == true){
            okBut.isReleased = false;
            return result_keyboard;
        }
        if(cancelBut.isReleased == true){
            cancelBut.isReleased = false;
            return -1;
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
        
    }
}

void RefreshCursor(uint8_t dx)
{
    uint16_t oldTextColor = BSP_LCD_GetTextColor();
    
    if(getTime().second%2 == 0)
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

void createFrame(void)
{
    //BSP_LCD_SetFont(&Oxygen_Mono_24);
	TC_clearButtons();

    drawMainBar(true, false, SMALL_LOGO_X, SMALL_LOGO_Y, " ");
    
    drawMainWindow();
    
    drawTextLabel(TEXT_CTRL_POS_X, TEXT_CTRL_POS_Y, TEXT_CTRL_SIZE_X, TEXT_CTRL_SIZE_Y, "          ");
    BSP_LCD_DisplayStringAt(TEXT_CTRL_POS_X + 300, TEXT_CTRL_POS_Y + 10, "Удалить", LEFT_MODE);

    drawStatusBarOkCancel();
    
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);	
    ////uint32_t dy = (BSP_LCD_GetYSize() - LINE_KEYS_POS_Y - 40);   //////// 
    BSP_LCD_FillRect(0, LINE_KEYS_POS_Y, BSP_LCD_GetXSize(),111);
    //Horizontal lines
//    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//    BSP_LCD_DrawLine(0, LINE_KEYS_POS_Y, BSP_LCD_GetXSize(), LINE_KEYS_POS_Y);
//    BSP_LCD_DrawLine(0, LINE_KEYS_POS_Y + 45, BSP_LCD_GetXSize(), LINE_KEYS_POS_Y + 45);
//    BSP_LCD_DrawLine(0, LINE_KEYS_POS_Y + 91, BSP_LCD_GetXSize(), LINE_KEYS_POS_Y + 91);
//    
//    //Vertical lines
//    BSP_LCD_DrawLine(0, LINE_KEYS_POS_Y, 0, LINE_KEYS_POS_Y + 91);
//    BSP_LCD_DrawLine(60, LINE_KEYS_POS_Y, 60, LINE_KEYS_POS_Y + 91);
//    BSP_LCD_DrawLine(120, LINE_KEYS_POS_Y, 120, LINE_KEYS_POS_Y + 91);
//    BSP_LCD_DrawLine(180, LINE_KEYS_POS_Y, 180, LINE_KEYS_POS_Y + 91);
//    BSP_LCD_DrawLine(240, LINE_KEYS_POS_Y, 240, LINE_KEYS_POS_Y + 91);
//    BSP_LCD_DrawLine(300, LINE_KEYS_POS_Y, 300, LINE_KEYS_POS_Y + 91);
//    BSP_LCD_DrawLine(360, LINE_KEYS_POS_Y, 360, LINE_KEYS_POS_Y + 91);
//    BSP_LCD_DrawLine(420, LINE_KEYS_POS_Y, 420, LINE_KEYS_POS_Y + 91);
//    BSP_LCD_DrawLine(479, LINE_KEYS_POS_Y, 479, LINE_KEYS_POS_Y + 91);
//    
//    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//    
//    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X, NUM_KEYS_POS_Y, "0", LEFT_MODE);
//    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 60, NUM_KEYS_POS_Y, "1", LEFT_MODE);
//    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 120, NUM_KEYS_POS_Y, "2", LEFT_MODE);
//    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 180, NUM_KEYS_POS_Y, "3", LEFT_MODE);
//    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 240, NUM_KEYS_POS_Y, "4", LEFT_MODE);
//    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 300, NUM_KEYS_POS_Y, "5", LEFT_MODE);
//    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 360, NUM_KEYS_POS_Y, "6", LEFT_MODE);
//    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 420, NUM_KEYS_POS_Y, "7", LEFT_MODE);
//    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X, NUM_KEYS_POS_Y + 46, "8", LEFT_MODE);
//    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 60, NUM_KEYS_POS_Y + 46, "9", LEFT_MODE);
//    BSP_LCD_DisplayStringAt(NUM_KEYS_POS_X + 120, NUM_KEYS_POS_Y + 46, "<", LEFT_MODE);
    BSP_LCD_SetFont(&Oxygen_Mono_24);
    _1 = drawFillButton(43, LINE_KEYS_POS_Y + 5, 70, 46, "1", false);
    _2 = drawFillButton(123, LINE_KEYS_POS_Y + 5, 70, 46, "2", false);
    _3 = drawFillButton(203, LINE_KEYS_POS_Y + 5, 70, 46, "3", false);
    _4 = drawFillButton(283, LINE_KEYS_POS_Y + 5, 70, 46, "4", false);
    _5 = drawFillButton(363, LINE_KEYS_POS_Y + 5, 70, 46, "5", false);
    _6 = drawFillButton(43, LINE_KEYS_POS_Y + 58, 70, 46, "6", false);
    _7 = drawFillButton(123, LINE_KEYS_POS_Y + 58, 70, 46, "7", false);
    _8 = drawFillButton(203, LINE_KEYS_POS_Y + 58, 70, 46, "8", false);
    _9 = drawFillButton(283, LINE_KEYS_POS_Y + 58, 70, 46, "9", false);
    _0 = drawFillButton(363, LINE_KEYS_POS_Y + 58, 70, 46, "0", false);
    BSP_LCD_SetFont(&Oxygen_Mono_20);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    
//		//Setting for key "0"
//    _0.xSize = 60;//
//    _0.x = NUM_KEYS_POS_X;
//    _0.y = NUM_KEYS_POS_Y;
//    _0.ySize = BSP_LCD_GetFont()->height;
//		
//		//Setting for key "1"
//    _1.xSize = 60;//
//    _1.x = NUM_KEYS_POS_X + 60;
//    _1.y = NUM_KEYS_POS_Y;
//    _1.ySize = BSP_LCD_GetFont()->height;
//    
//		//Setting for key "2"
//    _2.xSize = 60;//
//    _2.x = NUM_KEYS_POS_X + 120;
//    _2.y = NUM_KEYS_POS_Y;
//    _2.ySize = BSP_LCD_GetFont()->height;
//    
//		//Setting for key "3"
//    _3.xSize = 60;//
//    _3.x = NUM_KEYS_POS_X + 180;
//    _3.y = NUM_KEYS_POS_Y;
//    _3.ySize = BSP_LCD_GetFont()->height;
//    
//		//Setting for key "4"
//    _4.xSize = 60;//
//    _4.x = NUM_KEYS_POS_X + 240;
//    _4.y = NUM_KEYS_POS_Y;
//    _4.ySize = BSP_LCD_GetFont()->height;
//    
//		//Setting for key "5"
//    _5.xSize = 60;//
//    _5.x = NUM_KEYS_POS_X + 300;
//    _5.y = NUM_KEYS_POS_Y;
//    _5.ySize = BSP_LCD_GetFont()->height;
//    
//		//Setting for key "6"
//    _6.xSize = 60;//
//    _6.x = NUM_KEYS_POS_X + 360;
//    _6.y = NUM_KEYS_POS_Y;
//    _6.ySize = BSP_LCD_GetFont()->height;
//    
//		//Setting for key "7"
//    _7.xSize = 60;//
//    _7.x = NUM_KEYS_POS_X + 420;
//    _7.y = NUM_KEYS_POS_Y;
//    _7.ySize = BSP_LCD_GetFont()->height;
//    
//		//Setting for key "8"
//    _8.xSize = 60;//
//    _8.x = NUM_KEYS_POS_X;
//    _8.y = NUM_KEYS_POS_Y + 46;
//    _8.ySize = BSP_LCD_GetFont()->height;
//    
//		//Setting for key "9"
//    _9.xSize = 60;//
//    _9.x = NUM_KEYS_POS_X + 60;
//    _9.y = NUM_KEYS_POS_Y + 46;
//    _9.ySize = BSP_LCD_GetFont()->height;
    
		//Setting for key "delete"
    delBut.xSize = 100;//
    delBut.x = TEXT_CTRL_POS_X + 300;
    delBut.y = TEXT_CTRL_POS_Y;
    delBut.ySize = 60;
    
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
    TC_addButton(&cancelBut);
	TC_addButton(&retBut);
	
	//PrintResultFromKeyboard();
    PrintResultFromKeyboard(0);
	
	enableClockDraw = false;
}

void PrintResultFromKeyboard(int32_t result)
{
    int32_t pre_result = result;
    
    if(pre_result >= 0 && pre_result <= 9 || (pre_result == 0 && result_keyboard != 0))
    {
        result_keyboard = (result_keyboard * 10) + pre_result;
        if(result_keyboard > _max)
        {
            result_keyboard = result_keyboard / 10;
        }
        else
        {
            if(result_keyboard > 9)
                dx += 11;
            else if(result_keyboard == 0)
                dx = 11;
        }
    }
        
    if(pre_result == 10)
    {
        result_keyboard = result_keyboard / 10;
        if(dx != 0) 
        {
            if(result_keyboard == 0)
                dx = 11;
            else
                dx -= 11;
        }
    }
    
    if(pre_result == 0 || result_keyboard == 0)
    {
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        drawFillArcRec(TEXT_CTRL_POS_X + 1, TEXT_CTRL_POS_Y + 2, TEXT_CTRL_SIZE_X - 100,  TEXT_CTRL_SIZE_Y - 3, LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(CURSOR_POS_X, CURSOR_POS_Y + 4, "0", LEFT_MODE);  
    }
    if(result_keyboard != 0)
    {       
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        drawFillArcRec(TEXT_CTRL_POS_X + 1, TEXT_CTRL_POS_Y + 2, TEXT_CTRL_SIZE_X - 100,  TEXT_CTRL_SIZE_Y - 3, LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(CURSOR_POS_X, CURSOR_POS_Y + 6, intToStr(result_keyboard), LEFT_MODE);        
    }
}