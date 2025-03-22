/* 2.9 Bitwise Operators
 *
 * Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n
 * bits that begin at position p set to the rightmost n bits of y, leaving the
 * other bits unchanged. */

#include <stdio.h>
#include "kr_bitwise.h"

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main()
{ 
  kr_print_binary(0x7ab4f0c9);
  printf("\n");
  kr_print_binary(0xffffea);
  printf("\n");
  kr_print_binary(setbits(0x7ab4f0c9, 17, 5, 0xffffea));
  printf("\n");
  return 0;
}

/*
 * x: 0000 0000 0000 0000 0000 0000 0000 1100
 *                                   p ->n   
 */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  unsigned mask = ~0u;
  int max_p, shift_pos;

  if (n == 0)
    return x;

  for (max_p = 0; (mask >>= 1) > 0; ++max_p)
    ;

  /* "begins at position p", p starting from 0, implies n <= p + 1 */
  shift_pos = p + 1 - n;
  if (p < 0 || p > max_p - 1 || shift_pos < 0)
    return x;

  /* The mask is like: 0000 0011 1100 0000
   *                          p ->n
   */
  mask = ~(~0u << n) << shift_pos;

  /* `& ~mask` creates a hole in a word, preserving the rest.
   * `& mask` filters out what is not within [p, p-n]. */
  return (x & ~mask) | ((y << shift_pos) & mask);
}


