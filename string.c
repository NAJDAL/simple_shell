#include "shell.h"

/**
 * _strlen - Calculate the length of a string
 * @s: The string whose length is to be determined
 *
 * Description: This function calculates the length of a given string.
 *
 * Return: The integer length of the string
 */
int _strlen(char *s)
{
    int i = 0;

    if (!s)
        return (0);

    while (*s++)
        i++;
    return (i);
}

/**
 * _strcmp - Compare two strings lexicographically
 * @s1: The first string
 * @s2: The second string
 *
 * Description: This function performs a lexicographic comparison of two strings.
 * It returns a negative value if s1 < s2, a positive value if s1 > s2, and 0 if s1 == s2.
 *
 * Return: The result of the comparison
 */
int _strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }
    if (*s1 == *s2)
        return (0);
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Check if one string starts with another
 * @haystack: The string to search within
 * @needle: The substring to find at the beginning of the haystack
 *
 * Description: This function checks if the 'needle' starts with the 'haystack.'
 * If it does, it returns the address of the next character in the 'haystack,' or NULL otherwise.
 *
 * Return: The address of the next character in the 'haystack,' or NULL if not found
 */
char *starts_with(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return (NULL);
    return ((char *)haystack);
}

/**
 * _strcat - Concatenate two strings
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Description: This function concatenates the 'src' string to the end of the 'dest' string.
 *
 * Return: Pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
    char *ret = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return (ret);
}
