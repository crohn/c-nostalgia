/* 1.5 Character Input and Output
 *   1.5.3 Line Counting
 *
 * Exercise 1-9. Write a program to copy its input to its output, replacing
 * each string of one or more blanks by a single blank. */

#include <stdio.h>

#define SPACE_IN    1 /* Currently processing spaces */
#define SPACE_OUT   0 /* Currently processing non-spaces */

/* Determine next state based on current character. */
int next_state(char c);

/* Determine if character should be printed based on current state. */
int should_print(char c, int state);

int main()
{
  int c, state;

  state = SPACE_OUT;

  /* Simple state machine to collapse consecutive spaces into a single space */
  while ((c = getchar()) != EOF) {
    if (should_print(c, state))
      putchar(c);
    state = next_state(c);
  }

  return 0;
}

int next_state(char c)
{
  if (c == ' ')
    return SPACE_IN;
  else
    return SPACE_OUT;
}

int should_print(char c, int state)
{
  if (state == SPACE_OUT)
    return 1;
  else
    return c != ' ';
}

