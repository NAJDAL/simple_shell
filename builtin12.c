#include "shell.h"

/**
 * _myhistory - Displays the shell's command history with line numbers.
 * @info: A structure containing potential arguments.
 *
 * This function displays the history list, showing each command with a line
 * number starting from 0. The information is extracted from the `info` structure,
 * and the command history is printed to the standard output.
 *
 * @param info - A structure containing relevant information.
 * @return Always 0.
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unset_alias - Unsets an alias by its name.
 * @info: A parameter struct containing information.
 * @str: The string representing the alias to unset.
 *
 * This function removes an alias with the provided name from the list of aliases
 * stored in the `info` structure. It locates the alias, deletes it, and returns 0
 * on success, or 1 on error.
 *
 * @param info - A structure containing relevant information.
 * @param str - The string alias to unset.
 * @return 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *p, c;
    int ret;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * set_alias - Sets an alias to a specific string.
 * @info: A parameter struct containing information.
 * @str: The string representing the alias to set.
 *
 * This function sets an alias with the provided name and value in the list of
 * aliases stored in the `info` structure. If the alias already exists, it is
 * updated; otherwise, a new alias is created. It returns 0 on success, or 1 on error.
 *
 * @param info - A structure containing relevant information.
 * @param str - The string alias to set.
 * @return 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *p;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (unset_alias(info, str));

    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string with single quotes.
 * @node: The alias node to print.
 *
 * This function prints an alias string with single quotes, separating the alias
 * name from its value. It is used to display aliases in a human-readable format.
 *
 * @param node - The alias node to print.
 * @return 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = _strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * _myalias - Manages shell aliases similar to the 'alias' command.
 * @info: A structure containing potential arguments.
 *
 * This function mimics the behavior of the 'alias' built-in command, allowing
 * the user to define, display, or unset aliases. It processes the provided
 * arguments and manages aliases accordingly.
 *
 * @param info - A structure containing relevant information.
 * @return Always 0.
 */
int _myalias(info_t *info)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        p = _strchr(info->argv[i], '=');
        if (p)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}
