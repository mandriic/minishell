/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_getenvs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:13:16 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/20 15:39:03 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char *ft_loc_getenv(char *valor, t_vars vars)
// {
// 	ft_get_value(valor, vars->env);
// }

char	*ft_get_env(char *str, int len, t_vars *vars)
{
	char	*var;
	char	*valor;
	char	*temp;
	int		i;

	valor = NULL;
	var = malloc(sizeof(char *) * len + 1);
	i = -1;
	if (str[1] == '?')
	{
		free(var);
		var = malloc(sizeof(char *) * 6);
		temp = ft_itoa(g_e_status);
		ft_strlcpy(var, temp, 5);
		free(temp);
		return (var);
	}
	else if (str[1] == '~')
	{
		free(var);
		var = malloc(sizeof(char *) * 6);
		ft_strlcpy(var, "HOME", 5);
	}
	else
		ft_sub_get_env(str, var, len, &i);
		// printf("var: %s\n", var);
	if (vars->temp_env)
		valor = ft_get_value(var, vars->temp_env);
	if (valor == NULL)
		valor = ft_get_value(var, vars->env_var);	// printf("valor: %s\n", valor);
	free(var);
	if (!valor)
		return (NULL);
	if (str[i + 1] == ' ' )
		temp = ft_strjoin(valor, " ");
	else if (str[i + 1] == '/')
		temp = ft_strjoin(valor, "/");
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
