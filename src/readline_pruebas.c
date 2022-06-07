#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void leakss()
{
	system("leaks a.out");
}

int	main()
{
	char	*wololo;

	wololo = NULL;
	atexit(leakss);
	while (1)
	{
	wololo = readline("\033[1;32mminishell:\033[0m ");
	printf("%s y mucho\n", wololo);
	free (wololo);
	}
	return (0);
}