/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_ADAFRUIT_TS_H
#define __STM32_ADAFRUIT_TS_H

#ifdef __cplusplus
 extern "C" {
#endif   
   


typedef struct
{
  uint16_t TouchDetected;
  uint16_t X;
  uint16_t Y;
  uint16_t Z;
	uint32_t X_t;
	uint32_t Y_t;
}TS_StateTypeDef;

typedef struct {
	uint32_t kX;
	uint32_t kY;
	uint32_t bX;
	uint32_t bY;
} stored_ts_conf_t;

#define TS_SWAP_NONE                    0x00
#define TS_SWAP_X                       0x01
#define TS_SWAP_Y                       0x02
#define TS_SWAP_XY                      0x04

#define Y_MAX 3900
#define X_MAX 3900
#define Y_MIN 280
#define X_MIN 400

#define MOD 1024



typedef enum 
{
  TS_OK       = 0x00,
  TS_ERROR    = 0x01,
  TS_TIMEOUT  = 0x02
}TS_StatusTypeDef;

uint8_t BSP_TS_Init(uint16_t XSize, uint16_t YSize);
void    BSP_TS_GetState(TS_StateTypeDef *TsState);
void BSP_TS_SetCalibCoef(int16_t kXe,int16_t kYe,int16_t bXe,int16_t bYe);
void BPS_TS_Calibrate(void);


#ifdef __cplusplus
}
#endif

#endif /* __STM32_ADAFRUIT_TS_H */
