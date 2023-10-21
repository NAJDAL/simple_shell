#include "shell.h"

/**
 * create_node - Creates a new node for a linked list.
 * @str: String to be stored in the node.
 * @num: Index used for history.
 *
 * Return: A pointer to the newly created node.
 */
list_t *create_node(const char *str, int num)
{
    list_t *new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    new_node->num = num;
    new_node->str = str ? duplicate_string(str) : NULL;
    new_node->next = NULL;

    return new_node;
}

/**
 * prepend_node - Prepends a node to the beginning of a linked list.
 * @head: Address of the pointer to the head node.
 * @str: String to be stored in the new node.
 * @num: Index used for history.
 *
 * Return: A pointer to the new head of the list.
 */
list_t *prepend_node(list_t **head, const char *str, int num)
{
    list_t *new_node = create_node(str, num);
    if (!new_node)
        return *head;

    new_node->next = *head;
    *head = new_node;

    return new_node;
}

/**
 * append_node - Appends a node to the end of a linked list.
 * @head: Address of the pointer to the head node.
 * @str: String to be stored in the new node.
 * @num: Index used for history.
 *
 * Return: A pointer to the newly added node.
 */
list_t *append_node(list_t **head, const char *str, int num)
{
    list_t *new_node = create_node(str, num);
    if (!new_node)
        return NULL;

    if (!*head)
        *head = new_node;
    else
    {
        list_t *node = *head;
        while (node->next)
            node = node->next;
        node->next = new_node;
    }

    return new_node;
}

/**
 * print_list_str - Prints only the 'str' element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: The number of elements in the list.
 */
size_t print_list_str(const list_t *h)
{
    size_t count = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        count++;
    }

    return count;
}

/**
 * remove_node_at_index - Deletes a node at the given index.
 * @head: Address of the pointer to the head node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int remove_node_at_index(list_t **head, unsigned int index)
{
    if (!head || !*head)
        return 0;

    if (index == 0)
    {
        list_t *temp = *head;
        *head = (*head)->next;
        free(temp->str);
        free(temp);
        return 1;
    }

    list_t *prev_node = NULL;
    list_t *current_node = *head;
    unsigned int i = 0;

    while (current_node && i < index)
    {
        prev_node = current_node;
        current_node = current_node->next;
        i++;
    }

    if (i == index)
    {
        prev_node->next = current_node->next;
        free(current_node->str);
        free(current_node);
        return 1;
    }

    return 0;
}

/**
 * free_list - Frees all nodes of a linked list.
 * @head_ptr: Address of the pointer to the head node.
 */
void free_list(list_t **head_ptr)
{
    if (!head_ptr)
        return;

    list_t *current_node = *head_ptr;
    while (current_node)
    {
        list_t *temp = current_node;
        current_node = current_node->next;
        free(temp->str);
        free(temp);
    }

    *head_ptr = NULL;
}
