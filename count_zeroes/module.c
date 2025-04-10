#include "module.h"

/*
 * This function receives an unsigned int "num" and counts the number
 * of zero bits in its binary representation. The size of the integer
 * is determined by the system's standards (BIT_COUNT).
 */
int count_zero_bits(unsigned int num) {
    int count = 0;
    int i;

    /*
     * Loop through all bits of the number.
     * In each iteration, isolate the least significant bit (LSB).
     * If the LSB is 0, increment the zero count.
     * Then right-shift the number to check the next bit.
     */
    for (i = 0; i < BIT_COUNT; i++) {
        if ((num & 1u) == 0)
          count++;
        num >>= 1;
    }

    return count;
} /* end of count_zero_bits */