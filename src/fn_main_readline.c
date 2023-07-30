/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_main_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:14:18 by mandriic          #+#    #+#             */
/*   Updated: 2023/07/29 19:42:42 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_check_shlvl(t_vars *vars)
{
	char	*shlvl;
	char	*temp;
	int		int_shlvl;

	(void)int_shlvl;(void)temp;
	shlvl = ft_get_value("SHLVL", vars->env_var);
	// printf("shlvl: %s\n", shlvl);
	
	// shlvl = shlvl + 1;
	// printf("shlvl: %s\n", shlvl);
	if (shlvl)
	{
		// printf( "inttest %d\n", ft_atoi(shlvl) + 1);
		temp = ft_itoa(ft_atoi(shlvl) + 1);
		ft_change_env(vars, "SHLVL=", temp, 6);
		free(temp);
	}
	// free(temp);
	// else
	// 	setenv("SHLVL", "1", 1);
}

void	ft_readline(t_vars *vars)
{
	ft_check_shlvl(vars);
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

//Anush has added  to check if the line is empty or not
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
	while (1)
	{
		vars->line = readline("Minishell $ "); 
		//printf("line: %s\n", vars->line);
		//Sirus´s code comented , it works for exit, but it doesnt work for enter
		/*if (!ft_strncmp ("exit", vars->line, ft_strlen(vars->line)))
		{
			write(1, "exit\n", 5);
			system("leaks minishell");
			exit (0);
		}*/
		if (vars->line && ft_strncmp(" ", vars->line, ft_strlen(vars->line) == 0))
			continue ; //this helps to get off the leaks when you try to exit the program
		if (vars->line == NULL)
		{
			//signal(SIGTERM, handler_ctrl_d);
			printf("exit\n"); //coregir para que escriba exit bien
			// system("leaks minishell");
			free(vars->line);
			exit(0);
		}
		//this one is also Sirus code
		if (ft_pre_check(vars)) //|| ft_check_rl(vars))
		{
			// free(vars->line);
			continue ;

		}
		if (vars->line)
		
			add_history(vars->line);
		vars->line_len = ft_strlen(vars->line);
		vars->type = ft_mask(vars->line, vars, 1);
		if (vars->type != NULL)
			ft_line_exist(vars);
		// ft_jose(vars);
		// printf("%s\n", vars->cmd_list->cmd_splited[0]);
		// ft_print_dp(vars->cmd_list->next->cmd, "vars->cmd_list->cmd");
		ft_mi_exec(vars);
		ft_end_of_cicle(vars);
	}
}
