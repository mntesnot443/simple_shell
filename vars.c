#include "shell.h"

/**
 * check_chain - Checks we should continue chaining based on the last status
 * @info: A parameter struct
 * @buf: A character buffer
 * @b: An address of current position in buf
 * @m: Starting position in buf
 * @len: Length of a buf
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *b, size_t m, size_t len)
{
	size_t y = *b;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[m] = 0;
			y = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[m] = 0;
			y = len;
		}
	}

	*b = y;
}

/**
 * is_chain - test if a current character in buffer is the chain delimeter.
 * @info: A parameter struct.
 * @buf: A character buffer.
 * @b: An address of a current position in buf
 * Return: If chain delimeter 1, else 0.
 */
int is_chain(info_t *info, char *buf, size_t *b)
{
	size_t y = *b;

	if (buf[y] == '|' && buf[y + 1] == '|')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[y] == ';') /* Found end of this command */
	{
		buf[y] = 0; /* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*b = y;
	return (1);
}

/**
 * replace_string - Replaces a string
 * @old: An address of the old string
 * @new: A new string
 * Return: If replaced 1, else 0.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * replace_vars - Replace vars in a tokenized string
 * @info: A  parameter struct
 * Return: If replaced 1, else 0.
 */
int replace_vars(info_t *info)
{
	int m = 0;
	list_t *node;

	for (m = 0; info->argv[m]; m++)
	{
		if (info->argv[m][0] != '$' || !info->argv[m][1])
			continue;

		if (!_strcmp(info->argv[m], "$?"))
		{
			replace_string(&(info->argv[m]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[m], "$$"))
		{
			replace_string(&(info->argv[m]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[m][1], '=');
		if (node)
		{
			replace_string(&(info->argv[m]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[m], _strdup(""));

	}
	return (0);
}

/**
 * replace_alias - Replace an alias in a tokenized string
 * @info: A parameter struct
 * Return: If replaced 1, else 0.
 */
int replace_alias(info_t *info)
{
	int m;
	list_t *node;
	char *b;

	for (m = 0; m < 10; m++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		b = _strchr(node->str, '=');
		if (!b)
			return (0);
		b = _strdup(b + 1);
		if (!b)
			return (0);
		info->argv[0] = b;
	}
	return (1);
}
