#include "shell.h"

/**
 * _strcat - Concatenates the two strings
 * @dest: A destination buffer
 * @src: A source buffer
 * Return: A pointer to a destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * _strlen - Return a length of the string.
 * @s: A string whose length to be checked.
 * Return: An integer length of a string.
 */
int _strlen(char *z)
{
	int m = 0;

	if (!z)
		return (0);

	while (*z++)
		m++;
	return (m);
}

/**
 * _strcmp - Performs lexicogarphic comparison of the two strangs.
 * @s1: The 1st strang
 * @s2: The 2nd strang
 * Return: If z1 < z2 Negative (-), if z1 > z2 Positive (+), if z1 == z2 Zero (0).
 */
int _strcmp(char *z1, char *z2)
{
	while (*z1 && *z2)
	{
		if (*z1 != *z2)
			return (*z1 - *z2);
		z1++;
		z2++;
	}
	if (*z1 == *z2)
		return (0);
	else
		return (*z1 < *z2 ? -1 : 1);
}

/**
 * starts_with - To check if a needle starts with haystack
 * @haystack: The string to search
 * @needle: The substring to be found
 * Return: An address of next character of a haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
