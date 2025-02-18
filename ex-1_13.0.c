/* 1.6 Arrays
 *
 * Exercise 1-13. Write a program to print a histogram of the lengths of words
 * in its input. It is easy to draw the histogram with the bars horizontal; a
 * vertical orientation is more challenging. */

#include <stdio.h>

#define WORD_IN                1
#define WORD_OUT               0

#define HISTO_MAX_BUCKET      10
#define HISTO_MAX_BAR         70

int main()
{
  int i, j, c, state;
  int length_curr, length_max;
  int lengths[HISTO_MAX_BUCKET];
  int bar_length;

  length_curr = length_max = 0;
  state = WORD_OUT;

  for (i = 0; i < HISTO_MAX_BUCKET; ++i)
    lengths[i] = 0;

  while ((c = getchar()) != EOF) {
    /* FIXME no-functions-yet */
    /* actions */
    if (state == WORD_IN)
      ++length_curr;

    if (state == WORD_IN && (c == ' ' || c == '\t' || c == '\n')) {
      if (length_curr > HISTO_MAX_BUCKET)
        length_curr = HISTO_MAX_BUCKET;

      ++lengths[length_curr - 1];

      if (lengths[length_curr - 1] > length_max)
        length_max = lengths[length_curr - 1];

      length_curr = 0;
    }

    /* FIXME no-ternary-yet */
    /* post-actions state management */
    if (c != ' ' && c != '\t' && c != '\n')
      state = WORD_IN;
    else
      state = WORD_OUT;
  }

  /* histogram print */
  for (i = 0; i < HISTO_MAX_BUCKET; ++i) {
    bar_length = lengths[i] * HISTO_MAX_BAR / length_max;
    printf("%2d %2d| ", i+1, lengths[i]);

    for (j = 0; j < bar_length; ++j)
      putchar('#');

    putchar('\n');
  }

  return 0;
}

