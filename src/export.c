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
{//esta funcion copia una matrix en otra a excepción del nulo del final
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
	return (aux);
}

void	ft_add_line_to_matrix(char ***matrix, char *line)
{
	char	**aux;
	int		len_matrix;

	len_matrix = 0;
	while ((*matrix)[len_matrix])
		len_matrix++;
	aux = malloc(sizeof(char *) * (len_matrix + 2));
	if (!aux)
		return ;
	ft_copy_matrix(*matrix, aux);
	aux[len_matrix - 1] = ft_strdup(line);
	aux[len_matrix] = NULL;
	free(*matrix);
	*matrix = aux;
	return ;
}

int	ft_export_without_anything_else(char **envp_copy)
{
	int	i;
	int	j;
	char **aux;

	if (envp_copy == NULL)
		return (0);
	i = 0;

	aux = ft_copy_envp_copy_to_export_matrix(envp_copy);
	while (aux[i] != NULL)
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (aux[i][j] != '=' && aux[i][j] != '\0')
		{
			ft_putchar_fd(aux[i][j], 1);
			j++;
		}
		while (aux[i][j])
		{
			ft_putchar_fd(aux[i][j], 1);
			if (aux[i][j] == '=')
				ft_putchar_fd('"', 1);
			j++;
		}
		 if (ft_strchr(aux[i], '='))
			ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}



int	ft_check_existing_variable(char *var_name)
{
	int	i;
	int	len_var_name;
	int len_key;
	int	wololo;
	int	mierda;

// printf("\n***********\n    %s\n*************\n", var_name);
	//recorrer todas las lineas
		//recorrer cada caracter de la variable guardada desde el primero hasta que haya un = o se termine
		//si ese caracter coincide con el corresondiente de la variable que se quiere comprobar pasar al siguiente
		//si cuando no coincide es el = de la variable y el nulo del añadido
			//es una variable ya guardada -> terminar la función devolver 1
			//si no son = y nulo, romper el bucle
		//si llega al final del bucle grande y no ha habido match, devolver 0
	i = 0;
	len_var_name = ft_env_var_key_len(var_name);
	printf("%d <- %s\n\n", len_var_name, var_name);
	while(g_data.envp_copy[i])
		{	
			len_key = ft_env_var_key_len(g_data.envp_copy[i]);
			printf("%d <- %s\n", len_key, g_data.envp_copy[i]);
			wololo = ft_strncmp(g_data.envp_copy[i], var_name, len_var_name);
			mierda = ft_strncmp(g_data.envp_copy[i], var_name, len_key);
			printf("%d -*- %d\n", wololo, mierda);
			/* if (wololo == 0
				&& (var_name[len_var_name] == '\0' || var_name[len_var_name] == '\0')
				&& (g_data.envp_copy[i][len_var_name] == '='
				|| g_data.envp_copy[i][len_var_name] == '\0'))
				{
					printf("Si es una variable de entorno\n");
					return (1);
				} */
			i++;
		}
	printf("NO es una variable de entorno\n");
	return (0);
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
	if (cmd.comando_bonito[1] == NULL)
		return (ft_export_without_anything_else(g_data.export));
	//ignorar espacios en blanco entre export y varible=valor -> ya lo hace split
	i = 1;
	while (cmd.comando_bonito[i])
	{
		if (ft_check_error_export(cmd.comando_bonito[i]) != 0)
			continue;//tiene que mostrar el error
		if (ft_check_existing_variable(cmd.comando_bonito[i]) == 1)
			ft_replace_line_in_envp_copy(cmd.comando_bonito[i]);
		else
			ft_add_line_to_matrix(&g_data.export, cmd.comando_bonito[i]);
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
