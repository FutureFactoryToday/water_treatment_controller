#include "main.h"
#define OK "Ок"
#define CANCEL "Отмена"

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
	#include "main.h"

	#define OK "OK"
	#define CANCEL "CANCEL"

	//Public defines sizers
	#define TOP_BOT_LINE_WIDTH 60
	#define MED_LINE_WIDTH 200

	//Public defines mainbar sizers
	#define MAINBAR_POS_X 0
	#define MAINBAR_POS_Y 0
	#define MAINBAR_SIZE_X BSP_LCD_GetXSize()
	#define MAINBAR_SIZE_Y TOP_BOT_LINE_WIDTH

	#define RETURN_BUT_POS_X 0
	#define RETURN_BUT_POS_Y 0
	#define RETURN_BUT_SIZE_X TOP_BOT_LINE_WIDTH
	#define RETURN_BUT_SIZE_Y 100


	//Public defines statusbar sizers
	#define STATUSBAR_POS_X 0
	#define STATUSBAR_POS_Y BSP_LCD_GetYSize() - TOP_BOT_LINE_WIDTH
	#define STATUSBAR_SIZE_X BSP_LCD_GetXSize()
	#define STATUSBAR_SIZE_Y TOP_BOT_LINE_WIDTH

	#define CANCEL_X 16
	#define CANCEL_Y TOP_BOT_LINE_WIDTH + MED_LINE_WIDTH + 13

	#define OK_X 430
	#define OK_Y TOP_BOT_LINE_WIDTH + MED_LINE_WIDTH + 13


	//Public defines main window sizers
	#define MAIN_WINDOW_POS_X 0
	#define MAIN_WINDOW_POS_Y BSP_LCD_GetYSize() - TOP_BOT_LINE_WIDTH - MED_LINE_WIDTH
	#define MAIN_WINDOW_SIZE_X BSP_LCD_GetXSize()
	#define MAIN_WINDOW_SIZE_Y MED_LINE_WIDTH


	//Public defines cursor sizers
	#define TEXT_CTRL_POS_X 0
	#define TEXT_CTRL_POS_Y TOP_BOT_LINE_WIDTH + 1
	#define TEXT_CTRL_SIZE_X BSP_LCD_GetXSize()
	#define TEXT_CTRL_SIZE_Y TOP_BOT_LINE_WIDTH


int32_t ShowKeyboardFrame(int32_t min, int32_t max);

	//Public defines keys sizers
	////Public defines number keys sizers
	#define NUM_KEYS_POS_X 25
	#define NUM_KEYS_POS_Y (TOP_BOT_LINE_WIDTH * 2) + 5

	int32_t ShowKeyboardFrame(void);

	void RefreshKeyboardFrame(void);

void PrintResultFromKeyboard();

	uint8_t KeyClick(void);

	void PrintResultFromKeyboard();

	void TranslateKeyboardFrameMSG(void);
#endif //_KEYBOARD_H_