#include "shell.h"

/**
 * bfree - Frees the pointer and NULLs an address
 * @ptr: An address of a pointer to be free
 * Return: If freed 1, else 0.
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
