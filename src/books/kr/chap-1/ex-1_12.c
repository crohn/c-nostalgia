/* 1.5 Character Input and Output
 *   1.5.4 Word Counting
 *
 * Exercise 1-12. Write a program that prints its input one word per line. */

/* Solution uses basic constructs only (no functions/ternary operators) */

#include <stdio.h>

/* State machine tracks word boundaries. When we detect the first space after
 * a word (SPACE_OUT → SPACE_IN transition), we output a newline instead. */

#define SPACE_IN    1 /* Currently processing spaces */
#define SPACE_OUT   0 /* Currently processing non-spaces */

int main()
{
  int c, state;

  state = SPACE_OUT;

  while ((c = getchar()) != EOF) {
    if (state == SPACE_OUT || c != ' ') {
      /* Replace the first space after each word with a newline. This
       * effectively puts each word on its own line. */
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

