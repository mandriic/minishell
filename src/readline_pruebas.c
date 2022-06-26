#include "../inc/minishell.h"

char	*ft_leelinea(void)
{
	char	*input;

	input = readline(">> ");
	//printf("%s y mucho\n", wololo);
	return (input);
}