#include "shell.h"

/**
 * hsh - Main shell loop
 * @info: Parameter and return info struct
 * @av: Argument vector from main()
 *
 * Description: This function represents the main shell loop. It continuously
 * reads user input, processes it, and executes commands or built-in functions.
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2)
    {
        clear_info(info);
        if (interactive(info))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        r = get_input(info);
        if (r != -1)
        {
            set_info(info, av);
            builtin_ret = find_builtin(info);
            if (builtin_ret == -1)
                find_cmd(info);
        }
        else if (interactive(info))
            _putchar('\n');
        free_info(info, 0);
    }
    write_history(info);
    free_info(info, 1);
    if (!interactive(info) && info->status)
        exit(info->status);
    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return (builtin_ret);
}

/**
 * find_builtin - Find a built-in command
 * @info: Parameter and return info struct
 *
 * Description: This function searches for and executes a built-in command if one is found.
 *
 * Return: -1 if the built-in command is not found, 0 if it's executed successfully,
 * 1 if the built-in command is found but not successful, -2 if a built-in command signals exit()
 */
int find_builtin(info_t *info)
{
    int i, built_in_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].type; i++)
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    return (built_in_ret);
}

/**
 * find_cmd - Find a command in PATH
 * @info: Parameter and return info struct
 *
 * Description: This function searches for a command in the PATH environment variable and
 * sets the command path for execution.
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
        if (!is_delim(info->arg[i], " \t\n"))
            k++;
    if (!k)
        return;

    path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_cmd(info);
    }
    else
    {
        if ((interactive(info) || _getenv(info, "PATH=")
            || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
            fork_cmd(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

/**
 * fork_cmd - Fork and execute a command
 * @info: Parameter and return info struct
 *
 * Description: This function forks a child process and executes the specified command.
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environ(info)) == -1)
        {
            free_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
        /* TODO: PUT ERROR FUNCTION */
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}
