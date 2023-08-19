/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_cleaning.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:10:48 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/18 19:41:38 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_del_quot(char *str, int *type, t_vars *vars)
{
	char	*clear;
	int		i;
	int		j;

	clear = malloc(sizeof(char) * ft_strlen(str) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (type[i] != 2 && type[i] != 1)
		{
			clear[j] = str[i];
			j++;
		}
		i++;
	}
	clear[j] = '\0';
	return (clear);
}
char	*ft_cleaning(char *str, t_vars *vars)
{
	char	*clear;
	int		*type;

	vars->i2 = -1;
	clear = NULL;
	vars->temp = NULL;
	type = ft_mask(str, vars, 0);
	clear = ft_del_quot(str, type, vars);
	free(type);
	return (clear);
}

void	ft_clean_dp(char **arr, t_vars *vars)
{
	int		i;
	char	*temp;

	i = -1;
	while (arr[++i])
	{
		vars->start2 = 0;
		temp = ft_cleaning(arr[i], vars);
		ft_my_free(arr[i]);
		arr[i] = ft_strdup(temp);
		ft_my_free(temp);
	}
}
