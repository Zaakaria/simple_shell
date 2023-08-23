#include "shell.h"

/**
 * _myenv - will print current environment
 * @info: Structure that contains potential arguments
 * Return: it is always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - will get value of an environ variable
 * @info: Structure that contains potential arguments
 * @name: it is env var name
 *
 * Return: it is the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *m = info->env;
	char *w;

	while (m)
	{
		w = starts_with(m->str, name);
		if (w && *w)
			return (w);
		m = m->next;
	}
	return (NULL);
}

/**
 * _mysetenv - will Initialize new environment variable
 * @info: Structure that contains potential arguments
 *  Return: it is always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - will Remove environment variable
 * @info: Structure that contains potential arguments
 * Return: it is always 0
 */
int _myunsetenv(info_t *info)
{
	int x;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= info->argc; x++)
		_unsetenv(info, info->argv[x]);

	return (0);
}

/**
 * populate_env_list - will populate env linked list
 * @info: Structure that contains potential arguments
 * Return: it is always 0
 */
int populate_env_list(info_t *info)
{
	list_t *c = NULL;
	size_t v;

	for (v = 0; environ[v]; v++)
		add_node_end(&c, environ[v], 0);
	info->env = c;
	return (0);
}
