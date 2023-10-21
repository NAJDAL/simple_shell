#include "shell.h"

/**
 * free_and_null - frees a pointer and sets it to NULL
 * @ptr: a pointer to a pointer
 *
 * This function frees the memory pointed to by ptr and sets it to NULL.
 */
void free_and_null(void **ptr)
{
    if (ptr != NULL && *ptr != NULL)
    {
        free(*ptr);
        *ptr = NULL;
    }
}
