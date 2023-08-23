#include "shell.h"

/**
 * list_len - will determine length of linked list
 * @h: it is pointer to first node
 *
 * Return: total size of list
 */
size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - will return array of strings of list->str
 * @head: it is pointer to first node
 *
 * Return: entire array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *z = head;
	size_t e = list_len(head), j;
	char **r;
	char *t;

	if (!head || !e)
		return (NULL);
	r = malloc(sizeof(char *) * (i + 1));
	if (!r)
		return (NULL);
	for (e = 0; z; z = z->next, e++)
	{
		t = malloc(_strlen(z->str) + 1);
		if (!t)
		{
			for (j = 0; j < e; j++)
				free(r[j]);
			free(r);
			return (NULL);
		}

		t = _strcpy(t, z->str);
		r[e] = t;
	}
	r[i] = NULL;
	return (r);
}


/**
 * print_list - will print all elements of list_t linked list
 * @h: it is pointer to first node
 *
 * Return: total size of list
 */
size_t print_list(const list_t *h)
{
	size_t y = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		y++;
	}
	return (y);
}

/**
 * node_starts_with - will return node string starts with prefix
 * @node: it is pointer to list head
 * @prefix: it is string to match
 * @c: its next character after prefix to match
 *
 * Return: the match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *u = NULL;

	while (node)
	{
		u = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*u == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - will get index of a node
 * @head: it is pointer to list head
 * @node: it is pointer to the node
 *
 * Return: either index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t q = 0;

	while (head)
	{
		if (head == node)
			return (q);
		head = head->next;
		q++;
	}
	return (-1);
}
