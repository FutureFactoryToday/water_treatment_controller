

#ifndef _TOUCH_CONTROLLER_H_
	#include "main.h"
	#define _TOUCH_CONTROLLER_H_
	#define MAX_BUT_NUM 20
	#define BUT_MAX_PRESS 101//Press time = 0.1s*(BUT_MAX_PRESS - 1)
	typedef struct {
		uint8_t butNum;
		button_t* buttons[MAX_BUT_NUM];
	} tc_button_list_t;

	extern tc_button_list_t buttonList;
	extern bool TC_isTouched;
	extern uint32_t TC_touchCnt;
	extern int32_t touchCheckDelay;
	
	void TC_Init (void);
	void TC_addButton (button_t* but);
	void TC_clearButtons(void);
	void TC_checkButtons(void);
	void TC_releaseButtons(void);
	void TC_Interrupt(uint8_t);
#endif //_TOUCH_CONTROLLER_H_
