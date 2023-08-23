#include "shell.h"

/**
 * bfree - will free pointer and NULLs the address
 * @ptr: it is address of the pointer to be free
 *
 * Return: if freed 1, 0 otherwise
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
