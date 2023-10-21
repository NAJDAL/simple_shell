#include "shell.h"

/**
 * get_environ - Returns a copy of the environment variables as an array of strings.
 * @info: A structure containing potential arguments. Used to maintain function prototype.
 *
 * This function retrieves a copy of the environment variables stored in the 'info' structure.
 * If the environment has been changed (env_changed flag set), it converts the environment
 * linked list into an array of strings and updates the 'info->environ' field with this new
 * representation.
 *
 * @param info - The structure containing potential arguments.
 * @return - A string array containing environment variables.
 */
char **get_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return info->environ;
}

/**
 * _unsetenv - Removes an environment variable from the environment list.
 * @info: A structure containing potential arguments. Used to maintain function prototype.
 * @var: The string representing the environment variable to be removed.
 *
 * This function removes an environment variable identified by 'var' from the environment
 * linked list stored in 'info'. If a matching variable is found, it is deleted, and the
 * 'info->env_changed' flag is set to indicate that the environment has been modified.
 *
 * @param info - The structure containing potential arguments.
 * @param var - The string representing the environment variable to be removed.
 * @return - 1 if the variable is successfully deleted, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return 0;

    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }

    return info->env_changed;
}

/**
 * _setenv - Initializes or modifies an environment variable.
 * @info: A structure containing potential arguments. Used to maintain function prototype.
 * @var: The string representing the environment variable name.
 * @value: The string representing the environment variable value.
 *
 * This function initializes a new environment variable identified by 'var' and assigns
 * it a value specified by 'value'. If an environment variable with the same name already
 * exists, its value is updated. The function first checks for an existing variable, and
 * if found, it modifies the value. If not found, it creates a new variable and appends
 * it to the environment linked list.
 *
 * @param info - The structure containing potential arguments.
 * @param var - The string representing the environment variable name.
 * @param value - The string representing the environment variable value.
 * @return - Always 0, indicating success.
 */
int _setenv(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return 0;

    buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return 1;

    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);

    node = info->env;

    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return 0;
        }
        node = node->next;
    }

    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;

    return 0;
}
