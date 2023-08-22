/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:58:20 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/19 18:36:27 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(t_vars *vars, t_command *cmd)
{
	int	i;

	(void)cmd;
	i = 0;
	while (vars->env_var[i] != NULL)
	{
		ft_putstr_fd(vars->env_var[i++], 1);
		ft_putstr_fd("\n", 1);
	}
	return (1);
}
