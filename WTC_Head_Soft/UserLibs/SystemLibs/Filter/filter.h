#ifndef _FILTER_H_
#define _FILTER_H_

#include "stdint.h"

	typedef struct 
	{
		uint16_t fvalue;
		int32_t del;
		uint8_t div;
		uint32_t big_val;
		uint8_t filtered;
	} filter_t;
														 
	uint16_t filter (filter_t* fil, uint16_t input);
	filter_t* initFilterStruct (filter_t* fil, uint16_t start_value, uint8_t devider);
	uint8_t isFiltered (filter_t* fil, uint16_t inp); 
#endif //_FILTER_H_
