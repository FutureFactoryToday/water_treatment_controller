#include "ProdTest.h"
#define TestFreq 10
#define HalFreq 1000
#define smallText Oxygen_Mono_16
#define bigText Oxygen_Mono_20
#define bufSize 299
typedef enum {
	FRAM_WRITE_ERR,
	FRAM_READ_TIMEOUT_ERR,
	FRAM_MISMATCH_ERR,
	RAM_WRITE_ERR,
	RAM_READ_TIMEOUT_ERR,
	RAM_MISMATCH_ERR,
	SIM_TIMEOUT
} mem_test_error_t;
static uint16_t x1,y1,yBut,xBut1,xBut2,xBut3,xBut4,xBut5, xButSize, yButSize , xGap, y6,xCur, xSize, ySize, yOffset;
static uint32_t oldHALTick;
static uint8_t curScreen;
static button_t motBut, tftBut, tsBut, memBut,ioBut, testBut, passBut, failBut, startBut;
static prod_test_t test;
static bool redrawWindow;
static bool memTestComplete;
static bool memTestFail;

uint8_t ramWriteTestData[bufSize+1];
uint8_t ramReadTestData[bufSize+1];
static mem_test_error_t memTestErr = 0;
uint16_t rectSize;
uint8_t rectWidth = 10;
uint32_t percent, oldPercent;
uint32_t failAddress;
test_result_t PT_DrawMainScreen();
test_result_t PT_DrawScreenTest();
test_result_t PT_DrawTouchTest();
test_result_t PT_DrawMotorTest();
void printADCResult (float value, uint8_t* name, uint8_t* valName, test_result_t pass, uint8_t poz);
void printTestResult (uint8_t* name, test_result_t pass, uint8_t poz);
void memInteractionComplete(void);
test_result_t PT_IOTest();
test_result_t PT_MemTest();

void drawMemStatus (uint32_t xS, uint32_t ySt, uint32_t adr, uint32_t maxAdr);
void ProductionTest(){
	__enable_irq();
	Start_Logic();
	Start_ADC();
	PC_Init();
	FM_Init();
	initGUI();
	
	FP_Init();
	Load_Default_Values();
	sysParams.consts.acRelay.workType = MANUAL_ON_AC;
	sysParams.consts.dcRelay.workType = MANUAL_ON;
	
	sysParams.vars.status.flags.AllInited = 1;
	test.inputVolt = NOT_START;
	test._3v3Volt = NOT_START;
	test._5Volt = NOT_START;
	test.relVolt = NOT_START;
	test.mot = NOT_START;
	test.tft = NOT_START;
	test.touch = NOT_START;
	test.mem = NOT_START;
	test.io = NOT_START;
	
	x1 = 30;
	y1 = 15;
	xCur = 0;
	xSize = BSP_LCD_GetXSize();
	ySize = BSP_LCD_GetFont()->height;
	
	
	xGap = 15;
	xButSize = 78;
	yButSize = 60;
	xBut1 = xGap;
	yBut = BSP_LCD_GetYSize() - yButSize - 5;
	xBut2 = xBut1 + xButSize + xGap;
	xBut3 = xBut2 + xButSize + xGap;
	xBut4 = xBut3 + xButSize + xGap;
	xBut5 = xBut4 + xButSize + xGap;
	
	
	
	
	
	
	
	PT_DrawMainScreen();
	//PT_MemTest();
}

