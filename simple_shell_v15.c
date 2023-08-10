#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define MAX_ALIASES 50

/* Struct to store aliases */
typedef struct {
    char *name;
    char *value;
} Alias;

int main(void)
{
    char *line;
    char **commands;
    int status;
    int num_aliases = 0;
    Alias aliases[MAX_ALIASES];
    int last_status = 0;

    do {
        printf("($) ");
        line = own_getline();
        line = remove_comments(line);
        commands = parse_line(line);
        
        int i = 0;
        while (commands[i] != NULL) {
            char **args = split_line(commands[i]);
            if (args[0] != NULL) {
                last_status = execute_commands(&commands[i], aliases, &num_aliases, &last_status);
            }
            free(args);
            i++;
        }

        free(line);
        free(commands);
    } while (status);

    return EXIT_SUCCESS;
}

/* Custom getline function */
char *own_getline(void)
{
    // ... (same as previous versions)
}

/* Parse a line into commands */
char **parse_line(char *line)
{
    // ... (same as previous versions)
}

/* Split a command into arguments */
char **split_line(char *line)
{
    // ... (same as previous versions)
}

/* Find the executable path using PATH */
char *find_path(char *command)
{
    // ... (same as previous versions)
}

/* Launch a process */
void launch_process(char **args)
{
    // ... (same as previous versions)
}

/* Set an environment variable */
void shell_setenv(char **args)
{
    // ... (same as previous versions)
}

/* Unset an environment variable */
void shell_unsetenv(char **args)
{
    // ... (same as previous versions)
}

/* Change current directory */
void shell_cd(char **args)
{
    // ... (same as previous versions)
}

/* Execute logical operators */
int execute_logical(char ***commands, Alias *aliases, int *num_aliases, int *last_status)
{
    // ... (implementation of logical operators)
}

/* Execute builtin commands */
int execute_builtin(char **args, Alias *aliases, int *num_aliases, int *last_status)
{
    // ... (implementation of builtin commands)
}

/* Print aliases */
void print_aliases(Alias *aliases, int num_aliases)
{
    // ... (same as previous versions)
}

/* Add an alias */
void add_alias(Alias *aliases, int *num_aliases, char *name, char *value)
{
    // ... (same as previous versions)
}

/* Replace an alias */
void replace_alias(Alias *aliases, int num_aliases, char *name, char *value)
{
    // ... (same as previous versions)
}

/* Get the value of an alias */
char *get_alias_value(Alias *aliases, int num_aliases, char *name)
{
    // ... (same as previous versions)
}

/* Replace variables in a line */
char *replace_variables(char *line, int last_status)
{
    // ... (same as previous versions)
}

/* Remove comments from a line */
char *remove_comments(char *line)
{
    char *result = malloc(BUFFER_SIZE);
    char *p = line;
    char *r = result;
    while (*p != '\0') {
        if (*p == '#') {
            break;
        }
        *r++ = *p++;
    }
    *r = '\0';
    return result;
}