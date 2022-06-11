#include "../inc/minishell.h"

char	*leelinea(void)
{
	char	*wololo;

	wololo = readline("minishell: ");
	printf("%s y mucho\n", wololo);
	return (wololo);
}