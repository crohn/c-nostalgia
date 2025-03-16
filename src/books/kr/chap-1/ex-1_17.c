/* 1.9 Character Arrays
 *
 * Exercise 1-17. Write a program to print all input lines that are longer than
 * 80 characters. */

#include <stdio.h>
#include "kr_strings.h"

#define MIN_LEN    80
#define MAX_LEN  1000


int main()
{
  int len;
  char line[MAX_LEN];

  while ((len = kr_getline(line, MAX_LEN)) > 0)
    if (len > MIN_LEN)
      printf("%d - %s\n", len, line);

  return 0;
}

