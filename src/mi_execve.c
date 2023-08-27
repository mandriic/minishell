/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mi_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:26:04 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/27 17:48:24 by mandriic         ###   ########.fr       */
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

char	*ft_sub_pars(char *path, char *ifhome, char *cmd, int *i, int *start)
{
	char *dir;

	dir = malloc(sizeof(char) * (*i - *start + 1));
	ft_strlcpy(dir, path + *start, *i - *start + 1);
	*start = *i + 1;
	if (ifhome)
	{
		if (dir)
			free(dir);
		dir = ft_strjoin(ifhome, dir);
	}
	if (ft_check_dir(dir, cmd, ft_strlen(cmd)) == 1)
		return (dir);
	free(dir);
	return(NULL);
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
			dir = ft_sub_pars(path, ifhome, cmd, &i, &start);
			if (dir)
				return (dir);
		}
		i++;
	}
	return (0);
}

void	ft_print_err(t_vars *vars, char *err_str, int err, int io_err)
{
	ft_putstr_fd(err_str, io_err);
	if (err != -1)
	{
		g_e_status = err;
		exit(g_e_status);
	}
}
void	ft_check_if_exists(char *str, t_vars *vars)
{
	int	fd;

	fd = open(str, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd < 0)
	{
		ft_print_err(vars, "Minishel: ", -1, 2);
		ft_print_err(vars, str, -1, 2);
		ft_print_err(vars, ": Permission denied\n", 1, 2);
	}
	close(fd);
}

