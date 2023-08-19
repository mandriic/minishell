/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_redirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:15:36 by mandriic          #+#    #+#             */
/*   Updated: 2022/09/30 16:15:39 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_heredoc(char **arr, t_command *data, int *i)
{
	char	*eofile;
	int		str_cmp;

	eofile = arr[i[0] + 1];
	str_cmp = 1;
	i[1] = -1;
	if (!data->heredocs)
		data->heredocs = malloc(sizeof(char *) * BUFFER_SIZE);
	while (1)
	{
		data->heredocs[++i[1]] = readline(">");
		str_cmp = ft_strncmp(eofile, data->heredocs[i[1]], ft_strlen(eofile));
		if (!str_cmp && ft_strlen(data->heredocs[i[1]]) == ft_strlen(eofile))
			break ;
	}
	free(data->heredocs[i[1]]);
	data->heredocs[i[1]--] = NULL;
	// ft_print_dp(data->heredocs, "heredocs");
	i[0]++;
}

void	ft_infile(char **arr, t_command *data, int *i)
{
	int i2;

	i2 = i[3];
	if (!data->infiles)
	{
		data->infiles = malloc(sizeof(char *) * BUFFER_SIZE);
		data->infiles[0] = NULL;
	}
	if (i[0] == 0)
		data->comando_a_pelo = arr[3];
	else if (!data->comando_a_pelo)
		data->comando_a_pelo = arr[0];
	if (data->infiles && data->infiles[0] == 0)
		free(data->infiles);
	data->infiles[0] = ft_strdup(arr[i[0] + 1]);
	data->infiles[1] = NULL;
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
		ft_heredoc(arr, data, i);
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