test_result_t PT_DrawMainScreen(){
	while(1){
		BSP_LCD_Clear(LCD_COLOR_WHITE);
		BSP_LCD_SetFont(&Oxygen_Mono_16);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		
		x1 = 30;
		y1 = 15;
		xCur = 0;
		xSize = BSP_LCD_GetXSize();
		ySize = BSP_LCD_GetFont()->height;
		
		
		xGap = 15;
		xButSize = 78;
		yButSize = 60;
		xBut1 = xGap;
		yBut = BSP_LCD_GetYSize() - yButSize - 5;
		xBut2 = xBut1 + xButSize + xGap;
		xBut3 = xBut2 + xButSize + xGap;
		xBut4 = xBut3 + xButSize + xGap;
		xBut5 = xBut4 + xButSize + xGap;
		
		uint32_t backColor = LCD_COLOR_WHITE;
		uint32_t textColor = LCD_COLOR_BLACK;
		uint32_t butColor = LCD_COLOR_GRAY;
		
	//	motBut = drawFillCustomButton(xBut1, yBut, xButSize, yButSize, "Test Mot",NULL,butColor,backColor,textColor, false);
	//	tftBut = drawFillCustomButton(xBut2, yBut, xButSize, yButSize, "Test TFT", NULL,butColor,backColor,textColor, false); 
	//	tsBut = drawFillCustomButton(xBut3, yBut, xButSize, yButSize, "Test Tch", NULL,butColor,backColor,textColor, false); 
	//	memBut = drawFillCustomButton(xBut4, yBut, xButSize, yButSize, "Test Mem", NULL,butColor,backColor,textColor, false);
		motBut = drawCustom3TextLabel(xBut1, yBut, xButSize, yButSize, "Test", "MOT", LCD_COLOR_BLACK, LCD_COLOR_GRAY);
		tftBut = drawCustom3TextLabel(xBut2, yBut, xButSize, yButSize, "Test", "TFT", LCD_COLOR_BLACK, LCD_COLOR_GRAY);
		tsBut = drawCustom3TextLabel(xBut3, yBut, xButSize, yButSize, "Test", "Touch", LCD_COLOR_BLACK, LCD_COLOR_GRAY);
		memBut = drawCustom3TextLabel(xBut4, yBut, xButSize, yButSize, "Test", "MEM", LCD_COLOR_BLACK, LCD_COLOR_GRAY);
		ioBut = drawCustom3TextLabel(xBut5, yBut, xButSize, yButSize, "Test", "IO", LCD_COLOR_BLACK, LCD_COLOR_GRAY);
		
		

		
		TC_addButton(&motBut);
		TC_addButton(&tftBut);
		TC_addButton(&tsBut);
		TC_addButton(&memBut);
		TC_addButton(&ioBut);
		
		redrawWindow = false;
		
		while(!redrawWindow){
			
			if (HAL_GetTick() - oldHALTick > HalFreq/TestFreq){
				//BSP_LCD_Clear(LCD_COLOR_WHITE);
				yOffset = 0;
				test.inputVolt = sysParams.vars.adc.floatParam[Vin] > 14.0;
				printADCResult(sysParams.vars.adc.floatParam[Vin],ITEM_PROD_TEST_MAINSCREEN[3+2*Vin],ITEM_PROD_TEST_MAINSCREEN[3+2*Vin+1],test.inputVolt,yOffset++);
				test._3v3Volt = sysParams.vars.adc.floatParam[_3V3] > 3.0;
				printADCResult(sysParams.vars.adc.floatParam[_3V3],ITEM_PROD_TEST_MAINSCREEN[3+2*_3V3],ITEM_PROD_TEST_MAINSCREEN[3+2*_3V3+1],test._3v3Volt,yOffset++);
				test._5Volt = sysParams.vars.adc.floatParam[_5V] > 4.5;
				printADCResult(sysParams.vars.adc.floatParam[_5V],ITEM_PROD_TEST_MAINSCREEN[3+2*_5V],ITEM_PROD_TEST_MAINSCREEN[3+2*_5V+1],test._5Volt,yOffset++);
				test.relVolt = sysParams.vars.adc.floatParam[VrelDC] > 14.0;
				printADCResult(sysParams.vars.adc.floatParam[VrelDC],ITEM_PROD_TEST_MAINSCREEN[3+2*VrelDC],ITEM_PROD_TEST_MAINSCREEN[3+2*VrelDC+1],test.relVolt,yOffset++);
				
				printTestResult(ITEM_PROD_TEST_MAINSCREEN[15], test.mot, yOffset++);
				printTestResult(ITEM_PROD_TEST_MAINSCREEN[16], test.tft, yOffset++);
				printTestResult(ITEM_PROD_TEST_MAINSCREEN[17], test.touch, yOffset++);
				printTestResult(ITEM_PROD_TEST_MAINSCREEN[18], test.mem, yOffset++);
				printTestResult(ITEM_PROD_TEST_MAINSCREEN[19], test.io, yOffset++);
				
				
				oldHALTick = HAL_GetTick();
			}
			if (motBut.isReleased){
				test.mot = PT_DrawMotorTest();
				redrawWindow = true;
				continue;
			}
			if (tftBut.isReleased){
			 test.tft = PT_DrawScreenTest();
				redrawWindow = true;
				continue;
			}
			if (tsBut.isReleased){
				test.touch = PT_DrawTouchTest();
				redrawWindow = true;
				continue;
			}
			if (memBut.isReleased){
				test.mem = PT_MemTest();
				redrawWindow = true;
				continue;
			}
			if (ioBut.isReleased){
				test.io = PT_IOTest();
				redrawWindow = true;
				continue;
			}
		}
		TC_clearButtons();
	}
}

