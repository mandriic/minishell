/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnadd_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:11:23 by mandriic          #+#    #+#             */
/*   Updated: 2023/06/18 14:14:16 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_my_free_d(char **arr)
{
	free (arr);
	arr = NULL;
}

void	ft_my_free(char *str)
{
	free(str);
	str = NULL;
}

void	ft_free_dob_arr(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			ft_my_free(arr[i]);
		ft_my_free_d(arr);
	}
}

void	ft_del_list(t_command *list)
{
	t_command	*last;
	t_command	*temp;

	temp = list;
	last = ft_lstlast_mod(list);
	while (1)
	{
		temp = list->next;
		ft_free_dob_arr(list->infiles);
		ft_free_dob_arr(list->outfiles);
		ft_free_dob_arr(list->appends);
		ft_free_dob_arr(list->heredocs);
		ft_free_dob_arr(list->cmd);
		free(list->cmd_splited);
		if (list->sub_arg)
			ft_my_free(list->sub_arg);
		free(list);
		if (list == last)
			break ;
		list = temp;
	}
}
