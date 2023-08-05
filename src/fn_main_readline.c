/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_main_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:14:18 by mandriic          #+#    #+#             */
/*   Updated: 2022/09/30 16:14:20 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// Chequear variable de entorno SHLVL y sumarle 1
void	ft_check_shlvl(t_vars *vars)
{
	char	*shlvl;
	char	*temp;
	int		int_shlvl;

	shlvl = ft_get_value("SHLVL", vars->env_var);
	printf("shlvl: %s\n", shlvl);
	
	// shlvl = shlvl + 1;
	// printf("shlvl: %s\n", shlvl);
	if (shlvl)
	{
		printf( "inttest %d\n", ft_atoi(shlvl) + 1);
		temp = ft_itoa(ft_atoi(shlvl) + 1);
		ft_change_env(vars, "SHLVL=", temp, 6);
	}
	free(temp);
	// else
	// 	setenv("SHLVL", "1", 1);
}

void	ft_readline(t_vars *vars)
{
	ft_check_shlvl(vars); // Chequear variable de entorno SHLVL y sumarle 1
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

void	ft_submain(t_vars *vars) // main funcion while (1)
{
	while (1)
	{
		vars->line = readline("Minishell $ "); // readline devuelve no parseado string
		printf("line: %s\n", vars->line);
		if (!ft_strncmp ("exit", vars->line, ft_strlen(vars->line))) //esta funcion es temporal, hace exit si linea es vacia, estoy usando cuando busco leaks

		{
			write(1, "exit\n", 5);
			system("leaks minishell");
			exit (0);
		}
		if (ft_pre_check(vars)) // checkea si linea contiene caracteres permitidos (hay que hacerlo mejor)
			continue ;
		add_history(vars->line); // funcion de readline
		vars->line_len = ft_strlen(vars->line);
		vars->type = ft_mask(vars->line, vars, 1); // devuelve un array de int con los tipos de comillas, pipes, etc (imprimibles o no) no hay que cambiar nada puede explotar
		if (vars->type != NULL)
		{
			ft_line_exist(vars); //puro parsing, si hace falta cambiar algo, mejor que hablas conmigo
			ft_mi_exec(vars); // ejecuta los comandos, aqui si que tienes que trabajar
			ft_end_of_cicle(vars); //libera memoria despues del circulo, no hay que cambiar nada
		}
		else
			ft_end_of_cicle(vars);
		// ft_jose(vars);
		// printf("%s\n", vars->cmd_list->cmd_splited[0]);
		// ft_print_dp(vars->cmd_list->next->cmd, "vars->cmd_list->cmd");
	}
}
