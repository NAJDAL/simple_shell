#include "shell.h"

/**
 * Custom implementation of strlen function.
 * Calculates the length of a string.
 *
 * @param s - the string to measure
 * @return - length of the string
 */
int custom_strlen(char *s)
{
    int length = 0;

    if (!s)
        return 0;

    while (*s)
    {
        length++;
        s++;
    }

    return length;
}

/**
 * Custom implementation of strcmp function.
 * Performs lexicographic comparison of two strings.
 *
 * @param s1 - the first string
 * @param s2 - the second string
 * @return - negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int custom_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }

    if (*s1 == *s2)
        return 0;
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * Custom implementation of starts_with function.
 * Checks if one string starts with another.
 *
 * @param haystack - the string to search
 * @param needle - the substring to find
 * @return - address of the next character in haystack or NULL
 */
char *custom_starts_with(const char *haystack, const char *needle)
{
    while (*needle)
    {
        if (*needle++ != *haystack++)
            return NULL;
    }

    return (char *)haystack;
}

/**
 * Custom implementation of strcat function.
 * Concatenates two strings.
 *
 * @param dest - the destination buffer
 * @param src - the source buffer
 * @return - pointer to the destination buffer
 */
char *custom_strcat(char *dest, char *src)
{
    char *result = dest;

    while (*dest)
    {
        dest++;
    }

    while (*src)
    {
        *dest++ = *src++;
    }

    *dest = *src;
    
    return result;
}
