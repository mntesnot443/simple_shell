#include "shell.h"

/**
 * input_buf - Chained commands of a buffer
 * @info: The parameter struct
 * @buf: Buffer address
 * @len: Len var address
 * Return: Read bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t k = 0;
	size_t len_p = 0;

	if (!*len) /* Fill it, if nothing left in the buffer. */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		k = getline(buf, &len_p, stdin);
#else
		k = _getline(info, buf, &len_p);
#endif
		if (k > 0)
		{
			if ((*buf)[k - 1] == '\n')
			{
				(*buf)[k - 1] = '\0'; /* Remove trailing new line */
				k--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* If (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = k;
				info->cmd_buf = buf;
			}
		}
	}
	return (k);
}

/**
 * get_input - To get the line minus a newline
 * @info: The parameter struct
 * Return: Read bytes
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t m, c, len;
	ssize_t k = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	k = input_buf(info, &buf, &len);
	if (k == -1) /* EOF */
		return (-1);
	if (len)	/* We have commands left in the chain buffer */
	{
		c = m; /* Init new iterator for current buf position */
		p = buf + m; /* Get pointer to return */

		check_chain(info, buf, &c, m, len);
		while (c < len) /* Iterate semicolon or end */
		{
			if (is_chain(info, buf, &c))
				break;
			c++;
		}

		m = c + 1; /* Increment past nulled ';'' */
		if (m >= len) /* End of buffer reached? */
		{
			m = len = 0; /* Length and reset position */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* To current command position Pass back pointer */
		return (_strlen(p)); /* Length of current command return */
	}

	*buf_p = buf; /* Pass back buffer from _getline(),  else not a chain */
	return (k); /* Length of buffer return from _getline() */
}

/**
 * read_buf - To reads the buffer
 * @info: A parameter struct
 * @buf: The buffer
 * @m: A size
 * Return: c
 */
ssize_t read_buf(info_t *info, char *buf, size_t *m)
{
	ssize_t c = 0;

	if (*m)
		return (0);
	c = read(info->readfd, buf, READ_BUF_SIZE);
	if (c >= 0)
		*m = c;
	return (c);
}

/**
 * _getline - To get a next line of input from STDIN
 * @info: The parameter struct
 * @ptr: Pre-allocated or NULL, address of pointer to buffer.
 * @length: A size of pre-allocated ptr buffer if not NULL.
 * Return: l
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t m, len;
	size_t n;
	ssize_t r = 0, l = 0;
	char *p = NULL, *new_p = NULL, *a;

	p = *ptr;
	if (p && length)
		l = *length;
	if (m == len)
		m = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	a = _strchr(buf + m, '\n');
	n = a ? 1 + (unsigned int)(a - buf) : len;
	new_p = _realloc(p, l, l ? l + n : n + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (l)
		_strncat(new_p, buf + m, n - m);
	else
		_strncpy(new_p, buf + m, n - m + 1);

	l += n - m;
	m = n;
	p = new_p;

	if (length)
		*length = l;
	*ptr = p;
	return (l);
}

/**
 * sigintHandler - To block ctrl-C
 * @sig_num: A signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
