/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:00:19 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/26 17:35:19 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_export_err_equal(t_command *cmd)
{
	size_t		temp3;
	int			i;

	i = -1;
	temp3 = 0;
	while (cmd->cmd[1][++i])
	{
		if (cmd->cmd[1][i] == '=')
			temp3++;
	}
	if (temp3 == ft_strlen(cmd->cmd[1]))
	{
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_e_status = 1;
		return (1);
	}
	return (0);
}

void	ft_put_err(char *str)
{
	ft_putstr_fd("Minishell: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	g_e_status = 1;
}

int	ft_export_err(t_command *cmd)
{
	char		**temp2;
	size_t		temp3;
	int			i;
	int			j;

	temp2 = ft_split(cmd->cmd[1], '=');
	i = -1;
	while (temp2[++i])
	{
		j = -1;
		temp3 = 0;
		while (temp2[i][++j])
		{
			if (ft_isdigit(temp2[i][j]))
				temp3++;
			if (i == 0 && (!ft_isalnum(temp2[i][j])
				|| temp3 == ft_strlen(temp2[0])))
			{
				ft_put_err(cmd->cmd[1]);
				return (1);
			}
		}
	}
	return (0);
}

void	ft_sub_export(t_vars *vars, int i)
{
	int		j;

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

int	ft_export(t_vars *vars, t_command *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	if (cmd->cmd[1] != NULL)
	{
		if (ft_export_err_equal(cmd) || ft_export_err(cmd))
			return (1);
		if (ft_strchr(cmd->cmd[1], '=') != NULL)
			vars->env_var = ft_append_to_env(vars, cmd->cmd[1]);
		else if (ft_find_in_temp_env(vars, cmd->cmd[1]) != NULL)
		{
			temp = ft_find_in_temp_env(vars, cmd->cmd[1]);
			vars->env_var = ft_append_to_env(vars, temp);
		}
		return (1);
	}
	ft_sub_export(vars, i);
	return (1);
}
