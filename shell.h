#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>

/* Constants */
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/**
 * Struct map - Maps a command name to a function.
 *
 * @command_name: Name of the command
 * @func: The function that executes the command
 */
typedef struct map {
    char *command_name;
    void (*func)(char **command);
} FunctionMap;

/* Global variables */
extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

/* Assistive functions */
void print(char *message, int file_descriptor);
char **tokenizer(char *input, char *delimiter);
void remove_newline(char *str);
int string_length(char *str);
void string_copy(char *dest, char *src);

/* Assistive functions*/
int string_compare(const char *str1, const char *str2);
char *string_concat(char *str1, char *str2);
int string_span(char *str, const char *delimiters);
int string_cspan(char *str, const char *reject);
char *string_find(char *str, char target);

/* Assistive functions */
char *string_token(char *str, const char *delimiters, char **saveptr);
int string_to_integer(const char *str);
void *reallocate_memory(void *ptr, size_t old_size, size_t new_size);
void ctrl_c_handler(int signal);
void remove_comment(char *input);

/* Utility functions */
int parse_command(char *input);
void execute_command(char **command, int type);
char *get_command_path(char *command_name);
void (*get_builtin_func(char *command_name))(char **);
char *get_environment_variable(char *name);

/* Built-in functions */
void custom_env(char **command);
void custom_quit(char **command);

/* Main functions */
extern void non_interactive_mode(void);
extern void initialize_shell(char **current_command, int command_type);

#endif /* SHELL_H */i
