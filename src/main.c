/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:18:52 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/20 15:30:27 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	vars = (t_vars){};
	vars.split = NULL;
	vars.cmd_list = NULL;
	vars.error = 0;
	vars.line = NULL;
	vars.quotes = "'";
	vars.temp_env = NULL;
	vars.env_var = ft_dupl_dp(envp);
	ft_readline(&vars);
}
