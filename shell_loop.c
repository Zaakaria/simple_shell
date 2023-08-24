#include "shell.h"

/**
 * hsh - its the main shell loop
 * @info: it is the parameter & return info
 * @av: its the argument vector from main()
 *
 * Return: on success 0, on error 1
 */
int hsh(info_t *info, char **av)
{
	ssize_t a = 0;
	int z = 0;

	while (a != -1 && z != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		a = get_input(info);
		if (a != -1)
		{
			set_info(info, av);
			z = find_builtin(info);
			if (z == -1)
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
	if (z == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (z);
}

/**
 * find_builtin - will find built-in command
 * @info: its the parameter & return info
 *
 * Return: if builtin not found -1,
 * if builtin executed successfully 0,
 * if builtin found but not successful 1,
 * if builtin signals exit() 2
 */
int find_builtin(info_t *info)
{
	int e, r = -1;
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

	for (e = 0; builtintbl[e].type; e++)
		if (_strcmp(info->argv[0], builtintbl[e].type) == 0)
		{
			info->line_count++;
			r = builtintbl[e].func(info);
			break;
		}
	return (r);
}

/**
 * find_cmd - will find command in PATH
 * @info: it is the parameter & return info
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *t = NULL;
	int y, u;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (y = 0, u = 0; info->arg[y]; y++)
		if (!is_delim(info->arg[y], " \t\n"))
			u++;
	if (!u)
		return;

	t = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (t)
	{
		info->path = t;
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
 * fork_cmd - will fork an exec thread to run cmd
 * @info: it is the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t o;

	o = fork();
	if (o == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (o == 0)
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
