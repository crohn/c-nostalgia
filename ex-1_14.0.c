/* 1.6 Arrays
 *
 * Exercise 1-14. Write a program to print a histogram of the frequencies of
 * different characters in its input. */ 

#include <stdio.h>

#define HISTO_MAX_BAR         70
#define ASCII_SIZE          0x7F

int main()
{
  int c, i, j;
  int freqs[ASCII_SIZE];
  int max_freq, bar_length;

  max_freq = 0;
  bar_length = 0;

  for (i = 0; i < ASCII_SIZE; ++i)
    freqs[i] = 0;

  while ((c = getchar()) != EOF) {
    ++freqs[c];

    if (freqs[c] > max_freq)
      max_freq = freqs[c];
  }

  /* FIXME no-functions-yet */
  for (i = 0; i < ASCII_SIZE; ++i) {
    if (freqs[i] > 0) {
      bar_length = freqs[i] * HISTO_MAX_BAR / max_freq;
      printf("%c %3d | ", i, freqs[i]);

      for (j = 0; j < bar_length; ++j)
        putchar('#');

      putchar('\n');
    }
  }

  return 0;
}

