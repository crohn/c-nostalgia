/* 1.6 Arrays
 *
 * Exercise 1-14. Write a program to print a histogram of the frequencies of
 * different characters in its input. */ 

/* Using basic constructs only (no functions/dynamic memory allocation) */

#include <stdio.h>

/* Track ASCII characters frequencies only, using an array as a map of
 * characters by their integer index value. */

#define HISTO_MAX_BAR         70 /* Histogram bar max length */
#define ASCII_SIZE          0x7F

int main()
{
  int c, i, j;
  int max_freq;     /* Max char frequency, to normalize histogram bars */
  int bar_length;   /* Current histogram bar length */
  int freqs[ASCII_SIZE] = {0};

  max_freq = 0;
  bar_length = 0;

  /* Scan the input character by character:
   *   1. increment the corresponding bucket
   *   2. update maximum frequency
   */
  while ((c = getchar()) != EOF) {
    ++freqs[c];

    if (freqs[c] > max_freq)
      max_freq = freqs[c];
  }

  /* Histogram
   * Print histogram with format:
   *    character frequency| #####...
   *
   * The number of # chars is proportional to max_freq.  */
  for (i = 0; i < ASCII_SIZE; ++i) {
    if (freqs[i] > 0) {
      /* Normalize bar length by maximum allowed length */
      bar_length = freqs[i] * HISTO_MAX_BAR / max_freq;

      /* Print label */
      printf("%c %3d | ", i, freqs[i]);

      /* Print bar */
      for (j = 0; j < bar_length; ++j)
        putchar('#');

      putchar('\n');
    }
  }

  return 0;
}

