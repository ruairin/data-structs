/**
 * Basic tests for data structures modules
 *
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "array_list.h"

void print_list(list_p list, int start, int end);
void strcat_dynamic(char *dest, char *src, int *dest_len);
void grow_str(char *str, int *current_length, int required_length);

#define TYPE int
#define PRINT_TYPE "%d"

int main(void)
{
  TYPE value = 0;

  list_p my_list;
  my_list = list_create(sizeof(TYPE));
  printf("List created\n\n");

  printf("--- Append ---\n");
  value = 10;
  list_append(my_list, &value);
  value = 20;
  list_append(my_list, &value);
  value = 30;
  list_append(my_list, &value);

  list_get(my_list, 0, &value);
  printf(PRINT_TYPE "\n", value);

  printf("List Contents:");
  print_list(my_list, 0, list_size(my_list) - 1);
  printf("List Size: %d\n", list_size(my_list));

  printf("\n--- Remove ---\n");
  printf("Remove Item at Index 2\n");
  list_remove(my_list, 2);
  printf("List Contents:");
  print_list(my_list, 0, list_size(my_list) - 1);
  printf("List Size: %d\n", list_size(my_list));

  printf("Remove Item at Index 0\n");
  list_remove(my_list, 0);
  printf("List Contents:");
  print_list(my_list, 0, list_size(my_list) - 1);
  printf("List Size: %d\n", list_size(my_list));

  printf("\n--- Insert ---\n");
  printf("Insert Item 100 at Index 1\n");
  value = 100;
  list_insert(my_list, &value, 1);
  printf("List Contents:");
  print_list(my_list, 0, list_size(my_list) - 1);
  printf("List Size: %d\n", list_size(my_list));

  printf("Insert Item 500 at Index 0\n");
  value = 500;
  list_insert(my_list, &value, 0);
  printf("List Contents:");
  print_list(my_list, 0, list_size(my_list) - 1);
  printf("List Size: %d\n", list_size(my_list));

  printf("Insert Item 500 at End of List\n");
  value = 500;
  list_insert(my_list, &value, list_size(my_list));
  printf("List Contents:");
  print_list(my_list, 0, list_size(my_list) - 1);
  printf("List Size: %d\n", list_size(my_list));

  printf("\n--- Set ---\n");
  printf("Set Item at Index 0 to -1000\n");
  value = -1000;
  list_set(my_list, &value, 0);
  printf("List Contents:");
  print_list(my_list, 0, list_size(my_list) - 1);
  printf("List Size: %d\n", list_size(my_list));

  printf("Set Item at Index 3 to -1000\n");
  value = -1000;
  list_set(my_list, &value, list_size(my_list) - 1);
  printf("List Contents:");
  print_list(my_list, 0, list_size(my_list) - 1);
  printf("List Size: %d\n", list_size(my_list));

  printf("\n--- Append ~1000 items ---\n");
  for (int i = 0; i < 1000; i++)
  {
    TYPE val = i;
    list_append(my_list, &val);
  }
  printf("End of List:\n");
  print_list(my_list, list_size(my_list) - 20, list_size(my_list) - 1);

  printf("\n--- Remove ~1000 items ---\n");
  for (int i = list_size(my_list) - 1; i > 10; i--)
  {
    list_remove(my_list, i);
  }
  printf("List Contents:\n");
  print_list(my_list, 0, list_size(my_list) - 1);

  // These fail on out of index out-of-bounds assertions
  // list_remove(my_list, 1000);
  // list_insert(my_list, 100, 1000);
  // list_set(my_list, -1000, 1000);
  // list_get(my_list, -1);

  list_delete(my_list);
  return 0;
}

/**
 * Print list contents
 *
 * Inputs:
 *  list - the list whose contents are to be printed
 *  start - the first index to be printed
 *  end - the last index to be printed
 *
 * Outputs:
 *  Nothing
 *
 * Returns:
 *  Nothing
 */
void print_list(list_p list, int start, int end)
{
  int buf_size = 256;
  char *buf = malloc(buf_size * sizeof(char));
  strcpy(buf, "");

  // temporary string for appending to buf
  char tmp[64] = "";

  // If the start of the array is being printed,
  // show the left bracket otherwise show dots
  if (start == 0)
    strcpy(tmp, "[");
  else
    strcpy(tmp, "..., ");

  strcat_dynamic(buf, tmp, &buf_size);

  for (int i = start; i <= end; i++)
  {
    TYPE value;
    list_get(list, i, &value);
    snprintf(tmp, sizeof(tmp), PRINT_TYPE ", ", value);
    strcat_dynamic(buf, tmp, &buf_size);
  }

  // If the end of the array is being printed,
  // remove the trailing comma and show the right bracket
  // otherwise show dots
  if (end == list_size(list) - 1)
  {
    buf[strlen(buf) - 2] = '\0';
    strcpy(tmp, "]\n");
  }
  else
    strcpy(tmp, ",...\n");

  strcat_dynamic(buf, tmp, &buf_size);
  printf("%s", buf);
  free(buf);
}

/**
 * Strncat a source string to a destination string
 * while ensuring the destination string has sufficient capacity
 *
 * Inputs:
 *  dest - The destination string
 *  src - The source string
 *  dest_len - the current length of the destination string
 *
 * Outputs:
 *  dest - updated destination string
 *  dest_len - updated destination length if the string length was updated
 *
 * Returns:
 *  Nothing
 */
void strcat_dynamic(char *dest, char *src, int *dest_len)
{
  // total length after concatenate. Add 1 for trailing \0
  int total_len = strlen(dest) + strlen(src) + 1;

  // Expand the string if it's not long enough
  grow_str(dest, dest_len, total_len);

  strcat(dest, src);
}

/**
 * Realloc a string so that it has the required length
 * The size is doubled on each call to avoid repeated calls
 * to realloc every time the string is updated.
 *
 * Inputs:
 *  str - The string
 *  current_length - The current string capacity
 *  required_length - The required length
 *
 * Outputs:
 *  str - reallocated string
 *  current_length - The string capacity following reallocation
 *
 * Returns:
 *  Nothing
 */
void grow_str(char *str, int *current_length, int required_length)
{
  const int GROW_FACTOR = 2;

  // Base case for recursion
  if (*current_length >= required_length)
    return;

  str = realloc(str, *current_length * GROW_FACTOR);
  assert(str != NULL && "Error in memory allocation");

  // Update variable to track allocated space
  *current_length = GROW_FACTOR * (*current_length);

  // Recursively double the length until there's sufficient capacity
  grow_str(str, current_length, required_length);
}
