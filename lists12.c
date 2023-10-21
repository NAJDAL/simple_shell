#include "shell.h"

/**
 * list_length - Determines the length of a linked list.
 * @head: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t list_length(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        head = head->next;
        count++;
    }

    return count;
}

/**
 * list_to_string_array - Converts a linked list of strings to an array of strings.
 * @head: Pointer to the first node.
 *
 * Return: An array of strings.
 */
char **list_to_string_array(list_t *head)
{
    size_t length = list_length(head);
    if (!head || length == 0)
        return NULL;

    char **strings = malloc(sizeof(char *) * (length + 1));
    if (!strings)
        return NULL;

    size_t i = 0;
    while (head)
    {
        strings[i] = duplicate_string(head->str);
        if (!strings[i])
        {
            for (size_t j = 0; j < i; j++)
                free(strings[j]);
            free(strings);
            return NULL;
        }
        i++;
        head = head->next;
    }
    strings[i] = NULL;

    return strings;
}

/**
 * print_list - Prints all elements of a list_t linked list.
 * @head: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_list(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        _puts(convert_number(head->num, 10, 0));
        _puts(": ");
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        count++;
    }

    return count;
}

/**
 * find_node_starts_with - Returns a node whose string starts with the given prefix.
 * @head: Pointer to the list head.
 * @prefix: String to match.
 * @c: The character to match after the prefix (-1 to ignore).
 *
 * Return: The matching node or NULL.
 */
list_t *find_node_starts_with(list_t *head, const char *prefix, char c)
{
    while (head)
    {
        if (starts_with(head->str, prefix) && (c == -1 || head->str[_strlen(prefix)] == c))
            return head;
        head = head->next;
    }

    return NULL;
}

/**
 * get_node_index - Gets the index of a node in the linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: The index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
    size_t index = 0;

    while (head)
    {
        if (head == node)
            return index;
        head = head->next;
        index++;
    }

    return -1;
}
