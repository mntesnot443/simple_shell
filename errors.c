#include "shell.h"

/**
 * _putfd - Write a char c to a given fd
 * @c: a char to be printed
 * @fd: a file descriptor to be write
 * Return: -1 on error, 1 on success and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}


/**
 * _eputchar - Write a char c to stderr
 * @c: a char to be printed
 * Return: -1 on error, 1 on success, errno is set appropriately.
 */
int _eputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}



/**
 *_eputs - Tp print the input string
 * @str: String to print
 * Return: nothing to return
 */
void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}


/**
 *_putsfd - To print the input string
 * @str: String to print
 * @fd: a file descriptor to be write
 * Return: Numbers of char put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
