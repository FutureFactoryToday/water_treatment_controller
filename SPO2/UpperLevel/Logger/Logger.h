#ifndef _LOGGER_H_
#define _LOGGER_H_

/*Includes*/
#include "main.h"

/*Typedef*/
typedef struct {
	uint32_t timeStamp;
	uint32_t cause;
	uint32_t param;
} log_data_t;

typedef enum {
	FAIL = 1,
	EVENT,
	WATER_SPEED,
	USAGE
} log_type_t;


/*Extern parameters*/
extern log_data_t displayData[];
/*Prototypes*/
uint8_t LOG_Init();
uint8_t LOG_Interrupt(void);
uint8_t LOG_GetErrors(uint16_t startEntry);
uint8_t LOG_GetWash(uint16_t startEntry);
uint8_t LOG_GetWaterUsage(uint16_t startEntry);
uint8_t LOG_GetWaterSpeed(uint16_t startEntry);
void LOG_Test();
#endif //_LOGGER_H_