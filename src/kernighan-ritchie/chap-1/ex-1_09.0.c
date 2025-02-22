/* 1.5 Character Input and Output
 *   1.5.3 Line Counting
 *
 * Exercise 1-9. Write a program to copy its input to its output, replacing
 * each string of one or more blanks by a single blank. */

#include <stdio.h>

#define SPACE_IN    1
#define SPACE_OUT   0

int main()
{
  int c, state;

  state = SPACE_OUT;

  while ((c = getchar()) != EOF) {
    /* FIXME no-functions-yet */
    if (state == SPACE_OUT || c != ' ')
      putchar(c);

    if (c == ' ')
      state = SPACE_IN;
    else
      state = SPACE_OUT;
  }

  return 0;
}

