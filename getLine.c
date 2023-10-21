#include "shell.h"

/**
 * input_buf - Buffers chained commands for further processing.
 * @info: A structure containing parameters and returns.
 * @buf: The address of the buffer to store input.
 * @len: The address of the length variable.
 *
 * Return: The number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len) /* If the buffer is empty, it is filled. */
    {
        /* bfree((void **)info->cmd_buf); */
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);
#if USE_GETLINE
        r = getline(buf, &len_p, stdin);
#else
        r = _getline(info, buf, &len_p);
#endif
        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0'; /* Remove the trailing newline character. */
                r--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
            /* if (_strchr(*buf, ';')) Is this a command chain? */
            {
                *len = r;
                info->cmd_buf = buf;
            }
        }
    }
    return r;
}

/**
 * get_input - Retrieves a line of input without the trailing newline character.
 * @info: A structure containing parameters and returns.
 *
 * Return: The number of bytes read.
 */
ssize_t get_input(info_t *info)
{
    static char *buf; /* The ';' command chain buffer */
    static size_t i, j, len;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    r = input_buf(info, &buf, &len);
    if (r == -1) /* End of File (EOF) */
        return -1;
    if (len) /* Commands are remaining in the chain buffer */
    {
        j = i; /* Initialize a new iterator to the current buffer position */
        p = buf + i; /* Get a pointer for return */

        check_chain(info, buf, &j, i, len);
        while (j < len) /* Iterate to the semicolon or the end. */
        {
            if (is_chain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1; /* Increment beyond the null ';' character. */
        if (i >= len) /* Reached the end of the buffer? */
        {
            i = len = 0; /* Reset the position and length. */
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p; /* Pass back a pointer to the current command position. */
        return _strlen(p); /* Return the length of the current command. */
    }

    *buf_p = buf; /* Otherwise, if it's not a chain, pass back the buffer from _getline(). */
    return r; /* Return the length of the buffer from _getline(). */
}

/**
 * read_buf - Reads data into a buffer.
 * @info: A structure containing parameters and returns.
 * @buf: The buffer.
 * @i: The size.
 *
 * Return: The number of bytes read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return 0;
    r = read(info->readfd, buf, READ_BUF_SIZE);
    if (r >= 0)
        *i = r;
    return r;
}

/**
 * _getline - Retrieves the next line of input from STDIN.
 * @info: A structure containing parameters and returns.
 * @ptr: The address of a pointer to a buffer, which can be preallocated or NULL.
 * @length: The size of the preallocated ptr buffer if not NULL.
 *
 * Return: The number of bytes read.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = read_buf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return -1;

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return p ? free(p), -1 : -1;

    if (s)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return s;
}

/**
 * sigintHandler - Blocks the Ctrl-C signal.
 * @sig_num: The signal number.
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
