/* 1.10 External Variables and Scope
 *
 * Exercise 1-24. Write a program to check a C program for rudimentary syntax
 * errors like unbalanced parentheses, brackets and braces. Don't forget about
 * quotes, both single and double, escape sequences, and comments. (This
 * program is hard if you do it in full generality.) */

#include <stdio.h>

/*
...............................................................................
...............................................................................
....[3].......[3].......[3].......[3]..........................................
....[2].......[2].......[2].......[2]..........................................
....[1].......[1].......[1].......[1]..........................................
.[(][0]....[ ][(]<...[)][(]<...[ ][0]..........................................
.......<..............................<........................................
...............................................................................
*/

#define STACK_EMPTY     -1
#define STACK_SIZE      100
#define TUPLE_COL       2
#define TUPLE_LINE      1
#define TUPLE_SIZE      3
#define TUPLE_TOKEN     0

/* tokens */
#define BAKSLASH        '\\'
#define NEWLINE         '\n'
#define QUOTE           '\''
#define DQUOTE          '"'
#define FWDSLASH        '/'
#define STAR            '*'
#define LPAREN          '('
#define RPAREN          ')'
#define LBRACKET        '['
#define RBRACKET        ']'
#define LBRACE          '{'
#define RBRACE          '}'
#define COMMENT_BGN     0x80 /* first symbol available after ASCII table size */
#define COMMENT_END     0x81

/* state */
#define S_NONE          0x0
#define S_ESCAPE        0x1
#define S_DQUOTE        0x2
#define S_QUOTE         0x4
#define S_COMMENT       0x8

/* output */
void debug_stack();
void debug_list(int stack[STACK_SIZE][TUPLE_SIZE], int top);

/* stack */
void push(int token, int line, int col);
int pop();
int peek();
int is_empty();

/* parser */
void handle_bakslash(int line, int col);
void handle_dquote(int line, int col);
void handle_escape_sequence(int c);
void handle_fwdslash(int line, int col);
void handle_lbrace(int line, int col);
void handle_lbracket(int line, int col);
void handle_lparen(int line, int col);
void handle_newline(int line, int col);
void handle_quote(int line, int col);
void handle_rbrace(int line, int col);
void handle_rbracket(int line, int col);
void handle_rparen(int line, int col);
void handle_star(int line, int col);

/* state */
void enter_character(int line, int col);
void exit_character(void);
void enter_comment(int line, int col);
void exit_comment(void);
void enter_escape(int line, int col);
void exit_escape(void);
void enter_string(int line, int col);
void exit_string(void);

int stack[STACK_SIZE][TUPLE_SIZE] = {0};
int top;
int line, col;
int state;


int main()
{
  extern int stack[STACK_SIZE][TUPLE_SIZE];
  extern int top;
  extern int line, col;
  extern int state;

  int c;
  
  top = -1;
  line = 1;
  col = 1;
  state = S_NONE;

  while ((c = getchar()) != EOF) {
    switch (c) {
      case BAKSLASH:
        handle_bakslash(line, col);
        break;
      case DQUOTE:
        handle_dquote(line, col);
        break;
      case FWDSLASH:
        handle_fwdslash(line, col);
        break;
      case LBRACE:
        handle_lbrace(line, col);
        break;
      case LBRACKET:
        handle_lbracket(line, col);
        break;
      case LPAREN:
        handle_lparen(line, col);
        break;
      case NEWLINE:
        handle_newline(line, col);
        break;
      case QUOTE:
        handle_quote(line, col);
        break;
      case RBRACE:
        handle_rbrace(line, col);
        break;
      case RBRACKET:
        handle_rbracket(line, col);
        break;
      case RPAREN:
        handle_rparen(line, col);
        break;
      case STAR:
        handle_star(line, col);
        break;
      default:
        handle_escape_sequence(c);
        break;
    }

    if (c == NEWLINE) {
      line += 1;
      col = 1;
    } else
      col += 1;
  }

  debug_stack();

  return 0;
}

/* Returns the next top index. */
void push(int token, int line, int col)
{
  if (top > STACK_SIZE - 1) {
    printf("ERR - Stack overflow\n");
    return;
  }

  top += 1;

  stack[top][TUPLE_TOKEN] = token;
  stack[top][TUPLE_LINE] = line;
  stack[top][TUPLE_COL] = col;
}

/* Returns the next top index. */
int pop()
{
  if (top < 0) {
    printf("ERR - Stack is empty\n");
    return -1;
  }

  int popped = stack[top][TUPLE_TOKEN];

  stack[top][TUPLE_TOKEN] = 0;
  stack[top][TUPLE_LINE] = 0;
  stack[top][TUPLE_COL] = 0;

  top -= 1;

  return popped;
}

int peek()
{
  return top < 0 ? STACK_EMPTY : stack[top][TUPLE_TOKEN];
}

int is_empty()
{
  return top < 0;
}

void debug_stack()
{
  extern int stack[STACK_SIZE][TUPLE_SIZE];
  extern int top;
  
  int i;
  int token;

  printf("top:%d\n", top);

  for (i = top; i >= 0; --i) {
    token = stack[i][TUPLE_TOKEN];
    if (token == NEWLINE) {
      printf(
        "[\\n,%d,%d]\n", stack[i][TUPLE_LINE], stack[i][TUPLE_COL]
      );
    } else if (token == COMMENT_BGN) {
      printf(
        "[/*,%d,%d]\n", stack[i][TUPLE_LINE], stack[i][TUPLE_COL]
      );
    } else if (token == COMMENT_END) {
      printf(
        "[*/,%d,%d]\n", stack[i][TUPLE_LINE], stack[i][TUPLE_COL]
      );
    } else {
      printf(
        "[%c,%d,%d]\n", token, stack[i][TUPLE_LINE], stack[i][TUPLE_COL]
      );
    }
  }
}