test_result_t PT_DrawScreenTest(){
	uint8_t yOffset;
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	yOffset = y1;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[20],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_SetFont(&Oxygen_Mono_16);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[21],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[22],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[23],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	testBut.x = 0;
	testBut.y = 0;
	testBut.xSize = BSP_LCD_GetXSize();
	testBut.ySize = BSP_LCD_GetYSize();
	
	startBut = drawCustomTextLabel(xBut3, yBut, xButSize, yButSize, "Start", LCD_COLOR_BLACK, LCD_COLOR_GRAY);
	TC_addButton(&startBut);
	while (!startBut.isReleased);
	TC_clearButtons();
	TC_addButton(&testBut);
	uint32_t colors[] = {LCD_COLOR_WHITE, LCD_COLOR_BLACK, LCD_COLOR_RED, LCD_COLOR_BLUE, LCD_COLOR_GREEN};
	
	for (uint8_t i =0; i < sizeof (colors)/sizeof(colors[0]);i++){
		BSP_LCD_Clear(colors[i]);
		while (!testBut.isReleased);
		testBut.isReleased = false;
	}
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	yOffset = y1;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[24],CENTER_MODE);
	
	passBut = drawCustomTextLabel(xBut1, yBut, xButSize, yButSize, "Pass", LCD_COLOR_BLACK, LCD_COLOR_GREEN);
	failBut = drawCustomTextLabel(xBut5, yBut, xButSize, yButSize, "Fail", LCD_COLOR_BLACK, LCD_COLOR_RED);
	
	TC_clearButtons();
	TC_addButton(&passBut);
	TC_addButton(&failBut);
	while(1){
		if (passBut.isReleased){
			return PASS;
		}
		if (failBut.isReleased){
			return TEST_FAIL;
		}
	}
}
test_result_t PT_DrawTouchTest(){
	uint8_t yOffset;
	uint32_t startTime = HAL_GetTick();
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	yOffset = y1;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[25],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_SetFont(&Oxygen_Mono_16);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[26],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[27],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[28],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[23],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	
	testBut.x = 0;
	testBut.y = 0;
	testBut.xSize = 48;
	testBut.ySize = 32;
	
	startBut = drawCustomTextLabel(xBut3, yBut, xButSize, yButSize, "Start", LCD_COLOR_BLACK, LCD_COLOR_GRAY);
	TC_addButton(&startBut);
	while (!startBut.isReleased);
	TC_clearButtons();
	TC_addButton(&testBut);
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	for (uint8_t col = 0; col < BSP_LCD_GetXSize()/testBut.xSize; col++){
		for(uint8_t row = 0; row < BSP_LCD_GetYSize()/testBut.ySize; row++){
			testBut = drawCustomTextLabel(testBut.x, testBut.y, testBut.xSize, testBut.ySize, "X", LCD_COLOR_BLACK, LCD_COLOR_GRAY);
			startTime = HAL_GetTick();
			testBut.isReleased = false;
			while(!testBut.isReleased){
				if (HAL_GetTick() - startTime > 10*1000){
					return TEST_FAIL;
				}
			}
			testBut.x = testBut.xSize*col;
			testBut.y = testBut.ySize*row;
			drawCustomTextLabel(testBut.x, testBut.y, testBut.xSize, testBut.ySize, "", LCD_COLOR_BLACK, LCD_COLOR_GREEN);
		}
	}
	testBut = drawCustomTextLabel(testBut.x, testBut.y, testBut.xSize, testBut.ySize, "X", LCD_COLOR_BLACK, LCD_COLOR_GRAY);
	startTime = HAL_GetTick();
	while(!testBut.isReleased){
		if (HAL_GetTick() - startTime > 10*1000){
			return TEST_FAIL;
		}
	}
	return PASS;
}
test_result_t PT_DrawMotorTest(){
	uint8_t yOffset;
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	yOffset = y1;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[29],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_SetFont(&Oxygen_Mono_16);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[30],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[31],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[32],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[23],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	testBut.x = 0;
	testBut.y = 0;
	testBut.xSize = BSP_LCD_GetXSize();
	testBut.ySize = BSP_LCD_GetYSize();
	
	startBut = drawCustomTextLabel(xBut3, yBut, xButSize, yButSize, "Start", LCD_COLOR_BLACK, LCD_COLOR_GRAY);
	TC_addButton(&startBut);
	while (!startBut.isReleased);
	
	sysParams.vars.pistonParams.curPoz = 0;
	uint8_t positions[] = {20, 100, 50, 0};
	uint8_t speeds[] = {50, 80, 100};
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	for(uint8_t speedPtr = 0; speedPtr < sizeof(speeds)/sizeof(speeds[0]);speedPtr++){
		for(uint8_t posPtr = 0; posPtr < sizeof(positions)/sizeof(positions[0]);posPtr++){
			PC_GoToPozWithSpeed(positions[posPtr], speeds[speedPtr]);
			while (!sysParams.vars.pistonParams.destComplete){
				if (HAL_GetTick() - oldHALTick > HalFreq/TestFreq){
					BSP_LCD_DrawBuffer_Start(x1,y1,390,BSP_LCD_GetFont()->height*2, LCD_COLOR_WHITE);
					BSP_LCD_SetBackColor(LCD_COLOR_WHITE);	
					xCur = 0;
					xCur += BSP_LCD_DisplayStringAt(x1,y1,"Destination position: ",LEFT_MODE);
					xCur += BSP_LCD_DisplayStringAt(x1+xCur,y1,intToStr(sysParams.vars.pistonParams.destPoz),LEFT_MODE);
					
					xCur = 0;
					xCur += BSP_LCD_DisplayStringAt(x1,y1 + BSP_LCD_GetFont()->height,"Current position: ",LEFT_MODE);
					xCur += BSP_LCD_DisplayStringAt(x1+xCur,y1 + BSP_LCD_GetFont()->height,intToStr(sysParams.vars.pistonParams.curPoz),LEFT_MODE);
					BSP_LCD_DrawBuffer_Stop();
				}
				if (sysParams.vars.error.flags.PistonFail || 
					sysParams.vars.error.flags.MotorFail ||
					sysParams.vars.error.flags.PistonStallFail){
					
					BSP_LCD_Clear(LCD_COLOR_WHITE);
					BSP_LCD_SetFont(&Oxygen_Mono_20);
					yOffset = y1;	
					BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[48],CENTER_MODE);
					yOffset += BSP_LCD_GetFont()->height;
					xCur = 0;	
					xCur += BSP_LCD_DisplayStringAt(x1 + xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[49],LEFT_MODE);
					BSP_LCD_DisplayStringAt(x1+xCur,yOffset,intToStr(sysParams.vars.pistonParams.destPoz),LEFT_MODE);
					
					yOffset += BSP_LCD_GetFont()->height;
					xCur = 0;	
					xCur += BSP_LCD_DisplayStringAt(x1 + xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[50],LEFT_MODE);
					BSP_LCD_DisplayStringAt(x1+xCur,yOffset,intToStr(sysParams.vars.pistonParams.curPoz),LEFT_MODE);
					yOffset += BSP_LCD_GetFont()->height;
						
					BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[51],CENTER_MODE);
					yOffset += BSP_LCD_GetFont()->height;
					failBut = drawCustomTextLabel(xBut3, yBut, xButSize, yButSize, "Fail", LCD_COLOR_BLACK, LCD_COLOR_RED);	
					TC_addButton(&failBut);
					while(1){
						if (failBut.isReleased){
							return TEST_FAIL;
						}
					}
				}
			}
		}
	}
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	passBut = drawCustomTextLabel(xBut3, yBut, xButSize, yButSize, "Pass", LCD_COLOR_BLACK, LCD_COLOR_GREEN);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,y1,ITEM_PROD_TEST_MAINSCREEN[47],CENTER_MODE);
	TC_addButton(&passBut);
	while(1){
		if (passBut.isReleased){
			return PASS;
		}
	}	
}

