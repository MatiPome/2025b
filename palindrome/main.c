#include <stdio.h>
#include "palindrome.h"
#include <string.h>
#include <ctype.h>

int main() {

   char str[81];
   int i;
   printf("Program started\n");
   printf("Enter your string: ");
   if(fgets(str, 81, stdin) == NULL) {
     printf("Input error\n");
     return 1;
   }
   str[strcspn(str, "\n")] = '\0';  /* remove newline */


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

   if(is_palindrome(str) == 1) {
     printf("Your string is palindrome\n");
   return 0;
   }
   else{
     printf("Your string is not a palindrome\n");
   return 1;
   }


   }