void debug_list(int stack[STACK_SIZE][TUPLE_SIZE], int top)
{
  int i;

  for (i = 0; i <= top; ++i)
    printf("Unbalanced '%c' at %d,%d\n", stack[i][TUPLE_TOKEN], stack[i][TUPLE_LINE], stack[i][TUPLE_COL]);
}

void handle_bakslash(int line, int col)
{
  extern int state;
  int token = peek();

  if (state & S_COMMENT)
    return;

  if (state == S_NONE) /* push because it's unexpected */
    push(BAKSLASH, line, col);
  else if (state & S_DQUOTE || state & S_QUOTE) {
    if (token == BAKSLASH)
      exit_escape();
    else
      enter_escape(line, col);
  }
}

void handle_dquote(int line, int col)
{
  extern int state;
  int token = peek();

  if (state & S_QUOTE || state & S_COMMENT)
    return;

  if (state & S_DQUOTE) {
    if (token == BAKSLASH) /* consume the escape token */
      exit_escape();
    else if (token == DQUOTE)
      exit_string();
  } else
    enter_string(line, col);
}

void handle_escape_sequence(int c)
{
  extern int state;

  if (!(state & S_ESCAPE))
    return;

  switch (c) {
    case 'a':
    case 'b':
    case 'f':
    case 'n':
    case 'r':
    case 't':
    case 'v':
    case '?':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case 'x':
      exit_escape();
  }
}

void handle_fwdslash(int line, int col)
{
  extern int state;
  int c;

  if (state & S_QUOTE || state & S_DQUOTE || state & S_COMMENT)
    return;

  c = getchar();

  if (c == STAR) /* look ahead */
    enter_comment(line, col);
  else
    ungetc(c, stdin);
}

void handle_lbrace(int line, int col)
{
  extern int state;

  if (state & S_QUOTE || state & S_DQUOTE || state & S_COMMENT)
    return;

  push(LBRACE, line, col);
}

void handle_lbracket(int line, int col)
{
  extern int state;

  if (state & S_QUOTE || state & S_DQUOTE || state & S_COMMENT)
    return;

  push(LBRACKET, line, col);
}

void handle_lparen(int line, int col)
{
  extern int state;

  if (state & S_QUOTE || state & S_DQUOTE || state & S_COMMENT)
    return;

  push(LPAREN, line, col);
}

void handle_newline(int line, int col)
{
  extern int state;
  int token = peek();

  if (state & S_DQUOTE) {
    if (state & S_ESCAPE && token == BAKSLASH)
      exit_escape();
    else
      push(NEWLINE, line, col);
  } else if (state & S_QUOTE)
    push(NEWLINE, line, col);
}

void handle_quote(int line, int col)
{
  extern int state;
  int token = peek();

  if (state & S_DQUOTE || state & S_COMMENT)
    return;

  if (state & S_QUOTE) {
    if (token == BAKSLASH)
      exit_escape();
    else if (token == QUOTE)
      exit_character();
  } else
    enter_character(line, col);
}

void handle_rbrace(int line, int col)
{
  extern int state;
  int token = peek();

  if (state & S_QUOTE || state & S_DQUOTE || state & S_COMMENT)
    return;

  if (token == LBRACE)
    pop();
  else
    push(RBRACE, line, col);
}

void handle_rbracket(int line, int col)
{
  extern int state;
  int token = peek();

  if (state & S_QUOTE || state & S_DQUOTE || state & S_COMMENT)
    return;

  if (token == LBRACKET)
    pop();
  else
    push(RBRACKET, line, col);
}

void handle_rparen(int line, int col)
{
  extern int state;
  int token = peek();

  if (state & S_QUOTE || state & S_DQUOTE || state & S_COMMENT)
    return;

  if (token == LPAREN)
    pop();
  else
    push(RPAREN, line, col);
}

void handle_star(int line, int col)
{
  extern int state;
  int c;

  if (state & S_QUOTE || state & S_DQUOTE)
    return;

  c = getchar(); /* look ahead */
  if (c == FWDSLASH) {
    if (state & S_COMMENT)
      exit_comment();
    else /* unbalanced comment termination */
      push(COMMENT_END, line, col);
  }
  else
    ungetc(c, stdin);
}

/* state machine actions */

void enter_character(int line, int col)
{
  extern int state;

  push(QUOTE, line, col);
  state |= S_QUOTE;
}

void exit_character(void)
{
  extern int state;

  pop();
  state ^= S_QUOTE;
}

void enter_comment(int line, int col)
{
  extern int state;

  push(COMMENT_BGN, line, col);
  state |= S_COMMENT;
}

void exit_comment(void)
{
  extern int state;

  pop();
  state ^= S_COMMENT;
}

void enter_escape(int line, int col)
{
  extern int state;

  push(BAKSLASH, line, col);
  state |= S_ESCAPE;
}

void exit_escape(void)
{
  extern int state;

  pop();
  state ^= S_ESCAPE;
}

void enter_string(int line, int col)
{
  extern int state;

  push(DQUOTE, line, col);
  state |= S_DQUOTE;
}

void exit_string(void)
{
  extern int state;

  pop();
  state ^= S_DQUOTE;
}

