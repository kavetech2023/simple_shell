#include "shell.h"

/**
 * exit_shell - exits the shell with a given exit status
 * @info: Structure containing potential arguments.
 *
 * Return: 0 if the exit status is valid, otherwise 1.
 */
int exit_shell(info_t *info) {
  int exit_status;

  if (info->argv[1]) {
    // Check if the exit status is a valid number.
    exit_status = _erratoi(info->argv[1]);
    if (exit_status == -1) {
      info->status = 2;
      print_error(info, "Illegal number: ");
      _eputs(info->argv[1]);
      _eputchar('\n');
      return 1;
    }
  } else {
    // Exit with the default exit status.
    exit_status = 0;
  }

  // Exit the shell.
  exit(exit_status);
}

/**
 * change_directory - changes the current working directory of the process.
 * @info: Structure containing potential arguments.
 *
 * Return: 0 if the directory was changed successfully, otherwise 1.
 */
int change_directory(info_t *info) {
  char *directory;

  if (!info->argv[1]) {
    // Change to the home directory.
    directory = getenv("HOME");
    if (directory == NULL) {
      // TODO: Handle this error.
      return 1;
    }
  } else if (strcmp(info->argv[1], "-") == 0) {
    // Change to the previous working directory.
    directory = getenv("OLDPWD");
    if (directory == NULL) {
      // TODO: Handle this error.
      return 1;
    }
  } else {
    // Change to the specified directory.
    directory = info->argv[1];
  }

  // Change the current working directory.
  if (chdir(directory) == -1) {
    print_error(info, "Can't change directory to ");
    _eputs(directory);
    _eputchar('\n');
    return 1;
  }

  // Update the PWD and OLDPWD environment variables.
  setenv("OLDPWD", getenv("PWD"), 1);
  setenv("PWD", getcwd(NULL, 0), 1);

  return 0;
}

/**
 * print_help - prints help information for the shell.
 * @info: Structure containing potential arguments.
 *
 * Return: 0.
 */
int print_help(info_t *info) {
  _puts("Shell help information:\n");
  _puts("exit: exits the shell with a given exit status.\n");
  _puts("cd: changes the current working directory of the process.\n");
  _puts("help: prints help information for the shell.\n");

  return 0;
}
