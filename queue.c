/**
 * queue.c
 *
 * Implementation of functions for the queue module
 *
 * @author ruairin
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
The queue is based on a linked data structure.
_element is a (private) data type representing a queue element
*/
typedef struct _element
{
  char *data; // The data stored in this the element
  struct _element *next; // pointer to the next element 
} *_element_p;


/*
The queue data type for the queue module
*/
typedef struct queue
{
  _element_p head; // top of the queue
  _element_p tail; // back of the queue
  int length;
  size_t element_size;
} *queue_p;

/*
Creates and initialises a new empty queue using the queue_p type

Inputs:
  element_size - the size of the primitive data type to be stored in the queue

Returns:
  A queue_p (pointer to the newly created queue)

Throws:
  aborts if the memory allocations fail

*/

queue_p queue_create(size_t element_size)
{
  queue_p queue;

  queue = (queue_p)malloc(sizeof(struct queue));
  assert(queue != NULL && "Error in memory allocation");

  queue->head = NULL;
  queue->tail = NULL;
  queue->length = 0;
  queue->element_size = element_size;

  return queue;
}

/*
Get the value of the item at the top/head of the queue

Inputs:
  queue - pointer to an instance of the queue type
  value - pointer to a variable containing the value of the item to be enqueued

Returns:
  Nothing

Throws:
  aborts on memory allocation error

*/

void queue_peek(queue_p queue, void *out)
{
  if (queue->head)
  {
    memcpy(out, queue->head->data, queue->element_size);
  }
  else
  {
    out = NULL;
  }
}

/*
Enqueue an item at the back/tail of the queue

Inputs:
  queue - pointer to an instance of the queue type
  value - pointer to a variable containing the value of the item to be enqueued

Returns:
  Nothing

Throws:
  aborts on memory allocation error

*/
void queue_enqueue(queue_p queue, void *value)
{
  _element_p new_element;
  new_element = (_element_p)malloc(sizeof(struct _element));
  assert(new_element != NULL && "Error in memory allocation");

  new_element->data = malloc(queue->element_size);
  assert(new_element->data != NULL && "Error in memory allocation");

  new_element->next = NULL;
  memcpy(new_element->data, value, queue->element_size);

  if (queue->head == NULL)
  {
    queue->head = new_element;
  }
  else
  {
    queue->tail->next = new_element;
  }
  queue->tail = new_element;
  queue->length++;
}

/*
Dequeue the item at the head of the queue

Inputs:
  queue - pointer to an instance of the queue type
  out - pointer to a variable containing the value of the dequeued item

Outputs:
  out - pointer to a variable containing the value of the dequeued item
        (NULL if the queue is empty)

Returns:
  Nothing

*/
void queue_dequeue(queue_p queue, void *out)
{
  if (queue->head != NULL)
  {
    memcpy(out, queue->head->data, queue->element_size);

    _element_p temp = queue->head->next;
    if (queue->head->data != NULL)
    {
      free(queue->head->data);
    }
    free(queue->head);
    queue->head = temp;
    queue->length--;
  }
  else
  {
    out = NULL;
  }
}

/*
Frees the memory allocated to queue

Inputs:
  queue - pointer to an instance of the list type

Returns:
  Nothing

*/
void queue_delete(queue_p queue)
{
  if (queue)
  {
    if (queue->head)
    {
      _element_p current = queue->head;
      while (current)
      {
        _element_p next = current->next;
        free(current->data);
        free(current);
        current = next;
      }
    }
    free(queue);
  }
}
