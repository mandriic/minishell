/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:19:48 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/26 16:43:49 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_e_status;

int	ft_echo(t_vars *vars, t_command *cmd)
{
	int	i;

	(void)vars;
	i = 1;
	if (ft_strncmp(cmd->cmd[1], "-n", 2) == 0 && ft_strlen(cmd->cmd[1]) == 2)
		i++;
	while (cmd->cmd[i] != NULL)
	{
		if (ft_strncmp(cmd->cmd[i], "$?", 2) == 0)
			ft_putnbr_fd(g_e_status, 1);
		else if (ft_strncmp(cmd->cmd[i], "$?", 2) != 0
			&& ft_strncmp(cmd->cmd[i], "-n", 2) != 0)
			ft_putstr_fd(cmd->cmd[i], 1);
		if (cmd->cmd[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (cmd->cmd[1] == NULL || (ft_strncmp(cmd->cmd[1], "-n", 2) != 0
			|| ft_strlen(cmd->cmd[1]) != 2))
		printf("\n");
	g_e_status = 0;
	return (1);
}
