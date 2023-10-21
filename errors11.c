#include "shell.h"

/**
 * _eputs - Prints a string to the standard error stream (stderr).
 * @str: The string to be printed to stderr.
 *
 * This function is used to write the provided string to the standard error stream,
 * typically used for error messages. It iterates through the string and writes
 * each character to stderr until the null-terminator is encountered.
 *
 * @param str - The string to print to stderr.
 * @return Nothing.
 */
void _eputs(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        _eputchar(str[i]);
        i++;
    }
}

/**
 * _eputchar - Writes a character to the standard error stream (stderr).
 * @c: The character to be printed to stderr.
 *
 * This function is used to write a single character to the standard error stream
 * (stderr). It can be used to display individual characters on the error stream.
 *
 * @param c - The character to print to stderr.
 * @return 1 on success or -1 on error (errno is set appropriately).
 */
int _eputchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * _putfd - Writes a character to the specified file descriptor.
 * @c: The character to be printed.
 * @fd: The file descriptor to write to.
 *
 * This function is used to write a single character to the specified file
 * descriptor. It can be employed to send individual characters to a specific
 * output stream, such as standard output (stdout) or a file.
 *
 * @param c - The character to print.
 * @param fd - The file descriptor to write to.
 * @return 1 on success or -1 on error (errno is set appropriately).
 */
int _putfd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * _putsfd - Writes a string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * This function writes the provided string to the specified file descriptor.
 * It iterates through the string and sends each character to the given file
 * descriptor. It returns the number of characters successfully written.
 *
 * @param str - The string to print.
 * @param fd - The file descriptor to write to.
 * @return The number of characters written.
 */
int _putsfd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return (0);
    while (*str)
    {
        i += _putfd(*str++, fd);
    }
    return (i);
}
