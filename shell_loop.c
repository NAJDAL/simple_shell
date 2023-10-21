#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter and return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or an error code
 */
int main_shell(info_t *info, char **av)
{
    ssize_t read_size = 0;
    int builtin_result = 0;

    while (read_size != -1 && builtin_result != -2)
    {
        clear_info(info);
        if (interactive(info))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        read_size = get_input(info);
        if (read_size != -1)
        {
            set_info(info, av);
            builtin_result = find_builtin(info);
            if (builtin_result == -1)
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
    if (builtin_result == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return builtin_result;
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter and return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
    int i;
    int built_in_result = -1;
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
    {
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_result = builtintbl[i].func(info);
            break;
        }
    }
    return built_in_result;
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter and return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
    char *path = NULL;
    int i, count;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    count = 0;
    for (i = 0; info->arg[i]; i++)
    {
        if (!is_delim(info->arg[i], " \t\n"))
        {
            count++;
        }
    }
    if (!count)
    {
        return;
    }
    path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_cmd(info);
    }
    else
    {
        if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
        {
            fork_cmd(info);
        }
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

/**
 * fork_cmd - forks an exec thread to run cmd
 * @info: the parameter and return info struct
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
            {
                exit(126);
            }
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
            {
                print_error(info, "Permission denied\n");
            }
        }
    }
}
