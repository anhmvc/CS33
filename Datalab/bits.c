/* 
 * CS:APP Data Lab 
 * 
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

/*
 * STEP 2: Modify the following functions according the coding rules.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* 
 * specialBits - return bit pattern 0xffca3fff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 3
 *   Rating: 1
 */
int specialBits(void) {
  return ~(215 << 14);
}

/*    
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int exception  = !(x+1);
  x = x+(x+1);
  return !((~x)|exception);
}

/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
  int evenMask = 0x55 ^ (0x55 << 8) ^ (0x55 << 16) ^ (0x55 << 24);
  return !!(x & evenMask);
}

/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  int mask = 0xFF << (n<<3);
  int replaceMask = c << (n<<3);
  return (x & ~mask) ^ replaceMask;
}

/* 
 * signMag2TwosComp - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: signMag2TwosComp(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int signMag2TwosComp(int x) {
  int mask = (1 << 31); // returns 100..01
  int MSB = (x >> 31); // return 00..00 for positive number and 11..11 for negative number
  return (MSB & (((~x)^mask)+1)) | (~MSB & x);
}

/* 
 * twosComp2SignMag - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
*   You can assume that x > TMin
 *   Example: twosComp2SignMag(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int twosComp2SignMag(int x) {
  int mask =  (1<<31);
  int MSB = (x>>31);
  return (MSB & ((~x+1)^mask)) | (~MSB & x);
}

/*
 * intLog2 - return floor(log base 2 of x), where x > 0
 *   Example: intLog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int intLog2(int x) {
  x = x | (x>>1);
  x = x | (x>>2);
  x = x | (x>>4);
  x = x | (x>>8);
  x = x | (x>>16);
  // create bitmask with 1s following to the left of the rightmost set bit
  x = (x&(0x55 + (0x55 << 8) + (0x55 << 16) + (0x55 << 24))) + ((x>>1)&(0x55 + (0x55 << 8) + (0x55 << 16) + (0x55 << 24))); // 01010101010101010101010101010101
  x = (x&(0x33 + (0x33 << 8) + (0x33 << 16) + (0x33 << 24))) + ((x>>2)&(0x33 + (0x33 << 8) + (0x33 << 16) + (0x33 << 24))); // 00110011001100110011001100110011
  x = (x&(0x0F + (0x0F << 8) + (0x0F << 16) + (0x0F << 24))) + ((x>>4)&(0x0F + (0x0F << 8) + (0x0F << 16) + (0x0F << 24))); // 00001111000011110000111100001111
  x = (x&(0xFF + (0xFF << 16))) + ((x>>8)&(0xFF + (0xFF << 16))); // 00000000111111110000000011111111
  x = (x&(0xFF + (0xFF << 8))) + ((x>>16)&(0xFF + (0xFF << 8)));  // 00000000000000001111111111111111
  // subtract one from final count because we're trying to find the floor of log2
  x = ~x + (x<<1);
  return x;
}
