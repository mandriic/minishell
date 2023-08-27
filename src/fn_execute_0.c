/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_execute_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:26:04 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/27 19:27:56 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_run_bltn(t_command *temp_cmd, t_vars *vars)
{
	if (ft_strncmp("export", temp_cmd->cmd[0], 6) == 0)
		ft_export(vars, temp_cmd);
	else if (ft_strncmp("unset", temp_cmd->cmd[0], 5) == 0)
		ft_unset(vars, temp_cmd);
	else if (ft_strncmp("cd", temp_cmd->cmd[0], 2) == 0)
		ft_cd(vars, temp_cmd);
	else
		ft_execuve(NULL, temp_cmd, vars);
}

void	ft_if_path_true(char *cmd_path, t_command *temp_cmd, t_vars *vars)
{
	char	*temp;

	temp = cmd_path;
	cmd_path = ft_strjoin(cmd_path, "/");
	free(temp);
	temp = cmd_path;
	cmd_path = ft_strjoin(cmd_path, temp_cmd->cmd[0]);
	free(temp);
	ft_get_dollar(vars, temp_cmd);
	ft_execuve(cmd_path, temp_cmd, vars);
	free(cmd_path);
}

void	ft_exec(t_command *temp_cmd, t_vars *vars)
{
	char	*path;
	char	*cmd_path;

	path = ft_get_val("PATH", vars->env_var);
	cmd_path = ft_pars_path(path, temp_cmd->cmd[0], 5, vars);
	if (temp_cmd->cmd[0] && !cmd_path && \
		(temp_cmd->cmd[0][0] == '.' || temp_cmd->cmd[0][0] == '/'))
		ft_execuve(temp_cmd->cmd[0], temp_cmd, vars);
	else if (cmd_path)
		ft_if_path_true(cmd_path, temp_cmd, vars);
	else if (temp_cmd->cmd[0])
	{
		ft_putstr_fd("Minishel: ", 2);
		ft_putstr_fd(temp_cmd->cmd[0], 2);
		ft_print_err(vars, ": command not found\n", 127, 2);
	}
}

void	ft_mi_exec(t_vars *vars)
{
	t_command	*temp_cmd;
	int			check;

	temp_cmd = vars->cmd_list;
	while (temp_cmd != NULL && temp_cmd->cmd)
	{
		check = ft_check_if_vars_asign(temp_cmd, vars);
		if (check == 2)
			continue ;
		else if (check == 1)
			break ;
		if (ft_check_if_builtins_true(vars, temp_cmd))
			ft_run_bltn(temp_cmd, vars);
		else
			ft_exec(temp_cmd, vars);
		temp_cmd = temp_cmd->next;
	}
}
