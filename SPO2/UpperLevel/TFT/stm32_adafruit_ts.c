#include "main.h"
#include "ts.h"
#include "stm32_adafruit_ts.h"
#include "lcd\ili9486\ili9486.h"

extern TS_DrvTypeDef     *ts_drv;
extern int32_t            ts_cindex[];
static uint16_t          TsXBoundary, TsYBoundary;

int16_t kX;
int16_t kY;
int16_t bX;
int16_t bY;

/**
  * @brief  Initializes and configures the touch screen functionalities and 
  *         configures all necessary hardware resources (GPIOs, clocks..).
  * @param  XSize: The maximum X size of the TS area on LCD
  * @param  YSize: The maximum Y size of the TS area on LCD  
  * @retval TS_OK: if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_Init(uint16_t XSize, uint16_t YSize)
{
  uint8_t ret = TS_ERROR;

  /* Initialize x and y positions boundaries */
  TsXBoundary = XSize;
  TsYBoundary = YSize;

	if (fp->isLoaded != 1){
		SERV_TS_CALIB();
	} else {
		if (sysParam.LCD_ROTATION != ILI9486_ORIENTATION || sysParam.LCD_TYPE != COMPILED_LCD_TYPE){
			SERV_TS_CALIB();
		} else {
			kX = (int16_t)fp->params.ts_conf.kX;
			bX = (int16_t)fp->params.ts_conf.bX;
			kY = (int16_t)fp->params.ts_conf.kY;
			bY = (int16_t)fp->params.ts_conf.bY;
		}
	}
	
	
  if(ts_drv)
    ret = TS_OK;

  if(ret == TS_OK)
  {
    /* Initialize the LL TS Driver */
    ts_drv->Init(0);
  }

  return ret;
}

/**
  * @brief  Returns status and positions of the touch screen.
  * @param  TsState: Pointer to touch screen current state structure
  */
void BSP_TS_GetState(TS_StateTypeDef* TsState)
{
  uint16_t x, y;
  int32_t  x1, y1, x2, y2;
  for (uint8_t i = 0; i < TS_RESCAN_TIME; i++){
		TsState->TouchDetected = ts_drv->DetectTouch(0);
		LL_mDelay(10);
	}
  TsState->TouchDetected = ts_drv->DetectTouch(0);
  if(TsState->TouchDetected)
  {
    ts_drv->GetXY(0, &x, &y);
    x1 = x; y1 = y;
		TsState->X_t = x1;
		TsState->Y_t = y1;
//    x2 = (ts_cindex[1] * x1 + ts_cindex[2] * y1 + ts_cindex[3]) / ts_cindex[0];
//    y2 = (ts_cindex[4] * x1 + ts_cindex[5] * y1 + ts_cindex[6]) / ts_cindex[0];
		
//		#if ILI9486_ORIENTATION == 3
//		x2 = x1*kX/MOD - bX/MOD;
//		y2 = y1*kY/MOD - bY/MOD;
//		#endif
//		
//		#if ILI9486_ORIENTATION == 1
		x2 = (x1*kX)/MOD + bX;
		y2 = (y1*kY)/MOD + bY;
//		#endif
    if(x2 < 0)
      x2 = 0;
    else if(x2 >= TsXBoundary)
      x2 = TsXBoundary - 1;

    if(y2 < 0)
      y2 = 0;
    else if(y2 >= TsYBoundary)
      y2 = TsYBoundary - 1;
    
    TsState->X = x2;
    TsState->Y = y2;
  }
}

void BSP_TS_SetCalibCoef(int16_t kXe,int16_t kYe,int16_t bXe,int16_t bYe){
		kX = kXe;
		kY = kYe;
		bX = bXe;
		bY = bYe;
}

bool wasTouch(){
	if (tsState.TouchDetected == 1){
		tsState.TouchDetected = 0;
		return 1;
	} else {
		return 0;
	}
}