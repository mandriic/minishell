#include <stdio.h>
#include <stdlib.h>			
#include <readline/readline.h>
#include <readline/history.h>

void leakss()
{
	// system("leaks a.out");
}

int	main()
{

	char *line;
	char *history;
	// atexit(leakss);
	while (1)
	{
	  	// printf("\033[1;31m");
		// printf("Minishell>");
		// printf("\033[0m");
        line = readline (">>");
		add_history(line);
        printf("es0 hay que parsear ->(%s) \n", line);

		free(line);
	}
	return (0);
}
