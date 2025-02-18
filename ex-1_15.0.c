/* 1.7 Functions
 *
 * Exercise 1-15. Rewrite the temperature conversion program of Section 1.2 to
 * use a function for conversion. */

#include <stdio.h>

float ftoc(float fahr);

int main()
{
  int fahr;

  for (fahr = 300; fahr >= 0; fahr = fahr - 20)
    printf("%3d %6.1f\n", fahr, ftoc(fahr));

  return 0;
}

float ftoc(float fahr)
{
  return (5.0 / 9.0) * (fahr - 32);
}

