/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_addit_4env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:09:29 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/27 18:28:02 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_find_in_env(t_vars *vars, char *to_find)
{
	int		i;
	char	*dst;

	i = -1;
	if (!vars->env_var)
		return (NULL);
	while (vars->env_var[++i])
	{
		if (ft_strncmp(vars->env_var[i], to_find, ft_strlen(to_find)) == 0)
		{
			dst = vars->env_var[i];
			return (dst);
		}
	}
	return (NULL);
}

char	**ft_append_to_env(t_vars *vars, char *to_append)
{
	int		i;
	char	**dst;
	char	*temp;

	i = -1;
	temp = ft_find_in_temp_env(vars, to_append);
	if (temp == NULL)
		temp = to_append;
	if (vars->env_var)
	{
		while (vars->env_var[++i])
			;
		dst = malloc(sizeof(char *) * (i + 2));
		i = -1;
		while (vars->env_var[++i])
			dst[i] = ft_strdup(vars->env_var[i]);
		dst[i++] = ft_strdup(temp);
		dst[i] = NULL;
		ft_free_dob_arr(vars->env_var);
		return (dst);
	}
	else
		return (NULL);
}

int	ft_change_env(t_vars *vars, char *name, char *new_value, int len)
{
	int	i;

	i = 0;
	while (vars->env_var[i] != NULL)
	{
		if (ft_strncmp(vars->env_var[i], name, len) == 0)
		{
			free(vars->env_var[i]);
			vars->env_var[i] = ft_strjoin(name, new_value);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_acumulate(char *dest, char *part)
{
	int		lenpart;
	char	*temp;

	lenpart = ft_strlen(part);
	if (lenpart == 0)
	{
		ft_my_free(part);
		return (dest);
	}
	if (!dest)
	{
		temp = ft_strdup(part);
		ft_my_free(part);
	}
	else
	{
		temp = ft_strjoin(dest, part);
		if (dest != NULL)
			ft_my_free(dest);
		ft_my_free(part);
	}
	return (temp);
}
