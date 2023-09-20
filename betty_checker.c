#include "shell.h"

/**
 * is_interactive - checks if the shell is in interactive mode
 * @shell_info: information about the shell
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive(shell_info_t *shell_info) {
  return (isatty(STDIN_FILENO) && shell_info->readfd <= 2);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @character: the character to check
 * @delimiters: the delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char character, char *delimiters) {
  while (*delimiters) {
    if (*delimiters++ == character) {
      return 1;
    }
  }
  return 0;
}

/**
 * is_alphabetic - checks if a character is alphabetic
 * @character: the character to check
 *
 * Return: 1 if the character is alphabetic, 0 otherwise
 */
int is_alphabetic(char character) {
  return (character >= 'a' && character <= 'z') ||
         (character >= 'A' && character <= 'Z');
}

/**
 * string_to_integer - converts a string to an integer
 * @string: the string to be converted
 *
 * Return: 0 if no numbers in the string, converted number otherwise
 */
int string_to_integer(char *string) {
  int sign = 1;
  int flag = 0;
  int output;
  unsigned int result = 0;

  for (int i = 0; string[i] != '\0' && flag != 2; i++) {
    if (string[i] == '-') {
      sign *= -1;
    }

    if (string[i] >= '0' && string[i] <= '9') {
      flag = 1;
      result *= 10;
      result += (string[i] - '0');
    } else if (flag == 1) {
      flag = 2;
    }
  }

  if (sign == -1) {
    output = -result;
  } else {
    output = result;
  }

  return output;
}
