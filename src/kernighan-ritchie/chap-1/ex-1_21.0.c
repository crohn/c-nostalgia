/* 1.10 External Variables and Scope
 *
 * Exercise 1-21. Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. Use the same
 * tab stops as for detab. When either a tab or a single blank would suffice to
 * reach a tab stop, which should be given preference? */

/*
 * ' '' ' C ' '' '' '' '' '' '' ' C  _  _  _  _  _  _ 
 *  0  1  2  3  4  5  6  7  0  1  2  3  4  5  6  7  0
 *  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
 *                       > T                     > T
 * */

#include <stdio.h>

#define TABSTOP   8

#define C_NEWLINE '\n'
#define C_SPACE   ' '
#define C_TAB     '\t'

int main()
{
  int c;
  int col, ws_count;
  int tabs;           /* tabs to insert */
  int spaces;         /* spaces to insert */

  col = 0;
  tabs = spaces = 0;
  ws_count = 0;

  while ((c = getchar()) != EOF) {
    if (c == C_SPACE) {
      ++col;
      ++ws_count;
    } else {
      if (ws_count > 0) {
        tabs = col / TABSTOP;
        spaces = col % TABSTOP;

        for (; tabs > 0; --tabs)
          putchar(C_TAB);

        for (; spaces > 0; --spaces)
          putchar(C_SPACE);
      }

      if (c == C_TAB)
        col += TABSTOP - (col % TABSTOP);
      else if (c == C_NEWLINE)
        col = 0;
      else
        ++col;

      putchar(c);

      ws_count = 0;
    }
  }

  return 0;
}

