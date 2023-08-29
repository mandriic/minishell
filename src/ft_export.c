/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:00:19 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/28 13:06:05 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_sub_export(t_vars *vars, int i, t_command *cmd)
{
	int		j;

	j = 0;
	if (cmd->next)
		ft_export_hijo(cmd, vars, i, j);
	else
	{
		if (ft_get_value("OLDPWD", vars->env_var) == 0)
			printf("declare -x OLDPWD\n");
		while (vars->env_var[i])
		{
			j = 0;
			printf("declare -x ");
			while (vars->env_var[i][j] != '=')
			{
				printf("%c", vars->env_var[i][j]);
				j++;
			}
			printf("=\"%s\"\n", vars->env_var[i] + j + 1);
		i++;
		}
	}
}

void	ft_sub_sub_export(t_vars *vars, t_command *cmd, int j)
{
	char	*var;
	char	*valor;
	char	*temp;

	var = ft_substr(cmd->cmd[j], 0, ft_strlen(cmd->cmd[j]) \
	- ft_strlen(ft_strchr(cmd->cmd[j], '=')));
	valor = ft_substr(cmd->cmd[j], ft_strlen(cmd->cmd[j]) \
	- ft_strlen(ft_strchr(cmd->cmd[j], '=')), \
	ft_strlen(ft_strchr(cmd->cmd[j], '=')));
	if (ft_find_in_env(vars, var) == 0)
		vars->env_var = ft_append_to_env(vars, cmd->cmd[j]);
	else if (ft_find_in_env(vars, var) != 0)
		ft_change_env(vars, var, valor, ft_strlen(var));
	else if (ft_find_in_temp_env(vars, cmd->cmd[j]) != NULL)
	{
		temp = ft_find_in_temp_env(vars, cmd->cmd[j]);
		vars->env_var = ft_append_to_env(vars, temp);
	}
	free(var);
	free(valor);
}

int	ft_export(t_vars *vars, t_command *cmd)
{
	int		i;
	int		j;

	i = 0;
	if (cmd->cmd[1] && cmd->next)
		return (0);
	if (cmd->cmd[1] != NULL)
	{
		j = 0;
		while (cmd->cmd[++j])
		{
			if (ft_export_err_equal(cmd->cmd[j]) || ft_export_err(cmd->cmd[j]))
				return (1);
			if (ft_strnstr(cmd->cmd[j], "==", ft_strlen(cmd->cmd[j])))
				continue ;
			ft_sub_sub_export(vars, cmd, j);
		}
		return (1);
	}
	ft_sub_export(vars, i, cmd);
	return (1);
}
