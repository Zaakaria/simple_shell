#include "shell.h"

/**
 * input_buf - will buffer connected commands
 * @info: it is parameter struct
 * @buf: it is address of buffer
 * @len: it is address of len var
 *
 * Return: bytes that got read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t n = 0;
	size_t a = 0;

	if (!*len) /* it will fill it if nothing left */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		n = getline(buf, &a, stdin);
#else
		n = _getline(info, buf, &a);
#endif
		if (n > 0)
		{
			if ((*buf)[n - 1] == '\n')
			{
				(*buf)[n - 1] = '\0'; /* remove trailing newline */
				n--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = n;
				info->cmd_buf = buf;
			}
		}
	}
	return (n);
}

/**
 * get_input - will get line minus the newline
 * @info: it is parameter struct
 *
 * Return: total bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *z; /* the ';' command chain buffer */
	static size_t e, t, y;
	ssize_t u = 0;
	char **o = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	u = input_buf(info, &z, &y);
	if (u == -1) /* EOF */
		return (-1);
	if (y) /* we have commands left in the chain buffer */
	{
		t = e; /* init new iterator to current buf position */
		p = z + e; /* get pointer for return */

		check_chain(info, z, &t, e, y);
		while (t < y) /* iterate to semicolon or end */
		{
			if (is_chain(info, z, &t))
				break;
			t++;
		}

		e = t + 1; /* increment past nulled ';'' */
		if (e >= y) /* reached end of buffer? */
		{
			e = y = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*o = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*o = z; /* else not a chain, pass back buffer from _getline() */
	return (u); /* return length of buffer from _getline() */
}

/**
 * read_buf - will read a buffer
 * @info: it is parameter struct
 * @buf: its a buffer
 * @i: its the size
 *
 * Return: r value
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t p = 0;

	if (*i)
		return (0);
	p = read(info->readfd, buf, READ_BUF_SIZE);
	if (p >= 0)
		*i = p;
	return (p);
}

/**
 * _getline - will get next line of input from STDIN
 * @info: it is parameter struct
 * @ptr: its the address of pointer to buffer
 * @length: it is size of preallocated ptr buffer
 *
 * Return: s value
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char q[READ_BUF_SIZE];
	static size_t d, f;
	size_t g;
	ssize_t h = 0, j = 0;
	char *k = NULL, *l = NULL, *c;

	k = *ptr;
	if (k && length)
		j = *length;
	if (d == f)
		d = f = 0;

	h = read_buf(info, q, &f);
	if (h == -1 || (h == 0 && f == 0))
		return (-1);

	c = _strchr(q + d, '\n');
	g = c ? 1 + (unsigned int)(c - q) : f;
	l = _realloc(k, j, j ? j + g : g + 1);
	if (!l) /* MALLOC FAILURE! */
		return (k ? free(k), -1 : -1);

	if (j)
		_strncat(l, q + d, g - d);
	else
		_strncpy(l, q + d, g - d + 1);

	j += g - d;
	d = g;
	k = l;

	if (length)
		*length = j;
	*ptr = k;
	return (j);
}

/**
 * sigintHandler - will block ctrl-C
 * @sig_num: it is the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
