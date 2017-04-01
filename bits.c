/*
 * Assignment: Bit Twiddling
 * Class: CSC 252 Spring 2017
 *
 * Name: Wenyi Chu
 * Partner's Name: <Insert Partner's Name Here, or leave as is if you have no partner>
 *
 * TAs: Sayak Chakraborti (schakr11@cs.rochester.edu)
 *      Kevin Gerami(kgerami@u.rochester.edu)
 *
 * Instructions:
 * Fill in the following functions and turn this file in.
 *
 * Restrictions:
 * You MAY NOT change any of the function defintions.
 * You MAY NOT define any global variables, macros, or other functions.
 * You MAY NOT use any operations not listed in the function's description.
 * You MAY NOT use any control statements (if, loops, switch, function calls).
 * You MAY NOT use any constants outside of an unsigned byte (0 - 255 (0xFF) inclusive).
 * You MAY NOT cast any variables.
 * You MAY NOT use data types other than ints.
 *
 * You MAY define local variables.
 * You MAY use the assignment versions of allowed operators (+=, |=, etc).
 * You MAY use more than one operator per line.
 *
 * Your results will be tested on a machine that:
 * Uses 2s complement, 32-bit representations of integers.
 * Performs right shifts arithmetically.
 * Has unpredictable behavior when shifting an integer by more than the word size.
 * Bits are 0-indexed and numbered in order of increasing significance (right-to-left) so the 0th bit is the rightmost bit.
 *
 * If any of the instructions or function descriptions are unclear please contact the TA (see
 * above).
 */

/*
 * evenBits: Return the word with all even-numbered bits set to 1.
 *   Legal ops: ! ~ & ^ | + << >>
 */
int evenBits(void) {

    int b = 0x55;
    int word = b | b<<8 | b<<16 | b<<24;
    return  word;
}

/*
 * bitAnd: Compute the bitwise-and of x and y.
 *   Example: bitAnd(3, 5) = 1
 *   Legal ops: ~ |
 */
int bitAnd(int x, int y) {
    int a = ~x;
    int b = ~y;
    int res = ~(a|b);
    return res;
}

/*
 * swapBytes: Swap the 0th (rightmost) and 2nd bytes of x.
 *   Example: swapBytes(0x33221100) = 0x33001122
 *   Legal ops: ! ~ & ^ | + << >>
 */
int swapBytes(int x) {
	// suppose x = byte3|byte2|byte1|byte0
	
	// int a = x<<16; 			// a = byte1|byte0|0000 |0000
	// a = 0x00ff0000 & a;		// a = 0000 |byte0|0000 |0000
	// int b = x>>16; 			// b = 0000 |0000 |byte3|byte2
	// b = 0x000000ff & b;		// b = 0000 |0000 |0000 |byte2

	
	// int c = a ^ b;			// c = 0000 |byte0|0000 |byte2
	// int d = 0xff00ff00 & x; // d = byte3|0000 |byte1|0000


	int a = x << 16; 			// a = byte1|byte0|0000 |0000
	a = (0x00ff<<16) & a;		// a = 0000 |byte0|0000 |0000
	int b = x >> 16; 			// b = 0000 |0000 |byte3|byte2
	b = 0x00ff & b;				// b = 0000 |0000 |0000 |byte2

	
	int c = a ^ b;				// c = 0000 |byte0|0000 |byte2
	int d = ((0xff00<<16)|0xff00) & x; 
								// d = byte3|0000 |byte1|0000

	int res = c ^ d;			// res = byte3|byte0|byte1|byte2

    return res;
}

/*
 * rotateLeft: Rotate x to the left by n bits. (For 0 <= n <= 31)
 *   Example: rotateLeft(0x76543210, 8) = 0x54321076
 *   Legal ops: ~ & ^ | + << >>
 */
int rotateLeft(int x, int n) {
    int a = x << n;				// 543210|00	
    int b = x >> (32-n);		// 000000|76
    
    int res = a | b;
    return res;
} 

/*
 * addOver: Determine if x + y overflows.
 *   Example: addOver(0x7FFFFFFE, 1) = 0
 *            addOver(0x7FFFFFFE, 2) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 */
