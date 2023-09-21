#include "shell.h"

/**
 * handleNonInteractiveMode - Handles non-interactive mode of the shell.
 *
 * Return: None.
 */
void handleNonInteractiveMode(void) {
    char **currentCommand = NULL;
    int i, commandType = 0;
    size_t bufferSize = 0;

    // Check if the input is not coming from a terminal
    if (!(isatty(STDIN_FILENO))) {
        while (getline(&line, &bufferSize, stdin) != -1) {
            // Remove newline and ignore comments
            removeNewlineCharacter(line);
            removeComment(line);

            // Tokenize input into separate commands
            commands = tokenizeInput(line, ";");

            for (i = 0; commands[i] != NULL; i++) {
                currentCommand = tokenizeInput(commands[i], " ");

                if (currentCommand[0] == NULL) {
                    free(currentCommand);
                    break;
                }

                // Parse the command and execute it
                commandType = parseCommand(currentCommand[0]);
                executeCommand(currentCommand, commandType);

                free(currentCommand);
            }

            free(commands);
        }

        free(line);
        exit(status);
    }
}