test_result_t PT_IOTest(){
		uint8_t yOffset;
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	yOffset = y1;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[33],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_SetFont(&Oxygen_Mono_16);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[34],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[35],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[36],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[37],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[23],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	
	
	startBut = drawCustomTextLabel(xBut3, yBut, xButSize, yButSize, "Start", LCD_COLOR_BLACK, LCD_COLOR_GRAY);
	TC_addButton(&startBut);
	while (!startBut.isReleased);
	TC_clearButtons();
	
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	yOffset = y1;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[38],CENTER_MODE);
	
	passBut = drawCustomTextLabel(xBut1, yBut, xButSize, yButSize, "Pass", LCD_COLOR_BLACK, LCD_COLOR_GREEN);
	failBut = drawCustomTextLabel(xBut5, yBut, xButSize, yButSize, "Fail", LCD_COLOR_BLACK, LCD_COLOR_RED);
	
	TC_clearButtons();
	TC_addButton(&passBut);
	TC_addButton(&failBut);
	bool output = false;
	uint32_t _100Hz_Hal_tick = 0, output_Hal_tick = HAL_GetTick();
	while(1){
		if (HAL_GetTick() - _100Hz_Hal_tick > HalFreq/TestFreq){
			uint8_t yOffset = y1;
			if (output){
				LL_GPIO_SetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
				LL_GPIO_SetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
			} else {
				LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
				LL_GPIO_ResetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
			}
			BSP_LCD_DrawBuffer_Start(x1,yOffset,390,BSP_LCD_GetFont()->height, LCD_COLOR_WHITE);
				xCur = 0;
				xCur += BSP_LCD_DisplayStringAt(x1,yOffset,ITEM_PROD_TEST_MAINSCREEN[41],LEFT_MODE);
				if(output){
					xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[39],LEFT_MODE);
				} else {
					xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[40],LEFT_MODE);
				}
			BSP_LCD_DrawBuffer_Stop();
			
			yOffset += BSP_LCD_GetFont()->height;
			BSP_LCD_DrawBuffer_Start(x1,yOffset,390,BSP_LCD_GetFont()->height, LCD_COLOR_WHITE);
				xCur = 0;
				xCur += BSP_LCD_DisplayStringAt(x1,yOffset,ITEM_PROD_TEST_MAINSCREEN[42],LEFT_MODE);
				if(sysParams.vars.status.flags.RelDCOn){
					xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[39],LEFT_MODE);
				} else {
					xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[40],LEFT_MODE);
				}
			BSP_LCD_DrawBuffer_Stop();
			
			yOffset += BSP_LCD_GetFont()->height;
			BSP_LCD_DrawBuffer_Start(x1,yOffset,390,BSP_LCD_GetFont()->height, LCD_COLOR_WHITE);
				xCur = 0;
				xCur += BSP_LCD_DisplayStringAt(x1,yOffset,ITEM_PROD_TEST_MAINSCREEN[43],LEFT_MODE);
				if(output){
					xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[39],LEFT_MODE);
				} else {
					xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[40],LEFT_MODE);
				}
			BSP_LCD_DrawBuffer_Stop();
			
			yOffset += BSP_LCD_GetFont()->height;
			BSP_LCD_DrawBuffer_Start(x1,yOffset,390,BSP_LCD_GetFont()->height, LCD_COLOR_WHITE);
				xCur = 0;
				xCur += BSP_LCD_DisplayStringAt(x1,yOffset,ITEM_PROD_TEST_MAINSCREEN[44],LEFT_MODE);
				if(sysParams.vars.status.flags.RelACOn){
					xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[39],LEFT_MODE);
				} else {
					xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[40],LEFT_MODE);
				}
			BSP_LCD_DrawBuffer_Stop();
			
			yOffset += BSP_LCD_GetFont()->height;
			BSP_LCD_DrawBuffer_Start(x1,yOffset,390,BSP_LCD_GetFont()->height, LCD_COLOR_WHITE);
				xCur = 0;
				xCur += BSP_LCD_DisplayStringAt(x1,yOffset,ITEM_PROD_TEST_MAINSCREEN[45],LEFT_MODE);
				if(!LL_GPIO_IsInputPinSet(DP_SWITCH_GPIO_Port, DP_SWITCH_Pin)){
					xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[39],LEFT_MODE);
				} else {
					xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[40],LEFT_MODE);
				}
			BSP_LCD_DrawBuffer_Stop();
			
			yOffset += BSP_LCD_GetFont()->height;
			BSP_LCD_DrawBuffer_Start(x1,yOffset,480-x1,BSP_LCD_GetFont()->height, LCD_COLOR_WHITE);
				BSP_LCD_SetBackColor(LCD_COLOR_WHITE);	
				xCur = 0;
				xCur += BSP_LCD_DisplayStringAt(x1,yOffset,ITEM_PROD_TEST_MAINSCREEN[46],LEFT_MODE);
				//xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,intToStr(FM_getFlowHzInt()),LEFT_MODE);
				float param = FM_getFlowHzFloat();
				if (param > 0){
		/*Float output*/
					uint32_t a = (int) param;
					xCur += BSP_LCD_DisplayStringAt(x1 + xCur,yOffset, intToStr(a), LEFT_MODE);
					xCur += BSP_LCD_DisplayStringAt(x1 + xCur,yOffset, ",", LEFT_MODE);
					param = param - a;
					param = param * 10;
					uint32_t b = (int) param;
					xCur += BSP_LCD_DisplayStringAt(x1 + xCur,yOffset, intToStr(b), LEFT_MODE);
					param = param - b;
					param = param * 10;
					b = (int) param;
					xCur += BSP_LCD_DisplayStringAt(x1 + xCur,yOffset, intToStr(b), LEFT_MODE);
				}
				else {
					xCur += BSP_LCD_DisplayStringAt(x1 + xCur,yOffset, "0.0", LEFT_MODE);
				}	
			BSP_LCD_DrawBuffer_Stop();
			 _100Hz_Hal_tick = HAL_GetTick();
		}
		if (HAL_GetTick() - output_Hal_tick > 2*1000){
			output = !output;
			
			output_Hal_tick = HAL_GetTick();
		}
		if (passBut.isReleased){
			return PASS;
		}
		if (failBut.isReleased){
			return TEST_FAIL;
		}
	}
}

