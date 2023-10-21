#include "shell.h"

/**
 * Custom implementation of strcpy function.
 * Copies a string from source to destination.
 *
 * @param dest - the destination
 * @param src - the source
 * @return - pointer to destination
 */
char *custom_strcpy(char *dest, char *src)
{
    int index = 0;

    if (dest == src || src == 0)
        return dest;

    while (src[index])
    {
        dest[index] = src[index];
        index++;
    }

    dest[index] = '\0';
    return dest;
}

/**
 * Custom implementation of strdup function.
 * Duplicates a string.
 *
 * @param str - the string to duplicate
 * @return - pointer to the duplicated string
 */
char *custom_strdup(const char *str)
{
    int length = 0;
    char *duplicate;

    if (str == NULL)
        return NULL;

    while (*str++)
        length++;

    duplicate = malloc(sizeof(char) * (length + 1));

    if (!duplicate)
        return NULL;

    for (length++; length--;)
        duplicate[length] = *--str;

    return duplicate;
}

/**
 * Custom implementation of puts function.
 * Prints an input string to stdout.
 *
 * @param str - the string to be printed
 * @return - Nothing
 */
void custom_puts(char *str)
{
    int index = 0;

    if (!str)
        return;

    while (str[index] != '\0')
    {
        custom_putchar(str[index]);
        index++;
    }
}

/**
 * Custom implementation of putchar function.
 * Writes the character c to stdout.
 *
 * @param c - The character to print
 * @return - On success 1, on error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar(char c)
{
    static int bufferIndex;
    static char outputBuffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || bufferIndex >= WRITE_BUF_SIZE)
    {
        write(1, outputBuffer, bufferIndex);
        bufferIndex = 0;
    }

    if (c != BUF_FLUSH)
        outputBuffer[bufferIndex++] = c;

    return 1;
}
