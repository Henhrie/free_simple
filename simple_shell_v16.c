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

int main(int argc, char *argv[])
{
    Alias aliases[MAX_ALIASES];
    int num_aliases = 0;
    int last_status = 0;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 2) {
        execute_from_file(argv[1], aliases, &num_aliases);
        return EXIT_SUCCESS;
    }

    char *line;
    char **commands;
    int status;

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
    // ... (same as previous versions)
}

/* Execute commands from a file */
void execute_from_file(const char *filename, Alias *aliases, int *num_aliases)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {
        line[strcspn(line, "\n")] = '\0'; // Remove trailing newline
        line = remove_comments(line);
        char **commands = parse_line(line);
        
        int i = 0;
        while (commands[i] != NULL) {
            char **args = split_line(commands[i]);
            if (args[0] != NULL) {
                int last_status = 0;
                execute_commands(&commands[i], aliases, num_aliases, &last_status);
            }
            free(args);
            i++;
        }

        free(commands);
    }

    free(line);
    fclose(file);
}