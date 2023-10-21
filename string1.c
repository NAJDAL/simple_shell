#include "shell.h"

/**
 * _strcpy - Copy a string
 * @dest: The destination
 * @src: The source
 *
 * Description: This function copies the characters from the 'src' string to the 'dest' string.
 *
 * Return: Pointer to the destination
 */
char *_strcpy(char *dest, char *src)
{
    int i = 0;

    if (dest == src || src == 0)
        return (dest);
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
    return (dest);
}

/**
 * _strdup - Duplicate a string
 * @str: The string to duplicate
 *
 * Description: This function duplicates the input string and returns a new string.
 *
 * Return: Pointer to the duplicated string or NULL if allocation fails
 */
char *_strdup(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return (NULL);
    while (*str++)
        length++;
    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return (NULL);
    for (length++; length--;)
        ret[length] = *--str;
    return (ret);
}

/**
 * _puts - Print a string
 * @str: The string to be printed
 *
 * Description: This function prints the characters in the input string 'str' to the standard output.
 *
 * Return: Nothing
 */
void _puts(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}

/**
 * _putchar - Write a character to stdout
 * @c: The character to print
 *
 * Description: This function writes the character 'c' to the standard output (stdout).
 *
 * Return: On success, it returns 1. On error, it returns -1, and errno is set appropriately.
 */
int _putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}
