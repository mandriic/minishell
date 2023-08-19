/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mi_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:26:04 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/19 20:00:56 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_get_val(char *str, char **env)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
			return (env[i]);
		i++;
	}
	return (0);
}

int	ft_check_dir(char *dir, char *cmd, size_t len)
{
	DIR				*d;
	struct dirent	*dirr;

	d = opendir(dir);
	if (!d)
		return (0);
	if (d)
	{
		while ((dirr = readdir(d)) != NULL)
		{
			if (ft_strncmp(dirr->d_name, cmd, len) == 0
				&& ft_strlen(dirr->d_name) == len)
			{
				closedir(d);
				return (1);
			}
		}
		closedir(d);
	}
	return (0);
}

char *ft_pars_path(char *path, char *cmd, int len, t_vars *vars) //char *
{
	int		i;
	int		start;
	char	*dir;
	char	*ifhome;

	i = len + 1;
	ifhome = NULL;
	start = len;
	while (path[i])
	{
		if (path[i] == '~')
		{
			ifhome = ft_get_val("HOME", vars->env_var);
			ifhome = ifhome + 5;
			i++;
			start++;
		}
		if (path[i] == ':')
		{
			dir = malloc(sizeof(char) * (i - start + 1));
			ft_strlcpy(dir, path + start, i - start + 1);
			start = i + 1;
			if (ifhome)
			{
				if (dir)
					free(dir);
				dir = ft_strjoin(ifhome, dir);
			}
			if (ft_check_dir(dir, cmd, ft_strlen(cmd)) == 1)
				return (dir);
			free(dir);
		}
		i++;
	}
	return (0);
}


void	ft_dup_infile(t_command *cmd)
{
	int	fd_infile;
	int i;

	i = 0;
	if (cmd->heredocs)
	{
		fd_infile = open("./.temp.txt", O_TRUNC | O_CREAT | O_RDWR, 0664);
		while (cmd->heredocs[i])
		{
			write(fd_infile, cmd->heredocs[i], ft_strlen(cmd->heredocs[i]));
			write(fd_infile, "\n", 1);
			i++;
		}
		fd_infile = open("./.temp.txt", O_RDONLY);
		dup2(fd_infile, 0);
		close(fd_infile);
	}
	else if (cmd->infiles)
	{
		fd_infile = open(cmd->infiles[0], O_RDONLY);
		if (fd_infile < 0)
		{
			perror("fd_infile");
			dup2(fd_infile, 0);
			close(fd_infile);
		}
	}
}


void	ft_dup_outfile(t_command *cmd)
{
	int	fd_outfile;

	if (cmd->appends)
	{
		fd_outfile = open(cmd->appends[0], O_APPEND | O_CREAT | O_RDWR, 0664);
		if (fd_outfile < 0)
			perror("fd_outfile:");
		close(STDOUT_FILENO);
		dup2(fd_outfile, 1);
		close(fd_outfile);
	}
	else if (cmd->outfiles != NULL)
	{
		fd_outfile = open(cmd->outfiles[0], O_TRUNC | O_CREAT | O_RDWR, 0664);
		if (fd_outfile < 0)
			perror("fd_outfile:");
		close(STDOUT_FILENO);
		dup2(fd_outfile, 1);
		close(fd_outfile);
	}
}

void	ft_redirections(t_command *cmd)
{
	ft_dup_infile(cmd);
	ft_dup_outfile(cmd);
}

