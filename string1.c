#include "shell.h"

/**
 *_puts - Print the input string
 *@str: A string to print
 * Return: nothing to return
 */
void _puts(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		_putchar(str[m]);
		m++;
	}
}

/**
 * _putchar - Writes a char k to stdout
 * @k: The char to be printed.
 * Return: 1 On success,
 * On error is returned -1, and set appropriately is errno.
 */
int _putchar(char k)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (k == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(1, buf, m);
		m = 0;
	}
	if (k != BUF_FLUSH)
		buf[m++] = k;
	return (1);
}

/**
 * _strcpy - Copies of the string
 * @dest: A destination
 * @src: A source
 * Return: A pointer to the destination.
 */
char *_strcpy(char *dest, char *src)
{
	int m = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[m])
	{
		dest[m] = src[m];
		m++;
	}
	dest[m] = 0;
	return (dest);
}

/**
 * _strdup - Duplicates the string
 * @str: The string to be duplicated
 * Return: A pointer to a duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}
