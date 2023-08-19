/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:00:02 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/19 18:35:11 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(t_vars *vars, t_command *cmd)
{
	int	i;

	(void)vars;
	(void)cmd;
	i = 0;
	while (vars->env_var[i] != NULL)
	{
		if (ft_strncmp(vars->env_var[i], "PWD=", 4) == 0)
			printf("%s\n", vars->env_var[i] + 4);
		i++;
	}
	return (1);
}
