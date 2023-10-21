#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @s: The pointer to the memory area.
 * @b: The byte to fill *s with.
 * @n: The number of bytes to be filled.
 *
 * This function takes a pointer to a memory area `s`, a byte value `b`, and the number of bytes `n`,
 * and fills the memory area `s` with the byte `b` for `n` bytes. It returns a pointer to the memory area `s`.

 * @param s - The pointer to the memory area.
 * @param b - The byte to fill *s with.
 * @param n - The number of bytes to be filled.
 * @return - A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
        s[i] = b;
    return s;
}
/**
 * ffree - Frees an array of strings.
 * @pp: Array of strings.
 *
 * This function is used to free an array of strings. It takes a pointer to an array of strings `pp` and
 * iteratively frees each string and then frees the array itself.

 * @param pp - Array of strings to be freed.
 */
void ffree(char **pp)
{
    char **a = pp;

    if (!pp)
        return;
    while (*pp)
        free(*pp++);
    free(a);
}
/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * This function reallocates a block of memory, allowing for resizing a previously allocated block.
 * It takes a pointer `ptr` to the previous block, its `old_size`, and the desired `new_size`. The function
 * returns a pointer to the new block of the specified size, copying the data from the old block to the new one
 * while also freeing the old block.

 * @param ptr - Pointer to the previous malloc'ated block.
 * @param old_size - Byte size of the previous block.
 * @param new_size - Byte size of the new block.
 * @return - Pointer to the new block of memory, or NULL if allocation fails.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;

    if (!ptr)
        return malloc(new_size);
    if (!new_size)
        return (free(ptr), NULL);
    if (new_size == old_size)
        return ptr;

    p = malloc(new_size);
    if (!p)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
        p[old_size] = ((char *)ptr)[old_size];
    free(ptr);
    return p;
}
