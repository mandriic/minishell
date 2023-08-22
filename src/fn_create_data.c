/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_create_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:12:58 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/19 18:41:00 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_apphdoc(char *str, char **com_bon, int *i, int *type)
{
	char	*temp;

	if (type[i[0]] == 11)
	{
		if (i[0] != 0 && str[i[0] - 1] != ' ')
		{
			temp = ft_substr(str, i[1], i[0] - i[1]);
			com_bon[i[2]++] = ft_strtrim(temp, " ");
			ft_my_free(temp);
			i[1] = i[0];
		}
		while (str[i[0]] == '<' || str[i[0]] == '>')
			i[0]++;
		temp = ft_substr(str, i[1], i[0] - i[1]);
		com_bon[i[2]++] = ft_strtrim(temp, " ");
		ft_my_free(temp);
		i[1] = i[0];
		return (1);
	}
	return (0);
}

int	ft_check_inoutfile(char *str, char **com_bon, int *i, int *type)
{
	char	*temp;

	if (type[i[0]] == 10)
	{
		if (i[0] != 0 && str[i[0] - 1] != ' ')
		{
			temp = ft_substr(str, i[1], i[0] - i[1]);
			com_bon[i[2]++] = ft_strtrim(temp, " ");
			ft_my_free(temp);
			i[1] = i[0];
		}
		while (str[i[0]] == '<' || str[i[0]] == '>')
			i[0]++;
		temp = ft_substr(str, i[1], i[0] - i[1]);
		com_bon[i[2]++] = ft_strtrim(temp, " ");
		ft_my_free(temp);
		i[1] = i[0];
		return (1);
	}
	return (0);
}

void	ft_check_total(char *str, char **com_bon, int *i, int *type)
{
	char	*temp;

	if (ft_check_apphdoc(str, com_bon, i, type))
		;
	else if (ft_check_inoutfile(str, com_bon, i, type))
		;
	else
	{
		temp = ft_substr(str, i[1], i[0] - i[1] + 1);
		com_bon[i[2]++] = ft_strtrim(temp, " ");
		ft_my_free(temp);
		i[1] = i[0] + 1;
	}
}

char	**ft_pre_com_bon(char *str, t_vars *vars)
{
	int		i[3];
	char	*temp;
	char	**com_bon;
	int		*type;

	ft_initint(i, 3);
	com_bon = malloc(sizeof(char *) * BUFFER_SIZE);
	type = ft_mask(str, vars, 0);
	i[0] = -1;
	while (str[++i[0]] != '\0')
	{
		if ((str[i[0]] == ' ' && type[i[0]] != 5 && type[i[0]] != 6)
			|| type[i[0]] == 11 || type[i[0]] == 10)
			ft_check_total(str, com_bon, i, type);
		if (str[i[0]] == '\0')
			break ;
	}
	temp = ft_substr(str, i[1], i[0] - i[1] + 1);
	com_bon[i[2]++] = ft_strtrim(temp, " ");
	ft_my_free(temp);
	com_bon[i[2]] = NULL;
	free(type);
	return (com_bon);
}

t_command	*ft_create_data(char *str, t_vars *vars)
{
	t_command	*data;

	data = malloc(sizeof(t_command));
	*data = (t_command){};
	if (!str[0])
	{
		while (str[0] == '\0')
			str = readline(">");
	}
	data->pre_comand_bon = ft_pre_com_bon(str, vars);
	if (!ft_check_redir(data->pre_comand_bon, data))
	{
		data->cmd = ft_dup_dp(data->pre_comand_bon);
		data->comando_a_pelo = data->cmd[0];
		data->fd[0] = -1;
		data->fd[1] = -1;
	}
	ft_resolv_com_bon(data, vars);
	return (data);
}
