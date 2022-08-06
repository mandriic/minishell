#include "../inc/minishell.h"

void	ft_print_error_export(char *argument)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(argument, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_check_export_input(char *argument)
{	
	if ((argument[0] >= 'A' && argument[0]<= 'Z') 
		|| (argument[0] >= 'a' && argument[0] <= 'z') 
		|| argument[0] == '_')
		return 0;
	else
	{
		ft_print_error_export (argument);
		return (1);
	}
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
	printf("X-X-X-X-X-\t\t%s\t\t-X-X-X-X-X-X-X-X-\n", line);
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


int	ft_check_existing_variable_in_matrix(char **matrix, char *var_name, int *index)
{
	int	i;
	int	len_var_name;
	int len_key;

	i = *index;
	len_var_name = ft_env_var_key_len(var_name);
	while(matrix[i])
		{	
			len_key = ft_env_var_key_len(matrix[i]);
			if (ft_strncmp(matrix[i], var_name, len_var_name) 
				== ft_strncmp(var_name, matrix[i], len_key))
				{
					*index = i;
					return (1);
				}
			i++;
		}
	return (0);
}

void	ft_replace_line_in_matrix(char **matrix, char *line, int index)
{
	free(matrix[index]);
	matrix[index] = ft_strdup(line);
	return ;
}



int	ft_export_builtin(t_command cmd)
{
	int	i;
	int	matrix_index;
	//export solo
	if (cmd.comando_bonito[1] == NULL)
		return (ft_export_without_anything_else(g_data.export));
	//ignorar espacios en blanco entre export y varible=valor -> ya lo hace split
	i = 1;
	int fd = open("wololo.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	ft_putendl_fd("ENVP_COPY antes:", fd);
	ft_print_matrix(g_data.envp_copy, fd);
	ft_putendl_fd("\n\n *-*--*-*-*-*-*-*-*-*-*-*--*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n", fd);
	ft_putendl_fd("EXPORT antes:", fd);
	ft_print_matrix(g_data.export, fd);
	close(fd);
	while (cmd.comando_bonito[i])
	{
		matrix_index = 0;
		if (ft_check_export_input(cmd.comando_bonito[i]) != 0)
		{
			i++;
			continue;//tiene que mostrar el error
		}
		if (ft_check_existing_variable_in_matrix(g_data.export, cmd.comando_bonito[i], &matrix_index) == 1)
			ft_replace_line_in_matrix(g_data.export, cmd.comando_bonito[i], matrix_index);
		else
			ft_add_line_to_matrix(&g_data.export, cmd.comando_bonito[i]);
		if (ft_strchr(cmd.comando_bonito[i], '=') != 0)
		{
			if (ft_check_existing_variable_in_matrix(g_data.envp_copy, cmd.comando_bonito[i], &matrix_index) == 1)
				ft_replace_line_in_matrix(g_data.envp_copy, cmd.comando_bonito[i], matrix_index);
			else
				ft_add_line_to_matrix(&g_data.envp_copy, cmd.comando_bonito[i]);
		}

		i++;
	}
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\n", 1);
	ft_putendl_fd("ENVP_COPY:", 1);
	ft_print_matrix(g_data.envp_copy, 1);
	ft_putendl_fd("\n\n *-*--*-*-*-*-*-*-*-*-*-*--*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n", 1);
	ft_putendl_fd("EXPORT:", 1);
	ft_print_matrix(g_data.export, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\n", 1);

	//si es digno de entrar en envp_copy (name=[value opcional]) -> meter en envp_copy y en export
	//si no es digno para envp_copy -> meter solo en export

	//¿Cuando comprobar si existe, antes o después 

			
	return (0);
}
