/**
 * Basic tests for queue data strucure
 *
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "queue.h"

void test_queue(void)
{
  printf("\n============================");
  printf("\n======== Queue Test ========");
  printf("\n============================\n\n");

  queue_p queue = queue_create(sizeof(int));

  int value;
  printf("Enqueue 4 items\n\n");
  value = 101;
  queue_enqueue(queue, &value);
  value = 201;
  queue_enqueue(queue, &value);
  value = 301;
  queue_enqueue(queue, &value);
  value = 401;
  queue_enqueue(queue, &value);

  for (int i = 0; i < 4; i++)
  {
    queue_peek(queue, &value);
    printf("Queue Peek: %d\n", value);

    queue_dequeue(queue, &value);
    printf("Dequeue item %d: %d\n\n", i + 1, value);
  }

  printf("Enqueue 4 items\n\n");
  value = 101;
  queue_enqueue(queue, &value);
  value = 201;
  queue_enqueue(queue, &value);
  value = 301;
  queue_enqueue(queue, &value);
  value = 401;
  queue_enqueue(queue, &value);
  
  queue_delete(queue);
  printf("Queue Deleted\n\n");
}