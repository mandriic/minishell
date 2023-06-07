/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:13:45 by mandriic          #+#    #+#             */
/*   Updated: 2023/04/07 20:57:55 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_merge_comando_args(t_command *data)
{
	int	i;

	i = -1;
	if (data->pre_args)
	{
		while (data->pre_args[++i])
			;
		data->cmd = malloc(sizeof(char *) * (i + 3));
		i = -1;
		while (data->pre_args[++i])
			data->cmd[i] = ft_strdup(data->pre_args[i]);
		data->cmd[i] = NULL;
	}
	else
		data->cmd = NULL;
	ft_free_dob_arr(data->pre_args);
}

int	ft_check_redir(char **arr, t_command *data)
{
	int	i[6];

	i[0] = -1;
	while (arr[++i[0]] != NULL)
	{
		if (arr[i[0]][0] == '<' || arr[i[0]][0] == '>')
		{
			ft_initint(i, 6);
			while (arr[i[0]] != NULL)
			{
				ft_check_redir_create(arr, data, i);
				i[0]++;
			}
			ft_merge_comando_args(data);
			ft_free_dob_arr(arr);
			return (1);
		}
	}
	return (0);
}

void	ft_resolv_com_bon(t_command *data, t_vars *vars)
{
	if (data->infiles || data->cmd || data->appends
		|| data->heredocs || data->outfiles)
	{
		if (data->infiles)
			ft_get_env2(&data->infiles, vars);
		if (data->cmd)
			ft_get_env2(&data->cmd, vars);
		if (data->appends)
			ft_get_env2(&data->appends, vars);
		if (data->heredocs)
			ft_get_env2(&data->heredocs, vars);
		if (data->outfiles)
			ft_get_env2(&data->outfiles, vars);
	}
}

void	ft_add2list(t_vars *vars, t_command *data, t_command **prev,
	t_command **temp)
{
	if (vars->cmd_list == NULL)
	{
		vars->cmd_list = ft_lstnew_mod((t_command *)data);
		data->prev = NULL;
		*temp = vars->cmd_list;
	}
	else
	{
		data->prev = *prev;
		*temp = ft_lstnew_mod(((t_command *)data));
		ft_lstadd_back_mod(&vars->cmd_list, *temp);
	}
}

void	ft_lst_cmd(t_vars *vars)
{
	t_command	*temp;
	t_command	*data;
	t_command	*prev;
	int			i;

	i = -1;
	if (vars->cmd_list)
		ft_del_list(vars->cmd_list);
	prev = NULL;
	temp = NULL;
	vars->cmd_list = NULL;
	while (vars->split[++i])
	{
		data = ft_create_data(vars->split[i], vars);
		ft_add2list(vars, data, &prev, &temp);
		prev = temp;
		temp = temp->next;
	}
	temp = vars->cmd_list;
	// while (temp)
	// {
	// 	if (temp->cmd)
	// 		ft_print_dp(temp->cmd, "!comando bonito!");
	// 	if (temp->prev)
	// 		ft_print_dp(temp->prev->cmd, "prev ");
	// 	if (temp->infiles)
	// 		ft_print_dp(temp->infiles, "infiles");
	// 	if (temp->outfiles)
	// 		ft_print_dp(temp->outfiles, "outfiles");
	// 	if (temp->appends)
	// 		ft_print_dp(temp->appends, "appends");
	// 	if (temp->heredocs)
	// 		ft_print_dp(temp->heredocs, "heredocs");
	// 	printf("end\n");
	// 	temp = temp->next;
	// }
	if (i != 1)
		ft_free_dob_arr(vars->split);
}
