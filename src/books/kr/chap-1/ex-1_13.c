/* 1.6 Arrays
 *
 * Exercise 1-13. Write a program to print a histogram of the lengths of words
 * in its input. It is easy to draw the histogram with the bars horizontal; a
 * vertical orientation is more challenging. */

/* Using basic constructs only (no functions/ternary operators) */

#include <stdio.h>

/* State machine tracks word boundaries. When we detect the end of a word, we
 * increment the corresponding word length count.
 * Keep track of max word length to normalize histogram bar lengths to fit
 * within HISTO_MAX_BAR characters. This makes sure that the histogram fits the
 * display space, keeping proportions between word lengths. */

#define WORD_IN                1 /* Currently processing word */
#define WORD_OUT               0 /* Currently processing non-word, eg. blanks */

#define HISTO_MAX_BUCKET      10
#define HISTO_MAX_BAR         70

int main()
{
  int i, j, c, state;
  int length_curr;      /* Current word length */
  int length_max;       /* Max word length count, to normalize histogram bars */
  int bar_length;       /* Current bar length -- histogram print */
  int lengths[HISTO_MAX_BUCKET]; /* Word count by length */

  length_curr = length_max = 0;
  state = WORD_OUT;

  for (i = 0; i < HISTO_MAX_BUCKET; ++i)
    lengths[i] = 0;

  while ((c = getchar()) != EOF) {
    /* Actions */
    if (state == WORD_IN)
      ++length_curr;

    /* End of word detection
     *   1. cap word length if needed
     *   2. increment corresponding word length count
     *   3. update max word length count -- histogram bar normalization
     *   4. reset current length counter */
    if (state == WORD_IN && (c == ' ' || c == '\t' || c == '\n')) {
      if (length_curr > HISTO_MAX_BUCKET)
        length_curr = HISTO_MAX_BUCKET;

      ++lengths[length_curr - 1];

      if (lengths[length_curr - 1] > length_max)
        length_max = lengths[length_curr - 1];

      length_curr = 0;
    }

    /* Post-actions state management */
    if (c != ' ' && c != '\t' && c != '\n')
      state = WORD_IN;
    else
      state = WORD_OUT;
  }

  /* Histogram
   * Print histogram with format:
   *    length count| #####...
   *
   * The number of # chars is proportionally normalized to length_max. */
  for (i = 0; i < HISTO_MAX_BUCKET; ++i) {
    /* Normalize bar length by maximum allowed length */
    bar_length = lengths[i] * HISTO_MAX_BAR / length_max;

    /* Print label */
    printf("%2d %2d| ", i+1, lengths[i]);

    /* Print bar */
    for (j = 0; j < bar_length; ++j)
      putchar('#');

    putchar('\n');
  }

  return 0;
}

