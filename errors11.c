#include "shell.h"

/**
 * _custom_puts - Outputs a string to the standard error stream.
 * @str: The string to be printed.
 *
 * Returns: Nothing.
 */
void _custom_puts(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0') {
        _custom_putchar(str[i]);
        i++;
    }
}

/**
 * _custom_putchar - Writes a character to the standard error stream.
 * @c: The character to print.
 *
 * Returns: 1 on success, -1 on error with errno set appropriately.
 */
int _custom_putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return 1;
}

/**
 * _write_to_fd - Writes a character to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Returns: 1 on success, -1 on error with errno set appropriately.
 */
int _write_to_fd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return 1;
}

/**
 * _custom_puts_to_fd - Outputs a string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Returns: The number of characters written.
 */
int _custom_puts_to_fd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return 0;
    while (*str) {
        i += _write_to_fd(*str++, fd);
    }
    return i;
}
