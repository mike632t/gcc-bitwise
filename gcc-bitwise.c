/*
 * bitwise.c
 *
 * Copyright(C) 2020 - MT
 *
 * Demonstrates a number of integer math operations using bitwise operators
 * which  makes  these algorithms suitable for use  on  processors  without
 * 
 *
 * This  program is free software: you can redistribute it and/or modify it
 * under  the terms of the GNU General Public License as published  by  the
 * Free  Software Foundation, either version 3 of the License, or (at  your
 * option) any later version.
 *
 * This  program  is distributed in the hope that it will  be  useful,  but
 * WITHOUT   ANY   WARRANTY;   without even   the   implied   warranty   of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You  should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * 26 Dec 20   0.1   - Initial version - MT
 * 08 Jan 21   0.2   - Created additional functions to handle signed values
 *                     (with the calculation being done by passing unsigned
 *                     values  to the existing functions and modifying  the
 *                     sign of the result - MT
 *                   - Added  separate type definitions for data structures
 *                     to handle functions with either one or two signed or
 *                     unsigned parameters - MT
 *
 * To Do:            - 
 */

#define NAME         "bitwise"
#define VERSION      "0.3"
#define BUILD        "0003"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define  DEBUG       0
#define  SHORT

#define  FALSE       0 
#define  TRUE        !(FALSE)

#ifdef   SHORT
#define  LOWER      -32768       /* Limit testing to 16-bit values */
#define  UPPER       32767
#else
#define  LOWER       INT_MIN
#define  UPPER       INT_MAX
#endif
#define  SAMPLES     3           /* Number of values to test in each range */


/* Count number of bits in a byte using bitwise operations */

char cbits(n) char n; /* Count number of bits in a byte */
{
   n = n - ((n >> 1) & 0x55); 
   n = (n & 0x33) + ((n >> 2) & 0x33);
   n = (n + (n >> 4));
   return (n & 0x07);
}


/* Count number of bits in a word using bitwise operations */

unsigned ubits(n) unsigned n; 
{
   /* https://stackoverflow.com/questions/109023/ */
   n = n - ((n >> 1) & 0x55555555);
   n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
   n = (n + (n >> 4)) & 0x0F0F0F0F;
   n = n + (n >> 8);
   n = n + (n >> 16);
   return (n & 0x00000003F);
}


/* Count number of bits in a word using a loop for testing */

unsigned _ubits(n) unsigned n; 
{
   int r;
   r = 0;
   while (n != 0)
   {
      if (n & 1) r++;
      n = n >> 1;
   }
   return r;
}


/* Unsigned Two's compliment */

unsigned uneg(n) unsigned n;
{
   return (~n + 1);
}

unsigned _uneg(n) unsigned n; 
{
   return (n * - 1);
}


 /* Signed absolute value */

int iabs(n) int n;
{
   if (n < 0)
      return (uneg((unsigned)(n)));
   else
      return (n);
}


/* Signed absolute value */

int _iabs(n) int n;
{
   return (abs(n));
}


/* Unsigned fast integer multiply by 10 using bitwise operations */

unsigned umult10(n) unsigned n; 
{
    return (n << 3) + (n << 1); /* n = n * 8 + n * 2 */
}


/* Unsigned integer multiply by 10 */

unsigned _umult10(n) unsigned n; 
{
   return (n * 10);
}


/* Signed fast integer multiply by 10 using bitwise operations */

int imult10(n) int n; 
{
   if (n < 0)
      return (uneg(umult10(uneg((unsigned)(n)))));
   else
      return (umult10(n));
}


/* Signed integer multiply by 10 */

int _imult10(n) int n; 
{
   return (n * 10);
}


/* Unsigned fast integer division by 3 using bitwise operations */

unsigned udiv3(n) unsigned n;
{
   int r;
   r  = 0;
   while (n > 3) {
      r = (n >> 2) + r;
      n = (n >> 2) + (n & 3);
   }
   if (n == 3) r++;
   return r; 
}


/* Normal unsigned division by 3 */

unsigned _udiv3(n) unsigned n;
{
   return (n / 3);
}


/* Signed fast integer division by 3 using bitwise operations */

int idiv3(n) int n;
{
   if (n < 0)
      return (uneg(udiv3(uneg((unsigned)(n)))));
   else
      return (udiv3(n));
}


