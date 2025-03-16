/* 2.9 Bitwise Operators
 *
 * Exercise 2-7. Write a function invert(x,p,n) that returs x with the n bits
 * that begin at position p inverted (ie. 1 changed to 0 and vice versa),
 * leaving the others unchanged. */

#include <stdio.h>

/* The function invert should make a copy of x and apply a XOR on a masked
 * section. The print_binary utility function helps debugging. */

unsigned invert(unsigned x, int p, int n);

void print_binary(unsigned x);

int main()
{
  print_binary(0xffu);
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

  /* validate p and n */

  /* create mask */
  mask = ~(~0u << n) << (p + 1); /* mask -> 0011 1100 ... 0000 */

  return (x & ~mask) | ((x ^ x) & mask);
}

/**
 * print_binary() - Print the provided integral number in binary format.
 * @x: The unsigned integral number to print.
 *
 * The binary string is produced by bitwise-and'ing the provided value with a
 * moving mask of 1 bit, shifting from the leftmost to the rightmost position.
 * 
 * The mask is obtained by leveraging the fact that ~0u does not carry the sign
 * bit when right-shifting, so:
 *
 *     ~0u       -> 1111 1111 ... 1111
 *     ~0u >> 1  -> 0111 1111 ... 1111
 *   ~(~0u >> 1) -> 1000 0000 ... 0000
 *
 * Formatting -- The binary string is printed starting from the MSB and for
 * easier readability, a whitespace is introduced every four characters.
 * Furthermore, no newline is added at the end of the binary string.
 */
void print_binary(unsigned x)
{
  unsigned mask = ~(~0u >> 1); /* mask -> 1000 0000 ... 0000  */
  int i = 0;                   /* used to print spacing every 4 bits */

  while (mask > 0) {
    printf("%c", x & mask ? '1' : '0');
    mask >>= 1;

    /* `mask > 1` avoids trailing space */
    if (i++ % 4 == 3 && mask > 1)
      printf(" ");
  }
}

