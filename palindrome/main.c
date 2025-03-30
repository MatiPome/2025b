#include <stdio.h>
#include "palindrome.h"
#include <string.h>
#include <ctype.h>

int main() {
   char str[81];
   printf("Enter your string: ");
   if(fgets(str, 81, stdin) == NULL) {
     printf("Input error\n");
     return 1;
   }
   str[strcspn(str, "\n")] = '\0';  // remove newline

   int i;
   for(i = 0; str[i] != '\0'; i++){
     if (!isalpha(str[i]) && !isspace(str[i])){
       printf("your string contains invalid character %c\n", str[i]);
       return 1;
     }
   }

   if ( str[0] == '\0') {
     printf("your string is empty\n");
     return 1;
   }

   return 0;
}
