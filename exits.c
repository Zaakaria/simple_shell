#include "shell.h"

/**
 **_strncpy - will copie a string
 *@dest: it is destination string to get copied to
 *@src: it is the source string
 *@n: it is amount of characters to be copied
 *Return: the new concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int w, x;
	char *c = dest;

	w = 0;
	while (src[w] != '\0' && w < n - 1)
	{
		dest[w] = src[w];
		w++;
	}
	if (w < n)
	{
		x = w;
		while (x < n)
		{
			dest[x] = '\0';
			x++;
		}
	}
	return (c);
}

/**
 **_strncat - will concatenate two strings
 *@dest: it is first string
 *@src: it is the second string
 *@n: it is the amount of bytes to get maximally used
 *Return: it is concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int c, v;
	char *s = dest;

	c = 0;
	v = 0;
	while (dest[c] != '\0')
		c++;
	while (src[v] != '\0' && v < n)
	{
		dest[c] = src[v];
		c++;
		v++;
	}
	if (v < n)
		dest[c] = '\0';
	return (s);
}

/**
 **_strchr - will locate a charac in string
 *@s: it is the string to get parsed
 *@c: it is the character to look for
 *Return: a pointer to the memory area
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
