#include "shell.h"

/**
 * main - Entry point of the program.
 *
 * Description: This function sets up a signal handler and runs the shell loop.
 *
 * Return: 0 on success.
 */
int main(void)
{
    /* Install signal handler */
signal(SIGINT, handle_signal);

    /* Run the shell loop */
shell_loop();

    return (EXIT_SUCCESS);
}
