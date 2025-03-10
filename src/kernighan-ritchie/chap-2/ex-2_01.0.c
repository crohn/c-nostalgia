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

/* NOTE
 * I'm starting with unsigned because UMAX >> 1 does not carry the sign, eg.
 *
 *    0xff >> 1 -> 0x7f
 *
 * From there, by two's complement definition, I get the min.
 */
#define COMPUTE_RANGES(UTYPE, STYPE, UMIN, UMAX, SMIN, SMAX) \
  const UTYPE UMIN = 0; \
  const UTYPE UMAX = ~UMIN; \
  const STYPE SMAX = UMAX >> 1; \
  const STYPE SMIN = ~SMAX;

#define POW_2_23          8388608.0f
#define POW_2_52          4503599627370496.0

/* denormalized scale -> 2^-126 */
#define FP32_DENORM_SCALE 1.17549435e-38f
#define FP32_NORM_BIAS    127
#define FP32_E_DENORM     0x00
#define FP32_E_INF_NAN    0xff

/* denormalized scale -> 2^-1022 */
#define FP64_DENORM_SCALE 2.2250738585072014e-308
#define FP64_NORM_BIAS    1023
#define FP64_E_DENORM     0x000
#define FP64_E_INF_NAN    0x7ff

float calc_float(int s, int e, int f);
double calc_double(int s, int e, long long f);

