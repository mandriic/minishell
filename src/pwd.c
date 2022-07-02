# include "../inc/minishell.h"

char	**ft_copy_enviroment_vars_into_matrix(char *envp_original[])
{
	int		i;
	int		num_vars;
	char	**envp_copy;

	i = 0;
	num_vars = -1;
	while (envp_original[++num_vars]);
	envp_copy = malloc(sizeof(char *) * num_vars);
	while (envp_original[i])
	{
		envp_copy[i] = ft_strdup(envp_original[i]);
		i++;
	}
	return (envp_copy);
}

t_list	**ft_copy_enviroment_vars_into_list(t_list **env_copy, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(env_copy, ft_lstnew((void *)envp[i]));
		i++;
	}
	return (0);
}

void	ft_print_list(t_list *env_copy)
{
	t_list *aux;
	int i = 0;

	aux = env_copy;
	while (aux->next)
	{
		i++;
		printf("%d - %s\n", i, (char *)(aux->content));
		aux = aux->next;
	}
	printf("%d - %s\n", ++i, (char *)(aux->content));
	
}

void	ft_pwd(char **env)
{
	// char	*directory;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		// que pasa si una variable empieza por PWD pero no es la ruta???
		if (!ft_strncmp("PWD", env[i], 3))
		{
			j = 0;
			while (env[i][j] != '=')
			{
				j++;
			}
			j++;
			ft_putstr_fd(&env[i][j], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return ;
}

int	main(int argc, char* argv[], char *envp[])
{
	t_list	*env_copy_list;
	char	**env_copy_array;
	int		i = 0;
	(void)argv;
	(void)argc;

	env_copy_list = 0;
	ft_copy_enviroment_vars_into_list(&env_copy_list, envp);
	ft_print_list(env_copy_list);
	printf("-----------------------------------------------------\n");
	env_copy_array = ft_copy_enviroment_vars_into_matrix(envp);
	while (env_copy_array[i])
	{
		printf("%d - %s\n", i+1, env_copy_array[i]);
		i++;
	}
	ft_pwd(env_copy_array);

	return (0);
}