#include "shell.h"

/**
 * **strtow - will split a string into words
 * @str: it is the input string
 * @d: it is the delimeter string
 * Return: pointer to an array of strings, on failure NULL 
 */

char **strtow(char *str, char *d)
{
	int a, z, e, r, t = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			t++;

	if (t == 0)
		return (NULL);
	s = malloc((1 + t) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, z = 0; z < t; z++)
	{
		while (is_delim(str[a], d))
			a++;
		e = 0;
		while (!is_delim(str[a + e], d) && str[a + e])
			e++;
		s[z] = malloc((e + 1) * sizeof(char));
		if (!s[z])
		{
			for (e = 0; e < z; e++)
				free(s[e]);
			free(s);
			return (NULL);
		}
		for (r = 0; r < e; r++)
			s[z][r] = str[a++];
		s[z][r] = 0;
	}
	s[z] = NULL;
	return (s);
}

/**
 * **strtow2 - will split string into words
 * @str: it is the input string
 * @d: it is the delimeter
 * Return: pointer to an array of strings, on failure NULL 
 */
char **strtow2(char *str, char d)
{
	int a, z, e, r, t = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			t++;
	if (t == 0)
		return (NULL);
	s = malloc((1 + t) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, z = 0; z < t; z++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		e = 0;
		while (str[a + e] != d && str[a + e] && str[a + e] != d)
			e++;
		s[z] = malloc((e + 1) * sizeof(char));
		if (!s[z])
		{
			for (e = 0; e < z; e++)
				free(s[e]);
			free(s);
			return (NULL);
		}
		for (r = 0; r < e; r++)
			s[z][r] = str[a++];
		s[z][r] = 0;
	}
	s[z] = NULL;
	return (s);
}
