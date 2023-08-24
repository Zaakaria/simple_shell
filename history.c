#include "shell.h"

/**
 * get_history_file - will get history file
 * @info: it is parameter struct
 *
 * Return: the allocated string
 */

char *get_history_file(info_t *info)
{
	char *u, *i;

	i = _getenv(info, "HOME=");
	if (!i)
		return (NULL);
	u = malloc(sizeof(char) * (_strlen(i) + _strlen(HIST_FILE) + 2));
	if (!u)
		return (NULL);
	u[0] = 0;
	_strcpy(u, i);
	_strcat(u, "/");
	_strcat(u, HIST_FILE);
	return (u);
}

/**
 * write_history - will create a file, or appends to existing file
 * @info: it is the parameter struct
 *
 * Return: on success 1, -1 else
 */
int write_history(info_t *info)
{
	ssize_t o;
	char *p = get_history_file(info);
	list_t *q = NULL;

	if (!p)
		return (-1);

	o = open(p, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(p);
	if (o == -1)
		return (-1);
	for (q = info->history; q; q = q->next)
	{
		_putsfd(q->str, o);
		_putfd('\n', o);
	}
	_putfd(BUF_FLUSH, o);
	close(o);
	return (1);
}

/**
 * read_history - will read history from file
 * @info: it is the parameter struct
 *
 * Return: success histcount, otherwise 0
 */
int read_history(info_t *info)
{
	int s, d = 0, f = 0;
	ssize_t g, h, j = 0;
	struct stat k;
	char *l = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	g = open(filename, O_RDONLY);
	free(filename);
	if (g == -1)
		return (0);
	if (!fstat(g, &k))
		j = k.st_size;
	if (j < 2)
		return (0);
	l = malloc(sizeof(char) * (j + 1));
	if (!l)
		return (0);
	h = read(g, l, j);
	l[j] = 0;
	if (h <= 0)
		return (free(l), 0);
	close(g);
	for (s = 0; s < j; s++)
		if (l[s] == '\n')
		{
			l[s] = 0;
			build_history_list(info, l + d, f++);
			d = s + 1;
		}
	if (d != s)
		build_history_list(info, l + d, f++);
	free(l);
	info->histcount = f;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - will add entry to history linked list
 * @info: Structure that contains potential arguments
 * @buf: it is a buffer
 * @linecount: it is the history linecount, histcount
 *
 * Return: it is always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *m = NULL;

	if (info->history)
		m = info->history;
	add_node_end(&m, buf, linecount);

	if (!info->history)
		info->history = m;
	return (0);
}

/**
 * renumber_history - will renumber the history linked list after changes
 * @info: Structure that contains potential arguments
 *
 * Return: it is the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *w = info->history;
	int x = 0;

	while (w)
	{
		w->num = x++;
		w = w->next;
	}
	return (info->histcount = x);
}
