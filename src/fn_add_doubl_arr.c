/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_add_doubl_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:09:29 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/27 17:59:19 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_del_from_dob_arr(t_vars *vars, char *to_del, char ***src)
{
	int		i;
	int		j;
	char	**dst;

	(void)vars;
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
