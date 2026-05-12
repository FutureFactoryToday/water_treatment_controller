#ifndef _W25_H_
#define _W25_H_

/*Includes*/
#include "main.h"

/*Typedef*/
typedef struct{
	unsigned BUSY:1;
	unsigned WEL:1;
	unsigned BP0:1;
	unsigned BP1:1;
	unsigned BP2:1;
	unsigned TB:1;
	unsigned SEC:1;
	unsigned SRP0:1;
} w25_status1_bits_t;

typedef struct{
	unsigned SRP1:1;
	unsigned QE:1;
	unsigned R0:1;
	unsigned LB1:1;
	unsigned LB2:1;
	unsigned LB3:1;
	unsigned CMP:1;
	unsigned SUS:1;
} w25_status2_bits_t;

typedef struct{
	unsigned R1:1;
	unsigned R2:1;
	unsigned WPS:1;
	unsigned R4:1;
	unsigned R5:1;
	unsigned DRV0:1;
	unsigned DRV1:1;
	unsigned HOLD_RES:1;
} w25_status3_bits_t;

typedef union{
	uint32_t all;
	w25_status1_bits_t bits;
} w25_status1_t;

typedef union{
	uint32_t all;
	w25_status2_bits_t bits;
} w25_status2_t;

typedef union{
	uint32_t all;
	w25_status3_bits_t bits;
} w25_status3_t;
/*Extern parameters*/
extern flash_driver_t W25_driver;
extern w25_status1_t w25Status;
extern w25_status2_t w25Status2;
extern w25_status3_t w25Status3;

/*Prototypes*/

void manualWriteData(uint32_t addr, uint8_t data);
void W25_Process(void);   /* вызывать из основного цикла */
#endif //_W25_H_