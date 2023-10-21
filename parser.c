#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * This function checks if the given `path` corresponds to an executable command by examining its
 * file status. If the file is a regular executable file, it returns 1; otherwise, it returns 0.

 * @param info - The info struct (not used in the function).
 * @param path - Path to the file to check.
 * @return 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return 0;

    if (st.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

/**
 * dup_chars - Duplicates characters from a string.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * This function creates a new buffer and duplicates characters from the `pathstr`
 * starting from the index `start` up to (but not including) the index `stop`. The
 * duplicated characters are placed in the buffer, and a pointer to the buffer is returned.

 * @param pathstr - The PATH string.
 * @param start - Starting index in the string.
 * @param stop - Stopping index in the string.
 * @return - Pointer to a new buffer containing the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
    buf[k] = 0;
    return buf;
}
/**
 * find_path - Finds the full path of a command in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * This function searches for the `cmd` within the `pathstr`, which contains a list
 * of directories in the system's PATH. If the command is found in any of these directories,
 * the function returns the full path to the command. If the command is not found, it returns NULL.

 * @param info - The info struct (not used in the function).
 * @param pathstr - The PATH string containing directories.
 * @param cmd - The command to find in the directories.
 * @return - The full path of the command if found, or NULL if not found.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return NULL;
    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (is_cmd(info, cmd))
            return cmd;
    }
    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (is_cmd(info, path))
                return path;
            if (!pathstr[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return NULL;
}
