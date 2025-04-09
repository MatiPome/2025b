#include "module.h"
/* to perserve portability, we take the size of int of the current system and not a fixed number */
#define BIT_COUNT (sizeof(unsigned int) * 8)

/*
   this function receives an unsigned int "num" and counts the number of 1 bits encountered,
   while building the binary number
*/
int count_ones(unsigned int num){
    int count = 0;
    int zero_bits = 0;
    /*
        as long as num can be divided by 2 and the result is larger than 1, we check the result for ones and zeroes
        that way we create the binary number from a decimal int number
    */
    while (num > 0){
          if(num % 2 == 1){
            count++;
          }
          num = num/2;

    } /* end of while loop */

    /* number of total bits minus number of 1's counted results in number of zeroes */
    zero_bits = sizeof(int) * 8 - count;
    return zero_bits;

} /* end of count_ones */
