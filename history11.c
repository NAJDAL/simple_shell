#include "shell.h"

/**
 * get_history_file_path - Get the path to the history file.
 * @info: Pointer to the info_t struct.
 *
 * Return: A dynamically allocated string containing the history file path.
 */
char *get_history_file_path(info_t *info)
{
    char *home_dir = _getenv(info, "HOME=");
    if (!home_dir)
        return NULL;

    char *history_file_path = malloc(_strlen(home_dir) + _strlen(HISTORY_FILE) + 2);
    if (!history_file_path)
        return NULL;

    history_file_path[0] = '\0';
    _strcpy(history_file_path, home_dir);
    _strcat(history_file_path, "/");
    _strcat(history_file_path, HISTORY_FILE);

    return history_file_path;
}

/**
 * save_history - Save the shell's command history to a file.
 * @info: Pointer to the info_t struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int save_history(info_t *info)
{
    char *history_file_path = get_history_file_path(info);
    if (!history_file_path)
        return -1;

    FILE *history_file = fopen(history_file_path, "w");
    free(history_file_path);

    if (!history_file)
        return -1;

    list_t *node = info->history;

    while (node)
    {
        fprintf(history_file, "%s\n", node->str);
        node = node->next;
    }

    fclose(history_file);
    return 1;
}

/**
 * load_history - Load command history from a file.
 * @info: Pointer to the info_t struct.
 *
 * Return: The number of history entries loaded.
 */
int load_history(info_t *info)
{
    char *history_file_path = get_history_file_path(info);
    if (!history_file_path)
        return 0;

    FILE *history_file = fopen(history_file_path, "r");
    free(history_file_path);

    if (!history_file)
        return 0;

    char line[MAX_INPUT];
    int linecount = 0;

    while (fgets(line, sizeof(line), history_file))
    {
        remove_newline(line);
        build_history_entry(info, line, linecount++);
    }

    fclose(history_file);
    return linecount;
}

/**
 * build_history_entry - Add an entry to the command history.
 * @info: Pointer to the info_t struct.
 * @command: The command to be added to the history.
 * @linecount: The line count for the history entry.
 *
 * Return: 0 on success, -1 on failure.
 */
int build_history_entry(info_t *info, const char *command, int linecount)
{
    list_t *node = add_node_end(&(info->history), duplicate_string(command), linecount);
    if (!node)
        return -1;

    return 0;
}

/**
 * renumber_history - Renumber the history entries to maintain continuity.
 * @info: Pointer to the info_t struct.
 */
void renumber_history(info_t *info)
{
    list_t *node = info->history;
    int linecount = 0;

    while (node)
    {
        node->num = linecount++;
        node = node->next;
    }

    info->histcount = linecount;
}
