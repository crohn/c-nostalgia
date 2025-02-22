/* 1.9 Character Arrays
 *
 * Exercise 1-19. Write a function reverse(s) that reverses the character
 * string s. Use it to write a program that reverses its input a line at a
 * time. */

#include <stdio.h>

#define MAX_LEN     100

int get_line(char s[], int max_len);
void reverse(char s[]);

int main()
{
  int len;
  char line[MAX_LEN];
  
  while (get_line(line, MAX_LEN) > 0) {
    reverse(line);
    printf("%s", line);
  }

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

void reverse(char s[])
{
  int i, j;
  char tmp;

  for (j = 0; s[j+1] != '\0'; ++j);

  if (s[j] == '\n')
    --j;

  for (i = 0; i < j; ++i, --j) {
    tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
  }
}

