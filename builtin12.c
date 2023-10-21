#include "shell.h"

/**
 * _myexit - Exits the shell with a specified exit status.
 * @info: Structure that holds potential arguments.
 *
 * Returns: 0 if info.argv[0] is not "exit".
 */
int _myexit(info_t *info)
{
	int exitCheck;

	if (info->argv[1]) {
		exitCheck = _erratoi(info->argv[1]);
		if (exitCheck == -1) {
			info->status = 2;
			print_error(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return 1;
		}
		info->err_num = _erratoi(info->argv[1]);
		return -2;
	}
	info->err_num = -1;
	return -2;
}

/**
 * _mycd - Changes the current working directory of the process.
 * @info: Structure containing potential arguments.
 *
 * Returns: Always 0.
 */
int _mycd(info_t *info)
{
	char *currentPath, *dir, buffer[1024];
	int chdirResult;

	currentPath = getcwd(buffer, 1024);
	if (!currentPath)
		_puts("TODO: Handle getcwd failure here\n");

	if (!info->argv[1]) {
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdirResult = /* TODO: Define this case */ chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdirResult = chdir(dir);
	} else if (_strcmp(info->argv[1], "-") == 0) {
		if (!_getenv(info, "OLDPWD=")) {
			_puts(currentPath);
			_putchar('\n');
			return 1;
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirResult = /* TODO: Define this case */ chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	} else {
		chdirResult = chdir(info->argv[1]);
	}

	if (chdirResult == -1) {
		print_error(info, "Cannot change directory to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	} else {
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	return 0;
}

/**
 * _myhelp - Provides assistance and information for the shell.
 * @info: Structure containing potential arguments.
 *
 * Returns: Always 0.
 */
int _myhelp(info_t *info)
{
	char **argArray;

	argArray = info->argv;
	_puts("The help function works but is not yet implemented.\n");
	if (0)
		_puts(*argArray); /* Temporary workaround for unused variable warning */
	return 0;
}
