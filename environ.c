#include "shell.h"

/**
 * _myenv - Prints the current environment variables.
 * @info: A structure containing potential arguments.
 *
 * This function displays the current environment variables by printing each
 * variable and its value to the standard output. The environment variables are
 * extracted from the `info` structure.
 *
 * @param info - A structure containing relevant information.
 * @return Always 0.
 */
int _myenv(info_t *info)
{
    print_list_str(info->env);
    return (0);
}

/**
 * _getenv - Retrieves the value of an environment variable by name.
 * @info: A structure containing potential arguments.
 * @name: The name of the environment variable to retrieve.
 *
 * This function searches for an environment variable with the given name and
 * returns its value. If the variable is not found, it returns NULL.
 *
 * @param info - A structure containing relevant information.
 * @param name - The name of the environment variable to retrieve.
 * @return The value of the environment variable, or NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *p;

    while (node)
    {
        p = starts_with(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * _mysetenv - Sets or modifies an environment variable.
 * @info: A structure containing potential arguments.
 *
 * This function allows the initialization or modification of an environment variable.
 * It expects two arguments: the name of the variable and its new value. If the number
 * of arguments is incorrect, an error message is displayed.
 *
 * @param info - A structure containing relevant information.
 * @return 0 on success, or 1 if there's an incorrect number of arguments.
 */
int _mysetenv(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (_setenv(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * _myunsetenv - Removes one or more environment variables.
 * @info: A structure containing potential arguments.
 *
 * This function allows the removal of environment variables by name. It can take
 * multiple variable names as arguments to unset them. If there are too few arguments,
 * an error message is displayed.
 *
 * @param info - A structure containing relevant information.
 * @return Always 0.
 */
int _myunsetenv(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return (0);
}

/**
 * populate_env_list - Populates the environment linked list from 'environ'.
 * @info: A structure containing potential arguments.
 *
 * This function initializes the environment linked list by populating it with
 * the environment variables and their values from the 'environ' global variable.
 *
 * @param info - A structure containing relevant information.
 * @return Always 0.
 */
int populate_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->env = node;
    return (0);
}
