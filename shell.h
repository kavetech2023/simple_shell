#ifndef SHELL_H
#define SHELL_H

// Include necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants to represent different types of commands
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

// Function prototype for a simple command mapper
typedef struct {
    char *command_name;
    void (*func)(char **command);
} CommandMapper;

// Global variables
extern char **environ;       // Environment variables
extern char *line;           // User input
extern char **commands;      // Parsed commands
extern char *shell_name;     // Name of the shell
extern int status;           // Command execution status

// Function prototypes for helper functions
void printMessage(char *message, int length);
char **tokenizeString(char *input, char *delimiter);
void removeNewline(char *text);
int stringLength(char *text);
void copyString(char *destination, char *source);

// More function prototypes for helper functions
int compareStrings(char *string1, char *string2);
char *concatenateStrings(char *string1, char *string2);
int findStringLengthInCharset(char *text, char *charset);
int findStringLengthNotInCharset(char *text, char *charset);
char *findCharacterInString(char *text, char character);

// More function prototypes for helper functions
char *tokenizeStringWithSave(char *input, char *delimiter, char **saveptr);
int convertStringToInt(char *text);
void *resizeMemoryBlock(void *ptr, unsigned int oldSize, unsigned int newSize);
void handleCtrlC(int signal);
void removeComments(char *text);

// Function prototypes for utility functions
int parseUserInput(char *input);
void executeParsedCommand(char **command, int commandType);
char *findExecutablePath(char *commandName);
void (*findCommandFunction(char *commandName))(char **);
char *getEnvironmentVariable(char *variableName);

// Function prototypes for built-in shell commands
void displayEnvironmentVariables(char **arguments);
void exitShell(char **arguments);

// Main function for non-interactive mode
extern void runNonInteractiveMode(void);

// Initialization function
extern void initializeShell(char **currentCommand, int commandType);

#endif /* SHELL_H */

