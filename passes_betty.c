#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024

/* Function prototypes */
void parse_line(char *, char **);
void execute_command(char **);

int main() {
  char line[MAX_LINE_LENGTH];
  char *args[MAX_LINE_LENGTH];

  /* Display the prompt */
  printf("$ ");

  /* Read the command line */
  fgets(line, MAX_LINE_LENGTH, stdin);

  /* Parse the command line */
  parse_line(line, args);

  /* Execute the command */
  execute_command(args);

  return 0;
}

void parse_line(char *line, char **args) {
  /* Split the command line into arguments */
  char *token = strtok(line, " ");
  int i = 0;
  while (token != NULL) {
    args[i] = token;
    i++;
    token = strtok(NULL, " ");
  }

  /* Terminate the args array with a NULL pointer */
  args[i] = NULL;
}

void execute_command(char **args) {
  /* Check if the command is a built-in */
  if (strcmp(args[0], "exit") == 0) {
    exit(0);
  }

  /* Fork a child process to execute the command */
  pid_t pid = fork();
  if (pid == 0) {
    /* Child process */
    execve(args[0], args, NULL);
    perror("execve");
    exit(1);
  } else {
    /* Parent process */
    int status;
    waitpid(pid, &status, 0);

    if (status != 0) {
      printf("%s: command failed\n", args[0]);
    }
  }
}
