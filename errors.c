#include "shell.h"

/**
 * _eputs - will print input string
 * @str: it is the string to get printed
 *
 * Return: it will be nothing
 */
void _eputs(char *str)
{
	int b = 0;

	if (!str)
		return;
	while (str[b] != '\0')
	{
		_eputchar(str[b]);
		b++;
	}
}

/**
 * _eputchar - will write the character c to stderr
 * @c: it is The character to be printed
 *
 * Return: 1 if success
 */
int _eputchar(char c)
{
	static int n;
	static char a[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, a, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		a[n++] = c;
	return (1);
}

/**
 * _putfd - will write character c to given fd
 * @c: it is The character to be printed
 * @fd: it is filedescriptor to be write to
 *
 * Return: 1 if success
 */
int _putfd(char c, int fd)
{
	static int z;
	static char e[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(fd, e, z);
		z = 0;
	}
	if (c != BUF_FLUSH)
		e[z++] = c;
	return (1);
}

/**
 * _putsfd - will print input string
 * @str: it is the string to get printed
 * @fd: it is filedescriptor to be write to
 *
 * Return: total number of chars put
 */
int _putsfd(char *str, int fd)
{
	int e = 0;

	if (!str)
		return (0);
	while (*str)
	{
		e += _putfd(*str++, fd);
	}
	return (e);
}
