#include <stdio.h>
#include "kr_common.h"
#include "kr_debug.h"

/**
 *
 */
void kr_debug_print_char(const char c)
{
  switch (c) {
    case KR_C_NEWLINE:
      printf("\\n");
      break;

    case KR_C_SPACE:
      printf("·");
      break;

    case KR_C_TAB:
      printf("\\t");
      break;

    default:
      printf("%c", c);
      break;
  }
}

/**
 *
 */
void kr_debug_print_str(const char s[], int len)
{
  int i;

  if (len <= 0 || s[0] == '\0') {
    printf("[ empty/invalid string ]\n");
    return;
  }

  printf("[ ");

  for (i = 0; i < len - 1 && s[i] != '\0'; ++i) {
    kr_debug_print_char(s[i]);
    printf("%c", KR_DEBUG_SEPARATOR);
  }

  if (i == len && s[i] != '\0')
    printf(" ... (unterminated) ]\n");
  else
    printf("\\0 ]\n");
}

