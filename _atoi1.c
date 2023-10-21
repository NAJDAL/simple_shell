#include "shell.h"

/**
 * Determines if the shell is running in interactive mode.
 *
 * This function checks whether the shell is in interactive mode by examining
 * the provided `info` struct and the standard input file descriptor. If the
 * conditions are met, it returns 1, indicating that the shell is in interactive
 * mode; otherwise, it returns 0.
 *
 * @param info - A struct containing relevant information about the shell.
 * @return 1 if the shell is in interactive mode, 0 otherwise.
 */
int interactive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * Checks if a character is a delimiter within a given delimiter string.
 *
 * This function takes a character `c` and a delimiter string `delim` as input.
 * It iterates through the `delim` string to determine whether the character `c`
 * is a delimiter. If the character is a delimiter, it returns 1; otherwise, it
 * returns 0.
 *
 * @param c - The character to check.
 * @param delim - The delimiter string.
 * @return 1 if `c` is a delimiter, 0 if not.
 */
int is_delim(char c, char *delim)
{
    while (*delim)
        if (*delim++ == c)
            return (1);
    return (0);
}

/**
 * Checks if a character is an alphabetic character.
 *
 * This function determines whether a given character `c` is an alphabetic
 * character, such as a letter (either lowercase or uppercase). If the character
 * is alphabetic, it returns 1; otherwise, it returns 0.
 *
 * @param c - The character to inspect.
 * @return 1 if `c` is an alphabetic character, 0 otherwise.
 */
int _isalpha(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 * Converts a string to an integer value.
 *
 * This function attempts to convert a given string `s` into an integer value.
 * It iterates through the string, handling signs and numeric characters to
 * produce the corresponding integer. If no numbers are found in the string, it
 * returns 0. The converted integer is returned as the result.
 *
 * @param s - The string to be converted to an integer.
 * @return The converted integer if numbers are present, or 0 if not.
 */
int _atoi(char *s)
{
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0; s[i] != '\0' && flag != 2; i++)
    {
        if (s[i] == '-')
            sign *= -1;

        if (s[i] >= '0' && s[i] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (s[i] - '0');
        }
        else if (flag == 1)
            flag = 2;
    }

    if (sign == -1)
        output = -result;
    else
        output = result;

    return (output);
}
