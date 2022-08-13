#include "../inc/minishell.h"

void	ft_delete_line_from_matrix(char ***matrix, char *line, int index)
{
(void)line;
	char	**aux;
	int		i;
	int		j;
	int		len_matrix;

	len_matrix = ft_matrix_len(*matrix);
	aux = malloc(sizeof(char *) * len_matrix);
	if (aux == NULL)
		return ;
	aux[len_matrix - 1] = NULL;
	i = 0;
	j = 0;
	while (i < len_matrix)
	{
		if (i != index)
		{
			aux[j] = (*matrix)[i];
			j++;
		}
		i++;
	}
	free(*matrix);
	*matrix = aux;
}

void	ft_unset_builtin(t_command cmd, t_data *g_data)
{
	(void)cmd;

	int i;
	int	index;

	i = 1;
	index = -1;
	while (cmd.comando_bonito[i])
	{
		if (ft_check_existing_variable_in_matrix(g_data->envp_copy, cmd.comando_bonito[i], &index) == 1)
			ft_delete_line_from_matrix(&g_data->envp_copy, cmd.comando_bonito[i], index);
		if (ft_check_existing_variable_in_matrix(g_data->export, cmd.comando_bonito[i], &index) == 1)
			ft_delete_line_from_matrix(&g_data->export, cmd.comando_bonito[i], index);
		i++;
	}
    return ;
}