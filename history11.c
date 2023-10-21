#include "shell.h"

/**
 * get_history_file - Retrieves the path to the shell's history file.
 * @info: A structure containing potential arguments. Used to maintain the constant function prototype.
 *
 * This function constructs the path to the shell's history file by appending the file name (HIST_FILE)
 * to the user's home directory (retrieved from the environment variables). It allocates memory for the path
 * and returns it as a dynamically allocated string.
 *
 * @param info - The structure containing potential arguments.
 * @return - A dynamically allocated string containing the history file path, or NULL on failure.
 */
char *get_history_file(info_t *info)
{
    char *buf, *dir;

    dir = _getenv(info, "HOME=");
    if (!dir)
        return NULL;

    buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
    if (!buf)
        return NULL;

    buf[0] = 0;
    _strcpy(buf, dir);
    _strcat(buf, "/");
    _strcat(buf, HIST_FILE);

    return buf;
}

/**
 * write_history - Writes the shell's command history to a file.
 * @info: The parameter struct.
 *
 * This function creates a new history file or overwrites an existing one, then appends each entry from
 * the history linked list to the file. It ensures that each entry is followed by a newline character.
 *
 * @param info - The structure containing potential arguments.
 * @return - 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
    ssize_t fd;
    char *filename = get_history_file(info);
    list_t *node = NULL;

    if (!filename)
        return -1;

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1)
        return -1;

    for (node = info->history; node; node = node->next)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }

    _putfd(BUF_FLUSH, fd);
    close(fd);

    return 1;
}

/**
 * read_history - Reads the shell's command history from a file.
 * @info: The parameter struct.
 *
 * This function reads the command history from a history file and stores it in the shell's history linked list.
 * It parses each line from the file and adds it as a new entry in the history linked list.
 *
 * @param info - The structure containing potential arguments.
 * @return - The number of history entries read on success, 0 otherwise.
 */
int read_history(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = get_history_file(info);

    if (!filename)
        return 0;

    fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return 0;

    if (!fstat(fd, &st))
        fsize = st.st_size;

    if (fsize < 2)
        return 0;

    buf = malloc(sizeof(char) * (fsize + 1));

    if (!buf)
        return 0;

    rdlen = read(fd, buf, fsize);
    buf[fsize] = 0;

    if (rdlen <= 0)
        return free(buf), 0;

    close(fd);

    for (i = 0; i < fsize; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            build_history_list(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != i)
        build_history_list(info, buf + last, linecount++);

    free(buf);
    info->histcount = linecount;

    while (info->histcount-- >= HIST_MAX)
        delete_node_at_index(&(info->history), 0);

    renumber_history(info);

    return info->histcount;
}

/**
 * build_history_list - Adds a command entry to the shell's history linked list.
 * @info: The structure containing potential arguments. Used to maintain
 * @buf: The buffer containing the command.
 * @linecount: The history line count (histcount).
 *
 * This function creates a new history entry by appending 'buf' to the history linked list,
 * along with its corresponding line count 'linecount'. It ensures the history linked list
 * is updated accordingly.
 *
 * @param info - The structure containing potential arguments.
 * @param buf - The command buffer to be added to the history.
 * @param linecount - The history line count.
 * @return - Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    add_node_end(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumber_history - Updates the line numbers of history entries.
 * @info: The structure containing potential arguments. Used to maintain
 *
 * This function iterates through the shell's history linked list and renumbers the line count (num)
 * for each history entry. It also updates the histcount field with the new count of history entries.
 *
 * @param info - The structure containing potential arguments.
 * @return - The new histcount.
 */
int renumber_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return (info->histcount = i);
}
