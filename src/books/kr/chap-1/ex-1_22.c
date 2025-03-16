/* 1.10 External Variables and Scope
 *
 * Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column.
 * */ 

#include <stdio.h>

#define C_NEWLINE   '\n'
#define C_SPACE     ' ' 
#define C_TAB       '\t'

#define BUFFER_LEN  100
#define MAX_COL     16

#define IS_WORD     1
#define IS_BLANK    2

void debug(char line[], int start, int end, int col, int row);

int get_line(char s[], int max_len);
int is_eol(char c);

int would_overflow(int start, int end, int offset);

int main()
{
  int len;
  int start, end;  /* sliding window to scan words and spaces */
  char line[BUFFER_LEN];
  short state;
  int col, row;

  len = get_line(line, BUFFER_LEN);

  col = row = 0;
  start = end = 0;

  while (end < len) {
    if (line[start] == C_SPACE) {
      state = IS_BLANK;     
      /* shift to end of blank string */
      while (!is_eol(line[end+1]) && line[end+1] == C_SPACE)
        ++end;
    } else {
      state = IS_WORD;
      /* shift to end of current word */
      while (!is_eol(line[end+1]) && line[end+1] != C_SPACE)
        ++end;
    }

    /* the current string overflows MAX_COL */
    if (would_overflow(start, end, 0)) {
      if (state == IS_BLANK) {
        start = ++end;
        continue;
      }

      while (start <= end) {
        putchar(line[start]);
        ++start;
        ++col;

        /* break current string, don't care about hyphenation */
        if (col >= MAX_COL) {
          putchar(C_NEWLINE);
          ++row;
          col = 0;
        }
      }

    /* the current string overflows MAX_COL, when starting at col */
    } else if (would_overflow(start, end, col)) {
      if (state == IS_BLANK) {
        start = ++end;
        continue;
      }

      /* start at new line, mindful that the string will fit */
      ++row;
      putchar(C_NEWLINE);
      
      col = end - start + 1;

      while (start <= end)
        putchar(line[start++]);
        
    } else {
      col += end - start + 1;

      while (start <= end)
        putchar(line[start++]);
    }

    start = ++end;

    if (is_eol(line[start])) {
      putchar(C_NEWLINE);
      break;
    }
  }

  return 0;
}

void debug(char line[], int start, int end, int col, int row)
{
    printf("%c:%2d - %c:%2d - C:%2d R:%2d\n", line[start], start, line[end], end, col, row);
}

int get_line(char s[], int max_len)
{
  int i, c;

  for (i = 0; i < max_len - 1 && ((c = getchar()) != EOF) && c != C_NEWLINE; ++i)
    s[i] = c;

  if (c == C_NEWLINE)
    s[i++] = c;

  s[i] = '\0';

  return i;
}

int is_eol(char c)
{
  return c == C_NEWLINE || c == '\0';
}

int would_overflow(int start, int end, int offset)
{
  return offset + (end - start + 1) > MAX_COL;
}

