/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_add_doubl_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:09:29 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/27 19:54:07 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_del_from_dob_arr(char *to_del, char ***src)
{
	int		i;
	int		j;
	char	**dst;

	i = -1;
	j = 0;
	while (src[0][++i])
	{
		if (ft_strncmp(src[0][i], to_del, ft_strlen(to_del)) == 0)
			j++;
	}
	dst = malloc(sizeof(char *) * (i - j + 1));
	i = -1;
	j = 0;
	while (src[0][++i])
	{
		if (ft_strncmp(src[0][i], to_del, ft_strlen(to_del)) != 0)
			dst[j++] = ft_strdup(src[0][i]);
	}
	dst[j] = NULL;
	ft_free_dob_arr(src[0]);
	src[0] = dst;
}
