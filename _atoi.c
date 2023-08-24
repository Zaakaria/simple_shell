#include "shell.h"

/**
 * interactive - true if shell is indeed interactive mode
 * @info: it is the struct address
 *
 * Return: if interactive mode 1, otherwise its 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - will check if the character is delimeter
 * @c: it is the char to check
 * @delim: it is the delimeter string
 * Return: if true 1, if false 0
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - will check for the alphabetic character
 * @c: it is The character to be input
 * Return: if c is alphabetic 1, otherwise 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - will convert string to integer
 * @s: it is the string to get converted
 * Return: if no numbers in string 0, otherwise converted number
 */

int _atoi(char *s)
{
	int a, z = 1, e = 0, r;
	unsigned int t = 0;

	for (a = 0; s[a] != '\0' && e != 2; a++)
	{
		if (s[a] == '-')
			z *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			e = 1;
			t *= 10;
			t += (s[a] - '0');
		}
		else if (e == 1)
			e = 2;
	}

	if (z == -1)
		r = -t;
	else
		r = t;

	return (r);
}
