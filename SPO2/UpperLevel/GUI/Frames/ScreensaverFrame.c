#include "ScreensaverFrame.h"

#define CHANGE_POSITION_COUNT 15 //sec
#define POSITIONS_QUANTITY 4
#define DEFAULT_POSITION_X 180
#define DEFAULT_POSITION_Y 220

const uint8_t CLOCK_X_POS_ARRAY[] = {200, 250, 120, 350};
const uint8_t CLOCK_Y_POS_ARRAY[] = {50, 200, 100, 150};

uint16_t clock_X_pos;
uint16_t clock_Y_pos;
uint16_t change_position_cnt;
uint8_t change_position_index;

static void Init_Frame();

static void CreateFrame();

static void Random_XY_pos();

void ShowScreensaverFrame(void) {
	Init_Frame(); 
	CreateFrame();
	while(1) {
		if(screenSaveDelay > 0)
			return;
		if (updateFlags.sec == true) {
			DrawScreensaverClock(LCD_COLOR_RED);
			--change_position_cnt;
			updateFlags.sec = false; 
			sysParams.vars.frameWDTTim = SOFT_WDT_TIM_VAL_DEF;
		}
		if(change_position_cnt == 0){
			DrawScreensaverClock(LCD_COLOR_BLACK);
			Random_XY_pos();
			change_position_cnt = CHANGE_POSITION_COUNT;	
			++change_position_index;
		}		
		if(change_position_index > (POSITIONS_QUANTITY-1)){
			change_position_index = 0;
		}			
	}
}

void Init_Frame() {
	clock_X_pos = CLOCK_X_POS_ARRAY[POSITIONS_QUANTITY-1];
	clock_Y_pos = CLOCK_Y_POS_ARRAY[POSITIONS_QUANTITY-1];
	change_position_cnt = CHANGE_POSITION_COUNT;
	change_position_index = 0;
}

void CreateFrame() {
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_FillRect(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
}


void DrawScreensaverClock(const uint32_t color) {
    
	uint16_t oldTextColor = BSP_LCD_GetTextColor();
	uint16_t oldBackColor = BSP_LCD_GetBackColor();
	time_t rtcTime = LL_RTC_TIME_Get(RTC);
	wtc_time_t time = intToWTCTime(rtcTime);
	BSP_LCD_SetFont(&Oxygen_Mono_52);
	
	BSP_LCD_SetTextColor(color);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	if (getTime().second % 2){
		BSP_LCD_DisplayStringAt(clock_X_pos, clock_Y_pos, getFormatedTime(" "),LEFT_MODE);
		
	} else {
		BSP_LCD_DisplayStringAt(clock_X_pos, clock_Y_pos, ":",LEFT_MODE);
	}
  BSP_LCD_DisplayStringAt(clock_X_pos - 3, clock_Y_pos, getFormatedTimeFromSource("hh", &time),RIGHT_MODE);
	BSP_LCD_DisplayStringAt(clock_X_pos + 14, clock_Y_pos, getFormatedTimeFromSource("mm", &time),LEFT_MODE);
}


void Random_XY_pos() {
	if(change_position_index >=0 && change_position_index < POSITIONS_QUANTITY) {
		clock_X_pos = CLOCK_X_POS_ARRAY[change_position_index];
		clock_Y_pos = CLOCK_Y_POS_ARRAY[change_position_index];
	}
	else {
		clock_X_pos = DEFAULT_POSITION_X;
		clock_Y_pos = DEFAULT_POSITION_Y;
	}
}