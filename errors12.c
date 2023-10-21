#include "shell.h"

/**
 * _erratoi - Converts a string to an integer with error handling.
 * @s: The string to be converted.
 *
 * This function converts a string to an integer. It checks for valid input
 * and handles potential errors. If the conversion is successful, it returns
 * the integer value. If there are errors or the number is out of range, it
 * returns -1.
 *
 * @param s - The string to be converted to an integer.
 * @return The converted integer value or -1 on error.
 */
int _erratoi(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;  /* Skip leading plus sign. */
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return (-1);  /* Integer out of range. */
        }
        else
            return (-1);  /* Invalid character found. */
    }
    return (result);
}

/**
 * print_error - Prints an error message with specific formatting.
 * @info: The parameter and return info struct.
 * @estr: String containing the specified error type.
 *
 * This function is used to print an error message to the standard error stream (stderr).
 * It includes the file name, line number, and the error description provided in the `estr`
 * parameter. This helps create well-formatted error messages for the user.
 *
 * @param info - The parameter and return info struct.
 * @param estr - The string containing the specified error type.
 * @return Nothing.
 */
void print_error(info_t *info, char *estr)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

/**
 * print_d - Prints a decimal (integer) number with specified formatting.
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * This function prints a decimal (integer) number with specified formatting. It can
 * handle both positive and negative numbers. It returns the number of characters printed.
 *
 * @param input - The input number to print.
 * @param fd - The file descriptor to write to.
 * @return The number of characters printed.
 */
int print_d(int input, int fd)
{
    int (*__putchar)(char) = _putchar;
    int i, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        __putchar = _eputchar;
    if (input < 0)
    {
        _abs_ = -input;
        __putchar('-');
        count++;
    }
    else
        _abs_ = input;
    current = _abs_;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (_abs_ / i)
        {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
    }
    __putchar('0' + current);
    count++;

    return count;
}

/**
 * convert_number - Converts a number to a string with specified base and flags.
 * @num: The number to convert.
 * @base: The base for the conversion (e.g., 10 for decimal).
 * @flags: Conversion flags.
 *
 * This function converts a number to a string with the specified base and flags.
 * It can handle both signed and unsigned numbers. The result is returned as a string.
 *
 * @param num - The number to convert.
 * @param base - The base for the conversion.
 * @param flags - Conversion flags (e.g., CONVERT_UNSIGNED for unsigned numbers).
 * @return The converted number as a string.
 */
char *convert_number(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }
    array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
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
 * remove_comments - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 *
 * This function is used to remove comments from a string by replacing the first
 * instance of '#' with a null terminator '\0'. It is often used for processing
 * configuration files or script input.
 *
 * @param buf - The address of the string to modify.
 * @return Nothing.
 */
void remove_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
    }
}
