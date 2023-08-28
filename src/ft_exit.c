/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:17:35 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/28 12:55:12 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_e_status;

int	ft_doublen(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int	ft_issing(char c)
{
	return (c == '-' || c == '+');
}

int	ft_isnum_exit(char *str)
{
	int	i;

	i = 0;
	if (ft_issing(str[i]) || ft_isdigit(str[i]))
		i++;
	else
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_exit_errors(t_command *cmd, __int128_t	num)
{
	if (cmd->cmd[1])
	{
		num = ft_atoll(cmd->cmd[1]);
		if (ft_doublen(cmd->cmd) > 2)
		{
			ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
			g_e_status = 1;
			return (1);
		}
		else if (!ft_isnum_exit(cmd->cmd[1])
			|| (num > LLONG_MAX || num < LLONG_MIN))
		{
			ft_putstr_fd("Minishell: exit: ", 2);
			ft_putstr_fd(cmd->cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		else
			exit(num);
	}
	return (0);
}

int	ft_exit(t_command *cmd)
{
	__int128_t	num;

	num = 0;
	if (ft_exit_errors(cmd, num))
		return (1);
	else
	{
		exit(g_e_status);
	}
	return (0);
}