int addOver(int x, int y) {
	// if overflow?
	// yes: 1  no: 0
	int sum = x + y;
	// An overflow occurs 
	// when x:+ y:+ but the sum is -
	// or when x:- y:- but the sum is +
	int signx = x >> 31;
	int signy = y >> 31;
	int signsum = sum >> 31;
	
	// printf("x = %d, y = %d, sum = %d\n", signx, signy, signsum);
	int res = !((signx ^ signy) | (~(signx ^ signsum)));
    return res;
}

/*
 * boundedMult: Compute 2x, but return the largest positive or negative signed integer if overflow
 *              would occur.
 *   Example: boundedMult(0x00000001) = 0x00000002
 *            boundedMult(0x50000000) = 0x7FFFFFFF (bound to largest positive int)
 *            boundedMult(0xA0000000) = 0x80000000 (bound to largest negative int)
 *   Legal ops: ! ~ & ^ | + << >>
 */
int boundedMult(int x) {

	// int mul = x << 1;			
	// int signx = x >> 31;		// the sign of x: 0/1
	// int signmul = mul >> 31;	// the sign of mul: 0/1

	// int ifoverflow = signx ^ signmul; // = 0xFFFFFFFF if overflow

	// // if overflow && signx=0, return 0x7FFFFFFF
	// // if overflow && signx=1, return 0x80000000
	// // if no overflow, return mul

	// int res = (mul | ifoverflow);


	// attempt2
	int signx = x >> 31;		// 0(pos) or -1(neg)
	int a = ( x << 1 ) >> 31; 			// the 2nd bit on the left
	// if a = 0, no overflow and if a = 1 postive number overflow 
	// if a = 1 and sign = 0 return 7FFFFFF (0111111111...)
	// if a = 1 and sign = 1 return 8000000 (1000000000...)

	int mul = x << 1;
	int b = a ^ signx;		// if different(-1/1111111) then overflow, if 0000 return the mul

	int c = signx ^ 0x7FFFFFFF;		// c = 0x7FFFFFFF if sign is positive, c = 0x80000000 if signx is negative
	
	int res = mul & (~b) | b & c ;

    return res;
}

/*
 * absHalf: Compute |x / 2| rounding towards 0.
 *   Example: absHalf(3)  = 1
 *            absHalf(-6) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 */
int absHalf(int x) {
	int a = x >> 31;
	int abs = (x + a) ^ a;					// abs is the absolute value of x
	int res = abs >> 1;
    return res;
}

/*
 * lessThan: Check if x < y.
 *   Example: lessThan(4, 5) = 1
 *            lessThan(5, 4) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 */
int lessThan(int x, int y) {
	// if x < y ?
	// yes: 1  no: 0
	int minusone = 0xFFFF << 16 | 0xFFFF;
	int a = x - y;
	
	// if a < 0 , x < y, return 1
	int signdiff = a >> 31; 				// to get the sign bit, -1

	signdiff = ~(signdiff + minusone); 		// change the -1 to 1 by reversly apply 2s complement

	int res = signdiff;
    return res;
}

/*
 * multFiveEighths: Compute 5/8ths of x rounding towards 0.
 *   Example: multFiveEighths(8)  = 5
 *            multFiveEighths(-9) = -5
 *   Legal ops: ! ~ & ^ | + << >>
 */
int multFiveEighths(int x) {
	// multiply by 4 and plus x to get 5x 
	int multiplybyfive = (x << 2) + x;

	// 5x/8
	int signx = x >> 31;
	int seven = 0x0007; 
	int toround = seven & signx;		// for positive x, toround = 0; else, equals to 7;
	// int add = multiplybyfive >> 3;		// in this case, the negative numbers would round dowm to neg infinity
	int res = (toround + multiplybyfive) >> 3;
    return res;
}

/*
 * isPwr2: Check if x is a power of 2. Assume x > 0.
 *   Example: isPwr2(2) = 1
 *            isPwr2(3) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 */
int isPwr2(unsigned int x) {
	// if power of 2?
	// yes: 1  no: 0
	int res = !(x & (x-1));
    return res;
}
