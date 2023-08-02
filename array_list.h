/**
 * @file array_list.h
 * @brief Public function prototypes for the array_list module
 *
 * Function prototypes required to use the array_list module
 *
 * @author ruairin
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef ARRAY_LIST
#define ARRAY_LIST

/**
 * @brief The list data type to be used with the array_list module
 */
typedef struct list *list_p;

/**
 * @brief create and initialise a new list
 *
 * The initial size of the list is zero.
 * Example usage to create a list of ints:
 * list_p my_list;
 * my_list = list_create(sizeof(int));
 *
 * @param[in] element_size The size of the data type to be stored in the list
 * @return A list_p (i.e. pointer to the list data type) to the created list 
 */
list_p list_create(size_t element_size);

/**
 * @brief append an item to the list
 * 
 * @param[in] list A pointer to an instance of the list_p data type
 * @param[in] value The value to be appended
 * @param[out] list Updated list
 * @return nothing
*/
void list_append(list_p list, void* value);

/**
 * @brief insert an item in the list at the specified index
 * 
 * @param[in] list A pointer to an instance of the list_p data type
 * @param[in] value Pointer to the value to be appended
 * @param[in] index The list index where the item should be inserted
 * @param[out] list Updated list
 * @return nothing
*/
void list_insert(list_p list, void* value, int index);

/**
 * @brief Get the current size (number of elements in use) of the list 
 * @param[in] list A pointer to an instance of the list_p data type
 * @return An integer, the size of the list
*/
int list_size(list_p list);

/**
 * @brief get the value of the item at the specified index
 * @param[in] list A pointer to an instance of the list_p data type
 * @param[in] index The list index of the item to get
 * @param[inout] out Address of a variable to store the result
 * @return The value at the specified index
*/
void list_get(list_p list, int index, void *out);

/**
 * @brief Set the value of the item at the specified index
 * @param[in] list A pointer to an instance of the list_p data type
 * @param[in] value pointer to the value to set at index 
 * @param[in] index The list index of the item to set
 * @param[out] list Updated data array in list->data
 * @return nothing
*/
void list_set(list_p list, void* value, int index);

/**
 * @brief Remove the item at the specified list index
 * @param[in] list A pointer to an instance of the list_p data type
 * @param[in] index The list index of the item to remove
 * @param[out] list Updated data array in list->data, updated list->size
 * @return The value of the item that was removed
*/
void list_remove(list_p list, int index);

/**
 * @brief Delete the list and free any memory allocated 
 * @param[in] list A pointer to an instance of the list_p data type
 * @return Nothing
*/
void list_delete(list_p list);


#endif