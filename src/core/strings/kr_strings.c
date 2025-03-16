#include <stdio.h>
#include "kr_common.h"
#include "kr_strings.h"

/**
 * kr_is_blank_char - Test if provided character is blank
 *
 * See kr_strings.h for API details.
 */
int kr_is_blank_char(char c)
{
  switch (c) {
    case KR_C_NEWLINE:
    case KR_C_SPACE:
    case KR_C_TAB:
      return 1;
    default:
      return 0;
  }
}


/**
 * kr_copy - Copy characters from a string buffer to another
 *
 * See kr_strings.h for API details.
 *
 * Implementation notes:
 *   - This is a simplified version of the standard strcpy() function
 *   - This function is unsafe
 *
 * Context: This implementation is based on K&R C Programming Language book.
 */
void kr_copy(char to[], const char from[])
{
  int i;

  for (i = 0; (to[i] = from[i]) != '\0'; ++i)
    ;
}


/**
 * kr_getline - Read input into a string buffer
 *
 * See kr_strings.h for API details.
 *
 * Implementation notes:
 *   - This is a simplified version of the standard getline() function
 *   - Character-by-character reading allows for precise control over buffer
 *     limits
 *   - Special return value of -1 to signal immediate EOF corner case
 *
 * Context: This implementation is based on K&R C Programming Language book.
 */
int kr_getline(char buffer[], int max_len)
{
  int i, c;

  for (i = 0; i < max_len - 1 && (c = getchar()) != EOF && c != KR_C_NEWLINE; ++i)
    buffer[i] = c;

  if (c == EOF && i == 0)
    return -1;

  if (c == KR_C_NEWLINE)
    buffer[i++] = c;

  buffer[i] = '\0';

  return i;
}


/**
 * kr_reverse - Reverse the provided character string
 *
 * Swap end-of-string and start-of-string characters converging to the middle
 * of the string.
 *
 * Since no string length is provided, end-of-string is computed by looking for
 * null terminator. For this reason, the function is considered unsafe.
 *
 * Context: This implementation is based on K&R C Programming Language book.
 */
void kr_reverse(char s[])
{
  int i, j;
  char tmp; /* temporary character to perform the swap */

  for (j = 0; s[j+1] != '\0'; ++j)
    ;

  /* Do not reverse newline character at end of string, if present */
  if (s[j] == KR_C_NEWLINE)
    --j;

  for (i = 0; i < j; ++i, --j) {
    tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
  }
}


/**
 * kr_trim - Remove trailing blanks from provided character string
 *
 * See kr_strings.h for API details.
 *
 * Implementation notes:
 *   - The string is scanned backwards for better performance 
 *   - Empty lines are deleted by returning len 0 and truncating the provided
 *   string with a null terminator at the beginning
 *
 * Context: This implementation is based on K&R C Programming Language book.
 */
int kr_trim(char s[], int len)
{
  int i;
  int last_newline = -1; /* Index of last newline char occurrence */

  /* Handle empty strings */
  if (len <= 0 || s[0] == '\0' || s[0] == KR_C_NEWLINE) {
    s[0] = '\0';
    return 0;
  }

  /* Scan backward, until the first non-blank char is found */
  for (i = len - 1; i > 0 && kr_is_blank_char(s[i]); --i)
    if (last_newline == -1 && s[i] == KR_C_NEWLINE)
      /* Note down last newline char position */
      last_newline = i;

  /* The string included only blank characters */
  if (i == 0 && kr_is_blank_char(s[i])) {
    s[0] = '\0';
    return 0;
  }

  /* Preserve newline character */
  if (last_newline > 0)
    s[++i] = KR_C_NEWLINE;

  s[i+1] = '\0';

  return i + 1;
}

