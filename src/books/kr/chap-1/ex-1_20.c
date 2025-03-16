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
#include "kr_common.h"


#define TABSTOP     8

int next_col(char c, int col, int spaces);
int spaces_to_tabstop(char c, int col);
void print(char c, int spaces);

int main()
{
  int c;
  int col, spaces;

  col = 0;
  spaces = 0;

  while ((c = getchar()) != EOF) {
    spaces = spaces_to_tabstop(c, col);
    col = next_col(c, col, spaces);
    print(c, spaces);
  }

  return 0;
}


int next_col(char c, int col, int spaces){
  if (c == KR_C_TAB)
    return col + spaces;

  if (c == KR_C_NEWLINE)
    return 0;

  return col + 1;
}

int spaces_to_tabstop(char c, int col)
{
  if (c == KR_C_TAB)
    return TABSTOP - (col % TABSTOP);
  
  return 0;
}


void print(char c, int spaces)
{
    for (; spaces > 0; --spaces)
      putchar(KR_C_SPACE);

    if (c != KR_C_TAB)
      putchar(c);
}

