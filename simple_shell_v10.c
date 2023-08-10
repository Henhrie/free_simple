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
    char **args;
    int status;

    do {
        printf("($) ");
        line = own_getline();
        args = parse_line(line);
        
        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                int exit_status = 0;
                if (args[1] != NULL) {
                    exit_status = atoi(args[1]);
                }
                free(line);
                free(args);
                exit(exit_status);
            } else if (strcmp(args[0], "env") == 0) {
                int i = 0;
                while (environ[i] != NULL) {
                    printf("%s\n", environ[i]);
                    i++;
                }
                status = 1;
            } else if (strcmp(args[0], "setenv") == 0) {
                status = shell_setenv(args);
            } else if (strcmp(args[0], "unsetenv") == 0) {
                status = shell_unsetenv(args);
            } else if (strcmp(args[0], "cd") == 0) {
                status = shell_cd(args);
            } else {
                /* Check if command exists in PATH */
                char *path = find_path(args[0]);
                if (path != NULL) {
                    free(args[0]);
                    args[0] = path;
                    status = launch_process(args);
                } else {
                    printf("Command not found: %s\n", args[0]);
                    status = 1;
                }
            }
        }

        free(line);
        free(args);
    } while (status);

    return EXIT_SUCCESS;
}

/* Custom getline function */
char *own_getline(void)
{
    // ... (same as previous versions)
}

/* Parse a line into arguments */
char **parse_line(char *line)
{
    return split_line(line);
}

/* Split a line into arguments */
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
int launch_process(char **args)
{
    // ... (same as previous versions)
}

/* Set an environment variable */
int shell_setenv(char **args)
{
    // ... (same as previous versions)
}

/* Unset an environment variable */
int shell_unsetenv(char **args)
{
    // ... (same as previous versions)
}

/* Change current directory */
int shell_cd(char **args)
{
    if (args[1] == NULL) {
        char *home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "cd: No home directory set\n");
            return 1;
        }
        if (chdir(home) != 0) {
            perror("cd");
        }
    } else if (strcmp(args[1], "-") == 0) {
        char *oldpwd = getenv("OLDPWD");
        if (oldpwd == NULL) {
            fprintf(stderr, "cd: No previous directory\n");
            return 1;
        }
        if (chdir(oldpwd) != 0) {
            perror("cd");
        }
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }

    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        perror("getcwd");
        return 1;
    }

    if (setenv("PWD", cwd, 1) != 0) {
        perror("setenv");
    }
    if (setenv("OLDPWD", cwd, 1) != 0) {
        perror("setenv");
    }
    
    free(cwd);

    return 1;
}