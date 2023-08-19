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

void	ft_print_dp(char **str, char *name)
{
	int	i;

	i = -1;
	printf("_____________printing doble punbtero %s _______\n", name);
	while (str[++i])
	{
		printf("\t %s[%d] = .%s.\n", name, i, str[i]);
	}
	printf("check NULL %s", str[i]);
	printf("\n");
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
