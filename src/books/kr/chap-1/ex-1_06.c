/* 1.5 Character Input and Output
 *   1.5.1 File Copying
 *
 * Exercise 1-6. Verify that the expression getchar() != EOF is 0 or 1. */

#include <stdio.h>

int main()
{
  /* 1 is considered truthy, while 0 is falsy. */
  printf("getchar() != EOF -> %d\n", getchar() != EOF);
  return 0;
}

