/*
 * ring_fifo.c
 *
 *  Created on: Dec 8, 2025
 *      Author: ricky.siah
 */

#include <string.h>
#include "ring_fifo.h"

int FIFO_Capacity = 0;
/**
 * @brief Initializes the single-threaded ring buffer.
 * @param rb Pointer to the ring buffer structure.
 * @param capacity The maximum number of items the buffer can hold.
 * @return 0 on success, -1 on failure.
 */
int rbst_init(RING_Fifo_t* rb, uint8_t *buffer, int capacity)
{
	FIFO_Capacity = capacity;
    rb->capacity = capacity;
    rb->buffer = buffer;
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;

    return 0;
}

/**
 * @brief Destroys the ring buffer and frees allocated memory.
 */
void rbst_destroy(RING_Fifo_t* rb)
{
    rb->capacity = 0;
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

/**
 * @brief Checks if the buffer is full.
 */
int rbst_is_full(RING_Fifo_t* rb)
{
    return rb->count == rb->capacity;
}

/**
 * @brief Checks if the buffer is empty.
 */
int rbst_is_empty(RING_Fifo_t* rb)
{
    return rb->count == 0;
}

/**
 * @brief Pushes an item into the buffer (non-blocking).
 * @param rb Pointer to the ring buffer structure.
 * @param item The item to push.
 * @return 0 on success, -1 if the buffer is full (EAGAIN).
 */
int rbst_push(RING_Fifo_t* rb, uint8_t item)
{
    if (rbst_is_full(rb))
    {
        return -1;
    }

    rb->buffer[rb->head] = item;
    rb->head = (rb->head + 1) % rb->capacity;
    rb->count++;

    return 0;
}

int rbst_num_push(RING_Fifo_t* rb, uint8_t* item, int num)
{
    if (rbst_count(rb) < num)
    {
        return -1;
    }

    int space_to_end = FIFO_Capacity - rb->tail;

    if (num <= space_to_end)
    {
        // Case 1: Data is contiguous
        memcpy(item, &rb->buffer[rb->tail], num);
        rb->tail = (rb->tail + num) % FIFO_Capacity;
    }
    else
    {
        // Case 2: Data wraps around

        // Copy the first segment (from tail to physical end)
        memcpy(item, &rb->buffer[rb->tail], space_to_end);

        // Copy the remaining segment from the start of the buffer
        int remaining_bytes = num - space_to_end;
        memcpy(item + space_to_end, &rb->buffer[0], remaining_bytes);

        // The new tail index is simply the remaining bytes count
        rb->tail = remaining_bytes;
    }

    rb->count -= num;
    return 0;
}

/**
 * @brief Pops an item from the buffer (non-blocking).
 * @param rb Pointer to the ring buffer structure.
 * @param item Pointer to store the popped item.
 * @return 0 on success, -1 if the buffer is empty (EAGAIN).
 */
int rbst_pop(RING_Fifo_t* rb, uint8_t* item)
{
    if (rbst_is_empty(rb))
    {
        return -1;
    }

    *item = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->capacity;
    rb->count--;

    return 0;
}

/**
 * @brief Returns the current number of items in the buffer.
 */
int rbst_count(RING_Fifo_t* rb)
{
    return rb->count;
}

