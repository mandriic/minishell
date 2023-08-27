/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_execute_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:04:38 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/27 19:26:47 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_e_status;

void	ft_if_appends(t_command *cmd, t_vars *vars)
{
	int	fd_infile;

	fd_infile = open(ft_last_redir(cmd->appends, vars, 1), \
		O_APPEND | O_CREAT | O_RDWR, 0664);
	dup2(fd_infile, 1);
	close(fd_infile);
}

int	ft_dup_file(t_command *cmd, t_vars *vars)
{
	size_t	i;
	int		*mask;

	mask = ft_mask(cmd->str_raw, vars, 0);
	i = -1;
	while (++i < ft_strlen(cmd->str_raw))
	{
		if (cmd->appends && mask[i] == 11)
		{
			ft_if_appends(cmd, vars);
			i++;
		}
		if (cmd->infiles && mask[i] == 10 && cmd->str_raw[i] == '<')
			ft_if_infile(cmd->infiles, cmd, vars, mask);
		if (cmd->outfiles && mask[i] == 10 && cmd->str_raw[i] == '>')
			ft_if_outfile(cmd->outfiles, cmd, vars, mask);
		if (cmd->heredocs && mask[i] == 11)
		{
			ft_if_heredoc(cmd);
			i++;
			return (0);
		}
	}
	free_from_dupfile(mask, cmd);
	return (0);
}

int	ft_redirections(t_command *cmd, t_vars *vars)
{	
	if (ft_dup_file(cmd, vars))
		return (1);
	return (0);
}

void	ft_checkifdir(char *path)
{
	int	dir;

	dir = open(path, O_DIRECTORY | O_RDONLY);
	if (dir > 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		g_e_status = 126;
		exit(g_e_status);
	}
}

void	ft_hijo_exec(t_command *cmd, t_vars *vars, char *path)
{
	if (execve(path, cmd->cmd, vars->env_var) == -1)
	{
		if (path[0] == '/' || path[0] == '.')
		{
			if (access(path, F_OK))
				ft_putstr_fd(strerror(errno), 2);
			else if (access(path, X_OK))
			{
				ft_putstr_fd(" Permission denied\n", 2);
				exit(126);
			}
			else
				ft_putstr_fd("No such file or directory\n", 2);
			exit(127);
		}
		else
		{
			ft_putstr_fd(": command not found\n", 2);
			exit(126);
		}
	}
}
