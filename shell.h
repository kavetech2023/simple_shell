#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define COMMAND_LENGTH 1024

void execute_command(char *args[]);
void tokenize_command(char *command, char *args[]);

#endif
