/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:59:00 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/27 20:35:31 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_e_status;

int	ft_unset(t_vars *vars, t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[++i])
	{
		if (cmd->cmd[i] != NULL)
		{
			if (ft_get_value(cmd->cmd[i], vars->env_var) != NULL)
			{
				ft_del_from_dob_arr(cmd->cmd[i], &vars->env_var);
				g_e_status = 0;
			}
			if (ft_get_value(cmd->cmd[i], vars->temp_env) != NULL)
			{
				ft_change_temp_env(vars, cmd->cmd[i], \
				"", ft_strlen(cmd->cmd[1]));
				g_e_status = 0;
			}
		}
	}
	return (1);
}
