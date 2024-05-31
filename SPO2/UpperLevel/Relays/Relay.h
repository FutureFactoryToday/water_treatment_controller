#ifndef _RELAYS_H_
#define _RELAYS_H_

/*Includes*/
#include "main.h"
/*Typedef*/
typedef struct{
	unsigned rabPoz:1;
	unsigned forwardWash:1;
	unsigned backwash:1;
	unsigned saltering:1;
	unsigned filling:1;
} relay_enable_t;

typedef enum {
	HALT,
	WASH,
	PULSE,
	NEIGHBOR
} dc_relay_work_t;

typedef struct{
	uint8_t workType;
	relay_enable_t pozEnable;
}relay_t;
/*Extern parameters*/

/*Prototypes*/
void RELAY_DC_CYCLE(void);
void RELAY_AC_CYCLE(void);
void RELAY_Init(void);
void RELAY_DC_ChangeType(dc_relay_work_t type);
#endif //_RELAYS_H_