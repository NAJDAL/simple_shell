#include "shell.h"

/**
 * is_executable - checks if a file is executable
 * @path: path to the file
 *
 * Return: 1 if executable, 0 otherwise
 */
int is_executable(char *path)
{
    struct stat st;
    return !stat(path, &st) && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR);
}

/**
 * find_executable - finds the full path of an executable in PATH
 * @pathstr: the PATH string
 * @cmd: the command to find
 *
 * Return: full path to the executable or NULL if not found
 */
char *find_executable(char *pathstr, char *cmd)
{
    char *token = strtok(pathstr, ":");
    while (token) {
        char path[MAX_PATH_LEN];
        snprintf(path, sizeof(path), "%s/%s", token, cmd);
        if (is_executable(path)) {
            return strdup(path);  // Remember to free the returned string when done
        }
        token = strtok(NULL, ":");
    }
    return NULL;
}
