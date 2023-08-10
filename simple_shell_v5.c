#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf("($) ");
        line = read_line();
        args = parse_line(line);
        
        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                free(line);
                free(args);
                exit(EXIT_SUCCESS);
            } else if (strcmp(args[0], "env") == 0) {
                int i = 0;
                while (environ[i] != NULL) {
                    printf("%s\n", environ[i]);
                    i++;
                }
                status = 1;
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

/* Read a line from stdin */
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            perror("read_line");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}

/* Parse a line into arguments */
char **parse_line(char *line)
{
    int bufsize = 64;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        perror("parse_line");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\a");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                perror("parse_line");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

/* Find the executable path using PATH */
char *find_path(char *command)
{
    char *path_env = getenv("PATH");
    char *path = strtok(path_env, ":");
    
    while (path != NULL) {
        char *full_path = malloc(strlen(path) + strlen(command) + 2);
        if (!full_path) {
            perror("find_path");
            exit(EXIT_FAILURE);
        }
        strcpy(full_path, path);
        strcat(full_path, "/");
        strcat(full_path, command);

        if (access(full_path, X_OK) == 0) {
            return full_path;
        }

        free(full_path);
        path = strtok(NULL, ":");
    }

    return NULL;
}

/* Launch a process */
int launch_process(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        /* Child process */
        if (execvp(args[0], args) == -1) {
            perror("launch_process");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Forking error */
        perror("launch_process");
    } else {
        /* Parent process */
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}