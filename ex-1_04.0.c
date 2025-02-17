/* 1.2 Variables and Arithmetic Expressions
 *
 * Exercise 1-4. Write a program to print the corresponding Celsius to
 * Fahrenheit table. */

#include <stdio.h>

int main()
{
  float fahr, celsius;
  int lower, upper, step;

  lower = 0;
  upper = 100;
  step = 10;

  printf("Celsius\tFahr\n");

  celsius = lower;
  while (celsius <= upper) {
    fahr = celsius * (9.0/5.0) + 32.0;
    printf("%5.0f\t%3.1f\n", celsius, fahr);
    celsius = celsius + step;
  }

  return 0;
}

