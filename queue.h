/**
 * @file queue.h
 * @brief Public function prototypes for the queue module
 *
 * Function prototypes required to use the queue module
 *
 * @author ruairin
 */

#include <stdlib.h>
#include "queue_p.h"

#ifndef QUEUE
#define QUEUE

/**
 * @brief Data type represeting the queue
 */
typedef struct queue *queue_p;

/**
 * @brief create and initialise a new queue
 *
 * The initial size of the queue is zero.
 * Example usage to create a list of ints:
 * queue_p my_queue;
 * my_queue = queue_create(sizeof(int));
 *
 * @param[in] element_size The size of the data type to be stored in the queue
 * @return A queue_p (i.e. pointer to the queue data type) to the created queue
 */
queue_p queue_create(size_t element_size);

/**
 * @brief get the value at the top/head of the queue
 *
 * @param[in] queue A pointer to an instance of the queue_p data type
 * @param[inout] out pointer to a variable storing the value at the top of the queue
 * @return nothing
 */
void queue_peek(queue_p queue, void *out);

/**
 * @brief add a new value to the back/tail of the queue
 *
 * @param[in] queue A pointer to an instance of the queue_p data type
 * @param[in] out pointer to a variable storing the value to be added to the queue
 * @return nothing
 */
void queue_enqueue(queue_p queue, void *value);

/**
 * @brief Remove the item at the top/head of the queue
 *
 * @param[in] queue A pointer to an instance of the queue_p data type
 * @param[inout] out pointer to a variable containing the value of the item that was dequeued
 * @return nothing
 */
void queue_dequeue(queue_p queue, void *out);

/**
 * @brief Delete the queue and deallocate memory
 *
 * @param[in] queue A pointer to an instance of the queue_p data type
 * @return nothing
 */
void queue_delete(queue_p queue);

#endif