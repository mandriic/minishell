#include "../inc/minishell.h"

t_list	**ft_copy_enviroment_vars_into_list(t_list **env_copy, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(env_copy, ft_lstnew((void *)envp[i]));
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

void	ft_print_list(t_list *env_copy)
{
	t_list *aux;

	aux = env_copy;
	while (aux->next)
	{
		printf("%s\n", (char *)(aux->content));
		aux = aux->next;
	}
	
}


int	main(int argc, char* argv[], char *envp[])
{
	int	i;
	t_list *env_copy;
	(void)argv;
	(void)argc;

	env_copy = 0;
	ft_copy_enviroment_vars_into_list(&env_copy, envp);
	ft_print_list(env_copy);
	i = 0;


	return (0);
}
