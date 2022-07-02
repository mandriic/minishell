# include "../inc/minishell.h"

void	ft_pwd(void)
{
	return ;
}

char	**ft_copy_enviroment_vars_into_matrix(char *envp_original[])
{
	int	i;
	int	j;
	int	num_vars;

	i = 0;
	j = 0;
	num_vars = 0;
	while (envp_original[num_vars])
	{
		num_vars++;
	}
	printf("%d\n", num_vars);
	return NULL;
}

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
	ft_copy_enviroment_vars_into_matrix(envp);
	i = 0;


	return (0);
}
