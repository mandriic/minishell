# include "../inc/minishell.h"

char	**ft_copy_enviroment_vars_into_matrix(char *envp_original[])
{
	int		i;
	int		num_vars;
	char	**matrix;

	i = 0;
	num_vars = -1;
	while (envp_original[++num_vars]);
	matrix = malloc(sizeof(char *) * (num_vars + 1));//puede no ser necesario
	while (envp_original[i])
	{
		matrix[i] = ft_strdup(envp_original[i]);
		i++;
	}
	matrix[i] = NULL;
	//esto hay que liberarlo
	return (matrix);
}

void	ft_free_array(char **envp_copy)
{
	int	i;

	if (envp_copy == NULL)
		return ;
	i = 0;
	while (envp_copy[i])
	{
		free(envp_copy[i]);
		i++;
	}
	free(envp_copy);
}

void	ft_free_list(t_list *lst)
{
	t_list	*aux;
	t_list	*aux2;

	aux = lst;
	while (aux)
	{
		aux2 = aux->next;
		free(aux);
		aux = aux2;
	}
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
	//esto hay que liberarlo
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

