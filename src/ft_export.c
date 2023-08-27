/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:00:19 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/27 11:56:19 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_export_err_equal(t_vars *vars, char *cmd)
{
	size_t		temp3;
	int			i;

	i = -1;
	temp3 = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '=')
			temp3++;
	}
	if (temp3 == ft_strlen(cmd))
	{
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_e_status = 1;
		return (1);
	}
	return (0);
}

void	ft_put_err( t_vars *vars, char *str)
{
	ft_putstr_fd("Minishell: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	g_e_status = 1;
}

int	ft_export_err(t_vars *vars, char *cmd)
{
	char		**temp2;
	size_t		temp3;
	int			i;
	int			j;

	temp2 = ft_split(cmd, '=');
	i = -1;
	while (temp2[++i])
	{
		j = -1;
		temp3 = 0;
		while (temp2[i][++j])
		{
			if (ft_isdigit(temp2[i][j]))
				temp3++;
			if (i == 0 && (!ft_isalnum(temp2[i][j])
				|| temp3 == ft_strlen(temp2[0])))
			{
				ft_put_err(vars, cmd);
				ft_free_dob_arr(temp2);
				return (1);
			}
		}
	}
	ft_free_dob_arr(temp2);
	return (0);
}

void	ft_sub_export(t_vars *vars, int i, t_command *cmd)
{
	int		j;
	pid_t	pid;
	int status;

	if (cmd->next)
	{
		pipe(cmd->fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(cmd->fd[1], 1);
			close(cmd->fd[0]);	
			if (ft_get_value("OLDPWD", vars->env_var) == 0)
			printf("declare -x OLDPWD\n");
			while (vars->env_var[i])
			{
				j = 0;
				printf("declare -x ");
				while (vars->env_var[i][j] != '=')
				{
					printf("%c", vars->env_var[i][j]);
					j++;
				}
				printf("=\"%s\"\n", vars->env_var[i] + j + 1);
			i++;
			}
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
			// dup2(cmd->fd[0], 0);
			// close(cmd->fd[1]);
		}
		
	}
	else
	{
		if (ft_get_value("OLDPWD", vars->env_var) == 0)
			printf("declare -x OLDPWD\n");
			while (vars->env_var[i])
			{
				j = 0;
				printf("declare -x ");
				while (vars->env_var[i][j] != '=')
				{
					printf("%c", vars->env_var[i][j]);
					j++;
				}
				printf("=\"%s\"\n", vars->env_var[i] + j + 1);
			i++;
			}
	}
		// close(cmd->fd[1]);

}

int	ft_export(t_vars *vars, t_command *cmd)
{
	int		i;
	char	*temp;
	int		j;
	char	*var;
	char	*valor;
	i = 0;
	// ft_print_dp(cmd->cmd, "cmd");
	if (cmd->cmd[1] && cmd->next)
		return(0);
	// printf("cmd->cmd[1]!: %s\n", cmd->cmd[1]);
	if (cmd->cmd[1] != NULL)
	{
		j = 0;
		while(cmd->cmd[++j])
		{
			if (ft_export_err_equal(vars, cmd->cmd[j]) || ft_export_err(vars, cmd->cmd[j]))
				return (1);
			if( ft_strnstr(cmd->cmd[j], "==", ft_strlen(cmd->cmd[j]))) //ft_strchr(cmd->cmd[j], '=') == NULL ||
					continue ;
			// printf("cmd: %s\n", cmd->cmd[j]);
			var = ft_substr(cmd->cmd[j], 0, ft_strlen(cmd->cmd[j]) - ft_strlen(ft_strchr(cmd->cmd[j], '=')));
			valor = ft_substr(cmd->cmd[j], ft_strlen(cmd->cmd[j]) - ft_strlen(ft_strchr(cmd->cmd[j], '=')), ft_strlen(ft_strchr(cmd->cmd[j], '=')));
			// printf("var: %s\n", var);
			// printf("valor: %s\n", valor);

			if (ft_find_in_env(vars, var) == 0)
				{
				// printf("check1\n");
				vars->env_var = ft_append_to_env(vars, cmd->cmd[j]);
				}
			else if (ft_find_in_env(vars, var) != 0)
			{
				// printf("check finded\n");
				ft_change_env(vars, var, valor, ft_strlen(var));
			}

			else if (ft_find_in_temp_env(vars, cmd->cmd[j]) != NULL)
			{
				// printf("check2\n");
				temp = ft_find_in_temp_env(vars, cmd->cmd[j]);
				vars->env_var = ft_append_to_env(vars, temp);
			}
			free(var);
			free(valor);
		}
		return (1);
	}
	ft_sub_export(vars, i, cmd);
	return (1);
}
