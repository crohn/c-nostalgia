/* 1.10 External Variables and Scope
 *
 * Exercise 1-20. Write a program detab that replaces tabs in the input with
 * the proper number of blanks to space to the next tab stop. Assume a fixed
 * set of tab stops, say every n columns. Should n be a variable or a symbolic
 * parameter? */

#include <stdio.h>

#define TABSTOP     8

int next_col(int c, int col);

int main()
{
  int c, i;
  int col;

  i = col = 0;

  while ((c = getchar()) != EOF) {
    col = next_col(c, col);
    
    if (c == '\t') {
      for (; i < col; ++i)
        putchar(' ');
    } else
      putchar(c);

    i = col;
  }

  return 0;
}

int next_col(int c, int col)
{
  if (c == '\n')
    return 0;

  if (c == '\t')
    return ((col / TABSTOP) + 1) * TABSTOP;

  return col + 1;
}

