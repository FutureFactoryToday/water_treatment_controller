#include "main.h"

//Public defines
//#define MODE_SOFTENING_CYCLE "SOFTENING CYCLE"
//#define MODE_MENU "MODE"
//#define DELAY_REGEN "DELAY REGEN"
//#define SPEED "SPEED"
//#define TIME "TIME"

#define MODE_SOFTENING_CYCLE 0
#define MODE_MENU 1
#define DELAY_REGEN 2
#define SPEED 3
#define TIME 4

//#define DELAY_REGEN_UNITS "DAYS"
//#define SPEED_UNITS "L/MIN"
//#define TIME_UNITS "HH:MM"

#define DELAY_REGEN_UNITS 5
#define SPEED_UNITS 6
#define TIME_UNITS 7

#define PL_NOT_INITED "---"

	#ifdef WDT_TEST_1

	extern bool wdt1While;
	#endif
	
	#ifdef WDT_TEST_2

	extern bool wdt2While;
	#endif
void ShowMainFrame(void);





