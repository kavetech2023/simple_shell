#include "shell.h"

/**
 * compareStrings - Compares two strings character by character.
 * @firstString: The first string to compare.
 * @secondString: The second string to compare.
 *
 * Return: The difference between the ASCII values of the first differing characters.
 */
int compareStrings(char *firstString, char *secondString) {
    int i = 0;

    // Compare characters until a difference is found or one string ends
    while (firstString[i] != '\0') {
        if (firstString[i] != secondString[i]) {
            break;
        }
        i++;
    }

    return firstString[i] - secondString[i];
}

/**
 * concatenateStrings - Concatenates two strings into a new one.
 * @destination: The string to concatenate to.
 * @source: The string to concatenate.
 *
 * Return: The address of the newly created string.
 */
char *concatenateStrings(char *destination, char *source) {
    char *newString = NULL;
    int lengthDestination = getStringLength(destination);
    int lengthSource = getStringLength(source);

    // Allocate memory for the new string
    newString = malloc(sizeof(*newString) * (lengthDestination + lengthSource + 1));

    // Copy the content of the destination and source strings into the new string
    copyString(destination, newString);
    copyString(source, newString + lengthDestination);

    // Add null terminator to the end of the new string
    newString[lengthDestination + lengthSource] = '\0';

    return newString;
}

/**
 * getCommonPrefixLength - Calculates the length of the common prefix of two strings.
 * @string1: The first string.
 * @string2: The second string.
 *
 * Return: The length of the common prefix.
 */
int getCommonPrefixLength(char *string1, char *string2) {
    int length = 0;
    int i = 0;

    // Compare characters until a difference is found or one string ends
    for (i = 0; string1[i] != '\0'; i++) {
        if (string1[i] != string2[i]) {
            break;
        }
        length++;
    }

    return length;
}

/**
 * findCharacterInString - Searches for a character in a string.
 * @string: The string to search.
 * @character: The character to find.
 *
 * Return: A pointer to the first occurrence of the character in the string, or NULL if not found.
 */
char *findCharacterInString(char *string, char character) {
    int i = 0;

    // Iterate through the string to find the character
    for (; string[i] != character && string[i] != '\0'; i++) {
        // No need to do anything here; we are just advancing the loop
    }

    if (string[i] == character) {
        // Return a pointer to the found character
        return (string + i);
    } else {
        // Character not found
        return NULL;
    }
}

