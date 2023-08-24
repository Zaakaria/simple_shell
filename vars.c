#include "shell.h"

/**
 * is_chain - will test current char
 * @info: it is the parameter struct
 * @buf: it is the char buffer
 * @p: it is address of current position
 *
 * Return: if chain delimeter 1 , otherwise 0
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t a = *p;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';') /* found end of this command */
	{
		buf[a] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = a;
	return (1);
}

/**
 * check_chain - will check we should continue chaining
 * @info: it is the parameter struct
 * @buf: it is the char buffer
 * @p: it is address of current position in buf
 * @i: it is starting position in buf
 * @len: it is length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t z = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			z = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			z = len;
		}
	}

	*p = z;
}

/**
 * replace_alias - will replace an aliases in the tokenized string
 * @info: it is the parameter struct
 *
 * Return: if replaced 1, otherwise 0
 */
int replace_alias(info_t *info)
{
	int e;
	list_t *r;
	char *t;

	for (e = 0; e < 10; e++)
	{
		r = node_starts_with(info->alias, info->argv[0], '=');
		if (!r)
			return (0);
		free(info->argv[0]);
		t = _strchr(r->str, '=');
		if (!t)
			return (0);
		t = _strdup(t + 1);
		if (!t)
			return (0);
		info->argv[0] = t;
	}
	return (1);
}

/**
 * replace_vars - will replace vars in the tokenized string
 * @info: it is the parameter struct
 *
 * Return: if replaced 1, otherwise 0
 */
int replace_vars(info_t *info)
{
	int y = 0;
	list_t *u;

	for (y = 0; info->argv[y]; y++)
	{
		if (info->argv[y][0] != '$' || !info->argv[y][1])
			continue;

		if (!_strcmp(info->argv[y], "$?"))
		{
			replace_string(&(info->argv[y]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[y], "$$"))
		{
			replace_string(&(info->argv[y]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		u = node_starts_with(info->env, &info->argv[y][1], '=');
		if (u)
		{
			replace_string(&(info->argv[y]),
					_strdup(_strchr(u->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[y], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - will replace string
 * @old: it is address of old string
 * @new: it is new string
 *
 * Return: if replaced 1, otherwise 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
