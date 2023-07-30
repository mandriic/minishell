/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_cleaning.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:10:48 by mandriic          #+#    #+#             */
/*   Updated: 2022/09/30 16:10:51 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_subcleaning(char *str, char **clear, t_vars *vars, int *type)
{
	if (str[vars->i2] == '~')
	{
		vars->temp = ft_strdup(getenv("HOME"));
	}
	else if (vars->i2 - vars->start2 != 0)
	{
		if (vars->start2 == 0)
			vars->temp = ft_substr(str, vars->start2, vars->i2 - vars->start2);
		else
			vars->temp = ft_substr(str, vars->start2 + 1,
					vars->i2 - vars->start2 - 1);
		*clear = ft_acumulate(*clear, vars->temp);
	}
	vars->start2 = vars->i2;
	vars->i2++;
	while (str[vars->i2] != '\0' && type[vars->i2] != 1 && type[vars->i2] != 2)
		vars->i2++;
	if (!vars->temp || str[vars->i2 + 1] == '\0')
	{
		// printf("vars->temp is null\n");
		vars->temp = ft_substr(str, vars->start2 + 1, vars->i2 - vars->start2 - 1);
	}
	vars->start2 = vars->i2;
	*clear = ft_acumulate(*clear, vars->temp);
}

int	ft_clear_quot(char *str, char **clear, t_vars *vars, int *type)
{
	if (type[vars->i2] == 2 || type[vars->i2] == 1 || str[vars->i2] == '~')
	{
		if ((str[vars->i2] == '"' && str[vars->i2 + 1] == '"')
			|| (str[vars->i2] == vars->quotes[0]
				&& str[vars->i2 + 1] == vars->quotes[0]))
		{
			free(type);
			return (1);
		}
		ft_subcleaning(str, clear, vars, type);
	}
	return (0);
}

char	*ft_cleaning(char *str, t_vars *vars)
{
	char	*clear;
	int		*type;

	vars->i2 = -1;
	clear = NULL;
	vars->temp = NULL;
	type = ft_mask(str, vars, 0);
	while (str[++vars->i2])
	{
		if (ft_clear_quot(str, &clear, vars, type))
			return (NULL);
		if (str[vars->i2] == '\0')
			break ;
	}
	free(type);
	if (vars->start2 != vars->i2 && clear != NULL)
	{
		vars->temp = ft_substr(str, vars->start2 + 1,
				vars->i2 - vars->start2 - 1);
		clear = ft_acumulate(clear, vars->temp);
		return (clear);
	}
	else if (clear == NULL)
		return (ft_strdup(str));
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
