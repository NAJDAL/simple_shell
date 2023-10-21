#include "shell.h"

/**
 * Checks if the current character in the buffer is a chain delimiter.
 *
 * @param info - the parameter struct
 * @param buf - the character buffer
 * @param p - address of the current position in buf
 * @return - 1 if a chain delimiter, 0 otherwise
 */
int isChainDelimiter(info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        info->cmdBufType = CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        info->cmdBufType = CMD_AND;
    }
    else if (buf[j] == ';') /* Found the end of this command */
    {
        buf[j] = 0; /* Replace semicolon with null */
        info->cmdBufType = CMD_CHAIN;
    }
    else
        return 0;
    *p = j;
    return 1;
}

/**
 * Checks whether we should continue chaining based on the last status.
 *
 * @param info - the parameter struct
 * @param buf - the character buffer
 * @param p - address of the current position in buf
 * @param i - starting position in buf
 * @param len - length of buf
 */
void checkChaining(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->cmdBufType == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }
    if (info->cmdBufType == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
 * Replaces aliases in the tokenized string.
 *
 * @param info - the parameter struct
 * @return - 1 if replaced, 0 otherwise
 */
int replaceAliases(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = findNodeWithPrefix(info->alias, info->argv[0], '=');
        if (!node)
            return 0;
        free(info->argv[0]);
        p = strchr(node->str, '=');
        if (!p)
            return 0;
        p = strdup(p + 1);
        if (!p)
            return 0;
        info->argv[0] = p;
    }
    return 1;
}

/**
 * Replaces variables in the tokenized string.
 *
 * @param info - the parameter struct
 * @return - 1 if replaced, 0 otherwise
 */
int replaceVariables(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!_strcmp(info->argv[i], "$?"))
        {
            replaceString(&(info->argv[i]), strdup(convertNumber(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->argv[i], "$$"))
        {
            replaceString(&(info->argv[i]), strdup(convertNumber(getpid(), 10, 0)));
            continue;
        }
        node = findNodeWithPrefix(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replaceString(&(info->argv[i]), strdup(strchr(node->str, '=') + 1));
            continue;
        }
        replaceString(&info->argv[i], strdup(""));
    }
    return 0;
}

/**
 * Replaces a string.
 *
 * @param old - address of the old string
 * @param new - new string
 * @return - 1 if replaced, 0 otherwise
 */
int replaceString(char **old, char *new)
{
    free(*old);
    *old = new;
    return 1;
}
