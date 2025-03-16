/* 2.7 Type Conversions
 *
 * Exercise 2-3. Write the function htoi(s), which converts a string to
 * hexadecimal digits (including an optional 0x or 0X) into its equivalent
 * integer value. The allowable digits are 0 through 9, a through f, and A
 * through F. */

#include <stdio.h>

int has_hex_suffix(const char s[]);
int htoi(const char s[]);
int get_decimal_value(char c);

int main()
{
  printf("8 -> %d\n", htoi("8"));
  printf("0x8 -> %d\n", htoi("0x8"));
  printf("a -> %d\n", htoi("a"));
  printf("f -> %d\n", htoi("f"));
  printf("10 -> %d\n", htoi("10"));
  printf("7f -> %d\n", htoi("7f"));
  printf("0X7f -> %d\n", htoi("0X7f"));
  printf("7g -> %d\n", htoi("7g"));

  return 0;
}

int has_hex_suffix(const char s[])
{
  return s[0] == '0' &&
    (s[1] == 'x' || s[1] == 'X');
}

int htoi(const char s[])
{
  int i, dec;
  int res = 0;
  int prev;

  i = has_hex_suffix(s) ? 2 : 0;

  for (; s[i] != '\0'; ++i) {
    if ((dec = get_decimal_value(s[i])) == -1)
      return -1;

    prev = res;
    res = res * 16 + dec; 

    /* error: overflow occurred */
    if (res < prev * 16)
      return -1;
  }

  return res;
}


int get_decimal_value(char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';

  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;

  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;

  return -1;
}

