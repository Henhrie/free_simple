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
        status = launch_process(args);

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