char	*ft_last_redir(char **redirs, t_vars *vars, int outfile)
{
	int	i;
	int	fd;

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

	test_infile = ft_last_redir(cmd->outfiles, vars, 1);
	if (!test_infile)
		return (1);
	fd_infile = open(ft_last_redir(cmd->outfiles, vars, 1), \
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
	return (0);
}
void	ft_if_heredoc(t_command *cmd)
{
	int i2;
				
	i2= -1;
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
void	ft_if_appends(t_command *cmd, t_vars *vars)
{
	int	fd_infile;

	fd_infile = open(ft_last_redir(cmd->appends, vars, 1),\
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

void 	ft_wait(t_command *cmd, int pid)
{
	int status;
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

void ft_execuve(char *path, t_command *cmd, t_vars *vars)
{
	int	status;
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
char	**ft_get_name_val(t_command *cmd_struct, int j)
{
	char **name_val;

	name_val = malloc((sizeof(char *)) * 3);
	name_val[0] = ft_substr(cmd_struct->cmd[j], 0, ft_strlen(cmd_struct->cmd[j])\
		- ft_strlen(ft_strchr(cmd_struct->cmd[j], '=')));
	name_val[1] = ft_substr(cmd_struct->cmd[j], ft_strlen(cmd_struct->cmd[j])\
		- ft_strlen(ft_strchr(cmd_struct->cmd[j], '=')), 
			ft_strlen(ft_strchr(cmd_struct->cmd[j], '=')));
	name_val[2] = NULL;
	return (name_val);

}
int ft_check_if_vars(t_vars *vars, t_command *cmd_struct)
{
	char	*temp;
	int		j;
	char **name_val;
	
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
				ft_change_temp_env(vars,name_val[0], name_val[1], ft_strlen(name_val[0]));
			ft_free_dob_arr(name_val);
			if (cmd_struct->cmd[j + 1] == NULL)
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
int	ft_check_if_vars_asign(t_command *temp_cmd, t_vars *vars)
{
	char	**temp2;

	if (ft_strncmp("0x0", temp_cmd->cmd[0], 3) == 0)
	{
		temp2 = temp_cmd->cmd;
		temp_cmd->cmd = ft_dupl_dp(temp_cmd->cmd + 1);
		ft_free_dob_arr(temp2);			
	}			
	if(ft_check_if_vars(vars, temp_cmd) && ft_strchr(temp_cmd->cmd[0], '=')) //&& ft_strncmp("export", temp_cmd->cmd[0], 6) != 0 
	{
		if (temp_cmd->next)
			return(2) ;
		else
			return (1) ;
	}
	return (0);
}
// ret1 - cont, ret0 - break

void 	ft_run_bltn(t_command *temp_cmd, t_vars *vars)
{
		// if (temp_cmd->next != NULL)
	if (ft_strncmp("export", temp_cmd->cmd[0], 6) == 0)
		ft_export(vars, temp_cmd);
	else if (ft_strncmp("unset", temp_cmd->cmd[0], 5) == 0)
		ft_unset(vars, temp_cmd);
	else if (ft_strncmp("cd", temp_cmd->cmd[0], 2) == 0)
		ft_cd(vars, temp_cmd);
	else 				
		ft_execuve(NULL, temp_cmd, vars); // ATENTION
}

void	ft_if_path_true(char *cmd_path, t_command *temp_cmd, t_vars *vars)
{
	char *temp;

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

void	ft_exec(t_command *temp_cmd, t_vars *vars)
{
	char *path;
	char *cmd_path;
	char *temp;

	path = ft_get_val("PATH", vars->env_var);
	cmd_path = ft_pars_path(path, temp_cmd->cmd[0], 5, vars);
	if (temp_cmd->cmd[0] && !cmd_path && \
		(temp_cmd->cmd[0][0] == '.' || temp_cmd->cmd[0][0] == '/'))
		ft_execuve(temp_cmd->cmd[0], temp_cmd, vars);
	else if (cmd_path)
	{
		ft_if_path_true(cmd_path, temp_cmd, vars);
		// temp = cmd_path;
		// cmd_path = ft_strjoin(cmd_path, "/");
		// free(temp);
		// temp = cmd_path;
		// cmd_path = ft_strjoin(cmd_path, temp_cmd->cmd[0]);
		// free(temp);
		// ft_get_dollar(vars, temp_cmd);
		// ft_execuve(cmd_path, temp_cmd, vars);  // ATENTION
		// free(cmd_path);
	}
	else if(temp_cmd->cmd[0])
	{
		ft_putstr_fd("Minishel: ", 2);
		ft_putstr_fd(temp_cmd->cmd[0], 2);
		ft_print_err(vars, ": command not found\n", 127, 2);
	}
}

void ft_mi_exec(t_vars *vars)
{
	t_command	*temp_cmd;
	char	*path;
	char	*cmd_path;
	char    *temp;
	int 	check;

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
		{
			ft_exec(temp_cmd, vars);
			// path = ft_get_val("PATH", vars->env_var);
			// cmd_path = ft_pars_path(path, temp_cmd->cmd[0], 5, vars);
			// if (temp_cmd->cmd[0] && !cmd_path && (temp_cmd->cmd[0][0] == '.' || temp_cmd->cmd[0][0] == '/'))
			// 	ft_execuve(temp_cmd->cmd[0], temp_cmd, vars);
			// else if (cmd_path)
			// {
			// 	temp = cmd_path;
			// 	cmd_path = ft_strjoin(cmd_path, "/");
			// 	free(temp);
			// 	temp = cmd_path;
			// 	cmd_path = ft_strjoin(cmd_path, temp_cmd->cmd[0]);
			// 	free(temp);
			// 	ft_get_dollar(vars, temp_cmd);
			// 	ft_execuve(cmd_path, temp_cmd, vars);  // ATENTION
			// 	free(cmd_path);
			// }
			// else if(temp_cmd->cmd[0])
			// {
			// 	ft_putstr_fd("Minishel: ", 2);
			// 	ft_putstr_fd(temp_cmd->cmd[0], 2);
			// 	ft_putstr_fd(": command not found\n", 2);
			// 	g_e_status = 127;
			// }
		}
		temp_cmd = temp_cmd->next;
	}
}
