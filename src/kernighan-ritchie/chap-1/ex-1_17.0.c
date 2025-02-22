/* 1.9 Character Arrays
 *
 * Exercise 1-17. Write a program to print all input lines that are longer than
 * 80 characters. */

#include <stdio.h>

#define MIN_LEN    80
#define MAX_LEN  1000

int get_line(char s[], int max_len);

#include <stdio.h>

int main()
{
  int len;
  char line[MAX_LEN];

  while ((len = get_line(line, MAX_LEN)) > 0)
    if (len > MIN_LEN)
      printf("%d - %s\n", len, line);

  return 0;
}

int get_line(char s[], int max_len)
{
  int i, c;

  for (i = 0; i < max_len - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
    
  if (c == '\n')
    s[i++] = c;

  s[i] = '\0';

  return i;
}

