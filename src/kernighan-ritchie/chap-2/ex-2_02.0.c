/* 2.6 Relational and Logical Operators
 *
 * Exercise 2-2. Write a loop equivalent for the for loop above without using
 * && or ||. 
 *
 * NOTE ~ The "loop above" is:
 *    for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
 *      s[i] = c;
 */

#include <stdio.h>

#define LIM   10

int main()
{
  int i;
  int c;
  int lim = LIM;
  char s[LIM] = {0};

  for (i = 0; i < lim - 1; ++i) {
    if ((c = getchar()) == EOF)
      break;

    if (c == '\n')
      break;

    s[i] = c;
  }

  return 0;
}

