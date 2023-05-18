#include "shell.h"

/**
 * populate_env_list - To  populate an env linked list
 * @info: structure to be containing potential argument.
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}


/**
 * _mysetenv -  Modify the existing one, or
 *		initialize the new env variable
 * @info: structure to be containing potential argument.
 *  Return: 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}


/**
 * _getenv - To get a value of the  environ variable
 * @info: structure to be containing potential argument.
 * @name: Name of env var
 * Return: a value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}


/**
 * _myenv - Print a current environment
 * @info: structure to be containing potential argument.
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}


/**
 * _myunsetenv - To remove the environment variable
 * @info: structure to be containing potential argument.
 *  Return: 0
 */
int _myunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}
