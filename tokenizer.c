#include "shell.h"

/**
 * Custom implementation of strtow function to split a string into words.
 * Repeated delimiters are ignored.
 *
 * @param str - the input string
 * @param d - the delimiter string
 * @return - a pointer to an array of strings, or NULL on failure
 */
char **custom_strtow(char *str, char *d)
{
    int i, j, k, m, numWords = 0;
    char **result;

    if (str == NULL || str[0] == '\0')
        return NULL;

    if (!d)
        d = " ";

    for (i = 0; str[i] != '\0'; i++)
    {
        if (!isDelimiter(str[i], d) && (isDelimiter(str[i + 1], d) || !str[i + 1]))
            numWords++;
    }

    if (numWords == 0)
        return NULL;

    result = malloc((1 + numWords) * sizeof(char *));

    if (!result)
        return NULL;

    for (i = 0, j = 0; j < numWords; j++)
    {
        while (isDelimiter(str[i], d))
            i++;

        k = 0;
        while (!isDelimiter(str[i + k], d) && str[i + k])
            k++;

        result[j] = malloc((k + 1) * sizeof(char));

        if (!result[j])
        {
            for (k = 0; k < j; k++)
                free(result[k]);
            free(result);
            return NULL;
        }

        for (m = 0; m < k; m++)
            result[j][m] = str[i++];

        result[j][m] = '\0';
    }

    result[j] = NULL;
    return result;
}

/**
 * Custom implementation of strtow2 function to split a string into words.
 *
 * @param str - the input string
 * @param d - the delimiter
 * @return - a pointer to an array of strings, or NULL on failure
 */
char **custom_strtow2(char *str, char d)
{
    int i, j, k, m, numWords = 0;
    char **result;

    if (str == NULL || str[0] == '\0')
        return NULL;

    for (i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] != d && str[i + 1] == d) || (str[i] != d && !str[i + 1]) || str[i + 1] == d)
            numWords++;
    }

    if (numWords == 0)
        return NULL;

    result = malloc((1 + numWords) * sizeof(char *));

    if (!result)
        return NULL;

    for (i = 0, j = 0; j < numWords; j++)
    {
        while (str[i] == d && str[i] != d)
            i++;

        k = 0;
        while (str[i + k] != d && str[i + k] && str[i + k] != d)
            k++;

        result[j] = malloc((k + 1) * sizeof(char));

        if (!result[j])
        {
            for (k = 0; k < j; k++)
                free(result[k]);
            free(result);
            return NULL;
        }

        for (m = 0; m < k; m++)
            result[j][m] = str[i++];

        result[j][m] = '\0';
    }

    result[j] = NULL;
    return result;
}
