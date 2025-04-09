/**
* This program calculates the number of zero bits in a binary number
* the program receives from the user a decimal number, converts it to binary and prints the amount of zeroes in the binary code,
* according to the system's standards of int bits.
*/

#include <stdio.h>
#include "module.h"

int main(){
  /* variables to be used in the code */
  int result;
  int num;
  printf("--------------------------------------------------------------------\n");
  printf("Welcome to the zero counter for decimal to binary program\n");
  printf("--------------------------------------------------------------------\n");
  printf("Please enter a number in decimal format and press enter: ");
    /* receive input from user */
  scanf("%d", &num);
  /* call function to calculate number of zeros */
    result = count_ones(num);
    printf("--------------------------------------------------------------------\n");
    printf("The number of zeros in the binary format is: %d\n", result);
    printf("--------------------------------------------------------------------\n");
    printf("Thank you for using the program, farewell\n");
    return 0;
 } /* end of main */

