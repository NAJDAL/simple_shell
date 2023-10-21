#include "shell.h"

/**
 * initialize_info - Initializes the info_t struct.
 * @info: Pointer to the info_t struct to be initialized.
 */
void initialize_info(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * configure_info - Configures the info_t struct with provided arguments.
 * @info: Pointer to the info_t struct to be configured.
 * @av: Argument vector (av).
 */
void configure_info(info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0];
    if (info->arg) {
        info->argv = tokenize(info->arg, " \t");
        if (!info->argv) {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv) {
                info->argv[0] = duplicate_string(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        replace_aliases(info);
        replace_variables(info);
    }
}

/**
 * release_info - Releases memory associated with the info_t struct fields.
 * @info: Pointer to the info_t struct.
 * @freeAll: Boolean indicating whether to free all fields or not.
 */
void release_info(info_t *info, int freeAll)
{
    free_string_array(info->argv);
    info->argv = NULL;
    info->path = NULL;

    if (freeAll) {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->env)
            free_linked_list(&(info->env));
        if (info->history)
            free_linked_list(&(info->history));
        if (info->alias)
            free_linked_list(&(info->alias));
        free_string_array(info->environ);
        info->environ = NULL;

        if (info->readfd > 2)
            close(info->readfd);
        write(STDOUT_FILENO, "\0", 1);
    }
}
