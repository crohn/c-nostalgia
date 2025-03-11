/* 2.8 Increment and Decrement Operators
 *
 * Exercise 2-5. Write the function any(s1,s2), which returns the first
 * location in the string s1 where any character from the string s2 occurs, or
 * -1 if s1 contains no characters from s2. (The standard library function
 * strpbrk does the same job but returns a pointer to the location.) */

#include <assert.h>
#include <stdio.h>

#define ASCII_SIZE      0x7f

int any(const char s1[], const char s2[]);

int main()
{
  assert(any("0123456789abcdef", "0") == 0);
  assert(any("0123456789abcdef", "a") == 10);
  assert(any("0123456789abcdef", "f") == 15);
  assert(any("0123456789abcdef", "g") == -1);

  return 0;
}

int any(const char s1[], const char s2[])
{
  int i;
  char lookup[ASCII_SIZE] = {0};
  unsigned char c;

  for (i = 0; s2[i] != '\0'; ++i) {
    c = s2[i];
    if (c <= ASCII_SIZE)
      lookup[c] = 1;
  }

  for (i = 0; s1[i] != '\0'; ++i) {
    c = s1[i];
    if (c <= ASCII_SIZE && lookup[c])
      return i;
  }

  return -1;
}

