# include "../inc/minishell.h"




void leaks()
{
	system ("leaks -fullContent minishell");
}

int	ft_check_path_route(char **envp, char *arg)
{(void)arg;
	int		i;
	char	*path_value;
	int		len_path;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			printf("ENCONTrADO\n");
			break;
		}
		i++;
	}
	len_path = ft_strlen(envp[i]);
	path_value = ft_substr(envp[i], (unsigned int)i - 1, len_path - i + 1);
	//free path_value
	return (0);

	
	//find linea de PATH
	//recortar desde el primer =
	//split en :
	//iterar en split[i] el access
		//si alguno da 0->mandar al hijo
		//si ninguno da 0->mandar al hijo la ruta q instroduzca el usuario
}

int main(int argc, char *argv[], char *envp[])
{
//atexit(leaks);
	(void)argc;
	(void)argv;
	(void)envp;
	// int	i = 0;
	 char **envp_copy;
	char *args[] = {"/bin/ls", "-la", "/Users/josgarci/Desktop", NULL};

//checkear si tengo access en alguna de las partes del path+bin (ojo flag X_OK)

//crear hijo
	 envp_copy = ft_copy_enviroment_vars_into_matrix(envp);
	ft_check_path_route(envp_copy, args[0]);
	/* while (envp_copy[i])
	{
		printf("%d - %s\n", i+1, envp_copy[i]);
		i++;
	} */
	/* if (execve("/bin/ls", args, envp_copy) == -1)
		printf("Error ejecutando\n"); */
	//ft_free_array(envp_copy);
	return (0);
}
