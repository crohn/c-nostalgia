/* 1.5 Character Input and Output
 *   1.5.3 Line Counting
 *
 * Exercise 1-9. Write a program to copy its input to its output, replacing
 * each string of one or more blanks by a single blank. */

#include <stdio.h>

/* I'm implementing a simple state machine that tracks whether the current
 * character is part of a whitespace string. */

#define SPACE_IN    1
#define SPACE_OUT   0

int main()
{
  int c, state;

  state = SPACE_OUT;

  while ((c = getchar()) != EOF) {
    /* Only suppress spaces that follow another space.
     * First space in a sequence gets printed (state -> SPACE_OUT).
     * Subsequent spaces are skipped (state -> SPACE_IN). */
    if (state == SPACE_OUT || c != ' ')
      putchar(c);

    if (c == ' ')
      state = SPACE_IN;
    else
      state = SPACE_OUT;
  }

  return 0;
}