void ft_execuve(char *path, t_command *cmd, t_vars *vars)
{
	int	status;
	int	pid;

	if (ft_strncmp("exit", cmd->cmd[0], 4) == 0)
		exit(0);
	pipe(cmd->fd);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGUSR2, handle_process_on); //signal to catch
		ft_redirections(cmd); //si es echo no lo hace
		if (cmd->next)
		{
			close(cmd->fd[0]);
			dup2(cmd->fd[1], 1);
			ft_redirections(cmd);
			close(cmd->fd[1]);
		}
		if (cmd->prev && cmd->prev->fd[0] != -1)
		{
			close(cmd->prev->fd[1]);
			dup2(cmd->prev->fd[0], 0);
			ft_redirections(cmd);
			close(cmd->prev->fd[0]);
		}
		if (ft_check_if_builtins(vars, cmd) == 0)
		{
			if (execve(path, cmd->cmd, vars->env_var) == -1)
			{
				printf("Minishell: command not found: %s \n", cmd->cmd[0]);
				exit(0);
			}
		}
		exit(0);
	}
	else if (pid < 0)
		printf("Error forking \n");
	else if (pid > 0)
	{
		signal(SIGUSR2, SIG_IGN); //signal to ignore
		rl_set_prompt("");
		if (cmd->prev && cmd->prev->fd[0] != -1)
		{
			close(cmd->prev->fd[0]);
			close (cmd->prev->fd[1]);//added after to heck the signals
		}
		if (cmd->prev && cmd->prev->fd[1] != -1)
		{
			close(cmd->prev->fd[1]);
			close (cmd->prev->fd[0]);//added after to check the signals
		}
		if (cmd->next == NULL) // it prints only the last command
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				vars->error = WEXITSTATUS(status);
			}
		}
	}
}

int ft_check_if_builtins_true(t_vars *vars, t_command *cmd)
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

int ft_check_if_builtins(t_vars *vars, t_command *cmd)
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
		return (ft_exit(vars, cmd));
	else
		return (0);
}

int ft_check_if_vars(t_vars *vars, t_command *cmd_struct)
{
	char	*temp;
	int		i;

	i = 0;
	while (cmd_struct->cmd[0][i])
	{
		if (cmd_struct->cmd[0][i++] == '=')
		{
			temp = ft_substr(cmd_struct->cmd[0], 0, i);
			if (ft_change_env(vars, temp, cmd_struct->cmd[0] + i, \
				ft_strlen(cmd_struct->cmd[0]) - i) == 0)
				vars->temp_env = ft_append_to_temp_env(vars, \
				cmd_struct->cmd[0]);
			free(temp);
			return (1);
		}
	}
	return (0);
}

int   ft_get_dollar(t_vars *vars, t_command *temp_cmd)
{
	int	i;

	(void)vars;
	i = 1;
	while (temp_cmd->cmd[i])
	{
		if (ft_strncmp(temp_cmd->cmd[i], "$?", 2) == 0)
		{
			free(temp_cmd->cmd[i]);
			temp_cmd->cmd[i] = ft_itoa(vars->error);
		}
		i++;
	}
	return (0);
}

void ft_sub_sub_exec(t_vars *vars, char *cmd_path, t_command *temp_cmd)
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

void ft_sub_exec(t_vars *vars, t_command *temp_cmd)
{
	char	*path;
	char	*cmd_path;

	path = ft_get_val("PATH", vars->env_var);
	cmd_path = ft_pars_path(path, temp_cmd->cmd[0], 5, vars);
	if (!cmd_path && (temp_cmd->cmd[0][0] == '.'
		|| temp_cmd->cmd[0][0] == '/'))
		ft_execuve(temp_cmd->cmd[0], temp_cmd, vars);
	else if (cmd_path)
		ft_sub_sub_exec(vars, cmd_path, temp_cmd);
	else
	{
		printf("Minishell: command not found: %s \n", temp_cmd->cmd[0]);
		vars->error = 127;
	}
}

void ft_mi_exec(t_vars *vars)
{
	t_command	*temp_cmd;

	temp_cmd = vars->cmd_list;
	while (temp_cmd != NULL && temp_cmd->cmd)
	{
		if (ft_check_if_vars(vars, temp_cmd))
		{
			if (temp_cmd->next)
				continue ;
			else
				break ;
		}
		if (ft_check_if_builtins_true(vars, temp_cmd))
		{
			if (ft_check_if_builtins_true(vars, temp_cmd)
				&& temp_cmd->next != NULL)
				ft_execuve(NULL, temp_cmd, vars);
			else
				ft_check_if_builtins(vars, temp_cmd);
		}
		else
			ft_sub_exec(vars, temp_cmd);
		temp_cmd = temp_cmd->next;
	}
}