int main()
{
  COMPUTE_RANGES(unsigned char, signed char, min_uchar, max_uchar, min_char, max_char)
  COMPUTE_RANGES(unsigned short, short, min_ushort, max_ushort, min_short, max_short)
  COMPUTE_RANGES(unsigned int, int, min_uint, max_uint, min_int, max_int)
  COMPUTE_RANGES(unsigned long, long, min_ulong, max_ulong, min_long, max_long)

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
  printf("\n");
  printf("RANGES FROM DIRECT COMPUTATION\n");
  printf("==============================\n");
  printf("u  char:   %20u\t%20u\n", min_uchar, max_uchar);
  printf("   char:   %20d\t%20d\n", min_char, max_char);
  printf("u short:   %20u\t%20u\n", min_ushort, max_ushort);
  printf("  short:   %20d\t%20d\n", min_short, max_short);
  printf("u   int:   %20u\t%20u\n", min_uint, max_uint);
  printf("    int:   %20d\t%20d\n", min_int, max_int);
  printf("u  long:   %20lu\t%20lu\n", min_ulong, max_ulong);
  printf("   long:   %20ld\t%20ld\n", min_long, max_long);
  printf("\n");
  printf("FP32 - notable cases\n");
  printf("==============================\n");
  printf("smallest positive subnormal:  %.10e\n", calc_float(0, 0x00, 0x000001));
  printf("          largest subnormal:  %.10e\n", calc_float(0, 0x00, 0x7fffff));
  printf("   smallest positive normal:  %.10e\n", calc_float(0, 0x01, 0x000000));
  printf("             largest normal:  %.10e\n", calc_float(0, 0xfe, 0x7fffff));
  printf("      largest number lt one:  %.10e\n", calc_float(0, 0x7e, 0x7fffff));
  printf("                        one:  %.10e\n", calc_float(0, 0x7f, 0x000000));
  printf("     smallest number gt one:  %.10e\n", calc_float(0, 0x7f, 0x000001));
  printf("                  minus two:  %.10e\n", calc_float(1, 0x80, 0x000000));
  printf("                       zero:  %.10e\n", calc_float(0, 0x00, 0x000000));
  printf("                 minus zero:  %.10e\n", calc_float(1, 0x00, 0x000000));
  printf("                   infinity:  %.10e\n", calc_float(0, 0xff, 0x000000));
  printf("             minus infinity:  %.10e\n", calc_float(1, 0xff, 0x000000));
  printf("                         pi:  %.10e\n", calc_float(0, 0x80, 0x490fdb));
  printf("                  one third:  %.10e\n", calc_float(0, 0x7d, 0x2aaaab));
  printf("                       qNaN:  %.10e\n", calc_float(0, 0xff, 0x400001));
  printf("                       sNaN:  %.10e\n", calc_float(0, 0xff, 0x000001));
  printf("\n");
  printf("FP64 - notable cases\n");
  printf("==============================\n");
  printf("                        one: %.16e\n", calc_double(0, 0x3ff, 0x0000000000000));
  printf("     smallest number gt one: %.16e\n", calc_double(0, 0x3ff, 0x0000000000001));
  printf("                        two: %.16e\n", calc_double(0, 0x400, 0x0000000000000));
  printf("                  minus two: %.16e\n", calc_double(1, 0x400, 0x0000000000000));
  printf("                      three: %.16e\n", calc_double(0, 0x400, 0x8000000000000));
  printf("                       four: %.16e\n", calc_double(0, 0x401, 0x0000000000000));
  printf("                       five: %.16e\n", calc_double(0, 0x401, 0x4000000000000));
  printf("                        six: %.16e\n", calc_double(0, 0x401, 0x8000000000000));
  printf("smallest positive subnormal: %.16e\n", calc_double(0, 0x000, 0x0000000000001));
  printf("          largest subnormal: %.16e\n", calc_double(0, 0x000, 0xfffffffffffff));
  printf("   smallest positive normal: %.16e\n", calc_double(0, 0x001, 0x0000000000000));
  printf("             largest normal: %.16e\n", calc_double(0, 0x7fe, 0xfffffffffffff));
  printf("                       zero: %.16e\n", calc_double(0, 0x000, 0x0000000000000));
  printf("                 minus zero: %.16e\n", calc_double(1, 0x000, 0x0000000000000));
  printf("                   infinity: %.16e\n", calc_double(0, 0x7ff, 0x0000000000000));
  printf("             minus infinity: %.16e\n", calc_double(1, 0x7ff, 0x0000000000000));
  printf("                       qNaN: %.16e\n", calc_double(0, 0x7ff, 0x0000000000001));
  printf("                       sNaN: %.16e\n", calc_double(0, 0x7ff, 0x8000000000000));
  printf("              alternate NaN: %.16e\n", calc_double(0, 0x7ff, 0xfffffffffffff));

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
 *    - Leading `1.` in significand
 * 
 *  DENORMALIZED -> E == 0x00
 *
 *  INFINITY/NAN -> E == 0xff
 */
float calc_float(int s, int e, int f)
{
  float sign, exp, significand;

  if (s != 0 && s != 1) {
    printf("ERROR: Sign bit must be either 0 or 1, got %d\n", s);
    return NAN;
  }

  if (e < 0 || e > 0xff) {
    printf("ERROR: Exponent must be between 0x00 and 0xff, got 0x%X\n", e);
    return NAN;
  }

  if (f < 0 || f > 0x7fffff) {
    printf("ERROR: Fraction must be between 0x000000 and 0x7fffff, got 0x%X\n", f);
    return NAN;
  }

  if (e == FP32_E_INF_NAN) {
    if (f == 0) {
      return s ? -INFINITY : INFINITY;
    }
    return NAN;
  }

  sign = s == 0 ? 1.0f : -1.0f;
  significand = ((float)f / POW_2_23);

  if (e == FP32_E_DENORM)
    exp = FP32_DENORM_SCALE;
  else {
    exp = powf(2.0f, e - FP32_NORM_BIAS);
    significand += 1.0f;
  }

  return sign * exp * significand;
}

/* FP64 representation
 *
 *  1     -11-                                   -52-
 *  0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
 *  S'----[E]----' '-----------------------------[F]------------------------------'
 *
 *  NORMALIZED
 *    - E != 0x000, E != 0x7ff
 *    - Leading `1.` in significand
 *
 *  DENORMALIZED -> E == 0x000
 *
 *  INFINITY/NAN -> E == 0x7ff
 */
double calc_double(int s, int e, long long f)
{
  double sign, exp, significand;

  if (s != 0 && s != 1) {
    printf("ERROR: Sign bit must be either 0 or 1, got %d\n", s);
    return NAN;
  }

  if (e < 0 || e > 0x7ff) {
    printf("ERROR: Exponent must be between 0x000 and 0x7ff, got 0x%X\n", e);
    return NAN;
  }

  if (f < 0 || f > 0xfffffffffffff) {
    printf("ERROR: Fraction must be between 0x0000000000000 and 0xfffffffffffff, got 0x%llX\n", f);
    return NAN;
  }

  if (e == FP64_E_INF_NAN) {
    if (f == 0) {
      return s ? -INFINITY : INFINITY;
    }
    return NAN;
  }

  sign = s == 0 ? 1.0 : -1.0;
  significand = ((double)f / POW_2_52);

  if (e == FP64_E_DENORM)
    exp = FP64_DENORM_SCALE;
  else {
    exp = pow(2.0, e - FP64_NORM_BIAS);
    significand += 1.0;
  }

  return sign * exp * significand;
}

