#include "shell.h"

/**
 * main - Entry point for the custom shell.
 * @ac: Argument count, the number of command-line arguments.
 * @av: Argument vector, an array of strings containing the arguments.
 *
 * This is the main entry point for a custom shell program. It initializes the
 * shell environment, processes command-line arguments, and manages the execution
 * of the shell. It opens and reads history, populates the environment list, and
 * then enters the shell loop to handle user commands.

 * @param ac - The number of command-line arguments.
 * @param av - An array of strings containing the command-line arguments.
 * @return - 0 on successful execution, 1 on error.
 */
int main(int ac, char **av)
{
    info_t info[] = { INFO_INIT };
    int fd = 2;

    // Assembly code to manipulate the 'fd' variable
    asm("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd));

    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY);

        if (fd == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _eputs(av[0]);
                _eputs(": 0: Can't open ");
                _eputs(av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return EXIT_FAILURE;
        }

        info->readfd = fd;
    }

    populate_env_list(info);
    read_history(info);
    hsh(info, av);

    return EXIT_SUCCESS;
}
