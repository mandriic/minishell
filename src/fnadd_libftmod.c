/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnadd_libftmod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:12:11 by mandriic          #+#    #+#             */
/*   Updated: 2022/09/30 16:12:17 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_command	*ft_lstnew_mod(t_command *content)
{
	t_command	*new;

	new = content;
	new->next = NULL;
	return (new);
}

t_command	*ft_lstlast_mod(t_command *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_mod(t_command **lst, t_command *new)
{
	t_command	*old_last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	old_last = ft_lstlast_mod(*lst);
	old_last->next = new;
}
