#include "shell.h"

/**
 * fork_cmd - Forks the  exec thread to run commad
 * @info: return info struct & a parameter  struct
 * Return: Void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

/**
 * hsh - The main shell loop
 * @info: Return info struct & a parameter struct
 * @av: An argument vector from main()
 * Return: On success 0, on error or error code 1.
 */
int hsh(info_t *info, char **av)
{
	ssize_t j = 0;
	int builtin_ret = 0;

	while (j != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		j = get_input(info);
		if (j != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_cmd - Find the cmd in PATH
 * @info: Return info struct & a parameter struct
 * Return: Void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int m, c;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (m = 0, c = 0; info->arg[m]; m++)
		if (!is_delim(info->arg[m], " \t\n"))
			c++;
	if (!c)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * find_builtin - Find the builtin cmd.
 * @info: Return info struct & a parameter.
 * Return: If builtin not found -1,
 * If builtin executed successfully 0,
 * If builtin found but not successful 1,
 * If builtin signals exit() -2.
 */
int find_builtin(info_t *info)
{
	int m, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (m = 0; builtintbl[m].type; m++)
		if (_strcmp(info->argv[0], builtintbl[m].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[m].func(info);
			break;
		}
	return (built_in_ret);
}
