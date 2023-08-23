#include "shell.h"

/**
 * main - it is entry point
 * @ac: it is arg count
 * @av: it is arg vector
 *
 * Return: on success 0, on error 1
 */
int main(int ac, char **av)
{
	info_t a[] = { INFO_INIT };
	int z = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (z)
			: "r" (z));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (z == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		a->readfd = z;
	}
	populate_env_list(a);
	read_history(a);
	hsh(a, av);
	return (EXIT_SUCCESS);
}
