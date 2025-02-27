/* 1.10 External Variables and Scope
 *
 * Exercise 1-23. Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly. C
 * comments do not nest. */ 

#include <stdio.h>

#define C_BAKSLASH  '\\'
#define C_FWDSLASH  '/'
#define C_NEWLINE   '\n'
#define C_QUOTE     '"'
#define C_STAR      '*'

#define S_NONE      0x0
#define S_ESCAPE    0x1
#define S_QUOTE     0x2
#define S_COMMENT   0x4

int main()
{
  int curr, next;
  int state;

  state = S_NONE;

  while ((curr = getchar()) != EOF) {
    if (state == S_NONE) {
      if (curr == C_BAKSLASH)
        state |= S_ESCAPE;

      if (curr == C_FWDSLASH) {
        next = getchar();
        if (next == C_STAR)
          state |= S_COMMENT;
        else
          ungetc(next, stdin);
      }

      if (curr == C_QUOTE)
        state |= S_QUOTE;

    } else if (state & S_ESCAPE) {
      state ^= S_ESCAPE;

    } else if (state & S_QUOTE) {
      if (curr == C_QUOTE)
        state ^= S_QUOTE;

    } else if (state & S_COMMENT) {
      if (curr == C_STAR) {
        next = getchar();
        if (next == C_FWDSLASH) {
          state ^= S_COMMENT;
          continue;
        } else
          ungetc(next, stdin);
      }
    }

    if (!(state & S_COMMENT))
      putchar(curr);
  }

  return 0;
}

