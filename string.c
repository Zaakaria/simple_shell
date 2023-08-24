#include "shell.h"

/**
 * _strlen - will return the length of string
 * @s: it is the string of length to check
 *
 * Return: it is integer length of string
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}

/**
 * _strcmp - will perform lexicogarphic comparison of two strangs
 * @s1: it is the first strang
 * @s2: it is the second strang
 *
 * Return: if s1 < s2 negative, if s1 > s2 positive, if s1 == s2 zero
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - will check if needle starts with haystack
 * @haystack: it is string to search
 * @needle: it is the substring to find
 *
 * Return: the address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - will concatenate two strings
 * @dest: it is the destination buffer
 * @src: it is the source buffer
 *
 * Return: the pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *z = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (z);
}
