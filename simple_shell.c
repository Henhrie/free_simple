#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * main - Entry point of the program.
 *
 * Description:
 *   Implements a simple shell loop that prompts the user for a command,
 *   reads the command from stdin, parses it into arguments, and launches a
 *   process to execute it.
 *   The loop continues until the user enters an exit command or
 *   an error occurs.
 *
 * Return:
 *   (int) EXIT_SUCCESS on successful execution.
 */
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

return (EXIT_SUCCESS);
}

/**
 * read_line - Read a line from stdin.
 *
 * Return:
 *   (char *) The line read from stdin as a dynamically allocated string.
 *   NULL if an error occurs or EOF is reached.
 */
char *read_line(void)
{
char *line = NULL;
size_t bufsize = 0;

if (getline(&line, &bufsize, stdin) == -1)
{
if (feof(stdin))
{
exit(EXIT_SUCCESS);
}
else
{
perror("read_line");
exit(EXIT_FAILURE);
}
}

return (line);
}

/**
 * parse_line - Parse a line into arguments.
 *
 * @line: The line to parse.
 *
 * Return:
 *   (char **) An array of pointers to the parsed arguments.
 *   The last element of the array is NULL.
 */
char **parse_line(char *line)
{
int bufsize = 64;
int position = 0;
char **tokens = malloc(bufsize * sizeof(char *));
char *token;

if (!tokens)
{
perror("parse_line");
exit(EXIT_FAILURE);
}

token = strtok(line, " \t\r\n\a");
while (token != NULL)
{
tokens[position] = token;
position++;

if (position >= bufsize)
{
bufsize += 64;
tokens = realloc(tokens, bufsize *sizeof(char *));
if (!tokens)
{
perror("parse_line");
exit(EXIT_FAILURE);
}
}

token = strtok(NULL, " \t\r\n\a");
}
tokens[position] = NULL;
return (tokens);
}

/**
 * launch_process - Launch a process to execute a command.
 *
 * @args: An array of pointers to the arguments of the command.
 *
 * Return:
 *   (int) 1 on successful execution of the command.
 */
int launch_process(char **args)
{
pid_t pid, wpid;
int status;

pid = fork();
if (pid == 0)
{
    /* Child process */
if (execvp(args[0], args) == -1)
{
perror("launch_process");
}
exit(EXIT_FAILURE);
}
else
if (pid < 0)
{
    /* Forking error */
perror("launch_process");
}
else
{
    /* Parent process */
do {
wpid = waitpid(pid, &status, WUNTRACED);
} while (!(WIFEXITED(status) || WIFSIGNALED(status)));
}

return (1);
}
