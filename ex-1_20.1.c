/* 1.10 External Variables and Scope
 *
 * Exercise 1-20. Write a program detab that replaces tabs in the input with
 * the proper number of blanks to space to the next tab stop. Assume a fixed
 * set of tab stops, say every n columns. Should n be a variable or a symbolic
 * parameter? */

/*
 *  C ' '\t  _  _  _  _  *  C ' '\t  _  _  _  _  *  C 
 *  0  1  2  3  4  5  6  7  0  1  2  3  4  5  6  7  0
 *  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
 *                       > T                     > T
 * */

#include <stdio.h>

#define TABSTOP     8

#define C_NEWLINE   '\n'
#define C_SPACE     ' '
#define C_TAB       '\t'

int spaces_to_tabstop(int col);

int main()
{
  int c;
  int col, spaces;

  col = 0;
  spaces = 0;

  while ((c = getchar()) != EOF) {
    if (c == C_TAB) {
      spaces = spaces_to_tabstop(col);
    } else if (c == C_NEWLINE) {
      col = 0;
    } else {
      ++col;
    }

    for (; spaces > 0; --spaces) {
      ++col;
      putchar(C_SPACE);
    }

    if (c != C_TAB)
      putchar(c);
  }

  return 0;
}

int spaces_to_tabstop(int col)
{
  return TABSTOP - (col % TABSTOP);
}

