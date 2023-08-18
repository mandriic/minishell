/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:18:52 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/18 15:20:16 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

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
