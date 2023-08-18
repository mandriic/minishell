/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnadd_libftmod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:12:11 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/18 19:29:00 by mandriic         ###   ########.fr       */
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

char	*ft_strjoin_mod(char *s1, char *s2)
{
	char	*p;
	int		count;
	int		count2;

	if (!s1 || !s2)
		return (0);
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (NULL == p)
		return (0);
	count = 0;
	while (s1[count] != '\0')
	{
		p[count] = s1[count];
		count++;
	}
	count2 = 0;
	while (s2[count2] != '\0')
	{
		p[count] = s2[count2];
		count++;
		count2++;
	}
	p[count] = '\0';
	free(s2);
	return (p);
}
