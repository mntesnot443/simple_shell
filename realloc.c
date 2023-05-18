#include "shell.h"

/**
 * _realloc - To reallocate the block of memory
 * @ptr: A pointer to a previous malloc'ated block
 * @old_size: A byte size of a previous block
 * @new_size: A byte size of a new block
 * Return: A pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *b;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	b = malloc(new_size);
	if (!b)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		b[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (b);
}

/**
 * ffree - To free the string of strings
 * @bb: A string of strings
 */
void ffree(char **bb)
{
	char **i = bb;

	if (!bb)
		return;
	while (*bb)
		free(*bb++);
	free(i);
}

/**
 **_memset - Fill memory with the constant byte
 *@z: Pointer to a memory area
 *@h: Bytes to fill *z
 *@k: Amount of bytes to fill
 *Return: (z) pointer to a memory area z
 */
char *_memset(char *z, char h, unsigned int k)
{
	unsigned int m;

	for (m = 0; m < k; m++)
		z[m] = h;
	return (z);
}
