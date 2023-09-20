#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024

int main() {
  char line[MAX_LINE_LENGTH];

  // Print the prompt.
  printf("$ ");

  // Read the user input.
  fgets(line, MAX_LINE_LENGTH, stdin);

  // Parse the command.
  char *argv[MAX_LINE_LENGTH];
  int argc = 0;
  char *token = strtok(line, " ");
  while (token != NULL) {
    argv[argc] = token;
    argc++;
    token = strtok(NULL, " ");
  }

  // Execute the command.
  int pid = fork();
  if (pid == 0) {
    // Child process.
    execvp(argv[0], argv);
    exit(1);
  } else {
    // Parent process.
    waitpid(pid, NULL, 0);
  }

  // Print the prompt again.
  printf("$ ");

  return 0;
}
