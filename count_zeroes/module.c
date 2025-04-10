#include "module.h"  /* Include the header for the module that contains function prototypes */

/*
 * count_zero_bits:
 *   This function receives an unsigned integer "num" and counts the number
 *   of zero bits in its binary representation. The size of the integer
 *   is determined by the system's standards (BIT_COUNT).
 *
 * Parameters:
 *   int num: The unsigned integer whose zero bits are to be counted.
 *
 * Returns:
 *   int: The number of zero bits in the binary representation of "num".
 */
int count_zero_bits(unsigned int num) {
    int count = 0;  /* Initialize the count of zero bits */
    int i;          /* Loop index to iterate through each bit */

    /*
     * Loop through all bits of the number.
     * In each iteration, isolate the least significant bit (LSB).
     * If the LSB is 0, increment the zero count.
     * Then right-shift the number to check the next bit.
     */
    for (i = 0; i < BIT_COUNT; i++) {  /* Loop for each bit in the integer (BIT_COUNT is usually 32) */
        if ((num & 1u) == 0)  /* Check if the least significant bit is 0 */
            count++;           /* Increment the zero bit count if LSB is 0 */
        num >>= 1;             /* Right shift the number to check the next bit */
    }

    return count;  /* Return the total count of zero bits */
} /* end of count_zero_bits */
