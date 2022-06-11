#include "../inc/minishell.h"

void leakss()
{
	system("leaks minishell");
}

int	main(int argc, char* argv[])
{
	(void)argc;
	int	i;
	char	*wololo;
atexit(leakss);
	wololo = leelinea();
	if (argc != 1)
		i = ft_atoi(argv[1]);
	else
		i = 1903;
	free (wololo);


	return (0);
}
