#include <string.h>
#include <ctype.h>

/*
 * is_palindrome:
 *   Receives a string `s` and checks whether it is a palindrome,
 *   ignoring spaces. Returns 1 if it is, 0 otherwise.
 */
int is_palindrome(char s[]) {
  int i = 0, j = 0;
  int left = 0, right;
  char str1[81];  /* Buffer to store cleaned string (no spaces) */

  /* Remove spaces from input string */
  for (i = 0; s[i] != '\0'; i++) {
    if (!isspace((unsigned char)s[i])) {
      str1[j++] = s[i];
    }
  }
  str1[j] = '\0';  /* Null-terminate cleaned string */

  /* Set right index for palindrome comparison */
  right = j - 1;

  /* Check characters from both ends */
  while (left < right) {
    if (str1[left] != str1[right]) {
      return 0;  /* Not a palindrome */
    }
    left++;
    right--;
  }

  return 1;  /* Is a palindrome */
}



