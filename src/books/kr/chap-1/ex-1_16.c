/* 1.9 Character Arrays
 *
 * Exercise 1-16. Revise the main routine of the longest-line program so it
 * will correctly print the length of arbitrarily long input lines, and as much
 * as possible of the text. */ 

#include <stdio.h>
#include "kr_strings.h"

#define NEWLINE   '\n'
#define MAX_LEN   10

int main()
{
  char line[MAX_LEN];      /* input buffer, stores input from stdin */
  int len;                 /* input buffer length, <= MAX_LEN - 1 by definition */
  char curr_line[MAX_LEN]; /* stores the first chunk of current input line */
  int curr_len;            /* accumulates current input line length */
  char max_line[MAX_LEN];  /* stores longest line's first chunk */
  int max_len;             /* longest line length */

  max_len = curr_len = 0;

  while ((len = kr_getline(line, MAX_LEN)) > 0) {
    /* Save each new line's first chunk. In case the current line is the
     * longest, this will be copied to max_line. */
    if (curr_len == 0)
      kr_copy(curr_line, line);

    curr_len += len;

    if (line[len - 1] == NEWLINE) {
      if (curr_len > max_len) {
        max_len = curr_len;
        kr_copy(max_line, curr_line);
      }

      curr_len = 0;
    }
  }

  printf("The longest line has length %d and starts with:\n%s\n", max_len, max_line);

  return 0;
}

