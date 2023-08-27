/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_execute_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:19:08 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/27 19:33:11 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_e_status;

int	ft_check_if_builtins(t_vars *vars, t_command *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0 && ft_strlen(cmd->cmd[0]) == 4)
		return (ft_echo(vars, cmd));
	else if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0
		&& ft_strlen(cmd->cmd[0]) == 2)
		return (ft_cd(vars, cmd));
	else if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0
		&& ft_strlen(cmd->cmd[0]) == 3)
		return (ft_pwd(vars, cmd));
	else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0
		&& ft_strlen(cmd->cmd[0]) == 6)
		return (ft_export(vars, cmd));
	else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0
		&& ft_strlen(cmd->cmd[0]) == 5)
		return (ft_unset(vars, cmd));
	else if (ft_strncmp(cmd->cmd[0], "env", 3) == 0
		&& ft_strlen(cmd->cmd[0]) == 3)
		return (ft_env(vars, cmd));
	else if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0
		&& ft_strlen(cmd->cmd[0]) == 4)
		return (ft_exit(cmd));
	else
		return (0);
}

char	**ft_get_name_val(t_command *cmd_struct, int j)
{
	char	**name_val;

	name_val = malloc((sizeof(char *)) * 3);
	name_val[0] = ft_substr(cmd_struct->cmd[j], 0, \
		ft_strlen(cmd_struct->cmd[j]) \
		- ft_strlen(ft_strchr(cmd_struct->cmd[j], '=')));
	name_val[1] = ft_substr(cmd_struct->cmd[j], ft_strlen(cmd_struct->cmd[j]) \
		- ft_strlen(ft_strchr(cmd_struct->cmd[j], '=')),
			ft_strlen(ft_strchr(cmd_struct->cmd[j], '=')));
	name_val[2] = NULL;
	return (name_val);
}

int	ft_check_if_vars(t_vars *vars, t_command *cmd_struct)
{
	int		j;
	char	**name_val;

	j = -1;
	while (cmd_struct->cmd[++j])
	{
		if (ft_strchr(cmd_struct->cmd[j], '='))
		{
			name_val = ft_get_name_val(cmd_struct, j);
			if (ft_find_in_env(vars, name_val[0]) != 0)
				ft_change_env(vars, name_val[0], name_val[1], \
					ft_strlen(name_val[0]));
			else if (ft_find_in_temp_env(vars, name_val[0]) == 0)
				vars->temp_env = ft_append_to_temp_env(vars, \
				cmd_struct->cmd[j]);
			else
				ft_change_temp_env(vars, name_val[0], name_val[1], \
					ft_strlen(name_val[0]));
			ft_free_dob_arr(name_val);
			if (cmd_struct->cmd[j + 1] == NULL)
				return (1);
		}
	}
	return (0);
}

int	ft_get_dollar(t_vars *vars, t_command *temp_cmd)
{
	int	i;

	(void)vars;
	i = 1;
	while (temp_cmd->cmd[i])
	{
		if (ft_strncmp(temp_cmd->cmd[i], "$?", 2) == 0)
		{
			free(temp_cmd->cmd[i]);
			temp_cmd->cmd[i] = ft_itoa(g_e_status);
		}
		i++;
	}
	return (0);
}

int	ft_check_if_vars_asign(t_command *temp_cmd, t_vars *vars)
{
	char	**temp2;

	if (ft_strncmp("0x0", temp_cmd->cmd[0], 3) == 0)
	{
		temp2 = temp_cmd->cmd;
		temp_cmd->cmd = ft_dupl_dp(temp_cmd->cmd + 1);
		ft_free_dob_arr(temp2);
	}			
	if (ft_check_if_vars(vars, temp_cmd) && ft_strchr(temp_cmd->cmd[0], '='))
	{
		if (temp_cmd->next)
			return (2);
		else
			return (1);
	}
	return (0);
}
