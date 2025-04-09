#include "module.h"

#define BIT_COUNT (sizeof(unsigned int) * 8)

int count_ones(unsigned int num){
    int count = 0;
    int zero_bits = 0;

    while (num > 0){
          if(num % 2 == 1){
            count++;
          }
          num = num/2;

    }
    zero_bits = sizeof(int) * 8 - count;
    return zero_bits;

}
