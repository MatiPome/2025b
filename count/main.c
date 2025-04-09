#include <stdio.h>
#include "module.h"

int main(){
  int result;
  int num;
  printf("Enter a number in decimal format: ");
  while(scanf("%d", &num)==1){
    result = count_ones(num);

    printf("The number of zeros in the binary format is: %d\n", result);

  }
  return 0;
}