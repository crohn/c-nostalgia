/* 1.5 Character Input and Output
 *   1.5.4 Word Counting
 *
 * Exercise 1-12. Write a program that prints its input one word per line. */

#include <stdio.h>

#define SPACE_IN    1
#define SPACE_OUT   0

int main()
{
  int c, state;

  state = SPACE_OUT;

  while ((c = getchar()) != EOF) {
    /* FIXME no-functions-yet */
    if (c != ' ' || state == SPACE_OUT) {
      /* FIXME no-ternary-yet */
      if (c == ' ')
        putchar('\n');
      else
        putchar(c);
    }

    if (c == ' ')
      state = SPACE_IN;
    else
      state = SPACE_OUT;
  }

  return 0;
}

