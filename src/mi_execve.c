/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mi_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:26:04 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/26 17:37:08 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_e_status;

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

char	*ft_pars_path(char *path, char *cmd, int len, t_vars *vars)
{
	int i = len + 1;
	int start = len;
	char *dir;
	char *ifhome = NULL;

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

char	*ft_last_redir(char **redirs, int outfile)
{
	int i = 0;
	int fd;

	while (redirs[i])
	{
		if (outfile == 1)
		{
			fd = open(redirs[i], O_TRUNC | O_CREAT | O_RDWR, 0644);
			if (fd < 0)
			{
				ft_putstr_fd("Minishel: ", 2);
				ft_putstr_fd(redirs[i], 2);
				ft_putstr_fd(": Permission denied\n", 2);
				g_e_status = 1;
				exit(g_e_status);
			}
			close(fd);
		}
		if (access(redirs[i], F_OK) == 0 || outfile == 1)
			i++;
		else if (access(redirs[i], F_OK) == -1 && outfile != 1)
		{
			ft_putstr_fd(redirs[i], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_e_status = 1;
			exit(g_e_status);
		}
	}
	return (redirs[i - 1]);
}
int	ft_what_is_first(char *line, t_vars *vars)
{
	static int i = -1;
	int *mask;

	mask = ft_mask(line, vars, 0);
	printf("mask is %d \n", mask[0]);
	printf("mask is %d \n", mask[1]);
	printf("mask is %d \n", mask[2]);
	printf("mask is %d \n", mask[3]);
	printf("mask is %d \n", mask[4]);
	while (line[++i])
	{
		if (mask[i] == 11 && mask[i + 1] == 10)
		{
			i++;
			return (11);
		}
		if (mask[i] == 10 && line[i] == '<')
			return (10);
	}
	return (0);
}
void	free_from_dupfile(int *mask, t_command *cmd)
{
	free(mask);
	free(cmd->str_raw);
}
int	ft_dup_file(t_command *cmd, t_vars *vars)
{
	char * test_infile;
	int	fd_infile;
	size_t i;
	int *mask;

	mask = ft_mask(cmd->str_raw, vars, 0);
	i = -1;
	while (++i < ft_strlen(cmd->str_raw))
	{
		if (cmd->appends && mask[i] == 11)
		{
			i++;
			fd_infile = open(ft_last_redir(cmd->appends,1), O_APPEND | O_CREAT | O_RDWR, 0664);
			dup2(fd_infile, 1);
			close(fd_infile);
		}
		if (cmd->infiles && mask[i] == 10 && cmd->str_raw[i] == '<')
		{
			test_infile = ft_last_redir(cmd->infiles, 0);
			if (!test_infile)
				g_e_status = 1;
			fd_infile = open(test_infile, O_RDONLY);
			if (fd_infile < 0)
				g_e_status = 1;
			if (fd_infile < 0)
			{
				ft_putstr_fd("check", 1);
				ft_putstr_fd(cmd->infiles[0], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				g_e_status = 1;
				free_from_dupfile(mask, cmd);
				exit(g_e_status);
			}
			dup2(fd_infile, 0);
			close(fd_infile);
		}
		if (cmd->outfiles && mask[i] == 10 && cmd->str_raw[i] == '>')
		{
			test_infile = ft_last_redir(cmd->outfiles, 1);
			if (!test_infile)
				return (1);
			fd_infile = open(ft_last_redir(cmd->outfiles, 1), \
			O_TRUNC | O_CREAT | O_RDWR, 0664);
			if (fd_infile < 0)
			{
				ft_putstr_fd("Minishel: ", 2);
				ft_putstr_fd(cmd->outfiles[0], 2);
				ft_putstr_fd(": Permission denied\n", 2);
				g_e_status = 1;
				free_from_dupfile(mask, cmd);
				exit (g_e_status);
			}
			dup2( fd_infile, 1);
			close(fd_infile);
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

void ft_checkifdir(char *path)
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

void ft_execuve(char *path, t_command *cmd, t_vars *vars)
{
	int	status;
	int	pid;

	pipe(cmd->fd);
	pid = fork();
	if (pid == 0)
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
		else
			exit(g_e_status);
		exit(0);
	}
	else if (pid < 0)
		printf("Error forking \n");
	else if (pid > 0)
	{
		signal(SIGUSR2, SIG_IGN);
		rl_set_prompt("");
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
			{
				perror("waitpid() failed");
				exit(EXIT_FAILURE);
			}
			if (WIFEXITED(status))
				g_e_status = WEXITSTATUS(status);
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
		return (ft_exit(cmd));
	else
		return (0);
}

int ft_check_if_vars(t_vars *vars, t_command *cmd_struct)
{
	char	*temp;
	int		i;

	i = 0;
	while (cmd_struct->cmd[0] && cmd_struct->cmd[0][i])
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
			temp_cmd->cmd[i] = ft_itoa(g_e_status);
		}
		i++;
	}
	return (0);
}

void ft_mi_exec(t_vars *vars)
{
	t_command	*temp_cmd;
	char		*path;
	char		*cmd_path;
	char		*temp;

	temp_cmd = vars->cmd_list;
	while (temp_cmd != NULL && temp_cmd->cmd)
	{
		if(ft_check_if_vars(vars, temp_cmd))
		{
			if (temp_cmd->next)
				continue ;
			else
				break ;
		}
		if (ft_check_if_builtins_true(vars, temp_cmd))
		{
				ft_execuve(NULL, temp_cmd, vars);
		}
		else
		{
			path = ft_get_val("PATH", vars->env_var);
			cmd_path = ft_pars_path(path, temp_cmd->cmd[0], 5, vars);
			if (temp_cmd->cmd[0] && !cmd_path && (temp_cmd->cmd[0][0] == '.' || temp_cmd->cmd[0][0] == '/'))
				ft_execuve(temp_cmd->cmd[0], temp_cmd, vars);
			else if (cmd_path)
			{
				temp = cmd_path;
				cmd_path = ft_strjoin(cmd_path, "/");
				free(temp);
				temp = cmd_path;
				cmd_path = ft_strjoin(cmd_path, temp_cmd->cmd[0]);
				free(temp);
				ft_get_dollar(vars, temp_cmd);
				ft_execuve(cmd_path, temp_cmd, vars);  // ATENTION
				free(cmd_path);
			}
			else if(temp_cmd->cmd[0])
			{
				ft_putstr_fd("Minishel: ", 2);
				ft_putstr_fd(temp_cmd->cmd[0], 2);
				ft_putstr_fd(": command not found\n", 2);
				g_e_status = 127;
			}
		}
		temp_cmd = temp_cmd->next;
	}
}
