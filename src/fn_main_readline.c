/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_main_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:22:00 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/26 16:42:41 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_check_shlvl(t_vars *vars)
{
	char	*shlvl;
	char	*temp;

	shlvl = ft_get_value("SHLVL", vars->env_var);
	if (shlvl)
	{
		temp = ft_itoa(ft_atoi(shlvl) + 1);
		ft_change_env(vars, "SHLVL=", temp, 6);
		free(temp);
	}
}

void	ft_readline(t_vars *vars)
{
	ft_check_shlvl(vars);
	ft_submain(vars);
}

void	ft_line_exist(t_vars *vars)
{
	vars->num_pipes = ft_numpipes(vars->line, vars->type);
	if (vars->num_pipes)
		vars->split = spliting(vars->line, vars->type, vars->num_pipes, vars);
	else
	{
		free(vars->type);
		vars->type = NULL;
		ft_triming(&vars->line, 0, vars, 1);
	}
	ft_lst_cmd(vars);
}

int	ft_check_rl(t_vars *vars)
{
	if (vars->line == NULL)
	{
		free(vars->line);
		rl_clear_history();
		exit(0);
	}
	if (vars->line[0] == '\0')
	{
		rl_on_new_line();
		return (1);
	}
	return (0);
}

void	ft_submain(t_vars *vars)
{
	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_singint_hand);
		vars->line = readline("Minishell $ ");
		if (vars->line && ft_strncmp(" ", vars->line,
				ft_strlen(vars->line) == 0))
			continue ;
		if (vars->line == NULL)
			ft_exit_mini(vars);
		if (ft_pre_check(vars))
			continue ;
		if (vars->line)
			add_history(vars->line);
		vars->line_len = ft_strlen(vars->line);
		vars->type = ft_mask(vars->line, vars, 1);
		if (vars->type != NULL)
			ft_line_exist(vars);
		ft_mi_exec(vars);
		ft_end_of_cicle(vars);
	}
}
