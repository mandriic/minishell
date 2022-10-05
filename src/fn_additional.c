/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_additional.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:10:25 by mandriic          #+#    #+#             */
/*   Updated: 2022/09/30 16:10:37 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_dup_dp(char **src)
{
	int		i;
	char	**dst;

	i = -1;
	while (src[++i])
		;
	dst = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (src[++i])
		dst[i] = ft_strdup(src[i]);
	dst[i] = NULL;
	ft_free_dob_arr(src);
	return (dst);
}

int	ft_pre_check(t_vars *vars)
{
	int	alpha;

	vars->i = -1;
	alpha = 0;
	while (vars->line[++vars->i])
	{
		if (ft_isalnum(vars->line[vars->i]))
			alpha++;
	}
	if (alpha == 0)
	{
		printf("Minishell: syntax error near unexpected token \n");
		free(vars->line);
		return (1);
	}
	return (0);
}

void	ft_end_of_cicle(t_vars *vars)
{
	ft_my_free(vars->line);
	free(vars->type);
}

void	ft_initint(int *i, int len)
{
	int	cou;

	cou = -1;
	while (++cou != len)
		i[cou] = 0;
}

void	ft_print_dp(char **str, char *name)
{
	int	i;

	i = -1;
	printf("_____________printing doble punbtero %s _______\n", name);
	while (str[++i])
	{
		printf("\t %s[%d] = .%s.\n", name, i, str[i]);
	}
	printf("DEBUG check NULL %s", str[i]);
	printf("\n");
}

// void	ft_strcopy(char *dst, const char *src)
// {
// 	size_t	i;
// 	size_t	srclen;

// 	i = 0;
// 	srclen = ft_strlen(src);
// 	if (!src)
// 		return ;
// 	while (src[i] && i < strlen)
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// }