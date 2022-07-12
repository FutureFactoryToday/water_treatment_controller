/**
  ******************************************************************************
  * @file    LinkedList.h
  * @brief   This file contains all the function prototypes for
  *          the LinkedList.c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _LinkedList_H_
#define _LinkedList_H_

/*Includes */
#include "main.h"

/*Public defines */
typedef struct {
	void* node;
	void* next;
} node_t;
/*Global params*/

/*Prototypes */
void* addNode (node_t* ll, void* node, int size);
void* findNode (node_t* ll, void* node);
void* deleteNode (node_t* ll, void* node);

#endif /* __LinkedList_H__ */

