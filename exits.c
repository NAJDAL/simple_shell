#include "shell.h"

/**
 * _custom_strncpy - Copies a string with a specified length.
 * @destination: The destination string to be copied to.
 * @source: The source string to be copied from.
 * @max_length: The maximum number of characters to copy.
 *
 * Returns: The concatenated string.
 */
char *_custom_strncpy(char *destination, char *source, int max_length)
{
    int i, j;
    char *result = destination;

    i = 0;
    while (source[i] != '\0' && i < max_length - 1) {
        destination[i] = source[i];
        i++;
    }

    if (i < max_length) {
        j = i;
        while (j < max_length) {
            destination[j] = '\0';
            j++;
        }
    }
    return result;
}

/**
 * _custom_strncat - Concatenates two strings with a specified length.
 * @destination: The first string.
 * @source: The second string to append.
 * @max_length: The maximum number of bytes to be used.
 *
 * Returns: The concatenated string.
 */
char *_custom_strncat(char *destination, char *source, int max_length)
{
    int i, j;
    char *result = destination;

    i = 0;
    j = 0;

    while (destination[i] != '\0') {
        i++;
    }

    while (source[j] != '\0' && j < max_length) {
        destination[i] = source[j];
        i++;
        j++;
    }

    if (j < max_length) {
        destination[i] = '\0';
    }
    return result;
}

/**
 * _custom_strchar - Locates a character in a string.
 * @string: The string to be searched.
 * @character: The character to find.
 *
 * Returns: A pointer to the memory area within the string.
 */
char *_custom_strchar(char *string, char character)
{
    do {
        if (*string == character) {
            return string;
        }
    } while (*string++ != '\0');

    return NULL;
}