test_result_t PT_MemTest(){
	uint32_t ramAdr = 0;
	uint8_t yOffset;
	rectSize = BSP_LCD_GetXSize()-2*x1;
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	yOffset = y1;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[52],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_SetFont(&Oxygen_Mono_16);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[53],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[54],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[23],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	
	startBut = drawCustomTextLabel(xBut3, yBut, xButSize, yButSize, "Start", LCD_COLOR_BLACK, LCD_COLOR_GRAY);
	TC_addButton(&startBut);
	while (!startBut.isReleased);
	
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	
	//FRAM Wtire test	
	ramWriteTestData[0] = 1;
	memTestFail = false;
	
	yOffset = y1;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[65],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;

	BSP_LCD_DrawRect(x1-1,yOffset-1,rectSize+2,rectWidth+2);
	uint32_t startTime = HAL_GetTick();
	uint16_t xCur = x1;
	//BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	//BSP_LCD_SetFont(&Oxygen_Mono_12);
	uint32_t framAdr = 0;
	while( framAdr < MAX_FRAM_ADR+1 && !memTestFail){
		memTestComplete = false;
		FP_Manual_FRAM_Write(&ramWriteTestData[0],framAdr,1,memInteractionComplete);
		while (!memTestComplete){
			if (HAL_GetTick() - startTime > 1000){
				memTestFail = true;
				memTestErr = FRAM_WRITE_ERR;
				break;
			}
		}
		startTime = HAL_GetTick();
		ramWriteTestData[0]++;
		if (ramWriteTestData[0] == 0) ramWriteTestData[0] = 1;
		//drawMemStatus(x1-1,yOffset-1,framAdr,MAX_FRAM_ADR);
		percent = rectSize*framAdr/MAX_FRAM_ADR;
		if (percent != oldPercent){
			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
			BSP_LCD_FillRect(xCur,yOffset,1,rectWidth);
			oldPercent = percent;
			xCur++;
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		}
		framAdr++;
	}
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	if (memTestFail){
		BSP_LCD_Clear(LCD_COLOR_WHITE);
		BSP_LCD_SetFont(&Oxygen_Mono_20);
		yOffset = y1;	
		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[55],CENTER_MODE);
		yOffset += BSP_LCD_GetFont()->height;
		xCur = 0;	
		xCur += BSP_LCD_DisplayStringAt(x1 + xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[56],LEFT_MODE);
		BSP_LCD_DisplayStringAt(x1+xCur,yOffset,intToStr(framAdr-1),LEFT_MODE);
		yOffset += BSP_LCD_GetFont()->height;				
		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[51],CENTER_MODE);
		yOffset += BSP_LCD_GetFont()->height;
		failBut = drawCustomTextLabel(xBut3, yBut, xButSize, yButSize, "Fail", LCD_COLOR_BLACK, LCD_COLOR_RED);	
		TC_addButton(&failBut);
		while(1){
			if (failBut.isReleased){
				return TEST_FAIL;
			}
		}
	}
	//FRAM Read test	
	ramWriteTestData[0] = 1;
	percent = 0; oldPercent = 0;
	memTestFail = false;
	//yOffset += rectWidth + 2 + smallText.height;
	yOffset += rectWidth + 2;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[66],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	rectSize = BSP_LCD_GetXSize()-2*x1;
	percent = 0; oldPercent = 0;
	startTime = HAL_GetTick();
	xCur = x1;
	BSP_LCD_DrawRect(x1-1,yOffset-1,rectSize+2,rectWidth+2);
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	framAdr = 0;
	while( framAdr < MAX_FRAM_ADR+1 && !memTestFail){
		memTestComplete = false;
		FP_Manual_FRAM_Read(&ramReadTestData[0],framAdr,1,memInteractionComplete);
		while (!memTestComplete){
			if (HAL_GetTick() - startTime > 1000){
				memTestFail = true;
				memTestErr = FRAM_READ_TIMEOUT_ERR;
				break;
			}
		}
		if (ramReadTestData[0] != ramWriteTestData[0]){
			memTestFail = true;
			memTestErr = FRAM_MISMATCH_ERR;
			break;
		}
		startTime = HAL_GetTick();
		ramWriteTestData[0]++;
		if (ramWriteTestData[0] == 0) ramWriteTestData[0] = 1;
		//drawMemStatus(x1-1,yOffset-1,framAdr,MAX_FRAM_ADR);
		percent = rectSize*framAdr/MAX_FRAM_ADR;
		if (percent != oldPercent){
			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
			BSP_LCD_FillRect(xCur,yOffset,1,rectWidth);
			oldPercent = percent;
			xCur++;
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		}
		framAdr++;
	}
	
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	if (memTestFail){
		BSP_LCD_Clear(LCD_COLOR_WHITE);
		BSP_LCD_SetFont(&Oxygen_Mono_20);
		yOffset = y1;	
		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[55],CENTER_MODE);
		yOffset += BSP_LCD_GetFont()->height;
		xCur = 0;
		if (memTestErr == FRAM_READ_TIMEOUT_ERR){
			xCur += BSP_LCD_DisplayStringAt(x1 + xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[57],LEFT_MODE);
			BSP_LCD_DisplayStringAt(x1+xCur,yOffset,intToStr(framAdr-1),LEFT_MODE);
			yOffset += BSP_LCD_GetFont()->height;				
			BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[51],CENTER_MODE);
			yOffset += BSP_LCD_GetFont()->height;
		} else {
			BSP_LCD_DisplayStringAt(x1 + xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[58],LEFT_MODE);
			yOffset += BSP_LCD_GetFont()->height;
			BSP_LCD_DisplayStringAt(x1 + xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[59],LEFT_MODE);
			xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,intToStr(ramWriteTestData[0]),LEFT_MODE);
			yOffset += BSP_LCD_GetFont()->height;		
			xCur = 0;			
			BSP_LCD_DisplayStringAt(x1 + xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[60],LEFT_MODE);
			xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,intToStr(ramReadTestData[0]),LEFT_MODE);
			yOffset += BSP_LCD_GetFont()->height;		
			BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[51],CENTER_MODE);
			yOffset += BSP_LCD_GetFont()->height;
		}
		failBut = drawCustomTextLabel(xBut3, yBut, xButSize, yButSize, "Fail", LCD_COLOR_BLACK, LCD_COLOR_RED);	
		TC_addButton(&failBut);
		while(1){
			if (failBut.isReleased){
				return TEST_FAIL;
			}
		}
	}
	//yOffset += rectWidth + 2 + smallText.height;
	yOffset += rectWidth + 2;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[70],CENTER_MODE);
	FP_ClearLog();
	LL_mDelay(10);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(0,yOffset,480,BSP_LCD_GetFont()->height);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	/**************************************************************************************/
	//RAM Wtire test
	/**************************************************************************************/
	
	failAddress = 0;
	memTestFail = false;
	percent = 0; oldPercent = 0;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[67],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;

	BSP_LCD_DrawRect(x1-1,yOffset-1,rectSize+2,rectWidth+2);
	startTime = HAL_GetTick();
	xCur = x1;
	
	//BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
  ramAdr = 0;
	uint8_t data = 0xAA;
	for (uint32_t i = 0; i < bufSize+1; i++){
		//ramWriteTestData[i] = (i==255) ?1:i + 1;
		ramWriteTestData[i] = data;
		data = ~data;
		ramReadTestData[i] = 0;
	}
	
	while(ramAdr < MAX_RAM_ADDRESS+1 && !memTestFail){
	
		memTestComplete = false;
		FP_Manual_RAM_Write(&ramWriteTestData,ramAdr,bufSize+1,memInteractionComplete);
		while (!memTestComplete){
			if (HAL_GetTick() - startTime > 2*1000){
				memTestFail = true;
				memTestErr = RAM_WRITE_ERR;
				break;
			}
		}
		startTime = HAL_GetTick();
		
		percent = rectSize*ramAdr/MAX_RAM_ADDRESS;
		if (percent != oldPercent){
			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
			BSP_LCD_FillRect(xCur,yOffset,1,rectWidth);
			oldPercent = percent;
			xCur++;
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		}
//		uint8_t textOffset = x1;
//		
//		BSP_LCD_DrawBuffer_Start(textOffset,yOffset + rectWidth + 2,rectSize,BSP_LCD_GetFont()->height,LCD_COLOR_WHITE);
//		textOffset += BSP_LCD_DisplayStringAt(textOffset,yOffset + rectWidth + 2, "Current address: ", LEFT_MODE);
//		textOffset += BSP_LCD_DisplayStringAt(textOffset,yOffset + rectWidth + 2, intToStr(ramAdr), LEFT_MODE);
//		textOffset += BSP_LCD_DisplayStringAt(textOffset,yOffset + rectWidth + 2, " from 16777215", LEFT_MODE);
//		
//		BSP_LCD_DrawBuffer_Stop();
		ramAdr += bufSize+1;
	}
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	if (memTestFail){
		BSP_LCD_Clear(LCD_COLOR_WHITE);
		BSP_LCD_SetFont(&Oxygen_Mono_20);
		yOffset = y1;	
		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[55],CENTER_MODE);
		yOffset += BSP_LCD_GetFont()->height;
		xCur = 0;	
		xCur += BSP_LCD_DisplayStringAt(x1 + xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[61],LEFT_MODE);
		BSP_LCD_DisplayStringAt(x1+xCur,yOffset,intToStr(ramAdr-1),LEFT_MODE);
		yOffset += BSP_LCD_GetFont()->height;				
		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[51],CENTER_MODE);
		yOffset += BSP_LCD_GetFont()->height;
		failBut = drawCustomTextLabel(xBut3, yBut, xButSize, yButSize, "Fail", LCD_COLOR_BLACK, LCD_COLOR_RED);	
		TC_addButton(&failBut);
		while(1){
			if (failBut.isReleased){
				return TEST_FAIL;
			}
		}
	}
	//RAM Read test	
	
	memTestFail = false;
	yOffset += rectWidth + 2;
	percent = 0; oldPercent = 0;
	//yOffset += rectWidth + 2 + smallText.height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[66],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	rectSize = BSP_LCD_GetXSize()-2*x1;
	BSP_LCD_DrawRect(x1-1,yOffset-1,rectSize+2,rectWidth+2);
	startTime = HAL_GetTick();
	xCur = x1;
	
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	ramAdr = 0;
	while( ramAdr < MAX_RAM_ADDRESS+1 && !memTestFail){
		memTestComplete = false;
		FP_Manual_RAM_Read(&ramReadTestData,ramAdr,bufSize+1,memInteractionComplete);
		while (!memTestComplete){
			if (HAL_GetTick() - startTime > 1000){
				memTestFail = true;
				memTestErr = RAM_READ_TIMEOUT_ERR;
				break;
			}
		}
		startTime = HAL_GetTick();
		for (uint32_t i = 0; i < bufSize+1 && !memTestFail; i++){
			if (ramReadTestData[i] != ramWriteTestData[i]){
				memTestFail = true;
				memTestErr = RAM_MISMATCH_ERR;
				failAddress = i;
				break;
			}
			ramReadTestData[i] = 0;
		}
		
		//drawMemStatus(x1-1,yOffset-1,ramAdr,MAX_RAM_ADDRESS);
		percent = rectSize*ramAdr/MAX_RAM_ADDRESS;
		if (percent != oldPercent){
			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
			BSP_LCD_FillRect(xCur,yOffset,1,rectWidth);
			oldPercent = percent;
			xCur++;
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		}
		ramAdr += bufSize+1;
	}
	
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	if (memTestFail){
		BSP_LCD_Clear(LCD_COLOR_WHITE);
		BSP_LCD_SetFont(&Oxygen_Mono_20);
		yOffset = y1;	
		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[55],CENTER_MODE);
		yOffset += BSP_LCD_GetFont()->height;
		xCur = 0;	
		if (memTestErr == RAM_READ_TIMEOUT_ERR){
			BSP_LCD_DisplayStringAt(x1 + xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[69],LEFT_MODE);
			yOffset += BSP_LCD_GetFont()->height;
			BSP_LCD_DisplayStringAt(x1 + xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[59],LEFT_MODE);
			xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,intToStr(ramWriteTestData[failAddress]),LEFT_MODE);
			yOffset += BSP_LCD_GetFont()->height;		
			xCur = 0;			
			BSP_LCD_DisplayStringAt(x1 + xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[60],LEFT_MODE);
			xCur += BSP_LCD_DisplayStringAt(x1+xCur,yOffset,intToStr(ramReadTestData[failAddress]),LEFT_MODE);
			yOffset += BSP_LCD_GetFont()->height;		
			BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[51],CENTER_MODE);
			yOffset += BSP_LCD_GetFont()->height;
		} else {
			xCur += BSP_LCD_DisplayStringAt(x1 + xCur,yOffset,ITEM_PROD_TEST_MAINSCREEN[62],LEFT_MODE);
			BSP_LCD_DisplayStringAt(x1+xCur,yOffset,intToStr(ramAdr + failAddress),LEFT_MODE);
			yOffset += BSP_LCD_GetFont()->height;				
			BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[51],CENTER_MODE);
			yOffset += BSP_LCD_GetFont()->height;
		}
		failBut = drawCustomTextLabel(xBut3, yBut, xButSize, yButSize, "Fail", LCD_COLOR_BLACK, LCD_COLOR_RED);	
		TC_addButton(&failBut);
		while(1){
			if (failBut.isReleased){
				return TEST_FAIL;
			}
		}
	}
	
	
	
	//FRAM and RAM Test
	
	yOffset += rectWidth + 2;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[70],CENTER_MODE);
	FP_ClearLog();
	LL_mDelay(10);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(0,yOffset,480,BSP_LCD_GetFont()->height);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	memTestFail = false;
	percent = 0; oldPercent = 0;
	//yOffset += rectWidth + 2 + smallText.height;
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[71],CENTER_MODE);
	yOffset += BSP_LCD_GetFont()->height;
	rectSize = BSP_LCD_GetXSize()-2*x1;
	BSP_LCD_DrawRect(x1-1,yOffset-1,rectSize+2,rectWidth+2);
	startTime = HAL_GetTick();
	xCur = x1;
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	ramAdr = 0;
	framAdr = 0;
	//for(uint8_t i = 0; i < FLASH_QUEUE_SIZE/4; i++){
 		FP_Manual_FRAM_Write(&ramWriteTestData,framAdr,bufSize+1,NULL);
		FP_Manual_RAM_Write(&ramWriteTestData,ramAdr,bufSize+1,NULL);
		FP_Manual_FRAM_Read(&ramReadTestData,framAdr,0x80,NULL);
		FP_Manual_RAM_Read(&ramReadTestData[0x80],ramAdr,0x80,NULL);
		framAdr += bufSize+1;
		ramAdr += bufSize+1;
		FP_Manual_FRAM_Write(&ramWriteTestData,framAdr,bufSize,NULL);
		FP_Manual_RAM_Write(&ramWriteTestData,ramAdr,bufSize,NULL);
		FP_Manual_FRAM_Read(&ramReadTestData,framAdr,0x80,NULL);
		FP_Manual_RAM_Read(&ramReadTestData[0x80],ramAdr,0x80,NULL);
		framAdr += bufSize+1;
		ramAdr += bufSize+1;
	//}
		while(!FP_isEmpty()){
			if (HAL_GetTick() - startTime > 5*1000){
				memTestFail = true;
				memTestErr = SIM_TIMEOUT;
				break;
			}
		}
		for(uint32_t i = 0; i < 0x100 && !memTestFail;i++){
			if (i < 0x80){
				if (ramReadTestData[i] != ramWriteTestData[i]){
					memTestFail = true;
					memTestErr = FRAM_MISMATCH_ERR;
				}
			} else {
				if (ramReadTestData[i] != ramWriteTestData[i - 0x80]){
					memTestFail = true;
					memTestErr = RAM_MISMATCH_ERR;
				}	
			}
		}
		
		
	if (memTestFail){
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_Clear(LCD_COLOR_WHITE);
		BSP_LCD_SetFont(&Oxygen_Mono_20);
		yOffset = y1;	
		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[55],CENTER_MODE);
		yOffset += BSP_LCD_GetFont()->height;
		xCur = 0;	

		switch (memTestErr){
			case (FRAM_MISMATCH_ERR):{
				xCur += BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[58],CENTER_MODE);
				break;
			}
			case (RAM_MISMATCH_ERR):{
				xCur += BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[69],CENTER_MODE);
				break;
			}
			case (SIM_TIMEOUT):{
				BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[72],CENTER_MODE);
				break;
			}
		}
		
		//BSP_LCD_DisplayStringAt(x1+xCur,yOffset,intToStr(ramAdr-1),LEFT_MODE);
		yOffset += BSP_LCD_GetFont()->height;		
		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,yOffset,ITEM_PROD_TEST_MAINSCREEN[51],CENTER_MODE);
		yOffset += BSP_LCD_GetFont()->height;
		failBut = drawCustomTextLabel(xBut3, yBut, xButSize, yButSize, "Fail", LCD_COLOR_BLACK, LCD_COLOR_RED);	
		TC_addButton(&failBut);
		while(1){
			if (failBut.isReleased){
				return TEST_FAIL;
			}
		}
	}
	/****/
	//PASSED
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	passBut = drawCustomTextLabel(xBut3, yBut, xButSize, yButSize, "Pass", LCD_COLOR_BLACK, LCD_COLOR_GREEN);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2,y1,ITEM_PROD_TEST_MAINSCREEN[47],CENTER_MODE);
	TC_addButton(&passBut);
	while(1){
		if (passBut.isReleased){
			return PASS;
		}
	}	
}


