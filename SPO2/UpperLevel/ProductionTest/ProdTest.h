#ifndef _PROFTEST_H_
#define _PROFTEST_H_

/*Includes */
#include "main.h"

typedef enum {
	TEST_FAIL,
	PASS, 
	NOT_START
} test_result_t;

typedef struct{
	test_result_t inputVolt;
	test_result_t _3v3Volt;
	test_result_t _5Volt;
	test_result_t relVolt;
	test_result_t mot;
	test_result_t tft;
	test_result_t touch;
	test_result_t mem;
	test_result_t io;
} prod_test_t;

void ProductionTest();

#endif //_PROFTEST_H_