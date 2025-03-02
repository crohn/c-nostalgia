/* 1.10 External Variables and Scope
 *
 * Exercise 1-24. Write a program to check a C program for rudimentary syntax
 * errors like unbalanced parentheses, brackets and braces. Don't forget about
 * quotes, both single and double, escape sequences, and comments. (This
 * program is hard if you do it in full generality.) */

/* NOTE ~ Without pointers this assignment becomes very unpractical, so I
 * decided to change approach and use extern variables for stack handling.
 * Please check ex-1_24.1.c to see the complete version. */

#include <stdio.h>

/*
...............................................................................
....[3].......[3].......[3].......[3]..........................................
....[2].......[2].......[2].......[2]..........................................
....[1].......[1].......[1].......[1]..........................................
.[(][0]....[ ][(]<...[)][(]<...[ ][0]..........................................
.......<..............................<........................................
...............................................................................
........[3]....................................................................
........[2]....................................................................
........[1]....................................................................
.....[ ]["]<...................................................................
...............................................................................
...............................................................................
...............................................................................
*/

#define STACK_SIZE      100
#define TUPLE_SIZE      3
#define TUPLE_TOKEN     0
#define TUPLE_LINE      1
#define TUPLE_COL       2

/* tokens */
#define NEWLINE         '\n'
#define LPAREN          '('
#define RPAREN          ')'
#define LBRACE          '{'
#define RBRACE          '}'
#define DQUOTE          '"'

void debug_stack(int stack[STACK_SIZE][TUPLE_SIZE], int top);
void debug_list(int stack[STACK_SIZE][TUPLE_SIZE], int top);

int push(int stack[STACK_SIZE][TUPLE_SIZE], int top, int token, int line, int col);
int pop(int stack[STACK_SIZE][TUPLE_SIZE], int top);
int peek(int stack[STACK_SIZE][TUPLE_SIZE], int top);
int is_empty(int top);

int main()
{
  int c;
  int stack[STACK_SIZE][TUPLE_SIZE] = {0};
  int top;
  int line, col;
  
  top = -1;
  line = 1;
  col = 1;

  while ((c = getchar()) != EOF) {
    if (c == DQUOTE) {
      if (!is_empty(top) && peek(stack, top) == DQUOTE)
        top = pop(stack, top);
      else
        top = push(stack, top, c, line, col);
    } else if (c == LPAREN) {
      if (is_empty(top) || (!is_empty(top) && peek(stack, top) != DQUOTE))
        top = push(stack, top, c, line, col);
    } else if (c == RPAREN) {
      if (is_empty(top) || (!is_empty(top) && peek(stack, top) != DQUOTE)) {
        if (top >= 0 && peek(stack, top) == LPAREN)
          top = pop(stack, top);
        else
          top = push(stack, top, c, line, col);
      }
    } else if (c == LBRACE)
      top = push(stack, top, c, line, col);
    else if (c == RBRACE) {
      if (top >= 0 && peek(stack, top) == LBRACE)
        top = pop(stack, top);
      else
        top = push(stack, top, c, line, col);
    }

    if (c == NEWLINE) {
      line += 1;
      col = 1;
    } else
      col += 1;
  }

  debug_stack(stack, top);

  return 0;
}

/* Returns the next top index. */
int push(int stack[STACK_SIZE][TUPLE_SIZE], int top, int token, int line, int col)
{
  if (top > STACK_SIZE - 1) {
    printf("ERR - Stack overflow\n");
    return -1;
  }

  top += 1;

  stack[top][TUPLE_TOKEN] = token;
  stack[top][TUPLE_LINE] = line;
  stack[top][TUPLE_COL] = col;

  return top;
}

/* Returns the next top index. */
int pop(int stack[STACK_SIZE][TUPLE_SIZE], int top)
{
  if (top < 0) {
    printf("ERR - Stack is empty\n");
    return -1;
  }

  stack[top][TUPLE_TOKEN] = 0;
  stack[top][TUPLE_LINE] = 0;
  stack[top][TUPLE_COL] = 0;

  top -= 1;

  return top;
}

int peek(int stack[STACK_SIZE][TUPLE_SIZE], int top)
{
  if (top < 0) {
    printf("ERR - Stack is empty\n");
    return -1;
  }

  return stack[top][TUPLE_TOKEN];
}

int is_empty(int top)
{
  return top < 0;
}

void debug_stack(int stack[STACK_SIZE][TUPLE_SIZE], int top)
{
  int i;

  printf("top:%d\n", top);

  for (i = top; i >= 0; --i)
    printf("[%c,%d,%d]\n", stack[i][TUPLE_TOKEN], stack[i][TUPLE_LINE], stack[i][TUPLE_COL]);
}

void debug_list(int stack[STACK_SIZE][TUPLE_SIZE], int top)
{
  int i;

  for (i = 0; i <= top; ++i)
    printf("Unbalanced '%c' at %d,%d\n", stack[i][TUPLE_TOKEN], stack[i][TUPLE_LINE], stack[i][TUPLE_COL]);
}

