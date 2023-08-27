/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:15:10 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/27 20:16:06 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_e_status;

int	ft_export_err_equal(char *cmd)
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

void	ft_put_err(char *str)
{
	ft_putstr_fd("Minishell: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	g_e_status = 1;
}

int	ft_export_err(char *cmd)
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
				ft_put_err(cmd);
				ft_free_dob_arr(temp2);
				return (1);
			}
		}
	}
	ft_free_dob_arr(temp2);
	return (0);
}

void	ft_subhijo_export(t_command *cmd, t_vars *vars, int i, int j)
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

void	ft_export_hijo(t_command *cmd, t_vars *vars, int i, int j)
{
	int	pid;
	int	status;

	pipe(cmd->fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(cmd->fd[1], 1);
		close(cmd->fd[0]);
		ft_subhijo_export(cmd, vars, i, j);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}
