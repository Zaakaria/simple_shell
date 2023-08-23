#include "shell.h"

/**
 * get_environ - will return the string array copy
 * @info: Structure that contains potential arguments
 * Return: it is always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - will Remove an environment variable
 * @info: Structure that contains potential arguments
 *  Return: on delete 1, otherwise 0
 * @var: it is the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *a = info->env;
	size_t z = 0;
	char *e;

	if (!a || !var)
		return (0);

	while (a)
	{
		e = starts_with(a->str, var);
		if (e && *e == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), z);
			z = 0;
			a = info->env;
			continue;
		}
		a = a->next;
		z++;
	}
	return (info->env_changed);
}

/**
 * _setenv - will Initialize a new environment variable
 * @info: Structure that contains potential arguments
 * @var: it is the string env var property
 * @value: it is the string env var value
 *  Return: it is always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *r = NULL;
	list_t *t;
	char *y;

	if (!var || !value)
		return (0);

	r = malloc(_strlen(var) + _strlen(value) + 2);
	if (!r)
		return (1);
	_strcpy(r, var);
	_strcat(r, "=");
	_strcat(r, value);
	t = info->env;
	while (t)
	{
		y = starts_with(t->str, var);
		if (y && *y == '=')
		{
			free(t->str);
			t->str = r;
			info->env_changed = 1;
			return (0);
		}
		t = t->next;
	}
	add_node_end(&(info->env), r, 0);
	free(r);
	info->env_changed = 1;
	return (0);
}
