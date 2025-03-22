#ifndef KR_BITWISE
#define KR_BITWISE

/**
 * print_binary() - Print the provided integral number in binary format
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
void kr_print_binary(unsigned x);


#endif /* KR_BITWISE */
