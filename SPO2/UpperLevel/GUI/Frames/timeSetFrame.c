/**
  ******************************************************************************
  * @file           : timeSetFrame.c
  * @brief          : 
  ******************************************************************************
  * @attention
  *
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "timeSetFrame.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define TIME_STR_WD "DD.MM.YYYY hh:mm:ss"
#define TIME_STR_WOD "DD.MM.YYYY hh:mm:ss"

#define MAIN_TEXT 0
#define SETTINGS_UP_TEXT 1
#define YEAR_TEXT 2
#define MONTH_TEXT 3
#define DAY_TEXT 4
#define HOUR_TEXT 5
#define MIN_TEXT 6
#define SAVE_TEXT 7
#define BACK_TEXT 8
#define EDIT_TEXT 9
#define CH_YEAR_TEXT 10
#define CH_MONTH_TEXT 11
#define CH_DAY_TEXT 12
#define CH_HOUR_TEXT 13
#define CH_MINUTE_TEXT 14

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
//uint8_t* ITEM_TIME_enText[] = {
//	"Date and time",
//	"Set date and time",
//	"YEAR",
//	"MONTH",
//	"DAY",
//	"HOUR",
//	"MINUTE",
//	"SAVE",
//	"DISCARD",
//	"Set date and time",
//	"Enter year",
//	"Enter month",
//	"Enter day",
//	"Enter hour",
//	"Enter minute"
//};

uint8_t** frameText;
uint8_t* timeStr = TIME_STR_WD;

char monthTable[7][7];
wtc_time_t displayedTime;
wtc_time_t editedTime;
extern date_name_t* dateName;

uint16_t setTimeButtonLength;
bool editBoxesShow = 0;
uint32_t rightButX;
button_t timeSetButton, dateSetButton;

/* Private function prototypes -----------------------------------------------*/
uint8_t refreshFrame();
uint8_t touchHandler();
void createFrame();
void drawMonth(void);
button_t drawMidClock(bool checked);
void drawEditBoxes(wtc_time_t editTime);
bool timeSetPressed = false;
/* Private user code ---------------------------------------------------------*/

int TSF_showFrame(){
	

	frameText = &ITEM_TIME_ruText;
	uint8_t memSec = getTime()->second;
	
	wtc_time_t *sysTimePtr = getTime();
	displayedTime = *sysTimePtr;
	
	createFrame();
	
	while(1)
    {
        if (updateFlags.sec == true){
            //drawClock();
            updateFlags.sec = false;
        }
			
			if (updateFlags.sec){
				displayedTime = *addSec(&displayedTime,1);
				drawMidClock(timeSetPressed);
				updateFlags.sec = false;
			} 
			if (timeSetButton.isPressed == true){
				timeSetPressed = true;
				drawMidClock(timeSetPressed);
				timeSetButton.isPressed = false;
			}
			if (timeSetButton.isReleased == true){
				wtc_time_t time = CSF_showFrame(&displayedTime);
				if (!isZeroDateTime(&time)){
					displayedTime.hour = time.hour;
					displayedTime.minute = time.minute;				
				}
				timeSetPressed = false;
				//drawMidClock(timeSetPressed);
				timeSetButton.isReleased = 0;
				createFrame();
                timeSetButton.isReleased = false;
			}
			if (dateSetButton.isPressed == true){
				drawDarkTextLabel(BSP_LCD_GetXSize()/2 - 100, MID_CLOCK_Y + BSP_LCD_GetFont()->height + 2*GAP,200, BSP_LCD_GetFont()->height + GAP, getFormatedTimeFromSource("DD MMM YYYY ", &displayedTime)); 
				dateSetButton.isPressed = false;
				
			}
			if (dateSetButton.isReleased == true){
				wtc_time_t date = CAL_showFrame(&displayedTime);
				if (!isZeroDateTime(&date)){
					displayedTime = *setDate(&displayedTime,&date); 
					
				}
				dateSetButton.isReleased = false;
				createFrame();
			}
			if (okBut.isReleased == true){
				setSysTime(&displayedTime);
				okBut.isReleased = false;
				return 0;
			}
			if (cancelBut.isReleased == true){
				cancelBut.isReleased = false;
				return 0;
			}
			if (retBut.isReleased == true){
				retBut.isReleased = false;
				return 0;
			}
            if (homeBut.isReleased == true){
				homeBut.isReleased = false;
				return 1;
			}
//			if (touchHandler()){
//					if (refreshFrame()){
//						return;
//					}
//			}		
    }
}


void createFrame(){
	//Static refresh
	//enableClockDraw = false;

	TC_clearButtons();
	BSP_LCD_Clear(MID_COLOR);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_MENU[0]);
	
	drawStatusBarOkCancel();

	timeSetButton = drawMidClock(false);
	dateSetButton = drawTextLabel(BSP_LCD_GetXSize()/2 - 100, MID_CLOCK_Y + BSP_LCD_GetFont()->height + 2*GAP,200, BSP_LCD_GetFont()->height + GAP, getFormatedTimeFromSource("DD MMM YYYY ", &displayedTime)); 
		
	TC_addButton(&okBut);
	TC_addButton(&cancelBut);
	TC_addButton(&retBut);
    TC_addButton(&homeBut);
	TC_addButton(&timeSetButton);
	TC_addButton(&dateSetButton);
}
button_t drawMidClock (bool checked){
	
	uint8_t* formatter = (getTime()->second % 2)? "hh:mm " : "hh mm ";
	return (!checked)? drawTextLabel(BSP_LCD_GetXSize()/2 - 50, MID_CLOCK_Y, 100, BSP_LCD_GetFont()->height + GAP, getFormatedTimeFromSource(formatter, &displayedTime)):
									drawDarkTextLabel(BSP_LCD_GetXSize()/2 - 50, MID_CLOCK_Y, 100, BSP_LCD_GetFont()->height + GAP, getFormatedTimeFromSource(formatter, &displayedTime)) ;
}


