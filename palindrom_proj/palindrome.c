#include <string.h>         /* Provides string manipulation functions like strlen() and strcpy() */
#include <ctype.h>          /* Provides character classification functions like isalpha() and isspace() */

/**
 * is_palindrome:
 *   Receives a string `s` and checks whether it is a palindrome,
 *   ignoring spaces. Returns 1 if it is, 0 otherwise.
 *
 * Parameters:
 *   char s[]: The string to check.
 *
 * Returns:
 *   int: 1 if the string is a palindrome, 0 otherwise.
 */
int is_palindrome(char s[]) {
  int i = 0, j = 0;             /* Loop indices for processing the input string */
  int left = 0, right;          /* Indices for comparing characters from both ends */
  char str1[81];                /* Buffer to store cleaned string (no spaces) */

  /* Remove spaces from the input string to create a cleaned version */
  for (i = 0; s[i] != '\0'; i++) {
    if (!isspace((unsigned char)s[i])) {
      str1[j++] = s[i];         /* Store non-space characters into the new string */
    }
  }
  str1[j] = '\0';               /* Null-terminate the cleaned string */

  /* Set the right index for comparison in palindrome check */
  right = j - 1;                /* Set the right index to the last character in the cleaned string */

  /* Check characters from both ends of the cleaned string */
  while (left < right) {
    if (str1[left] != str1[right]) {
      return 0;                  /* Return 0 if characters don't match (not a palindrome) */
    }
    left++;                      /* Move the left index to the right */
    right--;                     /* Move the right index to the left */
  }

  return 1;                      /* Return 1 if the string is a palindrome */
}




