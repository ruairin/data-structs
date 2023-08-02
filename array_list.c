/**
 * array_list.h
 *
 * Implementation of functions for the array_list module
 *
 * @author ruairin
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "array_list_p.h"

// The initial capacity of the data array
#define INITIAL_CAPACITY 16

// The factor by which the array grows when
// its capacity is exceeded
#define CAPACITY_GROW_FACTOR 2
#define CAPACITY_SHRINK_FACTOR 0.5

#define DEBUG 0

/*
The list data type for the array_list module
*/
typedef struct list
{
  int *data;
  int size;
  int capacity;
  size_t element_size;
} *list_p;

/*
Creates and initialises a new list using the list_p type

Inputs:
  element_size - the size of the primitive data type to be stored in the list

Returns:
  A list_p (pointer to the newly created list) is returned

Throws:
  aborts if the memory allocations fail

*/
list_p list_create(size_t element_size)
{
  list_p list;
  list = (list_p)malloc(sizeof(struct list));
  assert(list != NULL && "Error in memory allocation");

  // From the user's viewpoint, the intial size of the list is 0
  // but internally the capacity is set via INITIAL_CAPACITY
  list->size = 0;
  list->capacity = INITIAL_CAPACITY;
  list->element_size = element_size;
  list->data = calloc(list->capacity, list->element_size);
  assert(list->data != NULL && "Error in memory allocation");

  return list;
}

/*
Gets the list item at the specified index

Inputs:
  list - pointer to an instance of the list type

Returns:
  The value of the item at the specified index

Throws:
  aborts if the specified index is outside the list bounds
  based on the current list size (list->size variable)

*/
int list_get(list_p list, int index)
{
  assert(!(_is_index_outside_bounds(list->size, index)) && "Error: list index out of range");
  return list->data[index];
}

/*
Gets the list item at the specified index

Inputs:
  list - pointer to an instance of the list type

Outputs:
  list - updated list->data array

Returns:
  Nothing

Throws:
  aborts if the specified index is outside the list bounds
  based on the current list size (list->size variable)

*/
void list_set(list_p list, int value, int index)
{
  assert(!(_is_index_outside_bounds(list->size, index)) && "Error: list index out of range");
  list->data[index] = value;
}

/*
Appends a new value to the end of the list by calling
list_insert with an index equal to the size of the list

Inputs:
  list - pointer to an instance of the list type
  value - The value to be appended

Returns:
  Nothing

Throws:
  list_insert aborts if there is insufficient capacity to append the item

*/
void list_append(list_p list, int value)
{
  list_insert(list, value, list->size);
}

/*
Inserts a new value at the specified index

Inputs:
  list - pointer to an instance of the list type
  value - The value to be inserted
  index - the list index to insert the value

Outputs:
  list - updated list->data array, updated list->size

Returns:
  Nothing

Throws:
  aborts if there is insufficient capacity to append the item or if the specified
  index is out of the bounds of the expanded list

*/
void list_insert(list_p list, int value, int index)
{
  // Check that there's capacity to insert another item
  if (_is_list_full(list))
  {
    _grow_array(list);
  }
  // Check that the specified index is not outside the bounds
  // of the list **following the update**. This allows items to appended
  // using e.g.
  // list_insert(my_list, my_value, list_size(my_list))
  // but doesnt allow inserting at an index that's not adjacent to the
  // current upper bound e.g.
  // list_insert(my_list, my_value, list_size(my_list) + 1)
  char error[64] = "";
  sprintf(error, "Error: Cannot add element at index %d.\n", index);
  assert(!(_is_index_outside_bounds(list->size + 1, index)) && error);

  // shift elements to the right
  // by looping backwards from the end
  for (int i = list->size; i > index; i--)
  {
    list->data[i] = list->data[i - 1];
  }
  list->data[index] = value;
  list->size++;
}

