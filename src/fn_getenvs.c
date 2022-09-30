/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_getenvs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:13:16 by mandriic          #+#    #+#             */
/*   Updated: 2022/09/30 16:13:24 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_get_env(char *str, int len)
{
	char	var[len];
	char	*valor;
	char	*temp;
	int 	i;

	i = -1;
	if(str[1] == '?')
	{
		var[0] = '$';
		var[1] = '?';
		var[2] = '\0';
	}
	else
		ft_sub_get_env(str, var, len, &i);
	valor = getenv(var);
	printf("valor %s\n",valor);
	if (!valor)
		return (NULL);
	if (str[i + 1] == ' ' ) //|| str[i + 1] == '"'
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
	while(arr[0][++i] != NULL)
	{
		temp = ft_checkif_var(arr[0][i], vars);
		if (temp == NULL)
		{
			ft_my_free(arr[0][i]);
			arr[0][i] = NULL;
		}
		else if(arr[0][i] != temp)
		{
			ft_my_free(arr[0][i]);
			arr[0][i] = ft_strdup(temp);
			ft_my_free(temp);
		}
	}
	ft_clean_dp(arr[0], vars);
}
