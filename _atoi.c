#include "shell.h"

/**
 * interactive - return true if the shell is on interactive mode
 * @info: to struct address
 * Return: if interactive mode 1, else 0.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if the char is the  delimeter
 * @j: a character to check
 * @delim: a delimeter string
 * Return: true 1, false 0
 */

int is_delim(char j, char *delim)
{
	while (*delim)
		if (*delim++ == j)
			return (1);
	return (0);
}

/**
 *_isalpha - check to  alphabetic char
 *@j:  char to input
 *
 *Return:  if b is alphabetic 1, else 0.
 */
int _isalpha(int j)
{
	if ((j >= 'a' && j <= 'z') || (j >= 'A' && j <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi -  string convert to an integer
 *@s: a string to convert
 *
 *Return: if no numbers in string 0, else converted number
 */

int _atoi(char *s)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0;  s[a] != '\0' && flag != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
