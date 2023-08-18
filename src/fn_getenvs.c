/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_getenvs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:13:16 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/18 19:32:39 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_change_symbol(char *str, char *var, t_vars *vars)
{
	if (str[1] == '?')
	{
		free(var);
		return (ft_itoa(vars->error));
	}
	else if (str[0] == '~')
	{
		free(var);
		return (ft_strdup(ft_get_value("HOME", vars->env_var)));
	}
	else if (str[0] == '$' && str[1] == '\0')
	{
		free(var);
		return (ft_strdup("$"));
	}
	return (NULL);
}

char	*ft_get_env(char *str, int len, t_vars *vars)
{
	char	*var;
	char	*valor;
	char	*temp;
	int		i;

	valor = NULL;
	var = malloc(sizeof(char *) * len + 1);
	i = -1;
	if (str[1] == '?' || str[0] == '~' || (str[0] == '$' && str[1] == '\0'))
		return (ft_change_symbol(str, var, vars));
	else
		ft_sub_get_env(str, var, len, &i);
	if (vars->temp_env)
		valor = ft_get_value(var, vars->temp_env);
	if (valor == NULL)
		valor = ft_get_value(var, vars->env_var);
	free(var);
	if (!valor)
		return (NULL);
	if (str[i + 1] == ' ' || str[i + 1] == '/')
		temp = ft_strjoin_mod(valor, ft_substr(str, i + 1, 1));
	else
		temp = ft_strdup(valor);
	return (temp);
}

void	ft_get_env2(char ***arr, t_vars *vars)
{
	int		i;
	char	*temp;

	i = -1;
	while (arr[0][++i] != NULL)
	{
		temp = ft_checkif_var(arr[0][i], vars);
		if (temp == NULL)
		{
			ft_my_free(arr[0][i]);
			arr[0][i] = NULL;
		}
		else if (arr[0][i] != temp)
		{
			ft_my_free(arr[0][i]);
			arr[0][i] = ft_strdup(temp);
			ft_my_free(temp);
		}
	}
	ft_clean_dp(arr[0], vars);
}
