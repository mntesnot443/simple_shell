#include "shell.h"

/**
 * find_path - Find this command in a PATH string
 * @info: An info struct
 * @pathstr: A PATH string
 * @cmd: A cmd to find
 * Return: If found or NULL full path of cmd
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int m = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[m] || pathstr[m] == ':')
		{
			path = dup_chars(pathstr, curr_pos, m);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[m])
				break;
			curr_pos = m;
		}
		m++;
	}
	return (NULL);
}

/**
 * is_cmd - Determines if the file is the executable cmd
 * @info: An info struct
 * @path: A path to the file
 * Return: If true 1, else 0.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicate a characters
 * @pathstr: A PATH string
 * @start: The starting index
 * @stop: The stopping index
 * Return: A pointer to the new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int m = 0, c = 0;

	for (c = 0, m = start; m < stop; m++)
		if (pathstr[m] != ':')
			buf[c++] = pathstr[m];
	buf[c] = 0;
	return (buf);
}
