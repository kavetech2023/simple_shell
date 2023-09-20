#include "shell.h"

/**
 * print_history - displays the history list, one command by line, preceded
 * by line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int print_history(info_t *info) {
  print_list(info->history);
  return (0);
}

/**
 * unset_alias - removes an alias from the shell.
 * @info: Structure containing potential arguments.
 * @alias: The alias to remove.
 *
 * Return: 0 if the alias was removed successfully, otherwise 1.
 */
int unset_alias(info_t *info, char *alias) {
  char *equals_sign = strchr(alias, '=');
  if (!equals_sign) {
    return 1;
  }

  *equals_sign = '\0';
  int index = get_node_index(info->alias, node_starts_with(info->alias, alias, -1));
  *equals_sign = '=';
  if (index == -1) {
    return 1;
  }

  delete_node_at_index(&(info->alias), index);
  return 0;
}

/**
 * set_alias - creates an alias for a command in the shell.
 * @info: Structure containing potential arguments.
 * @alias: The alias to create.
 *
 * Return: 0 if the alias was created successfully, otherwise 1.
 */
int set_alias(info_t *info, char *alias) {
  char *equals_sign = strchr(alias, '=');
  if (!equals_sign) {
    return 1;
  }

  *equals_sign = '\0';
  unset_alias(info, alias);
  *equals_sign = '=';

  return (add_node_end(&(info->alias), alias, 0) == NULL);
}

/**
 * print_alias - prints an alias string.
 * @node: The alias node to print.
 *
 * Return: Always 0.
 */
int print_alias(list_t *node) {
  if (node) {
    char *equals_sign = strchr(node->str, '=');
    for (char *a = node->str; a <= equals_sign; a++) {
      putchar(*a);
    }
    putchar('\'');
    puts(equals_sign + 1);
    puts("'\n");
    return (0);
  }

  return (1);
}

/**
 * manage_aliases - mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int manage_aliases(info_t *info) {
  int i = 0;
  char *equals_sign = NULL;
  list_t *node = NULL;

  if (info->argc == 1) {
    node = info->alias;
    while (node) {
      print_alias(node);
      node = node->next;
    }
    return (0);
  }

  for (i = 1; info->argv[i]; i++) {
    equals_sign = strchr(info->argv[i], '=');
    if (equals_sign) {
      set_alias(info, info->argv[i]);
    } else {
      print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }
  }

  return (0);
}
