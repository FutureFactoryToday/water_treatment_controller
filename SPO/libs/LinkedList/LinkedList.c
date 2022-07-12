/**
  ******************************************************************************
  * @file           : LinkedList.c
  * @brief          : 
  ******************************************************************************
  * @attention
  *
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "LinkedList.h"
#include "stdlib.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void* findTail (node_t* ll);
/* Private user code ---------------------------------------------------------*/
void* addNode (node_t* ll, void* node, int size){
	node_t* tail = findTail(ll);
	if (tail == NULL) {
		ll = node;
	} 
	else {
		tail->next = node;
	}
	return ll;
}

void* findNode (node_t* ll, void* node){
	
	return NULL;
}

void* deleteNode (node_t* ll, void* node){
	
	return NULL;
}

void* findTail(node_t* ll){
	if (ll == NULL) {
		return NULL;
	} else {
		while(ll->next != NULL){
			ll = ll->next;
		}
		return ll;
	}
}
