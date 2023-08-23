#include "shell.h"

/**
 * is_cmd - will determine if file is an executable command
 * @info: it is the info struct
 * @path: it is path to the file
 *
 * Return: if true 1, otherwise 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat a;

	(void)info;
	if (!path || stat(path, &a))
		return (0);

	if (a.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - will duplicate characters
 * @pathstr: it is the PATH string
 * @start: it is starting index
 * @stop: it is stopping index
 *
 * Return: the pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char e[1024];
	int r = 0, t = 0;

	for (t = 0, r = start; r < stop; r++)
		if (pathstr[r] != ':')
			e[t++] = pathstr[r];
	e[t] = 0;
	return (e);
}

/**
 * find_path - will find this cmd in the PATH string
 * @info: it is the info struct
 * @pathstr: it is the PATH string
 * @cmd: it is the cmd to find
 *
 * Return: the full cmd's path if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int y = 0, curr_pos = 0;
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
		if (!pathstr[y] || pathstr[y] == ':')
		{
			path = dup_chars(pathstr, curr_pos, y);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[y])
				break;
			curr_pos = y;
		}
		y++;
	}
	return (NULL);
}
