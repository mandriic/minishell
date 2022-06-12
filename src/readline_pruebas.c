#include "../inc/minishell.h"

char	*leelinea(void)
{
	char	*wololo;

	wololo = readline(">> ");
	//printf("%s y mucho\n", wololo);
	return (wololo);
}