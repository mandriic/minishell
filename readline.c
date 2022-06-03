#include <stdio.h>
#include <std>
#include <readline/readline.h>

void leakss()
{
	// system("leaks a.out");
}

int	main()
{
	char	*wololo;

	wololo = NULL;
	atexit(leakss);
	while (1)
	{
        wololo = readline("");
        printf("%s y mucho\n", wololo);
        free (wololo);
	}
	return (0);
}