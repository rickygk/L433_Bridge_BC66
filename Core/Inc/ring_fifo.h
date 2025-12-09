/*
 * ring_fifo.h
 *
 *  Created on: Dec 8, 2025
 *      Author: ricky.siah
 */

#ifndef INC_RING_FIFO_H_
#define INC_RING_FIFO_H_

#include <stdint.h>

typedef struct {
    uint8_t* buffer;
    int capacity;	// Max items
    int head;     	// Write index
    int tail;     	// Read index
    int count;    	// Current number of items
} RING_Fifo_t;

// Function Prototypes
int rbst_init(RING_Fifo_t* rb, uint8_t *buffer, int capacity);
void rbst_destroy(RING_Fifo_t* rb);
int rbst_push(RING_Fifo_t* rb, uint8_t item);
int rbst_pop(RING_Fifo_t* rb, uint8_t* item);
int rbst_count(RING_Fifo_t* rb);
int rbst_is_full(RING_Fifo_t* rb);
int rbst_is_empty(RING_Fifo_t* rb);

#endif /* INC_RING_FIFO_H_ */
