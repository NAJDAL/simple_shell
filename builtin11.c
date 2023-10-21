#include "shell.h"

/**
 * _myexit - Exits the shell or sets the exit status.
 * @info: A structure containing potential arguments.
 *
 * This function allows the shell to exit with a specified exit status or handle
 * error cases. If an exit argument is provided, it attempts to convert it to an
 * integer. If successful, it sets the shell's exit status accordingly. If the
 * exit argument is not valid, an error message is printed, and the status is set
 * to indicate an error.
 *
 * @param info - A structure containing relevant information.
 * @return -2 if the shell should exit with the specified status, or 1 if an error
 * occurs while processing the exit argument.
 */
int _myexit(info_t *info)
{
    int exitcheck;

    if (info->argv[1])  /* If there is an exit argument */
    {
        exitcheck = _erratoi(info->argv[1]);
        if (exitcheck == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return (1);
        }
        info->err_num = _erratoi(info->argv[1]);
        return (-2);
    }
    info->err_num = -1;
    return (-2);
}

/**
 * _mycd - Changes the current directory of the process.
 * @info: A structure containing potential arguments.
 *
 * This function enables the shell to change the current directory of the
 * process. It supports changing to the home directory, the previous directory,
 * or a specified directory. It updates environment variables and handles
 * error cases.
 *
 * @param info - A structure containing relevant information.
 * @return Always 0.
 */
int _mycd(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        _puts("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdir_ret = /* TODO: what should this be? */
                chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(s);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(info, "OLDPWD=")), _putchar('\n');
        chdir_ret = /* TODO: what should this be? */
            chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(info->argv[1]);
    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * _myhelp - Displays a help message.
 * @info: A structure containing potential arguments.
 *
 * This function is intended to provide help and information within the shell.
 * Currently, it displays a placeholder message, and its functionality is not
 * yet implemented. The input argument array is processed, although not used.
 *
 * @param info - A structure containing relevant information.
 * @return Always 0.
 */
int _myhelp(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arg_array); /* temp att_unused workaround */
    return (0);
}
