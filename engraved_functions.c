#include "shell.h"

/**
 * printEnvironment - Prints the current environment variables.
 *
 * Return: void
 */
void printEnvironment(void) {
    int i;
    for (i = 0; environ[i] != NULL; i++) {
        printString(environ[i], STDOUT_FILENO);
        printString("\n", STDOUT_FILENO);
    }
}

/**
 * exitShell - Exits the shell.
 * @tokenizedCommand: The command and its arguments.
 *
 * Return: void
 */
void exitShell(char **tokenizedCommand) {
    int numTokens = 0, exitStatus;
    
    // Count the number of tokens in the command
    for (; tokenizedCommand[numTokens] != NULL; numTokens++);

    if (numTokens == 1) {
        // No argument provided, exit with the default status
        freeResourcesAndExit(status);
    } else if (numTokens == 2) {
        // Argument provided, try to parse it as an integer
        exitStatus = customAtoi(tokenizedCommand[1]);
        
        if (exitStatus == -1) {
            // Invalid argument, print an error message
            printString(shell_name, STDERR_FILENO);
            printString(": 1: exit: Illegal number: ", STDERR_FILENO);
            printString(tokenizedCommand[1], STDERR_FILENO);
            printString("\n", STDERR_FILENO);
            status = 2;
        } else {
            // Valid argument, exit with the specified status
            freeResourcesAndExit(exitStatus);
        }
    } else {
        // More than one argument provided, print an error message
        printString("$: exit doesn't take more than one argument\n", STDERR_FILENO);
    }
}

/**
 * freeResourcesAndExit - Frees allocated resources and exits the shell.
 * @exitStatus: The exit status.
 *
 * Return: None (exits the program).
 */
void freeResourcesAndExit(int exitStatus) {
    free(line);
    free(commands);
    exit(exitStatus);
}

