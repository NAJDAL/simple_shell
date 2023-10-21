#include "shell.h"

/**
 * my_memset - Fill memory with a constant byte.
 * @ptr: Pointer to the memory area.
 * @value: The byte to fill *ptr with.
 * @num: Number of bytes to be filled.
 * 
 * Return: A pointer to the memory area ptr.
 */
char *my_memset(char *ptr, char value, unsigned int num) {
    unsigned int i;

    for (i = 0; i < num; i++)
        ptr[i] = value;
    return ptr;
}

/**
 * my_free_strings - Free an array of strings.
 * @str_array: Array of strings to be freed.
 */
void my_free_strings(char **str_array) {
    char **temp = str_array;

    if (!str_array)
        return;
    while (*str_array)
        free(*str_array++);
    free(temp);
}

/**
 * my_realloc - Reallocate a block of memory.
 * @ptr: Pointer to the previously allocated block.
 * @old_size: Size in bytes of the old block.
 * @new_size: Size in bytes of the new block.
 * 
 * Return: A pointer to the reallocated block of memory.
 */
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size) {
    char *new_ptr;

    if (!ptr)
        return malloc(new_size);
    if (!new_size)
        return (free(ptr), NULL);
    if (new_size == old_size)
        return ptr;

    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
        new_ptr[old_size] = ((char *)ptr)[old_size];
    free(ptr);
    return new_ptr;
}
