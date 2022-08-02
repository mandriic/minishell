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

void	ft_copy_matrix(char **envp_copy, char **aux)
{
	int	i;

	i = 0;
	while (envp_copy[i])
	{
		aux[i] = envp_copy[i];
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
	return (aux);
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
	char **aux;

	if (envp_copy == NULL)
		return (0);
	i = 0;

	aux = ft_copy_envp_copy_to_export_matrix(envp_copy);
	while (aux[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(aux[i], STDOUT_FILENO);
		i++;
	}
	return (0);
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
		ft_check_error_export(cmd.comando_bonito[i]);
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
