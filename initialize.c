#include "shell.h"

/**
 * executeCommand - Executes a command based on its type.
 * @command: The command to be executed.
 * @commandType: The type of command (EXTERNAL_COMMAND, INTERNAL_COMMAND, PATH_COMMAND).
 *
 * Return: None.
 */
void executeCommand(char **command, int commandType) {
    pid_t childProcessID;

    // If it's an external or path command, fork a new process
    if (commandType == EXTERNAL_COMMAND || commandType == PATH_COMMAND) {
        childProcessID = fork();

        if (childProcessID == 0) {
            // Child process executes the command
            executeCommandInChild(command, commandType);
        } else {
            // Parent process waits for the child to finish
            waitForChildProcess(childProcessID);
        }
    } else {
        // Execute the command directly for internal commands
        executeCommandInChild(command, commandType);
    }
}

/**
 * executeCommandInChild - Executes a command in the child process.
 * @command: The command to be executed.
 * @commandType: The type of command (EXTERNAL_COMMAND, INTERNAL_COMMAND, PATH_COMMAND).
 *
 * Return: None.
 */
void executeCommandInChild(char **command, int commandType) {
    // Execute the command based on its type
    switch (commandType) {
        case EXTERNAL_COMMAND:
            // Execute external command
            executeExternalCommand(command);
            break;
        case INTERNAL_COMMAND:
            // Execute internal (built-in) command
            executeInternalCommand(command);
            break;
        case PATH_COMMAND:
            // Execute command with specified path
            executeCommandWithPath(command);
            break;
        default:
            // Handle invalid command type
            handleInvalidCommandType();
            break;
    }
}

/**
 * waitForChildProcess - Waits for the child process to finish.
 * @childPID: The PID of the child process.
 *
 * Return: None.
 */
void waitForChildProcess(pid_t childPID) {
    int childStatus;

    // Parent process waits for the child to finish
    waitpid(childPID, &childStatus, 0);

    // Get the exit status of the child process
    status = childStatus >> 8;
}

/**
 * handleInvalidCommandType - Handles the case when an invalid command type is encountered.
 *
 * Return: None.
 */
void handleInvalidCommandType() {
    // Handle the error when an invalid command type is encountered
    printString("Error: Invalid command type\n", STDERR_FILENO);
}

/**
 * executeExternalCommand - Executes an external command.
 * @command: The external command to be executed.
 *
 * Return: None.
 */
void executeExternalCommand(char **command) {
    // Execute an external command (e.g., ls, pwd) using execvp
    execvp(command[0], command);

    // If execvp fails, print an error message
    printString("Error: Command not found\n", STDERR_FILENO);

    // Exit the child process with an error code
    exit(EXIT_FAILURE);
}

/**
 * executeInternalCommand - Executes an internal (built-in) command.
 * @command: The internal command to be executed.
 *
 * Return: None.
 */
void executeInternalCommand(char **command) {
    // Execute an internal (built-in) command
    // (e.g., handle built-in commands like 'exit' and 'env')
    if (isExitCommand(command)) {
        // Handle the 'exit' command
        handleExitCommand(command);
    } else if (isEnvCommand(command)) {
        // Handle the 'env' command
        handleEnvCommand(command);
    } else {
        // Handle other internal commands here if needed
        printString("Error: Internal command not supported\n", STDERR_FILENO);
        // Exit the child process with an error code
        exit(EXIT_FAILURE);
    }
}

/**
 * executeCommandWithPath - Executes a command with a specified path.
 * @command: The command to be executed with a path.
 *
 * Return: None.
 */
void executeCommandWithPath(char **command) {
    // Execute a command with a specified path
    // (e.g., handle commands with full or relative paths)
    execvp(command[0], command);

    // If execvp fails, print an error message
    printString("Error: Command not found\n", STDERR_FILENO);

    // Exit the child process with an error code
    exit(EXIT_FAILURE);
}

/**
 * isExitCommand - Checks if the command is the 'exit' command.
 * @command: The command to check.
 *
 * Return: 1 if the command is 'exit', 0 otherwise.
 */
int isExitCommand(char **command) {
    // Check if the command is the 'exit' command
    return (compareStrings(command[0], "exit") == 0);
}

/**
 * handleExitCommand - Handles the 'exit' command.
 * @command: The 'exit' command to be handled.
 *
 * Return: None.
 */
void handleExitCommand(char **command) {
    // Handle the 'exit' command
    // (e.g., exit the shell with the specified exit code)
    int exitCode = EXIT_SUCCESS;

    // Check if an exit code is provided as an argument
    if (command[1] != NULL) {
        exitCode = customAtoi(command[1]);
    }

    // Exit the child process with the specified exit code
    exit(exitCode);
}

/**
 * isEnvCommand - Checks if the command is the 'env' command.
 * @command: The command to check.
 *
 * Return: 1 if the command is 'env', 0 otherwise.
 */
int isEnvCommand(char **command) {
    // Check if the command is the 'env' command
    return (compareStrings(command[0], "env") == 0);
}

/**
 * handleEnvCommand - Handles the 'env' command.
 * @command: The 'env' command to be handled.
 *
 * Return: None.
 */
void handleEnvCommand(char **command) {
    // Handle the 'env' command
    // (e.g., display environment variables)
    int i = 0;

    // Iterate through the environment variables and print them
    while (environ[i] != NULL) {
        printString(environ[i], STDOUT_FILENO);
        printString("\n", STDOUT_FILENO);
        i++;
    }
}