/* Normal signed division by 3 */

int _idiv3(n) int n; 
{
   return (n / 3);
}


/* Unsigned fast integer division by 10 using bitwise operations */

unsigned udiv10(n) unsigned n; 
{
   /* https://stackoverflow.com/questions/5558492/ */   
   unsigned q, r;
   q = (n >> 1) + (n >> 2);
   q = q + (q >> 4);
   q = q + (q >> 8);
   q = q + (q >> 16); /* Not required for 16 bits values*/
   q = q >> 3;
   r = n - (((q << 2) + q) << 1);
   return (q + (r > 9));
}


/* Normal unsigned division */

unsigned _udiv10(n) unsigned n; 
{
   return (n / 10);
}


/* Signed fast integer division by 10 using bitwise operations */

int idiv10(n) int n; 
{
   unsigned m;
   if (n < 0)
      m = uneg(udiv10(uneg((unsigned)(n))));
   else
      m = udiv10(n);
   return m; 
}


/* Normal signed division */

int _idiv10(n) int n; 
{
   return (n / 10);
}


/* Signed integer square root using bitwise operations (16-bit only) */

int isqrt(n) int n; 
{

   int p, q, r;
   p = n;
   r = 0; q = 0x4000;
   if (p >= 0)  /* Check for negative n */
   {
      while (q != 0)
      {
         if (p >= (r + q)) {
            p = p - (r + q); /* Find remainder */
            r = (r >> 1) + q; 
         } else {
            r = r >> 1;
         }
         q = q >> 2;
      }
   }
   else
   {
      r = -1;
   }
   return r;
}


/* Normal signed integer square root */

int _isqrt(n) int n; 
{
   int r;
   if (n >= 0)  /* Check for negative n */
      r = sqrt(n);
   else
      r = -1;
   return r;
}


/* Signed signed integer logarithm (base10) using bitwise division */

int ilog10(n) int n; 
{
   unsigned r;
   r = -1;
   if (n > 0)
   {
      while (n != 0)
      {
         n = udiv10(n);
         r++;   
      }
   }
   return r;
}


/* Normal signed integer logarithm (base10) */

int _ilog10(n) int n; 
{
   int r;
   r = -1;
   if (n > 0) /* Values less than 1 are invalid*/
      r = log10(n);
   return r;
}


/* Unsigned integer multiplication using bitwise operations */

unsigned umult(m, n) unsigned m, n; 
{
   unsigned r;
   r = 0;
   while (n != 0)
   {
      if (n & 1) r = r + m; /* Check for overflow needed here */
      m = m << 1;
      n = n >>1;
   }
   return r;
}


 /* Normal unsigned integer multiplication */
 
unsigned _umult(m, n) unsigned m, n;
{
   return (m * n);
}


/* Signed integer multiplication using bitwise operations */

int imult(m, n) int m, n;
{
   unsigned o;
   if (n < 0)
      return (uneg(umult(uneg((unsigned)(m)), n)));
   else
      return (umult(m, n));
    
}


/* Normal signed integer multiplication */

int _imult(m, n) int m, n; 
{
   return (m * n);
}


/* Unsigned integer division using bitwise operations */

unsigned udiv(m, n) unsigned m, n;
{
   /* https://stackoverflow.com/questions/12697523/ */
   int i, p, q, r;
   q = 0; r = 0;
   p = 31; /* Number of bits - 1 */
   if(n > 0)
      for(i = 31 ; i >= 0 ; i--)
      {
         q = q << 1;
         r = r << 1;
         r |= (m & (1 << i)) >> i;
         if(r >= n) {
            r = r - n;
            q |= 1;
         }
      }
   else
   {
      printf("\nDivision by zero.\n");
      q = -1;
   }
   return q;
}


/* Normal unsigned integer division */

unsigned _udiv(m, n) unsigned m, n;
{
   return (m / n);
}


/* Signed integer division using bitwise operations */

int idiv(m, n) int m, n; 
{
   unsigned o, p;
   if (m < 0)
      return (uneg(udiv(uneg((unsigned)(m)), n)));
   else
      return (udiv(m, n));
   return m; 
}


/* Normal signed integer division */

int _idiv(m, n) int m, n; 
{
   return (m / n);
}

