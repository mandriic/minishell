/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:15:50 by mandriic          #+#    #+#             */
/*   Updated: 2022/09/30 16:15:53 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_checkif_var(char *str, t_vars *vars)
{
	int		*type;
	char	*acum;

	vars->start = 0;
	type = ft_mask(str, vars, 0);
	acum = NULL;
	ft_checkif_var_subfoo(str, &acum, type, vars);
	if ((acum == NULL || str[vars->start - 1] == '\0') && str[0] != '$')
	{
		free(type);
		if (vars->start - 1 > 0 && str[vars->start - 1] == '\0'
			&& acum != NULL)
			return (acum);
		return (str);
	}
	vars->temp2 = ft_substr(str, vars->start, vars->i - vars->start + 1);
	if (vars->temp2 != NULL)
	{
		acum = ft_acumulate(acum, vars->temp2);
		free(type);
		return (acum);
	}
	free(type);
	return (acum);
}

void	ft_pre_getenv(char *str, char **acum, t_vars *vars)
{
	char	lastchar;

	lastchar = '\0';
	if (vars->i - vars->start > 0 && (str [vars->i - 1] == ' '
			|| lastchar == '/' || str[vars->i - 1] != vars->quotes[0]))
	{
		vars->temp = ft_substr(str, vars->start, vars->i - vars->start);
		*acum = ft_acumulate(*acum, vars->temp);
	}
	vars->start = vars->i + 1;
	vars->i++;
	while (str[vars->i] != ' ' && str[vars->i] != '\0' && str[vars->i] != '/'
		&& str[vars->i] != '"' && str[vars->i] != '$'
		&& str[vars->i] != vars->quotes[0])
		vars->i++;
	vars->var = ft_get_env(str + vars->start - 1, vars->i - vars->start);
	vars->start = vars->i + 1;
	*acum = ft_acumulate(*acum, vars->var);
	lastchar = str[vars->i];
	if (str[vars->i] == '$' && str[vars->i - 1] != ' '
		&& str[vars->i - 1] != '"')
		vars->i--;
}

void	ft_checkif_var_subfoo(char *str, char **acum, int *type, t_vars *vars)
{
	vars->i = 0;
	while (1)
	{
		if (str[vars->i] == '$' && (type[vars->i] == 6 \
		|| type[vars->i] == 0) && str[vars->i + 1] != ' ')
			ft_pre_getenv(str, acum, vars);
		if (str[vars->i] == '\0')
			break ;
		vars->i++;
	}
}

void	ft_sub_get_env(char *str, char *var, int len, int *i)
{
	while (++*i != len)
	{
		var[*i] = str[*i + 1];
		if (str[*i + 1] == '\0' || str[*i + 1] == '$')
			break ;
	}
	var[*i] = '\0';
}
