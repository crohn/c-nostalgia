/* 2.9 Bitwise Operators
 *
 * Exercise 2-7. Write a function invert(x,p,n) that returs x with the n bits
 * that begin at position p inverted (ie. 1 changed to 0 and vice versa),
 * leaving the others unchanged. */

#include <stdio.h>
#include "kr_bitwise.h"

/* The function invert should make a copy of x and apply a XOR on a masked
 * section. The print_binary utility function helps debugging. */

unsigned invert(unsigned x, int p, int n);

int main()
{
  unsigned value = 0xa1u;

  kr_print_binary(value);
  printf("\n");
  kr_print_binary(invert(value, 7, 5));
  printf("\n");

  return 0;
}

/**
 * invert() - Invert subset of contiguous bits, leaving the others untouched.
 * @x: The unsigned integral number target of inversion.
 * @p: Bit inversion starting position, zero-based.
 * @n: The amount of bits that will be inverted.
 *
 * p and n are validated so that 0 <= p <= size(x) and 0 <= n <= p+1.
 *
 * Return: --
 */
unsigned invert(unsigned x, int p, int n)
{
  unsigned mask;

  if (n == 0)
    return x;

  if (n < 0 || n > p + 1) {
    printf("ERROR: n must me such that 0 <= n <= p + 1, got n:%d, p:%d\n", n, p);
    return x;
  }

  /* create mask */
  mask = ~(~0u << n) << (p + 1 - n); /* mask -> 0011 1100 ... 0000 */

  return (x & ~mask) | (~x & mask);
}