/* The rest of the program is used to check that the results of the bitwise 
   operations  are correct (by comparing the results of a range  of  values
   around zero as well as he specified maximum and minimum values). */


/* Evaluate minimum */

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
      _a < _b ? _a : _b; })


/* Evaluate maximum */

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
      _a > _b ? _a : _b; })


int main()
{
   int i, j, k;
   int l, m, n;
   
   char *passed = " - Passed\n";
   char *failed = " - Failed\n";

   struct unsigned_unary {
      char *c;
      unsigned (*f) (unsigned);
      unsigned (*g) (unsigned);
   };

   struct signed_unary {
      char *c;
      int (*f) (int);
      int (*g) (int);
   };

   struct unsigned_binary {
      char *c;
      unsigned (*f)(unsigned, unsigned);
      unsigned (*g)(unsigned, unsigned);
   };
   
   struct signed_binary {
      char *c;
      int (*f)(int, int);
      int (*g)(int, int);
   };

   static const struct unsigned_unary unsigned_unary_tests[4] = 
   {
      {"ubits"    , ubits     , _ubits},
      {"uneg"     , uneg      , _uneg},
      {"umult10"  , umult10   , _umult10},
      {"udiv10"   , udiv10    , _udiv10}
   };
      
   static const struct signed_unary signed_unary_tests[5] = 
   {
      {"imult10"  , imult10   , _imult10},
      {"idiv10"   , idiv10    , _idiv10},
      {"isqrt"    , isqrt     , _isqrt},
      {"ilog"     , ilog10    , _ilog10},
      {"iabs"     , iabs      , _iabs}
   };

   static const struct unsigned_binary unsigned_binary_tests[2] = 
   {
      {"umult"    , umult     , _umult},
      {"udiv"     , udiv      , _udiv}
   };
      
   static const struct signed_binary signed_binary_tests[2] = 
   {
      {"imult"    , imult     , _imult},
      {"idiv"     , idiv      , _idiv},
   };

 
   int evaluate_unsigned_unary(test, n) struct unsigned_unary test; int n; 
   {
      int r = (test.f(n) ==  test.g(n));
      if (DEBUG || !r)
      {
         printf("%7s(%11d)  = % -11d ", test.c, n, test.f(n));
         if (r)
            printf("(Pass)\n");
         else
            printf("(Fail) Expected = % -11d \n", test.g(n));
      }
      return r;
   }

   int evaluate_signed_unary(test, n) struct signed_unary test; int n; 
   {
      int r = (test.f(n) ==  test.g(n));
      if (DEBUG || !r)
      {
         printf("%7s(%11d)  = % -11d ", test.c, n, test.f(n));
         if (r)
            printf("(Pass)\n");
         else
            printf("(Fail) Expected = % -11d \n", test.g(n));
      }
      return r;
   }

   int evaluate_unsigned_binary(test, m, n) struct unsigned_binary test; int m, n; 
   {
      int r = (test.f(m, n) ==  test.g(m, n));
      if (DEBUG || !r)
      {
         printf("%7s(%11d,%-11d) = % -11d ", test.c, m, n, test.f(m, n));
         if (r)
            printf("(Pass)\n");
         else
            printf("(Fail) Expected = % -11d \n", test.g(m, n));
      }
      return r;
   }

   int evaluate_signed_binary(test, m, n) struct signed_binary test; int m, n; 
   {
      int r = (test.f(m, n) ==  test.g(m, n));
      if (DEBUG || !r)
      {
         printf("%7s(%11d,%-11d) = % -11d ", test.c, m, n, test.f(m, n));
         if (r)
            printf("(Pass)\n");
         else
            printf("(Fail) Expected = % -11d \n", test.g(m, n));
      }
      return r;
   }


   /* Test an unsigned unary function */

   void test_unsigned_unary(test) struct unsigned_unary test; 
   {
      int r = TRUE;
      for (i = LOWER; i <= min(LOWER + SAMPLES - 1, UPPER); i++) 
         if (!evaluate_unsigned_unary(test, i)) r = FALSE;

      for (i = max(LOWER + SAMPLES, 0 - SAMPLES); i <= min(UPPER - SAMPLES, SAMPLES); i++) 
         if (!evaluate_unsigned_unary(test, i)) r = FALSE;

      l = 0;
      for (i = max(LOWER + SAMPLES, UPPER - SAMPLES + 1); l < UPPER; i++) 
      {
         l = i;
         if (!evaluate_unsigned_unary(test, i)) r = FALSE;
      } 
      if (r)
         printf("%7s()%s", test.c, passed);
      else
         printf("%7s()%s", test.c, failed);
      if (DEBUG) printf("\n");
   }   


   /* Test a signed unary function */

   void test_signed_unary(test) struct signed_unary test; 
   {
      int r = TRUE;
      for (i = LOWER; i <= min(LOWER + SAMPLES - 1, UPPER); i++) 
         if (!evaluate_signed_unary(test, i)) r = FALSE;

      for (i = max(LOWER + SAMPLES, 0 - SAMPLES); i <= min(UPPER - SAMPLES, SAMPLES); i++) 
         if (!evaluate_signed_unary(test, i)) r = FALSE;

      l = 0;
      for (i = max(LOWER + SAMPLES, UPPER - SAMPLES + 1); l < UPPER; i++) 
      {
         l = i;
         if (!evaluate_signed_unary(test, i)) r = FALSE;
      } 
      if (r)
         printf("%7s()%s", test.c, passed);
      else
         printf("%7s()%s", test.c, failed);
      if (DEBUG) printf("\n");
   }   


   /* Test an unsigned binary function */

   void test_unsigned_binary(test, j) struct unsigned_binary test;  int j; 
   {
      int r = TRUE;
      for (i = LOWER; i <= min(LOWER + SAMPLES - 1, UPPER); i++) 
         if (!evaluate_unsigned_binary(test, i, j)) r = FALSE;

      for (i = max(LOWER + SAMPLES, 0 - SAMPLES); i <= min(UPPER - SAMPLES, SAMPLES); i++) 
         if (!evaluate_unsigned_binary(test, i, j)) r = FALSE;

      l = 0;
      for (i = max(LOWER + SAMPLES, UPPER - SAMPLES + 1); l < UPPER; i++) 
      {
         l = i;
         if (!evaluate_unsigned_binary(test, i, j)) r = FALSE;
      } 
      if (r)
         printf("%7s()%s", test.c, passed);
      else
         printf("%7s()%s", test.c, failed);
      if (DEBUG) printf("\n");
   }   


   /* Test a signed binary function */

   void test_signed_binary(test, j) struct signed_binary test;  int j; 
   {
      int r = TRUE;
      for (i = LOWER; i <= min(LOWER + SAMPLES - 1, UPPER); i++) 
         if (!evaluate_signed_binary(test, i, j)) r = FALSE;

      for (i = max(LOWER + SAMPLES, 0 - SAMPLES); i <= min(UPPER - SAMPLES, SAMPLES); i++) 
         if (!evaluate_signed_binary(test, i, j)) r = FALSE;

      l = 0;
      for (i = max(LOWER + SAMPLES, UPPER - SAMPLES + 1); l < UPPER; i++) 
      {
         l = i;
         if (!evaluate_signed_binary(test, i, j)) r = FALSE;
      } 
      if (r)
         printf("%7s()%s", test.c, passed);
      else
         printf("%7s()%s", test.c, failed);
      if (DEBUG) printf("\n");
   }   
   
   
   /* Test all the unsigned unary functions */
   
   k = sizeof(unsigned_unary_tests)/sizeof(unsigned_unary_tests[0]);
   for (j = 0; j < k; j++)
      test_unsigned_unary(unsigned_unary_tests[j],i);

   /* Test all the signed unary functions */
   
   k = sizeof(signed_unary_tests)/sizeof(signed_unary_tests[0]);
   for (j = 0; j < k; j++)
      test_signed_unary(signed_unary_tests[j],i);

   /* Test all the unsigned binary functions */
   
   k = sizeof(unsigned_binary_tests)/sizeof(unsigned_binary_tests[0]);
   for (j = 0; j < k; j++)
      test_unsigned_binary(unsigned_binary_tests[j], 5);
 
   /* Test all the signed binary functions */
   
   k = sizeof(signed_binary_tests)/sizeof(signed_binary_tests[0]);
   for (j = 0; j < k; j++)
      test_signed_binary(unsigned_binary_tests[j], 5);
}
