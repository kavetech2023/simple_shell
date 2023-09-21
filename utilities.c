#include "shell.h"

/**
 * determineCommandType - Determines the type of a command.
 * @command: The command to be parsed.
 *
 * Return: A constant representing the type of the command:
 *   - EXTERNAL_COMMAND (1) for commands like /bin/ls
 *   - INTERNAL_COMMAND (2) for commands like exit, env
 *   - PATH_COMMAND (3) for commands found in the PATH like ls
 *   - INVALID_COMMAND (-1) for invalid commands
 */
int determineCommandType(char *command) {
    int i;
    char *internalCommands[] = {"env", "exit", NULL};
    char *path = NULL;

    // Check if the command contains a '/'
    for (i = 0; command[i] != '\0'; i++) {
        if (command[i] == '/') {
            return EXTERNAL_COMMAND;
        }
    }

    // Check if the command is an internal command
    for (i = 0; internalCommands[i] != NULL; i++) {
        if (_strcmp(command, internalCommands[i]) == 0) {
            return INTERNAL_COMMAND;
        }
    }

    // Check if the command is found in the PATH
    path = findCommandInPath(command);
    if (path != NULL) {
        free(path);
        return PATH_COMMAND;
    }

    return INVALID_COMMAND;
}

/**
 * executeCommand - Executes a command based on its type.
 * @tokenizedCommand: The tokenized form of the command (e.g., {"ls", "-l", NULL}).
 * @commandType: The type of the command (EXTERNAL_COMMAND, INTERNAL_COMMAND, PATH_COMMAND).
 *
 * Return: None.
 */
void executeCommand(char **tokenizedCommand, int commandType) {
    void (*functionPointer)(char **);

    // Execute the command based on its type
    switch (commandType) {
        case EXTERNAL_COMMAND:
            // Execute an external command
            executeExternalCommand(tokenizedCommand);
            break;
        case INTERNAL_COMMAND:
            // Execute an internal (built-in) command
            functionPointer = getCommandFunction(tokenizedCommand[0]);
            if (functionPointer != NULL) {
                functionPointer(tokenizedCommand);
            } else {
                handleInvalidCommand(tokenizedCommand[0]);
            }
            break;
        case PATH_COMMAND:
            // Execute a command found in the PATH
            executeCommandFromPath(tokenizedCommand[0], tokenizedCommand);
            break;
        case INVALID_COMMAND:
            // Handle an invalid command
            handleInvalidCommand(tokenizedCommand[0]);
            break;
    }
}

/**
 * findCommandInPath - Checks if a command is found in the PATH environment variable.
 * @command: The command to be searched in the PATH.
 *
 * Return: The full path where the command is found, or NULL if not found.
 */
char *findCommandInPath(char *command) {
    char **pathArray = NULL;
    char *tempPath, *tempConcatenatedPath, *copiedPath;
    char *pathEnv = _getenv("PATH");
    int i;

    // Check if PATH is not set or empty
    if (pathEnv == NULL || _strlen(pathEnv) == 0) {
        return NULL;
    }

    // Create a copy of the PATH environment variable
    copiedPath = malloc(sizeof(char) * (_strlen(pathEnv) + 1));
    _strcpy(pathEnv, copiedPath);

    // Tokenize the PATH into an array
    pathArray = tokenizePath(copiedPath);

    for (i = 0; pathArray[i] != NULL; i++) {
        tempConcatenatedPath = concatenatePathAndCommand(pathArray[i], command);
        if (fileExists(tempConcatenatedPath)) {
            free(copiedPath);
            freePathArray(pathArray);
            return tempConcatenatedPath;
        }
        free(tempConcatenatedPath);
    }

    free(copiedPath);
    freePathArray(pathArray);

    return NULL;
}

/**
 * getCommandFunction - Retrieves a function pointer based on the command name.
 * @command: The command name.
 *
 * Return: A pointer to the corresponding function, or NULL if not found.
 */
void (*getCommandFunction(char *command))(char **) {
    int i;
    function_map commandMapping[] = {
        {"env", executeEnvCommand},
        {"exit", executeExitCommand},
        // Add more internal commands here if needed
    };

    for (i = 0; i < sizeof(commandMapping) / sizeof(commandMapping[0]); i++) {
        if (_strcmp(command, commandMapping[i].command_name) == 0) {
            return commandMapping[i].func;
        }
    }

    return NULL;
}

/**
 * executeEnvCommand - Executes the 'env' command.
 * @command: The 'env' command and its arguments.
 *
 * Return: None.
 */
void executeEnvCommand(char **command) {
    int i;

    // Iterate through the environment variables and print them
    for (i = 0; environ[i] != NULL; i++) {
        printString(environ[i], STDOUT_FILENO);
        printString("\n", STDOUT_FILENO);
    }
}

