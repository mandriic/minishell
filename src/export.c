#include "../inc/minishell.h"

int	ft_check_error_export(char *argument)
{
	(void)argument;
	//errores para comprobar:
		//primer caracter az_AZ
		//hay un = -> si no hay no tira error pero no hace nada
		//no hay espacios antes ni después del primer =
	return 0;
}

void	ft_copy_matrix(char **source, char **destiny)
{
	int	i;

	i = 0;
	while (source[i])
	{
		destiny[i] = source[i];
		i++;
	}
	return ;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	aux;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			aux = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (aux);
		}
		i++;
	}
	return (0);
}

void	ft_sort_int_tab(char **tab, int size)
{
	int		index;
	int		counter;
	char	*temp;

	counter = 0;
	while (counter < size)
	{
		index = 0;
		while (index < size - 1)
		{
			if (ft_strcmp(tab[index], tab[index + 1]) > 0)
			{
				temp = tab[index];
				tab[index] = tab[index + 1];
				tab[index + 1] = temp;
			}
			index++;
		}
		counter++;
	}
}

char	**ft_copy_envp_copy_to_export_matrix(char **envp_copy)
{
	int	i;
	int	j;
	int	matrix_len;
	char	**aux;

	i = 0;
	j = 0;
	while(envp_copy[i])
		i++;
	matrix_len = i;
	aux = malloc(sizeof(char *) * (matrix_len + 1));
	if (aux == NULL)
		return (NULL);//esto hay que mejorarlo
	aux[matrix_len] = NULL;
	ft_copy_matrix(envp_copy, aux);
	ft_sort_int_tab(aux, matrix_len);
	i = 0;
	while (aux[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(aux[i], STDOUT_FILENO);
		i++;
	}
	free(aux);//los punteros los tiene almacenados envp_copy, no hay que liberarlos, solo el puntero doble
	return (NULL);
}


int	ft_export_without_anything_else(char **envp_copy)
{
	int	i;

	if (envp_copy == NULL)
		return (0);
	i = 0;

	ft_copy_envp_copy_to_export_matrix(envp_copy);
	/* while (envp_copy[i] != NULL)
	{
		ft_putnbr_fd(i, 1);
		ft_putstr_fd(" ", 1);
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(envp_copy[i], STDOUT_FILENO);
		i++;
	} */
	return (0);
}

void	ft_add_line_to_envp_copy(char *line)
{
	char	**aux;
	int		len_matrix;

	len_matrix = 0;
	while (g_data.envp_copy[len_matrix])
		len_matrix++;
	aux = malloc(sizeof(char *) * (len_matrix + 2));
	ft_copy_matrix(g_data.envp_copy, aux);
	aux[len_matrix - 1] = ft_strdup(line);
	aux[len_matrix] = NULL;
	free(g_data.envp_copy);//por si no viene de la variable global q no se olvide liberar
	g_data.envp_copy = aux;
}

int	ft_check_existing_variable(char *var_name)
{
	int	i;
	int	j;

printf("\n***********\n    %s\n*************\n", var_name);
	i = 0;
	while(g_data.envp_copy[i])
		{
			j = 0;
			while(g_data.envp_copy[i][j] != '=' && g_data.envp_copy[i][j] != '\0')
			{
				if (g_data.envp_copy[i][j] != var_name[j])
				{
					printf("No es una variable de entorno\n");
					return (0);
				}
				j++;
			}
			i++;
		}
	printf("Si es una variable de entorno\n");
	return (1);
}

void	ft_replace_line_in_envp_copy(char *line)
{
	(void)line;
	return ;
}

int	ft_export_builtin(t_command cmd)
{
	int	i;
	//export solo

	if (/* ft_strncmp("export", cmd.comando_a_pelo, ft_strlen("export")) == 0
		&&  */cmd.comando_bonito[1] == NULL)
		return (ft_export_without_anything_else(g_data.envp_copy));
	//ignorar espacios en blanco entre export y varibale=valor -> ya lo hace split
	i = 1;
	while (cmd.comando_bonito[i])
	{
		if (ft_check_error_export(cmd.comando_bonito[i]) != 0)
			continue;//tiene que mostrar el error
		if (ft_check_existing_variable(cmd.comando_bonito[i]) == 1)
			ft_replace_line_in_envp_copy(cmd.comando_bonito[i]);
		else
			ft_add_line_to_envp_copy(cmd.comando_bonito[i]);
		i++;
	}

	//bucle para cada argumento de export
	//chequear errores de sintaxis -> escupir error
	//buscar si ya existe
		//si existe reemplazar puntero
		//si no existe
			//preparar matrix con envp_copy len+1
			//copiar todos los punteros
			//añadir nueva linea
			//añadir null final
			
	return (0);
}
