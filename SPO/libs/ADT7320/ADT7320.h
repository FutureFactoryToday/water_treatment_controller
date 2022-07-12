#ifndef _ADT7320_H_
	#define _ADT7320_H_
	#include <stdint.h>
	#include "spi.h"
	#include "gpio.h"
	
	
		
		
	#define ADT_TEMP_VAL_REG_ADR 0x02
		
	#define ADT_ID_REG_ADR	0x03
		#define ADT_ID_DEFAULT 0xC3
		
	#define ADT_T_CRIT_REG_ADR 0x04
	#define ADT_T_HYST_REG_ADR 0x05
	#define ADT_T_HIGH_REG_ADR 0x06
	#define ADT_T_LOW_REG_ADR 0x07
	
	
typedef struct {
	uint8_t status;
	int16_t temp;
} ADT_TEMP_t;

/* Prototypes */
int ADT_INIT (void);
int16_t ADT_SIMPLE_READ_DATA(uint8_t adr);
ADT_TEMP_t ADT_READ_TEMP (void);
void ADT_WRITE_DATA(uint8_t adr, uint16_t data);
#endif //_ADT7320_H_
