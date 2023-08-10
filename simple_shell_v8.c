#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

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