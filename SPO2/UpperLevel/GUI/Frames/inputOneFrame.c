#include "inputOneFrame.h"

#include "filterSelectionFrame.h"

#define MARK_GAP MARK_BOX + 20
#define MARK_BOX 330
static int8_t markItem = 0;
static void createFrame(void);
static button_t menuLine[2], checkBox[2];
static void markLines();
static void calcButParam();

int showInputOneFrame(void)
{

	if(sysParams.consts.ExternalCommandType == EXTERNAL_START){
		markItem = 1;
	} else {
		markItem = 2;
	}

	createFrame();
	while(1)
	{
		if (updateFlags.sec == true){
//			drawClock(); 
//			drawMainStatusBar(144, 2305, 16);
			updateFlags.sec = false;
		}
		if(okBut.isReleased == true){
			if (markItem == 1){
				sysParams.consts.ExternalCommandType = EXTERNAL_START;	        
			}
			if (markItem == 2){
				sysParams.consts.ExternalCommandType = EXTERNAL_ENABLE;	        
			}
			FP_SaveParam();
			okBut.isReleased = false;
			return 0;
		}
		if(retBut.isReleased == true){
				retBut.isReleased = false;
				return 0;
		}
		if (cancelBut.isReleased == true){
				cancelBut.isReleased = false;
				return 0;
		}
		if (homeBut.isReleased == true){
			homeBut.isReleased = false;
      goHome = true;
		}
		if (goHome){
			return -1;
		}
		
		for (uint8_t i = 0; i < sizeof(menuLine)/sizeof(menuLine[0]); i++){
			if (checkBox[i].isPressed){
					drawFillButton(checkBox[i].x, checkBox[i].y, checkBox[i].xSize, checkBox[i].ySize,"", true);
					checkBox[i].isPressed = false;
			}
			if (checkBox[i].isReleased){
				markItem = i + 1;

				markLines();
				checkBox[i].isReleased = false;
			}
		}
  }
}

void createFrame(void)
{
	TC_clearButtons();
  //Static refresh
	calcButParam();
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_INPUT_ONE_FRAME[2]);
	
	drawStatusBarOkCancel();
	
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	calcButParam();
	
	for (uint8_t i = 0; i < sizeof(menuLine)/sizeof(menuLine[0]); i++){
		BSP_LCD_DisplayStringAt(menuLine[i].x,menuLine[i].y, ITEM_INPUT_ONE_FRAME[i],LEFT_MODE);
	}
	markLines();	
	/*Add buttons parameters*/
	
	drawStaticLines();
}

void markLines(){
	bool checked;
    char* status;
	for (uint8_t i = 0; i < sizeof(menuLine)/sizeof(menuLine[0]); i++){
		checked = (markItem - 1 == i)? true: false;
    status = (markItem - 1 == i)? "X": "";
		checkBox[i] = drawFillButton(SCROLLKEYUP_POS_X - 5 - 40, STATIC_LINE_Y + STATIC_LINE_SPASER*i + 3, 40, 40,status, checked);
	}
	
}

void calcButParam()
{
  TC_clearButtons();
  for (uint8_t i = 0; i < sizeof(menuLine)/sizeof(menuLine[0]); i++){
		menuLine[i].x = FIRST_CURSOR_POS_X + 9;
		menuLine[i].y = STATIC_LINE_Y + i*STATIC_LINE_SPASER + 9;
		menuLine[i].xSize = 250;
		menuLine[i].ySize = 40;
		//TC_addButton(&menuLine[i]);
	}
	for (uint8_t i = 0; i < sizeof(checkBox)/sizeof(checkBox[0]); i++){
		TC_addButton(&checkBox[i]);
	}
	TC_addButton(&retBut);
	TC_addButton(&okBut);
	TC_addButton(&cancelBut);
	TC_addButton(&homeBut);
}

//static void createFrame(void);
//static button_t inputOneBut[2],checkBox[2];
//int showInputOneFrame()
//{
//	createFrame();
//	while(1)
//	{
//		if (updateFlags.sec == true){
//				 drawClock(); drawMainStatusBar(144, 2305, 16);
//				updateFlags.sec = false;
//		}
//		if(retBut.isReleased == true) {
//				retBut.isReleased = false;
//				return 0;
//		}
//		if(homeBut.isReleased == true) {
//				homeBut.isReleased = false;
//				return 1;
//		}
//		for(uint8_t i = 0; i < 4; i ++){
//			if (inputOneBut[i].isPressed){
//					drawFillArcRec(inputOneBut[i].x, inputOneBut[i].y, inputOneBut[i].xSize, inputOneBut[i].ySize, LCD_COLOR_BLUE);
//					BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//					BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//					BSP_LCD_DisplayStringAt(inputOneBut[i].x, inputOneBut[i].y, ITEM_INPUT_ONE_FRAME[i], LEFT_MODE);
//					inputOneBut[i].isPressed = false;
//			}
//			if (inputOneBut[i].isReleased){
//					drawFillArcRec(inputOneBut[i].x, inputOneBut[i].y, inputOneBut[i].xSize, inputOneBut[i].ySize, LCD_COLOR_WHITE);
//					BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//					BSP_LCD_DisplayStringAt(inputOneBut[i].x, inputOneBut[i].y, ITEM_INPUT_ONE_FRAME[i], LEFT_MODE);
//					
//					inputOneBut[i].isReleased = false;
//			}
//		}
//	}  
//}

//void createFrame(void)
//{
//	TC_clearButtons();
//	//Static refresh
//	BSP_LCD_Clear(LCD_COLOR_WHITE);
//	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_INPUT_ONE_FRAME[2]);
//	drawStaticLines();
//	//drawStatusBarEmpty();
//	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//	for(uint8_t i = 0; i < 2; i ++){
//		BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + GAP, STATIC_LINE_Y + STATIC_LINE_SPASER*i + 9,ITEM_INPUT_ONE_FRAME[i], LEFT_MODE);
//		inputOneBut[i].x = FIRST_CURSOR_POS_X;
//		inputOneBut[i].y = STATIC_LINE_Y + STATIC_LINE_SPASER*i;
//		inputOneBut[i].xSize = 300;
//		inputOneBut[i].ySize = 40;
//		TC_addButton(&inputOneBut[i]);
//	}

////	TC_addButton(&okBut);
////	TC_addButton(&cancelBut);
//	TC_addButton(&retBut);	
//  TC_addButton(&homeBut);
//	drawClock(); 
//	drawMainStatusBar(144, 2305, 16);
//}
