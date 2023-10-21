#include "shell.h"

/**
 * bfree - Frees a pointer and sets its address to NULL.
 * @ptr: Address of the pointer to free.
 *
 * This function takes a pointer to a pointer and frees the memory
 * that it points to. After freeing the memory, it sets the pointer
 * to NULL to avoid any potential dangling references.

 * @param ptr - Address of the pointer to free.
 * @return - 1 if memory was freed successfully, otherwise 0.
 */
int bfree(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return 1;
    }
    return 0;
}
