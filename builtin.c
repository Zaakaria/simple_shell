#include "shell.h"

/**
 * _myexit - will exit shell
 * @info: Structure that contains potential arguments
 * Return: exits with an exit status
 */
int _myexit(info_t *info)
{
	int y;

	if (info->argv[1]) /* If theres some exit arguement */
	{
		y = _erratoi(info->argv[1]);
		if (y == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - will change current directory of the process
 * @info: Structure thqt contains potential arguments
 * Return: it is always 0
 */
int _mycd(info_t *info)
{
	char *u, *o, buffer[1024];
	int p;

	u = getcwd(buffer, 1024);
	if (!u)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		o = _getenv(info, "HOME=");
		if (!o)
			p = /* TODO: what should this be? */
				chdir((o = _getenv(info, "PWD=")) ? o : "/");
		else
			p = chdir(o);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(u);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		p = /* TODO: what should this be? */
			chdir((o = _getenv(info, "OLDPWD=")) ? o : "/");
	}
	else
		p = chdir(info->argv[1]);
	if (p == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - will change current directory of the process
 * @info: Structure that contains potential arguments
 * Return: it is always 0
 */
int _myhelp(info_t *info)
{
	char **q;

	q = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*q); /* temp att_unused workaround */
	return (0);
}
