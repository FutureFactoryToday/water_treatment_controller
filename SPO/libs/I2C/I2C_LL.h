#ifndef _I2C_LINKEDLIST_H_
#define _I2C_LINKEDLIST_H_
#include <stdlib.h>

typedef struct {
	void* next;
	void (*func) (void);
} task_node_t;


void* addNodeLL (void* tail, int size);

#endif //_I2C_LINKEDLIST_H_
