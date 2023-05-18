#include "shell.h"

/**
 * **strtow2 - Split the string to words.
 * @str: An input string.
 * @b: The delimeter.
 * Return: NULL on failure, a pointer to an array of the string.
 */
char **strtow2(char *str, char b)
{
	int m, y, c, i, numwords = 0;
	char **z;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (m = 0; str[m] != '\0'; m++)
		if ((str[m] != b && str[m + 1] == b) ||
		    (str[m] != b && !str[m + 1]) || str[m + 1] == b)
			numwords++;
	if (numwords == 0)
		return (NULL);
	z = malloc((1 + numwords) * sizeof(char *));
	if (!z)
		return (NULL);
	for (m = 0, y = 0; y < numwords; y++)
	{
		while (str[m] == b && str[m] != b)
			m++;
		c = 0;
		while (str[m + c] != b && str[m + c] && str[m + c] != b)
			c++;
		z[y] = malloc((c + 1) * sizeof(char));
		if (!z[y])
		{
			for (c = 0; c < y; c++)
				free(z[c]);
			free(z);
			return (NULL);
		}
		for (i = 0; i < c; i++)
			z[y][i] = str[m++];
		z[y][i] = 0;
	}
	z[y] = NULL;
	return (z);
}

/**
 * **strtow - Split the string into words. repeat delimeteres are ignored.
 * @str: An  input string
 * @b: A delimeter string
 * Return: NULL on failure, or the pointer to an array of a string.
 */

char **strtow(char *str, char *b)
{
	int m, y, c, i, numwords = 0;
	char **z;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!b)
		b = " ";
	for (m = 0; str[m] != '\0'; m++)
		if (!is_delim(str[m], b) && (is_delim(str[m + 1], b) || !str[m + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	z = malloc((1 + numwords) * sizeof(char *));
	if (!z)
		return (NULL);
	for (m = 0, y = 0; y < numwords; y++)
	{
		while (is_delim(str[m], b))
			m++;
		c = 0;
		while (!is_delim(str[m + c], b) && str[m + c])
			c++;
		z[y] = malloc((c + 1) * sizeof(char));
		if (!z[y])
		{
			for (c = 0; c < y; c++)
				free(z[c]);
			free(z);
			return (NULL);
		}
		for (i = 0; i < c; i++)
			z[y][i] = str[m++];
		z[y][i] = 0;
	}
	z[y] = NULL;
	return (z);
}
