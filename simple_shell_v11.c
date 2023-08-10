#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char *line;
    char **commands;
    int status;

    do {
        printf("($) ");
        line = own_getline();
        commands = parse_line(line);
        
        int i = 0;
        while (commands[i] != NULL) {
            char **args = split_line(commands[i]);
            if (args[0] != NULL) {
                if (strcmp(args[0], "exit") == 0) {
                    int exit_status = 0;
                    if (args[1] != NULL) {
                        exit_status = atoi(args[1]);
                    }
                    free(line);
                    free(commands);
                    free(args);
                    exit(exit_status);
                } else if (strcmp(args[0], "env") == 0) {
                    int j = 0;
                    while (environ[j] != NULL) {
                        printf("%s\n", environ[j]);
                        j++;
                    }
                } else if (strcmp(args[0], "setenv") == 0) {
                    shell_setenv(args);
                } else if (strcmp(args[0], "unsetenv") == 0) {
                    shell_unsetenv(args);
                } else if (strcmp(args[0], "cd") == 0) {
                    shell_cd(args);
                } else {
                    /* Check if command exists in PATH */
                    char *path = find_path(args[0]);
                    if (path != NULL) {
                        free(args[0]);
                        args[0] = path;
                        launch_process(args);
                    } else {
                        printf("Command not found: %s\n", args[0]);
                    }
                }
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
    char **commands = malloc(BUFFER_SIZE * sizeof(char*));
    if (!commands) {
        perror("parse_line");
        exit(EXIT_FAILURE);
    }

    char *command;
    int position = 0;
    while ((command = strchr(line, ';')) != NULL) {
        *command = '\0';
        commands[position] = line;
        line = command + 1;
        position++;
    }
    commands[position] = line;
    commands[position + 1] = NULL;

    return commands;
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