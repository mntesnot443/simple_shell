#include "shell.h"

/**
 * _myhistory -  Preceed with line numbers, start at 0,
 *		display a history list, one command by line.
 * @info: structure to be containing potential argument.
 *  Return: 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - To set an  alias string
 * @info: The parameter struct
 * @str: An alias string.
 * Return: on error 1,  on success 0.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, a;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	a = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = a;
	return (ret);
}

/**
 * set_alias - To set string alias.
 * @info: The parameter struct
 * @str: An alias string
 * Return: on error 1, on success 0.
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Print the alias string
 * @node: An alias node
 * Return: on error 1,  on succes 0.
 */
int print_alias(list_t *node)
{
	char *p = NULL, *c = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (c = node->str; c <= p; c++)
			_putchar(*c);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - To mimic an alias builtin
 * @info: structure to be containing potential argument
 *  Return: 0
 */
int _myalias(info_t *info)
{
	int j = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		p = _strchr(info->argv[j], '=');
		if (p)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
