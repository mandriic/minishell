/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_redirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:15:36 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/25 13:44:21 by pepealkalin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_read_here(char **arr, int*fd, int *i, t_command *data)
{
	char	*eofile;
	int		str_cmp;

	eofile = arr[i[0] + 1];
	str_cmp = 1;
	i[1] = -1;
	if (!data->heredocs)
		data->heredocs = malloc(sizeof(char *) * BUFFER_SIZE);
	signal(SIGINT, ft_here_signal);
	while (1)
	{
		data->heredocs[++i[1]] = readline("> ");
		str_cmp = ft_strncmp(eofile, data->heredocs[i[1]], ft_strlen(eofile));
		if (!str_cmp && ft_strlen(data->heredocs[i[1]]) == ft_strlen(eofile))
			break ;
	}
	close(fd[0]);
	close(fd[1]);
	free(data->heredocs[i[1]]);
	data->heredocs[i[1]--] = NULL; 
	i[0]++;
	exit(0);
}

void	ft_heredoc(char **arr, t_command *data, int *i)
{
	int	pid;
	int	fd[2];
	int	status;

	pipe(fd);
	pid = fork();
	status = 0;
	signal(SIGINT, SIG_IGN);
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return ;
	}
	if (pid == 0)
	{
		ft_read_here(arr, fd, i, data);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
	}
	if (!status)
	{
		close(fd[0]);
		close(fd[1]);
		return ;
	}
}

void	ft_infile(char **arr, t_command *data, int *i)
{
	int fd_infile = 0;

	if (!data->infiles)
	{
		data->infiles = malloc(sizeof(char *) * BUFFER_SIZE);
		data->infiles[0] = NULL;
	}
	if (i[0] == 0)
		data->comando_a_pelo = arr[3];
	else if (!data->comando_a_pelo)
		data->comando_a_pelo = arr[0];
	data->infiles[i[3]++] = ft_strdup(arr[i[0] + 1]);
	data->infiles[i[3]] = NULL;
	i[0]++;
}

void	ft_appends(char **arr, t_command *data, int *i)
{
	if (!data->appends)
		data->appends = malloc(sizeof(char *) * BUFFER_SIZE);
	if (i[0] == 0)
		data->comando_a_pelo = arr[3];
	else if (!data->comando_a_pelo)
		data->comando_a_pelo = arr[0];
	data->appends[i[4]++] = ft_strdup(arr[i[0] + 1]);
	data->appends[i[4]] = NULL;
	i[0]++;
}

void	ft_outfiles(char **arr, t_command *data, int *i)
{
	if (!data->outfiles)
		data->outfiles = malloc(sizeof(char *) * BUFFER_SIZE);
	if (i[0] == 0)
		data->comando_a_pelo = arr[3];
	else if (!data->comando_a_pelo)
		data->comando_a_pelo = arr[0];
	data->outfiles[i[5]++] = ft_strdup(arr[i[0] + 1]);
	data->outfiles[i[5]] = NULL;
	i[0]++;
}

void	ft_check_redir_create(char **arr, t_command *data, int *i)
{
	if (arr[i[0]][0] == '<' && arr[i[0]][1] == '<')
	{
		ft_heredoc(arr, data, i);
		i[0]++;
	}
	else if (arr[i[0]][0] == '<')
		ft_infile(arr, data, i);
	else if (arr[i[0]][0] == '>' && arr[i[0]][1] == '>')
		ft_appends(arr, data, i);
	else if (arr[i[0]][0] == '>')
		ft_outfiles(arr, data, i);
	else
	{
		if (!data->pre_args)
			data->pre_args = malloc(sizeof(char *) * BUFFER_SIZE);
		data->pre_args[i[2]++] = ft_strdup(arr[i[0]]);
		data->pre_args[i[2]] = NULL;
	}
}
