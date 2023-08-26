/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_addit_4env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:09:29 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/19 18:40:35 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_del_from_dob_arr(t_vars *vars, char *to_del, char ***src)
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

// int	ft_change_temp_env(t_vars *vars, char *name, char *new_value, int len)
// {
// 	int	i;

// 	i = 0;
// 	while (vars->env_var[i] != NULL)
// 	{
// 		if (ft_strncmp(vars->env_var[i], name, len) == 0)
// 		{
// 			free(vars->env_var[i]);
// 			vars->env_var[i] = ft_strjoin(name, new_value);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }