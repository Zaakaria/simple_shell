#include "shell.h"

/**
 * add_node - will add a node to the list's start
 * @head: it is pointer's address to node's head
 * @str: it is str field of node
 * @num: it is node index used by history
 *
 * Return: total size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *a;

	if (!head)
		return (NULL);
	a = malloc(sizeof(list_t));
	if (!a)
		return (NULL);
	_memset((void *)a, 0, sizeof(list_t));
	a->num = num;
	if (str)
	{
		a->str = _strdup(str);
		if (!a->str)
		{
			free(a);
			return (NULL);
		}
	}
	a->next = *head;
	*head = a;
	return (a);
}

/**
 * add_node_end - will add a node to the list's end
 * @head: it is address of pointer to head node
 * @str: it is str field of node
 * @num: it is node index used by history
 *
 * Return: total size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *z, *e;

	if (!head)
		return (NULL);

	e = *head;
	z = malloc(sizeof(list_t));
	if (!z)
		return (NULL);
	_memset((void *)z, 0, sizeof(list_t));
	z->num = num;
	if (str)
	{
		z->str = _strdup(str);
		if (!z->str)
		{
			free(z);
			return (NULL);
		}
	}
	if (e)
	{
		while (e->next)
			e = e->next;
		e->next = z;
	}
	else
		*head = z;
	return (z);
}

/**
 * print_list_str - will print only the str element of a list_t
 * @h: it is a pointer to first node
 *
 * Return: total size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t r = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		r++;
	}
	return (r);
}

/**
 * delete_node_at_index - will delete node at given index
 * @head: it is address of pointer to first node
 * @index: it is index of node to delete
 *
 * Return: on success 1, on failure 0
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *y, *t;
	unsigned int u = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		y = *head;
		*head = (*head)->next;
		free(y->str);
		free(y);
		return (1);
	}
	y = *head;
	while (y)
	{
		if (u == index)
		{
			t->next = y->next;
			free(y->str);
			free(y);
			return (1);
		}
		u++;
		t = y;
		y = y->next;
	}
	return (0);
}

/**
 * free_list - will free all nodes of a list
 * @head_ptr: it is address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *p, *o, *q;

	if (!head_ptr || !*head_ptr)
		return;
	q = *head_ptr;
	p = q;
	while (p)
	{
		o = p->next;
		free(p->str);
		free(p);
		p = o;
	}
	*head_ptr = NULL;
}
