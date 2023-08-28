/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_addit_4loc_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:58:24 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/28 11:18:07 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_change_temp_env(t_vars *vars, char *name, char *new_value, int len)
{
	int	i;

	i = 0;
	while (vars->temp_env[i] != NULL)
	{
		if (ft_strncmp(vars->temp_env[i], name, len) == 0)
		{
			free(vars->temp_env[i]);
			vars->temp_env[i] = ft_strjoin(name, new_value);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_find_in_temp_env(t_vars *vars, char *to_append)
{
	int		i;
	char	*dst;

	i = -1;
	if (!vars->temp_env)
		return (NULL);
	while (vars->temp_env[++i])
	{
		if (ft_strncmp(vars->temp_env[i], to_append, ft_strlen(to_append)) == 0)
		{
			dst = vars->temp_env[i];
			return (dst);
		}
	}
	return (NULL);
}

char	**ft_append_to_temp_env(t_vars *vars, char *to_append)
{
	int		i;
	char	**dst;

	i = -1;
	if (vars->temp_env)
	{
		while (vars->temp_env[++i])
			;
		dst = malloc(sizeof(char *) * (i + 2));
		i = -1;
		while (vars->temp_env[++i])
			dst[i] = ft_strdup(vars->temp_env[i]);
		dst[i++] = ft_strdup(to_append);
		dst[i] = NULL;
		ft_free_dob_arr(vars->temp_env);
		return (dst);
	}
	else
	{
		vars->temp_env = malloc(sizeof(char *) * 2);
		vars->temp_env[0] = ft_strdup(to_append);
		vars->temp_env[1] = NULL;
		return (vars->temp_env);
	}
}
