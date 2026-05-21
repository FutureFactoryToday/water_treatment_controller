#include "filter.h"

filter_t* initFilterStruct (filter_t* fil, uint16_t start_value, uint8_t devider)
{
	fil->fvalue = start_value;
	fil->del = 0;
	fil->div = devider;
	fil->big_val = fil->fvalue * fil->div;
	fil->filtered = 0;
	return fil;
}

uint32_t filter (filter_t* fil, uint32_t input){
	
	fil->del = input - fil->fvalue;
	fil->big_val = fil->big_val + fil->del;
	fil->fvalue = fil->big_val/fil->div;
	
	isFiltered(fil,input);
	
	return fil->fvalue;
}

uint8_t isFiltered (filter_t* fil, uint32_t inp)
{
	uint16_t mod_del = (fil->del > 0)? fil->del: (- fil->del);
	if (mod_del < inp/100 )
	{
		fil->filtered = 1;
	}
	else 
	{
		fil->filtered = 0;
	}
	return fil->filtered;
}
