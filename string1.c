#include "shell.h"

/**
 * _strcpy - will copie a string
 * @dest: it is the destination
 * @src: it is the source
 *
 * Return: the pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _strdup - will duplicate string
 * @str: it is the string to duplicate
 *
 * Return: the pointer to duplicated string
 */
char *_strdup(const char *str)
{
	int z = 0;
	char *e;

	if (str == NULL)
		return (NULL);
	while (*str++)
		z++;
	e = malloc(sizeof(char) * (z + 1));
	if (!e)
		return (NULL);
	for (z++; z--;)
		e[z] = *--str;
	return (e);
}

/**
 * _puts - will print an input string
 * @str: it is the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int r = 0;

	if (!str)
		return;
	while (str[r] != '\0')
	{
		_putchar(str[r]);
		r++;
	}
}

/**
 * _putchar - will write the character c to stdout
 * @c: it is The character to print
 *
 * Return: 1 On success
 */
int _putchar(char c)
{
	static int t;
	static char y[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(1, y, t);
		i = 0;
	}
	if (c != BUF_FLUSH)
		y[t++] = c;
	return (1);
}
