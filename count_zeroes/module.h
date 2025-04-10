#ifndef MODULE_H
#define MODULE_H

#include <limits.h>

/* BIT_COUNT: total number of bits in an unsigned int on this system */
#define BIT_COUNT (sizeof(unsigned int) * CHAR_BIT)

/**
 * count_zero_bits:
 *   Receives an unsigned integer and returns the number of 0 bits
 *   in its binary representation.
 */
int count_zero_bits(unsigned int num);

#endif /* MODULE_H */
