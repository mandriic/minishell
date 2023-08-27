/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:36:41 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/27 15:21:14 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_e_status;

void	ft_singint_hand(int sig)
{
	if (sig == SIGINT)
	{
		g_e_status = 130;
		printf("\n");
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ft_exit_mini(t_vars *vars)
{
	printf("exit\n");
	free(vars->line);
	exit(0);
}
