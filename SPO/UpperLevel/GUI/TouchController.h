#include "main.h"

#ifndef _TOUCH_CONTROLLER_H_

	#define _TOUCH_CONTROLLER_H_
	#define MAX_BUT_NUM 10

	typedef struct {
		uint8_t butNum;
		button_t* buttons[MAX_BUT_NUM];
	} tc_button_list_t;

	extern tc_button_list_t buttonList;

	void TC_Init (void);
	void TC_addButton (button_t* but);
	void TC_clearButtons(void);
	void TC_Interrupt(void);

#endif //_TOUCH_CONTROLLER_H_
