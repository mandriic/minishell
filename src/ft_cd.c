/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:04:25 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/26 17:35:35 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_e_status;

char	*ft_get_value(char *str, char **env)
{
	int	i;

	i = 0;
	if (!str || !env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
		{
			if (ft_strlen(env[i]) == ft_strlen(str))
				return (env[i] + ft_strlen(str));
			else if (env[i][ft_strlen(str)] == '=')
				return (env[i] + ft_strlen(str) + 1);
		}
		i++;
	}
	return (0);
}

int	ft_cd_err(t_command *cmd)
{
	if (chdir(cmd->cmd[1]) == -1)
	{
		perror("Minishel: cd");
		g_e_status = 1;
		return (0);
	}
	return (1);
}

int	ft_cd(t_vars *vars, t_command *cmd)
{
	char	*cdir;

	if (chdir(cmd->cmd[1]) == 0)
	{
		cdir = getcwd(NULL, 0);
		ft_change_env(vars, "OLDPWD=", ft_get_value("PWD", vars->env_var), 6);
		ft_change_env(vars, "PWD=", cdir, 4);
		g_e_status = 0;
		free(cdir);
	}
	else if (cmd->cmd[1] == NULL)
	{
		if (chdir(ft_get_value("HOME", vars->env_var)) == 0)
		{
			cdir = getcwd(NULL, 0);
			ft_change_env(vars, "OLDPWD=", \
			ft_get_value("PWD", vars->env_var), 6);
			ft_change_env(vars, "PWD=", cdir, 4);
			g_e_status = 0;
			free(cdir);
		}
	}
	else if (!ft_cd_err(cmd))
		return (1);
	return (1);
}
