/* 1.9 Character Arrays
 *
 * Exercise 1-16. Revise the main routine of the longest-line program so it
 * will correctly print the length of arbitrarily long input lines, and as much
 * as possible of the text. */ 

#include <stdio.h>

#define MAX_LEN   10

void copy(char to[], char from[]);
int get_line(char s[], int max_len);

int main()
{
  int len, curr_len, max_len;
  char line[MAX_LEN], curr_line[MAX_LEN], max_line[MAX_LEN];

  max_len = curr_len = 0;

  while ((len = get_line(line, MAX_LEN)) > 0) {
    /* buffer current line starting text to have it available in case the
     * current string is the longest one */
    if (curr_len == 0)
      copy(curr_line, line);

    curr_len += len;

    if (line[len - 1] == '\n') {
      if (curr_len > max_len) {
        max_len = curr_len;
        copy(max_line, curr_line);
      }

      curr_len = 0;
    }
  }

  printf("The longest line has length %d and starts with:\n%s\n", max_len, max_line);

  return 0;
}


/* Assuming that to has enough space to contain from. */
void copy(char to[], char from[])
{
  int i;

  for (i = 0; (to[i] = from[i]) != '\0'; ++i)
    ;
}


int get_line(char s[], int max_len)
{
  int i, c;

  for (i = 0; i < max_len - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if (c == '\n')
    s[i++] = c;
  /* Handle the case when the last character is not newline. */
  else if (i > 0 && c == EOF)
    s[i++] = '\n';

  s[i] = '\0';

  if (c == EOF && i == 0)
    return -1;

  return i;
}

