/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_main_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:14:18 by mandriic          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/07 19:33:05 by angalsty         ###   ########.fr       */
=======
/*   Updated: 2023/05/18 20:14:35 by angalsty         ###   ########.fr       */
>>>>>>> b447e562ae4c366cc6354a5d8bdd187107f881fe
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	 ft_readline(t_vars *vars)
{
	// vars = (t_vars){};
	// vars.split = NULL;
	// // vars.list = NULL;
	// vars.line = NULL;
	// vars.quotes  = "'";
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

void	ft_submain(t_vars *vars)
{
	while (1)
	{
		vars->line = readline("Minishell $ ");
		if (!ft_strncmp("exit", vars->line, ft_strlen(vars->line)))
		{
			write(1, "exit\n", 5);
			system("leaks minishell");
			exit(0);
		}
		if (ft_pre_check(vars))
			continue ;
		add_history(vars->line);
		vars->line_len = ft_strlen(vars->line);
		vars->type = ft_mask(vars->line, vars, 1);
		if (vars->type != NULL)
			ft_line_exist(vars);
		// ft_jose(vars);
		// printf("%s\n", vars->cmd_list->cmd_splited[0]);
		// ft_print_dp(vars->cmd_list->pre_args, "vars->cmd_list->cmd");
<<<<<<< HEAD
		printf("sdfsdffss %s\n", vars->cmd_list->cmd[0]);
		printf("sdfsdffss %s\n", vars->cmd_list->cmd[1]);
		printf("sdfsdffss %s\n", vars->cmd_list->cmd[2]);
		ft_mi_exec(vars);
=======
		ft_mi_exec(vars, vars->env_var);
>>>>>>> b447e562ae4c366cc6354a5d8bdd187107f881fe
		ft_end_of_cicle(vars);
	}
}
