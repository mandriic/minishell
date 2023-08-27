/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:59:00 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/20 15:46:06 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_e_status;


int	ft_unset(t_vars *vars, t_command *cmd)
{
	if (cmd->cmd[1] != NULL)
	{
		if (ft_get_value(cmd->cmd[1], vars->env_var) != NULL)
		{
			// ft_change_env(vars, cmd->cmd[1], "", ft_strlen(cmd->cmd[1]));
			ft_del_from_dob_arr(vars, cmd->cmd[1], &vars->env_var);
			g_e_status = 0;
			return (1);
		}
		else if (ft_get_value(cmd->cmd[1], vars->temp_env) != NULL)
		{
			ft_change_temp_env(vars, cmd->cmd[1], "", ft_strlen(cmd->cmd[1]));
			g_e_status = 0;
			return (1);
		}
	}
	return (1);
}
