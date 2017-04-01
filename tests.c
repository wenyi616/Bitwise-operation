/*
 * Assignment: Bit Twiddling
 * Class: CSC 252 Spring 2017
 *
 * TAs: Sayak Chakraborti (schakr11@cs.rochester.edu)
 *      Kevin Gerami(kgerami@u.rochester.edu)
 *
 * You may use this program to write tests for your solutions in bits.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include "bits.h"

int main(int argc, char **argv) {
    /* Write your tests here. */
    /* test 2 */
	printf("bitAnd Output = %d\n", bitAnd(12,25) );

	/* test3 */
	printf("swapBytes Output = %d\n", swapBytes(0x33221100));

	/* test4 */
	printf("rotateLeft Output = %d\n", rotateLeft(0x76543210, 8));

	/* test5 */	
	printf("addOver Output = %d\n", addOver(0x7FFFFFFE, 2));
	printf("addOver Output2 = %d\n", addOver(0x80000000,0x80000000));
	printf("addOver Output3 = %d\n", addOver(0x80000000,0x70000000));

	/* test6 */
	printf("boundedMult Output = %d\n", boundedMult(0x00000001)); // 0 000 00...001
	printf("boundedMult Output = %x\n", boundedMult(0x50000000)); // 0 101 00...000
	printf("boundedMult Output = %x\n", boundedMult(0xA0000000)); // 1 010 00...000
	printf("boundedMult Output = %d\n", boundedMult(0xF0000000)); // 1 111 00...000
	
	/* test7 */
	printf("absHalf Output = %d\n", absHalf(-199));

	/* test8 */
	printf("lessThan Output = %d\n", lessThan(4, 5));
	printf("lessThan Output = %d\n", lessThan(5, 4));
	printf("lessThan Output = %d\n", lessThan(99, 130));

	/* multFiveEighths */
	/* todo */
	printf("multFiveEighths Output = %d\n", multFiveEighths(-9));
	printf("multFiveEighths Output = %d\n", multFiveEighths(9));

	/* test10*/
	printf("isPwr2 Output = %d\n", isPwr2(0));

    return 0;
}
