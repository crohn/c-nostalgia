/* 1.9 Character Arrays
 *
 * Exercise 1-19. Write a function reverse(s) that reverses the character
 * string s. Use it to write a program that reverses its input a line at a
 * time. */

#include <stdio.h>
#include "kr_strings.h"

#define MAX_LEN     100


int main()
{
  char line[MAX_LEN];
  
  while (kr_getline(line, MAX_LEN) > 0) {
    kr_reverse(line);
    printf("%s", line);
  }

  return 0;
}

