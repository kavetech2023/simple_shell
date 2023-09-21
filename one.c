#include "shell.h"

/**
 * tokenizeInput - Tokenizes input and stores it in an array.
 * @inputString: The input to be parsed.
 * @delimiter: The delimiter used for tokenization (a single character).
 *
 * Return: An array of tokens.
 */
char **tokenizeInput(char *inputString, char *delimiter) {
    int numTokens = 0;
    char **tokensArray = NULL;
    char *token = NULL;
    char *savePtr = NULL;

    // Use strtok_r to split the inputString into tokens
    token = _strtok_r(inputString, delimiter, &savePtr);

    while (token != NULL) {
        // Resize the tokens array to accommodate the new token
        tokensArray = _realloc(tokensArray, sizeof(*tokensArray) * numTokens, sizeof(*tokensArray) * (numTokens + 1));
        tokensArray[numTokens] = token;

        // Get the next token
        token = _strtok_r(NULL, delimiter, &savePtr);
        numTokens++;
    }

    // Add a NULL pointer at the end to indicate the end of the array
    tokensArray = _realloc(tokensArray, sizeof(*tokensArray) * numTokens, sizeof(*tokensArray) * (numTokens + 1));
    tokensArray[numTokens] = NULL;

    return tokensArray;
}

/**
 * printString - Prints a string to the standard output.
 * @string: The string to be printed.
 * @outputStream: The output stream to print to (e.g., STDOUT).
 *
 * Return: None.
 */
void printString(char *string, int outputStream) {
    int i = 0;
    while (string[i] != '\0') {
        // Write each character of the string to the specified output stream
        write(outputStream, &string[i], 1);
        i++;
    }
}

/**
 * removeNewlineCharacter - Removes newline character from a string.
 * @str: The string to be processed.
 *
 * Return: None.
 */
void removeNewlineCharacter(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            // Replace newline character with null terminator
            str[i] = '\0';
            break;
        }
        i++;
    }
}

/**
 * copyString - Copies a string from source to destination.
 * @source: The source string to be copied.
 * @destination: The destination buffer to copy to.
 *
 * Return: None.
 */
void copyString(char *source, char *destination) {
    int i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0'; // Add null terminator to the destination string
}

/**
 * getStringLength - Computes the length of a string.
 * @string: The input string.
 *
 * Return: The length of the string.
 */
int getStringLength(char *string) {
    int length = 0;
    if (string == NULL)
        return length;

    while (string[length] != '\0') {
        length++;
    }
    return length;
}

