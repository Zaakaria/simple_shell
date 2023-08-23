#include "shell.h"

/**
 * _memset - will fill memory with constant byte
 * @s: it is the pointer to the memory area
 * @b: it is the byte to fill *s with
 * @n: it is the amount of bytes to be filled
 * Return: pointer to the memory area
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * ffree - will free string of strings
 * @pp: it is string of strings
 */
void ffree(char **pp)
{
	char **z = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(z);
}

/**
 * _realloc - will reallocate block of memory
 * @ptr: it is pointer to previous malloc'ated
 * @old_size: it is byte size of previous block
 * @new_size: it is byte size of new block
 *
 * Return: the pointer to da ol'block nameen
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *e;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	e = malloc(new_size);
	if (!e)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		e[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (e);
}
