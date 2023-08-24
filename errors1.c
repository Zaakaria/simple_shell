#include "shell.h"

/**
 * _erratoi - will convert string to integer
 * @s: it is the string to get converted
 * Return: 0 if no numbers in string
 */
int _erratoi(char *s)
{
	int r = 0;
	unsigned long int t = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (r = 0;  s[r] != '\0'; r++)
	{
		if (s[r] >= '0' && s[r] <= '9')
		{
			t *= 10;
			t += (s[r] - '0');
			if (t > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (t);
}

/**
 * print_error - will print error message
 * @info: it is the parameter
 * @estr: it is string that contains error type
 * Return: 0 if no numbers, -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - its function prints a decimal number
 * @input: it is the input
 * @fd: it is filedescriptor to be write to
 *
 * Return: its number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int y, o = 0;
	unsigned int u, i;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		u = -input;
		__putchar('-');
		o++;
	}
	else
		u = input;
	i = u;
	for (y = 1000000000; y > 1; y /= 10)
	{
		if (u / y)
		{
			__putchar('0' + i / y);
			o++;
		}
		i %= y;
	}
	__putchar('0' + i);
	o++;

	return (o);
}

/**
 * convert_number - its a converter function
 * @num: its a number
 * @base: its the base
 * @flags: it is argument flags
 *
 * Return: the string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *p;
	static char q[50];
	char s = 0;
	char *d;
	unsigned long f = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		f = -num;
		s = '-';

	}
	p = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	d = &q[49];
	*d = '\0';

	do	{
		*--d = p[f % base];
		f /= base;
	} while (f != 0);

	if (s)
		*--d = s;
	return (d);
}

/**
 * remove_comments - a function replace first instance of '#' with '\0'
 * @buf: it is address of the string to modify
 *
 * Return: will always be 0
 */
void remove_comments(char *buf)
{
	int g;

	for (g = 0; buf[g] != '\0'; g++)
		if (buf[g] == '#' && (!g || buf[g - 1] == ' '))
		{
			buf[g] = '\0';
			break;
		}
}
