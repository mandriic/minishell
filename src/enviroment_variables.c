#include "../inc/minishell.h"

void	ft_copy_enviroment_vars_into_list(t_list **env_copy, char **envp)
{
	(void)env_copy;
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("Argumento nº %d: %s\n", i, envp[i]);
		i++;
	}
}




int	main(int argc, char* argv[], char *envp[])
{
	int	i;
	t_list *env_copy;
	(void)argv;
	(void)argc;
//	char	*wololo;
//	wololo = leelinea();
//	free (wololo);
	env_copy = NULL;
	ft_copy_enviroment_vars_into_list(&env_copy, envp);
	i = 0;


	return (0);
}
