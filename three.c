#include "shell.h"

/**
 * customStrtok - Tokenizes a string.
 * @inputString: The string to be tokenized.
 * @delimiter: The delimiter used to tokenize the string.
 * @savePtr: A pointer to keep track of the next token.
 *
 * Return: The next available token.
 */
char *customStrtok(char *inputString, char *delimiter, char **savePtr) {
    char *tokenEnd;

    // If inputString is NULL, continue from where we left off
    if (inputString == NULL) {
        inputString = *savePtr;
    }

    // Skip leading delimiters
    inputString += customStrspn(inputString, delimiter);

    // If the current position is at the end of the string, return NULL
    if (*inputString == '\0') {
        *savePtr = inputString;
        return NULL;
    }

    // Find the end of the token
    tokenEnd = inputString + customStrcspn(inputString, delimiter);

    // If we reached the end of the string, return the current token
    if (*tokenEnd == '\0') {
        *savePtr = tokenEnd;
        return inputString;
    }

    // Null-terminate the token and update savePtr to point to the next character
    *tokenEnd = '\0';
    *savePtr = tokenEnd + 1;

    return inputString;
}

/**
 * customAtoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted integer.
 */
int customAtoi(char *s) {
    unsigned int result = 0;
    int isNegative = 0;

    // Check for negative sign
    if (*s == '-') {
        isNegative = 1;
        s++;
    }

    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        s++;
    }

    return isNegative ? -result : result;
}

/**
 * customRealloc - Reallocates memory.
 * @ptr: A pointer to the memory block to be reallocated.
 * @oldSize: The current size of the memory block.
 * @newSize: The new size of the memory block.
 *
 * Return: A pointer to the new memory block.
 */
void *customRealloc(void *ptr, unsigned int oldSize, unsigned int newSize) {
    void *newBlock;
    unsigned int i;

    // Allocate new memory
    newBlock = malloc(newSize);

    // Copy data from the old block to the new block
    if (newBlock != NULL) {
        for (i = 0; i < customMin(oldSize, newSize); i++) {
            *((char *)newBlock + i) = *((char *)ptr + i);
        }
        free(ptr);
        return newBlock;
    } else {
        return NULL;
    }
}

/**
 * handleCtrlC - Handles the SIGINT signal (e.g., CTRL-C).
 * @signalNumber: The signal number.
 *
 * Return: None.
 */
void handleCtrlC(int signalNumber) {
    if (signalNumber == SIGINT) {
        printString("\n($) ", STDIN_FILENO);
    }
}

/**
 * removeComments - Removes everything after a '#' character in a string.
 * @input: The input string.
 *
 * Return: None.
 */
void removeComments(char *input) {
    int i = 0;

    // Remove the '#' character and everything after it
    if (input[i] == '#') {
        input[i] = '\0';
    }

    // Search for a '#' character after a space and remove it
    while (input[i] != '\0') {
        if (input[i] == '#' && input[i - 1] == ' ') {
            break;
        }
        i++;
    }
    input[i] = '\0';
}

