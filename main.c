#include "shell.h"

/* Main function */
int main(void)
{
    /* Install signal handler */
signal(SIGINT, handle_signal);

    /* Run the shell loop */
shell_loop();

return (EXIT_SUCCESS);
}