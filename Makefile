#ifndef SHELL_H
#define SHELL_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

// Core Pipeline Functions
char *read_line(void);
char **split_line(char *line);
int execute_command(char **args);

// Built-in Shell Commands
int shell_cd(char **args);
int shell_exit(char **args);
int num_builtins(void);

#endif // SHELL_H
