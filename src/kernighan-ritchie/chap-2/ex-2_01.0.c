/* 2.2 Data Types and Sizes
 *
 * Exercise 2-1. Write a program to determine the ranges of char, short, int,
 * and long variables, both signed and unsigned, by printing appropriate values
 * from standard headers and by direct computation. Harder if you compute them:
 * determine the ranges of the various floating-point types. */

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

/* NOTE ~ Two's complement representation, shifting the unsigned 0xff so the
 * leading 1 is not carried: 0xff > 0x7f */
/* 0x7f > 0x80 */
#define COMPUTE_RANGES(UTYPE, STYPE, UMIN, UMAX, SMIN, SMAX) \
  const UTYPE UMIN = 0; \
  const UTYPE UMAX = ~UMIN; \
  const STYPE SMAX = UMAX >> 1; \
  const STYPE SMIN = ~SMAX;

#define POW_2_23          8388608.0f
#define POW_2_52          4503599627370496.0

#define FP32_DENORM_POW  -126
#define FP32_NORM_BIAS    127
#define FP32_E_DENORM     0x00
#define FP32_E_INF_NAN    0xff


float calc_float(int s, int e, int f);
double calc_double(int s, int e, long long f);

int main()
{
  COMPUTE_RANGES(unsigned char, signed char, min_uchar, max_uchar, min_char, max_char)
  COMPUTE_RANGES(unsigned short, short, min_ushort, max_ushort, min_short, max_short)
  COMPUTE_RANGES(unsigned int, int, min_uint, max_uint, min_int, max_int)
  COMPUTE_RANGES(unsigned long, long, min_ulong, max_ulong, min_long, max_long)

  const float max_flt = calc_float(0, 0xfe, 0x7fffff);
  const float min_flt = calc_float(1, 0xfe, 0x7fffff);
  const float neg_inf = calc_float(1, 0xff, 0x0);
  const float pos_inf = calc_float(0, 0xff, 0x0);
  const float nan = calc_float(0, 0xff, 0x1);

  printf("RANGES FROM STANDARD HEADERS\n");
  printf("============================\n");
  printf("u  char:   %20u\t%20u\n", 0, UCHAR_MAX);
  printf("   char:   %20d\t%20d\n", SCHAR_MIN, SCHAR_MAX);
  printf("u short:   %20u\t%20u\n", 0, USHRT_MAX);
  printf("  short:   %20d\t%20d\n", SHRT_MIN, SHRT_MAX);
  printf("u   int:   %20u\t%20u\n", 0, UINT_MAX);
  printf("    int:   %20d\t%20d\n", INT_MIN, INT_MAX);
  printf("u  long:   %20lu\t%20lu\n", 0L, ULONG_MAX);
  printf("   long:   %20ld\t%20ld\n", LONG_MIN, LONG_MAX);
  printf("\nRANGES FROM DIRECT COMPUTATION\n");
  printf("==============================\n");
  printf("u  char:   %20u\t%20u\n", min_uchar, max_uchar);
  printf("   char:   %20d\t%20d\n", min_char, max_char);
  printf("u short:   %20u\t%20u\n", min_ushort, max_ushort);
  printf("  short:   %20d\t%20d\n", min_short, max_short);
  printf("u   int:   %20u\t%20u\n", min_uint, max_uint);
  printf("    int:   %20d\t%20d\n", min_int, max_int);
  printf("u  long:   %20lu\t%20lu\n", min_ulong, max_ulong);
  printf("   long:   %20ld\t%20ld\n", min_long, max_long);
  printf("\nFP32                          \n");
  printf("==============================\n");
  printf("  float max:   %e\n", max_flt);
  printf("  float min:   %e\n", min_flt);
  printf("       -inf:   %f\n", neg_inf);
  printf("       +inf:   %f\n", pos_inf);
  printf("        NaN:   %f\n", nan);

  return 0;
}

/* FP32 representation
 *
 *  1   -8-                -23-            
 *  0000 0000 0000 0000 0000 0000 0000 0000
 *  S'--[E]---''-----------[F]------------'
 * 
 *  NORMALIZED
 *    - E != 0x00, E != 0xff
 *    - Leading `1` in significand
 * 
 *  DENORMALIZED -> E == 0x00
 *
 *  INFINITY/NAN -> E == 0xff
 */
float calc_float(int s, int e, int f)
{
  float sign, exp, significand;

  if (e == FP32_E_INF_NAN) {
    if (f == 0) {
      return s ? -INFINITY : INFINITY;
    }
    return NAN;
  }

  sign = powf(-1.0f, s);
  significand = ((float)f / POW_2_23);

  if (e == FP32_E_DENORM)
    exp = powf(2.0f, FP32_DENORM_POW);
  else {
    exp = powf(2.0f, e - FP32_NORM_BIAS);
    significand += 1.0f;
  }

  return sign * exp * significand;
}

