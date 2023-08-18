/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_mask.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:14:34 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/18 19:59:54 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_singquot(char *line, int *type, t_vars *vars, int check)
{
	type[vars->i] = 1;
	while (line[++vars->i] != vars->quotes[0] && line[vars->i] != '\0' )
	{
		type[vars->i] = 5;
		if (line[vars->i] == '$')
			type[vars->i] = 8;
	}
	if (line[vars->i] == '\0' && check)
	{
		printf("Minishell: Not interpret unclosed quotes \n");
		free(type);
		return (1);
	}
	else if (line[vars->i] == '\0' && !check)
	{
		type[vars->i - 1] = 1;
		return (0);
	}
	else
		type[vars->i] = 1;
	return (0);
}

int	ft_dobquot(char *line, int *type, t_vars *vars, int check)
{
	type[vars->i] = 2;
	while (line[++vars->i] != '"' && line[vars->i] != '\0')
	{
		type[vars->i] = 6;
		if (line[vars->i] == '$')
			type[vars->i] = 7;
	}
	if (line[vars->i] == '\0' && check)
	{
		printf("Minishell: Not interpret unclosed quotes \n");
		free(type);
		return (1);
	}
	else if (line[vars->i] == '\0' && !check)
	{
		type[vars->i - 1] = 0;
		return (0);
	}
	else
		type[vars->i] = 2;
	return (0);
}

int	ft_check_error(char *line, int *type, int len)
{
	int i;

	i = -1;
	while (++i < len)
	{
		if (type[i] == 11 && (type[i + 1] != 10 || type[i + 2] == 10)
			|| (type[i] == 10 && type[i + 1] == 10))
		{
			if (type[i + 1] == 11)
				printf("Minishell: syntax error near unexpected token `%c%c'\n",
					line[i + 1], line[i + 2]);
			else
				printf("Minishell: syntax error near unexpected token `%c'\n",
					line[i + 1]);
			free(type);
			return (1);
		}
	}
	return (0);
}

int	ft_search_redir(char *line, t_vars *vars, int check, int *type)
{
	if (line[vars->i] == vars->quotes[0]
		&& ft_singquot(line, type, vars, check))
		return (1);
	else if (line[vars->i] == '"' && ft_dobquot(line, type, vars, check))
		return (1);
	else if (line[vars->i] == '|')
		type[vars->i] = 3;
	else if (line[vars->i] == '|' && line[vars->i + 1] == '\0')
		type[vars->i] = 4;
	else if ((line[vars->i] == '<' && line[vars->i + 1] == '<')
		|| (line[vars->i] == '>' && line[vars->i + 1] == '>'))
		type[vars->i] = 11;
	else if (line[vars->i] == '<' || line[vars->i] == '>')
		type[vars->i] = 10;
	else if (line[vars->i] == '$')
		type[vars->i] = 7;
	else if (line[vars->i] != '"' && line[vars->i] != vars->quotes[0]
		&& line[vars->i] != '\0')
		type[vars->i] = 0;
	return (0);
}

int	*ft_mask(char *line, t_vars *vars, int check)
{
	int	len;
	int	*type;

	vars->i = -1;
	type = NULL;
	len = ft_strlen(line);
	if (len == 0)
		return (type);
	type = malloc(sizeof(int) * len + 2);
	while (line[++vars->i] != '\0')
	{
		if (ft_search_redir(line, vars, check, type))
			return (NULL);
		if (line[vars->i] == '\0')
			break ;
	}
	if (ft_check_error(line, type, ft_strlen(line)))
		return (NULL);
	return (type);
}

