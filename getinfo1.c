#include "shell.h"

/**
 * clear_info - Initializes an info_t struct by setting its fields to initial values.
 * @info: A pointer to the info_t struct to be initialized.
 *
 * This function sets the fields of the info_t struct to their initial values. It
 * clears or sets the pointers to NULL, effectively preparing the structure for
 * subsequent use.
 *
 * @param info - The info_t struct to be initialized.
 */
void clear_info(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * set_info - Initializes an info_t struct using command arguments.
 * @info: A pointer to the info_t struct to be initialized.
 * @av: Argument vector (command arguments).
 *
 * This function initializes the info_t struct based on the provided command
 * arguments and prepares it for use in the shell. It sets the program name
 * (fname), parses and stores the command arguments (argv), and processes
 * alias replacement and variable substitution.
 *
 * @param info - The info_t struct to be initialized.
 * @param av - Argument vector containing command arguments.
 */
void set_info(info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0];
    if (info->arg)
    {
        info->argv = strtow(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = _strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        replace_alias(info);
        replace_vars(info);
    }
}

/**
 * free_info - Frees the fields of an info_t struct.
 * @info: A pointer to the info_t struct whose fields need to be freed.
 * @all: A boolean value (true if freeing all fields, false if partial).
 *
 * This function frees various fields within the info_t struct, depending on
 * the 'all' parameter. When 'all' is set to true, it clears and deallocates
 * memory for fields like 'argv', 'path', 'env', 'history', 'alias', and 'environ'.
 * It also closes the file descriptor associated with 'readfd'. If 'all' is false,
 * it only frees the 'argv' field to release memory allocated for command arguments.
 *
 * @param info - The info_t struct whose fields are to be freed.
 * @param all - A boolean value (true for freeing all fields, false for partial).
 */
void free_info(info_t *info, int all)
{
    ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;

    if (all)
    {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->env)
            free_list(&(info->env));
        if (info->history)
            free_list(&(info->history));
        if (info->alias)
            free_list(&(info->alias));
        ffree(info->environ);
        info->environ = NULL;
        bfree((void **)info->cmd_buf);

        if (info->readfd > 2)
            close(info->readfd);
        _putchar(BUF_FLUSH);
    }
}
