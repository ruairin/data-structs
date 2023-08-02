/**
 * array_list_p.h
 * 
 * Private header file for array_list module
 * 
 * @author ruairin
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "array_list.h"

#ifndef ARRAY_LIST_P
#define ARRAY_LIST_P

bool _is_index_outside_bounds(int size, int index);
bool _is_list_full(list_p list);
bool _is_list_too_empty(list_p list);
void _grow_array(list_p list);
void _shrink_array(list_p list);
void _resize(list_p list, int capacity);

#endif