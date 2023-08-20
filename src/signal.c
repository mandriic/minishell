/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:55:10 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/20 16:40:21 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int g_e_status;

void	ft_singint_hand(int sig)
{
	struct termios	prompt_conf;

	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_e_status = 127 + sig;
		signal(SIGINT, ft_singint_hand);
	}
	tcgetattr(STDIN_FILENO, &prompt_conf);
	prompt_conf.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &prompt_conf);
}



