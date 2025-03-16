/* 2.8 Increment and Decrement Operators
 *
 * Exercise 2-4. Write an alternate version of squeeze(s1,s2) that deletes each
 * character in s1 that matches any character in the string s2.
 *
 * NOTE ~ The original implementation of squeeze is:
 *
 *   // squeeze: delete all c from s
 *   void squeeze(char s[], int c)
 *   {
 *      int i, j;
 *      for (i = j = 0; s[i] != '\0'; i++)
 *        if (s[i] != c)
 *          s[j++] = s[i];
 *      s[j] = '\0';
 *   }
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define ASCII_SIZE   0x7f

void squeeze(char s1[], const char s2[]);

int main()
{
  char s1[] = "sono solo stasera senza di te.";
  char s2[] = "so.";

  printf("Original string: \"%s\"\n", s1);
  printf("Removing character: \"%s\"\n", s2);

  squeeze(s1, s2);

  printf("Resulting string: \"%s\"\n", s1);
  assert(strcmp(s1, "n l taera enza di te") == 0);

  return 0;
}

void squeeze(char s1[], const char s2[])
{
  int i, j;
  unsigned char lookup[ASCII_SIZE] = {0};

  for (i = 0; s2[i] != '\0'; ++i)
    if ((unsigned char)s2[i] <= ASCII_SIZE)
      lookup[(unsigned char)s2[i]] = 1;

  for (i = j = 0; s1[i] != '\0'; ++i)
    if (!lookup[(unsigned char)s1[i]])
      s1[j++] = s1[i];

  s1[j] = '\0';
}

