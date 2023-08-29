/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_execute_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:02:46 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/28 13:06:58 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_e_status;

char	*ft_last_redir(char **redirs, t_vars *vars, int outfile)
{
	int	i;

	i = 0;
	while (redirs[i])
	{
		if (outfile == 1)
			ft_check_if_exists(redirs[i], vars);
		if (access(redirs[i], F_OK) == 0 || outfile == 1)
			i++;
		else if (access(redirs[i], F_OK) == -1 && outfile != 1)
		{
			ft_putstr_fd(redirs[i], 2);
			ft_print_err(vars, ": No such file or directory\n", 1, 2);
		}
	}
	return (redirs[i - 1]);
}

void	free_from_dupfile(int *mask, t_command *cmd)
{
	free(mask);
	free(cmd->str_raw);
}

int	ft_if_outfile(char **outfiles, t_command *cmd, t_vars *vars, int *mask)
{
	char	*test_infile;
	int		fd_infile;

	(void)outfiles;
	test_infile = ft_last_redir(cmd->outfiles, vars, 1);
	if (!test_infile)
		return (1);
	fd_infile = open(ft_last_redir(cmd->outfiles, vars, 1), \
	O_TRUNC | O_CREAT | O_RDWR, 0664);
	if (fd_infile < 0)
	{
		if (!cmd->infiles)
		{
			ft_putstr_fd("Minishel: ", 2);
			ft_putstr_fd(cmd->outfiles[0], 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
		g_e_status = 1;
		free_from_dupfile(mask, cmd);
		exit (g_e_status);
	}
	dup2(fd_infile, 1);
	close(fd_infile);
	return (0);
}

void	ft_if_heredoc(t_command *cmd)
{
	int	i2;

	i2 = -1;
	pipe(cmd->fd);
	close(cmd->fd[1]);
	dup2(cmd->fd[0], 0);
	close(cmd->fd[0]);
	while (cmd->heredocs[++i2])
	{
		ft_putstr_fd(cmd->heredocs[i2], 1);
		ft_putstr_fd("\n", 1);
	}
}

void	ft_if_infile(char **infiles, t_command *cmd, t_vars *vars, int *mask)
{
	char	*test_infile;
	int		fd_infile;

	(void)infiles;
	test_infile = ft_last_redir(cmd->infiles, vars, 0);
	if (!test_infile)
		g_e_status = 1;
	fd_infile = open(test_infile, O_RDONLY);
	if (fd_infile < 0)
		g_e_status = 1;
	if (fd_infile < 0)
	{
		ft_putstr_fd(cmd->infiles[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_e_status = 1;
		free_from_dupfile(mask, cmd);
		exit(g_e_status);
	}
	dup2(fd_infile, 0);
	close(fd_infile);
}
