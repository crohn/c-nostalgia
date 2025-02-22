/* 1.9 Character Arrays
 *
 * Exercise 1-18. Write a program to remove trailing blanks and tabs from each
 * line of input, and to delete entirely blank lines. */

#include <stdio.h>

#define MAX_LEN     100

int get_line(char s[], int max_len);
int is_blank(char c);
void print_char(char c);
void print_debug(char s[]);
int trim(char s[], int len);

int main()
{
  int len;
  char line[MAX_LEN];
  
  while ((len = get_line(line, MAX_LEN)) > 0) {
    print_debug(line);
    len = trim(line, len);
    print_debug(line);
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


int is_blank(char c)
{
  return c == ' ' || c == '\t' || c == '\n';
}


void print_char(char c)
{
  if (c == '\0')
    printf("\\0 | ");
  else if (c == '\t')
    printf("\\t | ");
  else if (c == '\n')
    printf("\\n | ");
  else
    printf("%c | ", c);
}


void print_debug(char s[])
{
  int i;

  for (i = 0; s[i] != '\0'; ++i)
  {
    print_char(s[i]);
  }
  printf("\n");
}


int trim(char s[], int len)
{
  int i, newline;

  if (s[0] == '\n') {
    s[0] = '\0';
    return 0;
  }

  newline = -1;

  for (i = len - 1; i > 0 && is_blank(s[i]); --i) {
    if (newline == -1 && s[i] == '\n')
      newline = i;
  }

  if (newline > 0)
    s[++i] = '\n';

  s[i+1] = '\0';

  return i;
}

