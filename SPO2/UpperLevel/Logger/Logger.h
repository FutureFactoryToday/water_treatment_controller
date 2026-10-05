#ifndef _LOGGER_H_
#define _LOGGER_H_

/*Includes*/
#include "main.h"

/*Typedef*/
typedef struct {
	uint32_t timeStamp;
	uint32_t cause;
	uint32_t param;
	uint32_t reserv;
} log_data_t;

typedef enum {
	FAIL = 1,
	EVENT,
	WATER_SPEED,
	USAGE
} log_type_t;

typedef struct{
	uint8_t* text;
	uint32_t data;
} ulog_entry_t;

typedef enum {
	MSG = 0xA3,
	STR = 0x5A,
	DATA = 0x11
} ulog_msg_type_t;

typedef struct {
	ulog_msg_type_t type;
	uint8_t* data;
	uint32_t size;
}ulog_msg_t;

typedef struct {
	ulog_msg_t msgs[UART_LOG_Q_SIZE];
	uint8_t head;
	uint8_t tail;
	bool empty;
	bool full;
} ulog_queue_t;

/*Extern parameters*/
extern volatile log_data_t displayData[];
extern uint8_t memBuf[128];
/*Prototypes*/
uint8_t LOG_Init(void);
uint8_t LOG_Interrupt(void);
uint8_t LOG_GetErrors(uint16_t startEntry);
uint8_t LOG_GetWash(uint16_t startEntry);
uint8_t LOG_GetWaterUsage(uint16_t startEntry);
uint8_t LOG_GetWaterSpeed(uint16_t startEntry);

bool UL_LogText (uint8_t* text, uint32_t data);

bool UL_LogCond (void);

//void UL_Start (void);

bool UL_StartMemoryRead(uint32_t adr);
void LOG_Test(void);
#endif //_LOGGER_H_
