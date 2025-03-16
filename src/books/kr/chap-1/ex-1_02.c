/* 1.1 Getting Started
 *
 * Exercise 1-2. Experiment to find out what happens when printf's argument
 * string contains \c, where c is some character not listed above. */

#include <stdio.h>

int main()
{
  /* \b deletes the previous 'l' character. */
  printf("Hello, worl\bd\n");

  /* If you uncomment the following line, the program won't compile with flags
   * [-Wall, -Werror], because -Wunknown-escape-sequence is included. */
  /* printf("\z"); */

  return 0;
}

