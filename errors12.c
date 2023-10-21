#include "shell.h"

/**
 * _custom_atoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Returns: The converted number or -1 on error.
 */
int _custom_atoi(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return -1;
        } else {
            return -1;
        }
    }
    return result;
}

/**
 * print_custom_error - Prints an error message.
 * @info: The parameter and return info struct.
 * @customError: String containing a specified error type.
 *
 * Returns: Nothing.
 */
void print_custom_error(info_t *info, char *customError)
{
    _custom_puts(info->fname);
    _custom_puts(": ");
    print_custom_d(info->line_count, STDERR_FILENO);
    _custom_puts(": ");
    _custom_puts(info->argv[0]);
    _custom_puts(": ");
    _custom_puts(customError);
}

/**
 * print_custom_d - Prints a decimal (integer) number (base 10).
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * Returns: The number of characters printed.
 */
int print_custom_d(int input, int fd)
{
    int (*custom_putchar)(char) = _custom_putchar;
    int i, count = 0;
    unsigned int absValue, current;

    if (fd == STDERR_FILENO)
        custom_putchar = _custom_putchar;

    if (input < 0) {
        absValue = -input;
        custom_putchar('-');
        count++;
    } else {
        absValue = input;
    }

    current = absValue;

    for (i = 1000000000; i > 1; i /= 10) {
        if (absValue / i) {
            custom_putchar('0' + current / i);
            count++;
        }
        current %= i;
    }

    custom_putchar('0' + current);
    count++;

    return count;
}

/**
 * custom_convert_number - Converter function, similar to itoa.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags.
 *
 * Returns: The converted string.
 */
char *custom_convert_number(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CUSTOM_CONVERT_UNSIGNED) && num < 0) {
        n = -num;
        sign = '-';
    }

    array = flags & CUSTOM_CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;

    return ptr;
}

/**
 * custom_remove_comments - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 *
 * Returns: Nothing.
 */
void custom_remove_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++) {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' ')) {
            buf[i] = '\0';
            break;
        }
    }
}
