#include <stdio.h>
#include "kr_bitwise.h"

/**
 * print_binary() - Print the provided integral number in binary format
 */
void kr_print_binary(unsigned x)
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

