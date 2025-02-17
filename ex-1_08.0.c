/* 1.5 Character Input and Output
 *   1.5.3 Line Counting
 *
 * Exercise 1-8. Write a program to count blanks, tabs and newlines. */

#include <stdio.h>

int main()
{
  int c;
  int blanks, tabs, newlines;

  blanks = tabs = newlines = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ')
      ++blanks;
    else if (c == '\t')
      ++tabs;
    else if (c == '\n')
      ++newlines;
  }

  printf("blanks %d tabs %d newlines %d\n", blanks, tabs, newlines);

  return 0;
}

