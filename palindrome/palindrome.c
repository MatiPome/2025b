#include "palindrome.h"
#include <string.h>
#include <ctype.h>

int is_palindrome(char s[]){
    int i = 0;
    int j = 0;
    char str1[81];
    for(i = 0; s[i] != '\0'; i++){
        if(!isspace(s[i])){
        str1[j++] = s[i];

      }
    }
    str1[j] = '\0';


    j=strlen(str1);

  int left = 0;
  int right =j - 1;

  while (left < right) {
    if (str1[left] != str1[right]) {
      return 0;
    }
    left++;
    right--;
  }
  return 1;
  }




