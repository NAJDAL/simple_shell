#include "shell.h"

/**
 * buffer_input - buffers a chain of commands.
 * @info: Structure containing potential arguments.
 * @buf: Address of the buffer.
 * @len: Address of the length variable.
 *
 * Returns: Bytes read.
 */
ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
    ssize_t bytes_read = 0;
    size_t length_processed = 0;

    if (!*len) {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, handle_interrupt);
#if USE_GETLINE
        bytes_read = getline(buf, &length_processed, stdin);
#else
        bytes_read = custom_getline(info, buf, &length_processed);
#endif
        if (bytes_read > 0) {
            if ((*buf)[bytes_read - 1] == '\n') {
                (*buf)[bytes_read - 1] = '\0'; /* Remove trailing newline */
                bytes_read--;
            }
            info->line_count_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->hist_count++);
            *len = bytes_read;
            info->cmd_buf = buf;
        }
    }
    return bytes_read;
}

/**
 * retrieve_input - Gets a line without the newline character.
 * @info: Structure containing potential arguments.
 *
 * Returns: Bytes read.
 */
ssize_t retrieve_input(info_t *info)
{
    static char *buf; /* Buffer for command chain */
    static size_t i, j, len;
    ssize_t bytes_read = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    bytes_read = buffer_input(info, &buf, &len);
    if (bytes_read == -1) {
        return -1; /* EOF */
    }
    if (len) {
        j = i; /* Initialize new iterator to the current buffer position */
        p = buf + i; /* Get pointer for return */

        check_command_chain(info, buf, &j, i, len);
        while (j < len) {
            if (is_command_chain(info, buf, &j)) {
                break;
            }
            j++;
        }

        i = j + 1; /* Increment past nulled ';'' */
        if (i >= len) { /* Reached the end of the buffer? */
            i = len = 0; /* Reset position and length */
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p; /* Pass back pointer to the current command position */
        return _strlen(p); /* Return the length of the current command */
    }

    *buf_p = buf; /* If not a chain, pass back the buffer from custom_getline() */
    return bytes_read; /* Return the length of the buffer from custom_getline() */
}

/**
 * read_buffer - Reads a buffer.
 * @info: Structure containing potential arguments.
 * @buffer: Buffer.
 * @i: Size.
 *
 * Returns: Bytes read.
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *i)
{
    ssize_t bytes_read = 0;

    if (*i) {
        return 0;
    }
    bytes_read = read(info->read_fd, buffer, READ_BUFFER_SIZE);
    if (bytes_read >= 0) {
        *i = bytes_read;
    }
    return bytes_read;
}

/**
 * custom_getline - Gets the next line of input from STDIN.
 * @info: Structure containing potential arguments.
 * @ptr: Address of a pointer to a buffer, preallocated or NULL.
 * @length: Size of the preallocated buffer if not NULL.
 *
 * Returns: Bytes read.
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
    static char buffer[READ_BUFFER_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t bytes_read = 0;
    int bytes_processed = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length) {
        bytes_processed = *length;
    }
    if (i == len) {
        i = len = 0;
    }

    bytes_read = read_buffer(info, buffer, &len);
    if (bytes_read == -1 || (bytes_read == 0 && len == 0)) {
        return -1;
    }

    c = custom_strchr(buffer + i, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : len;
    new_p = custom_realloc(p, bytes_processed, bytes_processed ? bytes_processed + k : k + 1);
    if (!new_p) { /* MALLOC FAILURE! */
        if (p) {
            free(p);
        }
        return -1;
    }

    if (bytes_processed) {
        custom_strncat(new_p, buffer + i, k - i);
    } else {
        custom_strncpy(new_p, buffer + i, k - i + 1);
    }

    bytes_processed += k - i;
    i = k;
    p = new_p;

    if (length) {
        *length = bytes_processed;
    }
    *ptr = p;
    return bytes_processed;
}

/**
 * handle_interrupt - Blocks Ctrl-C.
 * @signal_number: The signal number.
 *
 * Returns: Void.
 */
void handle_interrupt(__attribute__((unused)) int signal_number)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
