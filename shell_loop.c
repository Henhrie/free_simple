#include "shell.h"

/* Implement the shell_loop function */
void shell_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("($) ");
        line = read_line();
        args = parse_line(line);
        status = execute_command(args);

        free(line);
        free(args);
    } while (status);
}