void drawMemStatus (uint32_t xS, uint32_t ySt, uint32_t adr, uint32_t maxAdr){
	uint32_t percent = 0;
	BSP_LCD_SetFont(&smallText);
	percent = rectSize*adr/maxAdr;
	uint8_t textOffset = xS+1;
	BSP_LCD_DrawBuffer_Start(xS,ySt,rectSize+2,rectWidth + 2 + BSP_LCD_GetFont()->height,LCD_COLOR_WHITE);
	BSP_LCD_DrawRect(xS,ySt,rectSize+2,rectWidth+2);
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_FillRect(xS+1,ySt+1,percent,rectWidth);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	textOffset += BSP_LCD_DisplayStringAt(textOffset,ySt + 1 + rectWidth + 2, "Current address: ", LEFT_MODE);
	textOffset += BSP_LCD_DisplayStringAt(textOffset,ySt + 1 + rectWidth + 2, intToStr(adr), LEFT_MODE);
	textOffset += BSP_LCD_DisplayStringAt(textOffset,ySt + 1 + rectWidth + 2, " from ", LEFT_MODE);
	textOffset += BSP_LCD_DisplayStringAt(textOffset,ySt + 1 + rectWidth + 2, intToStr(maxAdr-01), LEFT_MODE);
	BSP_LCD_DrawBuffer_Stop();


	BSP_LCD_SetFont(&bigText);
}
void memInteractionComplete(void){
	memTestComplete = true;
}
void printADCResult (float value, uint8_t* name, uint8_t* valName, test_result_t pass, uint8_t poz){
		
		BSP_LCD_DrawBuffer_Start(0,y1 + poz*BSP_LCD_GetFont()->height,xSize,ySize, LCD_COLOR_WHITE);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);	
		xCur = 0;
		xCur += BSP_LCD_DisplayStringAt(x1,y1 + poz*BSP_LCD_GetFont()->height,name,LEFT_MODE);
			
		if (pass == PASS){
			BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		} else {
			BSP_LCD_SetBackColor(LCD_COLOR_RED);
		}
		float param = value;
		if (param > 0){
/*Float output*/
			uint32_t a = (int) param;
			xCur += BSP_LCD_DisplayStringAt(x1 + xCur,y1 + poz*BSP_LCD_GetFont()->height, intToStr(a), LEFT_MODE);
			xCur += BSP_LCD_DisplayStringAt(x1 + xCur,y1 + poz*BSP_LCD_GetFont()->height, ",", LEFT_MODE);
			param = param - a;
			param = param * 10;
			uint32_t b = (int) param;
			xCur += BSP_LCD_DisplayStringAt(x1 + xCur,y1 + poz*BSP_LCD_GetFont()->height, intToStr(b), LEFT_MODE);
			param = param - b;
			param = param * 10;
			b = (int) param;
			xCur += BSP_LCD_DisplayStringAt(x1 + xCur,y1 + poz*BSP_LCD_GetFont()->height, intToStr(b), LEFT_MODE);
		}
		else {
			xCur += BSP_LCD_DisplayStringAt(x1 + xCur,y1 + poz*BSP_LCD_GetFont()->height, "0.0", LEFT_MODE);
		}	
		xCur += BSP_LCD_DisplayStringAt(x1 + xCur,y1 + poz*BSP_LCD_GetFont()->height,valName,LEFT_MODE);
		xCur += 10;
		//xCur += BSP_LCD_DisplayStringAt(x1 + xCur,y1 + poz*BSP_LCD_GetFont()->height,ITEM_PROD_TEST_MAINSCREEN[pass],LEFT_MODE);
    BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize(),y1 + poz*BSP_LCD_GetFont()->height,ITEM_PROD_TEST_MAINSCREEN[pass],RIGHT_MODE);
		BSP_LCD_DrawBuffer_Stop();
		
}

void printTestResult (uint8_t* name, test_result_t pass, uint8_t poz){
		
		BSP_LCD_DrawBuffer_Start(0,y1 + poz*BSP_LCD_GetFont()->height,xSize,ySize, LCD_COLOR_WHITE);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);	
		xCur = 0;
		xCur += BSP_LCD_DisplayStringAt(x1,y1 + poz*BSP_LCD_GetFont()->height,name,LEFT_MODE);
			
		if (pass == PASS){
			BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		} else if (pass == TEST_FAIL){
			BSP_LCD_SetBackColor(LCD_COLOR_RED);
		}
		
		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize(),y1 + poz*BSP_LCD_GetFont()->height,ITEM_PROD_TEST_MAINSCREEN[pass],RIGHT_MODE);

		BSP_LCD_DrawBuffer_Stop();
		
}
