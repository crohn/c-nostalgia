/* 1.9 Character Arrays
 *
 * Exercise 1-18. Write a program to remove trailing blanks and tabs from each
 * line of input, and to delete entirely blank lines. */

#include "kr_debug.h"
#include "kr_strings.h"

#define MAX_LEN     100

int main()
{
  int len;
  char line[MAX_LEN];
  
  while ((len = kr_getline(line, MAX_LEN)) > 0) {
    kr_debug_print_str(line, '|');
    kr_trim(line, len);
    kr_debug_print_str(line, '|');
  }

  return 0;
}