/**
 * executeExitCommand - Executes the 'exit' command.
 * @command: The 'exit' command and its arguments.
 *
 * Return: None.
 */
void executeExitCommand(char **command) {
    int exitCode = EXIT_SUCCESS;

    // Check if an exit code is provided as an argument
    if (command[1] != NULL) {
        exitCode = customAtoi(command[1]);
    }

    // Exit the shell with the specified exit code
    exit(exitCode);
}

/**
 * handleInvalidCommand - Handles the case when an invalid command is encountered.
 * @commandName: The name of the invalid command.
 *
 * Return: None.
 */
void handleInvalidCommand(char *commandName) {
    // Print an error message for the invalid command
    printString(shell_name, STDERR_FILENO);
    printString(": 1: ", STDERR_FILENO);
    printString(commandName, STDERR_FILENO);
    printString(": not found\n", STDERR_FILENO);
    status = 127;
}

/**
 * fileExists - Checks if a file exists.
 * @path: The path to the file.
 *
 * Return: 1 if the file exists, 0 otherwise.
 */
int fileExists(char *path) {
    return (access(path, F_OK) == 0);
}

/**
 * tokenizePath - Tokenizes the PATH environment variable into an array.
 * @pathEnv: The PATH environment variable.
 *
 * Return: An array of path directories.
 */
char **tokenizePath(char *pathEnv) {
    return tokenizeInput(pathEnv, ":");
}

/**
 * concatenatePathAndCommand - Concatenates a path and a command with a '/' separator.
 * @path: The path.
 * @command: The command.
 *
 * Return: The concatenated string.
 */
char *concatenatePathAndCommand(char *path, char *command) {
    char *separator = "/";
    return customStrcat(customStrcat(path, separator), command);
}

/**
 * freePathArray - Frees memory allocated for a path array.
 * @pathArray: The path array.
 *
 * Return: None.
 */
void freePathArray(char **pathArray) {
    int i;
    for (i = 0; pathArray[i] != NULL; i++) {
        free(pathArray[i]);
    }
    free(pathArray);
}

/**
 * customStrcat - Custom implementation of strcat to concatenate two strings.
 * @destination: The destination string.
 * @source: The source string to be concatenated.
 *
 * Return: The address of the new concatenated string.
 */
char *customStrcat(char *destination, char *source) {
    char *newString = NULL;
    int lenDest = customStrlen(destination);
    int lenSource = customStrlen(source);
    newString = malloc(sizeof(char) * (lenDest + lenSource + 1));
    customStrcpy(destination, newString);
    customStrcpy(source, newString + lenDest);
    newString[lenDest + lenSource] = '\0';
    return newString;
}

/**
 * customStrlen - Custom implementation of strlen to count string length.
 * @string: The string to be counted.
 *
 * Return: The length of the string.
 */
int customStrlen(char *string) {
    int length = 0;
    if (string == NULL) {
        return length;
    }
    for (; string[length] != '\0'; length++) {
    }
    return length;
}

/**
 * customStrcpy - Custom implementation of strcpy to copy a string.
 * @source: The source string to be copied.
 * @destination: The destination string to copy to.
 *
 * Return: None.
 */
void customStrcpy(char *source, char *destination) {
    int i = 0;
    for (; source[i] != '\0'; i++) {
        destination[i] = source[i];
    }
    destination[i] = '\0';
}

/**
 * customAtoi - Custom implementation of atoi to convert a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted integer.
 */
int customAtoi(char *s) {
    unsigned int n = 0;
    int isNegative = 0;

    // Handle negative numbers
    if (*s == '-') {
        isNegative = 1;
        s++;
    }

    // Iterate through the string to convert to an integer
    while (*s != '\0') {
        if (*s < '0' || *s > '9') {
            return -1;  // Invalid input
        }
        n = (n * 10) + (*s - '0');
        s++;
    }

    // Handle negative numbers
    if (isNegative) {
        return -n;
    }

    return n;
}

/**
 * executeExternalCommand - Executes an external command.
 * @command: The command and its arguments.
 *
 * Return: None.
 */
void executeExternalCommand(char **command) {
    if (execve(command[0], command, NULL) == -1) {
        perror(_getenv("PWD"));
        exit(EXIT_FAILURE);
    }
}

/**
 * executeCommandFromPath - Executes a command found in the PATH.
 * @commandName: The name of the command.
 * @command: The command and its arguments.
 *
 * Return: None.
 */
void executeCommandFromPath(char *commandName, char **command) {
    char *fullPath = findCommandInPath(commandName);
    if (fullPath != NULL) {
        if (execve(fullPath, command, NULL) == -1) {
            perror(_getenv("PWD"));
            exit(EXIT_FAILURE);
        }
    } else {
        handleInvalidCommand(commandName);
    }
}

