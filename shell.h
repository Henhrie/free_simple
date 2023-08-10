#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


/* Function prototypes */
void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
char *find_path(char *command);
int execute_command(char **args);
int launch_process(char **args);
void handle_signal(int signo);
int execute_builtin(char **args);
char *own_getline(void);
char **split_line(char *line);
int shell_setenv(char **args);
int shell_unsetenv(char **args);
int shell_cd(char **args);
int execute_commands(char ***commands);
int execute_logical(char ***commands, int logical_operator);
int execute_logical(char ***commands, Alias *aliases, int *num_aliases);
void print_aliases(Alias *aliases, int num_aliases);
void add_alias(Alias *aliases, int *num_aliases, char *name, char *value);
void replace_alias(Alias *aliases, int num_aliases, char *name, char *value);
char *get_alias_value(Alias *aliases, int num_aliases, char *name);
char *replace_variables(char *line, int last_status);
char *remove_comments(char *line);
int execute_commands(char ***commands, Alias *aliases, int *num_aliases, int *last_status);
void execute_from_file(const char *filename, Alias *aliases, int *num_aliases);

extern char **environ;



#endif /* SHELL_H */