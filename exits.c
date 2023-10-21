#include "shell.h"

/**
 * _strncpy - Copies a string up to a specified number of characters.
 * @dest: The destination string to be copied to.
 * @src: The source string to be copied from.
 * @n: The maximum number of characters to copy.
 *
 * This function copies a portion of the source string into the destination string,
 * up to a specified maximum number of characters (n). If the source string is shorter
 * than n characters, the rest of the destination is filled with null terminators.
 *
 * @param dest - The destination string.
 * @param src - The source string.
 * @param n - The maximum number of characters to copy.
 * @return The concatenated string (dest).
 */
char *_strncpy(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    i = 0;
    while (src[i] != '\0' && i < n - 1)
    {
        dest[i] = src[i];
        i++;
    }
    if (i < n)
    {
        j = i;
        while (j < n)
        {
            dest[j] = '\0';
            j++;
        }
    }
    return s;
}

/**
 * _strncat - Concatenates two strings, up to a specified maximum number of characters.
 * @dest: The first string.
 * @src: The second string to be concatenated.
 * @n: The maximum number of bytes to be used for concatenation.
 *
 * This function appends a portion of the source string onto the end of the destination
 * string, up to a specified maximum number of characters (n). If the source string is
 * shorter than n characters, it is appended entirely, and null terminators are added
 * to the result if necessary.
 *
 * @param dest - The first string.
 * @param src - The second string to be concatenated.
 * @param n - The maximum number of characters to concatenate.
 * @return The concatenated string (dest).
 */
char *_strncat(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    i = 0;
    j = 0;
    while (dest[i] != '\0')
        i++;
    while (src[j] != '\0' && j < n)
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    if (j < n)
        dest[i] = '\0';
    return s;
}

/**
 * _strchr - Locates a character in a string and returns a pointer to it.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * This function searches for the first occurrence of the specified character (c) in
 * the given string (s). If found, it returns a pointer to the location of the character
 * in the memory area of the string. If the character is not found, it returns NULL.
 *
 * @param s - The string to be searched.
 * @param c - The character to locate.
 * @return A pointer to the memory area containing the character (s) or NULL if not found.
 */
char *_strchr(char *s, char c)
{
    do {
        if (*s == c)
            return s;
    } while (*s++ != '\0');

    return NULL;
}
