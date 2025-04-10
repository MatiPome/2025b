#ifndef MODULE_H
#define MODULE_H

#include <limits.h>  /* Include the limits.h header for CHAR_BIT, which provides the number of bits in a byte */

/*
 * BIT_COUNT:
 *   This macro calculates the total number of bits in an unsigned int on this system.
 *   It multiplies the size of an unsigned int (in bytes) by the number of bits per byte
 *   (CHAR_BIT, which is typically 8 for most systems).
 *
 *   This will give the total number of bits (e.g., 32 or 64) that an unsigned int can hold
 *   on the current system.
 */
#define BIT_COUNT (sizeof(unsigned int) * CHAR_BIT)  /* Calculate the bit width of unsigned int */

/**
 * count_zero_bits:
 *   This function receives an unsigned integer (num) and returns the number of zero bits
 *   in its binary representation.
 *
 *   Parameters:
 *     int num: The unsigned integer whose zero bits are to be counted.
 *
 *   Returns:
 *     int: The number of zero bits in the binary representation of the number.
 *
 *   The function works by iterating through all the bits in the given integer, counting the
 *   number of bits that are 0.
 */
int count_zero_bits(unsigned int num);  /* Function prototype for count_zero_bits */

#endif /* MODULE_H */

