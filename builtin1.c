#include "shell.h"

/**
 * _myhistory - will display history list as one command by line
 * @info: Structure that contains potential arguments
 *  Return: it is always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - will set an alias to string
 * @info: it is parameter struct
 * @str: it is the string alias
 *
 * Return: 0 on success, or 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *s, d;
	int f;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	d = *s;
	*s = 0;
	f = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*s = d;
	return (f);
}

/**
 * set_alias - will set an alias to string
 * @info: is it parameter struct
 * @str: it is the string alias
 *
 * Return: 0 on success, or 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *g;

	g = _strchr(str, '=');
	if (!g)
		return (1);
	if (!*++g)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - will print alias string
 * @node: it is the alias node
 *
 * Return: 0 on success, or 1 on error
 */
int print_alias(list_t *node)
{
	char *h = NULL, *j = NULL;

	if (node)
	{
		h = _strchr(node->str, '=');
		for (j = node->str; j <= h; j++)
		_putchar(*j);
		_putchar('\'');
		_puts(h + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - will mimic alias built-in
 * @info: Structure that contains potential arguments
 *  Return: it is always 0
 */
int _myalias(info_t *info)
{
	int k = 0;
	char *l = NULL;
	list_t *m = NULL;

	if (info->argc == 1)
	{
		m = info->alias;
		while (m)
		{
			print_alias(m);
			m = m->next;
		}
		return (0);
	}
	for (k = 1; info->argv[k]; k++)
	{
		l = _strchr(info->argv[k], '=');
		if (l)
			set_alias(info, info->argv[k]);
		else
			print_alias(node_starts_with(info->alias, info->argv[k], '='));
	}

	return (0);
}
