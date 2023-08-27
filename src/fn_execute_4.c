/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_execute_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:12:44 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/27 19:27:31 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_e_status;

void	ft_hijo(t_command *cmd, t_vars *vars, char *path)
{
	if (cmd->next || cmd->outfiles)
	{
		close(cmd->fd[0]);
		dup2(cmd->fd[1], 1);
		close(cmd->fd[1]);
	}
	if (cmd->prev && cmd->prev->fd[0] != -1)
	{
		close(cmd->prev->fd[1]);
		dup2(cmd->prev->fd[0], 0);
		close(cmd->prev->fd[0]);
	}
	if (ft_redirections(cmd, vars))
		exit(g_e_status);
	if (ft_check_if_builtins(vars, cmd) == 0)
	{
		ft_checkifdir(path);
		ft_hijo_exec(cmd, vars, path);
	}
	else
		exit(g_e_status);
	exit(0);
}

void	ft_check_pipes(t_command *cmd)
{
	if (cmd->prev && cmd->prev->fd[0] != -1)
	{
		close(cmd->prev->fd[0]);
		close (cmd->prev->fd[1]);
	}
	if (cmd->prev && cmd->prev->fd[1] != -1)
	{
		close(cmd->prev->fd[1]);
		close (cmd->prev->fd[0]);
	}
}

void	ft_wait(t_command *cmd, int pid)
{
	int	status;

	if (ft_strncmp("cat", cmd->cmd[0], 3) == 0 && cmd->next != NULL)
	{
		waitpid(pid, &status, WNOWAIT);
		g_e_status = 0;
	}
	else if (ft_strncmp("exit", cmd->cmd[0], 4) == 0)
	{
		waitpid(pid, &status, 0);
		g_e_status = WEXITSTATUS(status);
		exit(g_e_status);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			exit(EXIT_FAILURE);
		if (WIFEXITED(status))
			g_e_status = WEXITSTATUS(status);
	}	
}

void	ft_execuve(char *path, t_command *cmd, t_vars *vars)
{
	int	pid;

	pipe(cmd->fd);
	pid = fork();
	if (pid == 0)
		ft_hijo(cmd, vars, path);
	else if (pid < 0)
		printf("Error forking \n");
	else if (pid > 0)
	{
		signal(SIGUSR2, SIG_IGN);
		rl_set_prompt("");
		ft_check_pipes(cmd);
		ft_wait(cmd, pid);
	}
}

int	ft_check_if_builtins_true(t_vars *vars, t_command *cmd)
{
	(void)vars;
	if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0 && ft_strlen(cmd->cmd[0]) == 4)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0
		&& ft_strlen(cmd->cmd[0]) == 2)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0
		&& ft_strlen(cmd->cmd[0]) == 3)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0
		&& ft_strlen(cmd->cmd[0]) == 6)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0
		&& ft_strlen(cmd->cmd[0]) == 5)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "env", 3) == 0
		&& ft_strlen(cmd->cmd[0]) == 3)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0
		&& ft_strlen(cmd->cmd[0]) == 4)
		return (1);
	else
		return (0);
}