/*
Removed the item at the specified index

Inputs:
  list - pointer to an instance of the list type
  index - the list index of the item to remove

Outputs:
  list - updated list->data array, updated list->size

Returns:
  The value of the item that was removed

Throws:
  aborts if the specified index is out of the current bounds of the list

*/
int list_remove(list_p list, int index)
{
  if (_is_list_too_empty(list))
  {
    _shrink_array(list);
  }

  char error[64] = "";
  sprintf(error, "Error: Cannot remove element at index %d.\n", index);
  assert(!(_is_index_outside_bounds(list->size, index)) && error);

  // Save the item for returning
  int removed = list->data[index];

  // Shift elements to the left
  for (int i = index; i < list->size - 1; i++)
    list->data[i] = list->data[i + 1];

  // Set the last item to zero
  // This is now outside the list bounds
  // following the removal
  list->data[list->size] = 0;
  list->size--;
  return removed;
}

/*
Get the current size (i.e. the number of elements currently populated) of the list

Inputs:
  list - pointer to an instance of the list type

Returns:
  The current size of the list

*/
int list_size(list_p list)
{
  return list->size;
}

/*
Frees the memory allocated to list

Inputs:
  list - pointer to an instance of the list type

Returns:
  Nothing

*/
void list_delete(list_p list)
{
  if (list)
  {
    if (list->data)
      free(list->data);
    free(list);
  }
}

/*
Internal function to check if an index is out of bounds
i.e. index < 0 or index > size-1

Inputs:
  size - integer representing the size of the list
  index - The index to be checked

Returns:
  True if the index is out of bounds, false othewise

*/
bool _is_index_outside_bounds(int size, int index)
{
  if (index < 0 || index > (size - 1))
    return true;
  return false;
}

/*
Internal function to check if the list is full
i.e. there is no further capacity in the allocated
storage to add another item

Inputs:
  list - pointer to an instance of the list type

Returns:
  True if the list is full
  False otherwise

*/
bool _is_list_full(list_p list)
{
  if (list->size >= list->capacity)
    return true;
  return false;
}

/*
Internal function to check if the list is too empty
In this implementaion the list is too empty if the
actual number of elements is less than a quarter of the capacity
This is based on examples in data structures & algorithms
(goodrich)

Inputs:
  list - pointer to an instance of the list type

Returns:
  True if the list is too empty
  False otherwise

*/
bool _is_list_too_empty(list_p list)
{
  int quarter_capacity = list->capacity >> 2;
  if (list->size <= quarter_capacity && list->size > INITIAL_CAPACITY)
    return true;
  return false;
}

/*
Internal wrapper to grow array size.
The CAPACITY_GROW_FACTOR of 2 is based on
data structures & algorithms (goodrich)

Inputs:
  list - pointer to an instance of the list type

Returns:
  Nothing
*/
void _grow_array(list_p list)
{
  int new_capacity = list->capacity * CAPACITY_GROW_FACTOR;
  _resize(list, new_capacity);
}

/*
Internal wrapper to shrink array size.
The CAPACITY_SHRINK_FACTOR of 0.25 is based on
data structures & algorithms (goodrich)

Inputs:
  list - pointer to an instance of the list type

Returns:
  Nothing
*/
void _shrink_array(list_p list)
{
  int new_capacity = list->capacity * CAPACITY_SHRINK_FACTOR;
  _resize(list, new_capacity);
}

/*
Internal function to resize array.
The CAPACITY_SHRINK_FACTOR of 0.25 is based on
data structures & algorithms (goodrich)

Inputs:
  list - pointer to an instance of the list type
  capacity - the new capacity for the list->data array

Outputs:
  list - resized list->data array, updated list->capacity

Returns:
  Nothing

Throws:
  aborts if memory allocation fails
*/
void _resize(list_p list, int capacity)
{

  list->data = realloc(list->data, capacity * list->element_size);
  if (list->data == NULL)
  {
    fprintf(stderr, "Error: Cannot resize list (Memory allocation failed).\n");
    abort();
  }
  list->capacity = capacity;

#if DEBUG
  printf("Resize: Current capacity %d\n", capacity);
#endif
}
