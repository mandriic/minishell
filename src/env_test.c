#include "../inc/minishell.h"
void ft_test(t_vars *vars)
{
	char *env;

	env = NULL;
	env = getenv("PATH");
	(void) vars;
	printf("%s\n", env);
}