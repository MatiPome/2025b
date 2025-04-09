#include "module.h"

/* to perserve portability, we take the size of int of the current system and not a fixed number */


/*
   this function receives an unsigned int "num" and counts the number of 1 bits encountered,
   while building the binary number
*/
int count_zero_bits(unsigned int num){
    int count = 0;
    int i;

    /*
        as long as num can be divided by 2 and the result is larger than 1, we check the result for ones and zeroes
        that way we create the binary number from a decimal int number
    */
for ( i = 0; i < BIT_COUNT; i++){
    if((num & 1u) == 0) count++;
    num >>= 1;

}
  /* end of while loop */

    /* number of total bits minus number of 1's counted results in number of zeroes */

    return count;

} /* end of count_ones */
