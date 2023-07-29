/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_mask.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:14:34 by mandriic          #+#    #+#             */
/*   Updated: 2022/09/30 16:14:37 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_singquot(char *line, int *type, t_vars *vars, int check)
{
	type[vars->i] = 1;
	while (line[++vars->i] != vars->quotes[0] && line[vars->i] != '\0' )
		type[vars->i] = 5;
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
		type[vars->i] = 6;
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
int ft_check_error(char *line, int *type, int len)
{
	int i;
	i = -1;
	while (++i < len)
	{
		// printf("type[%d] = %d\n", i, type[i]);
		if (type[i] == 11 && (type[i + 1] != 10 || type[i + 2] == 10) || (type[i] == 10 && type[i + 1] == 10))
		{
		// printf("type[%d] = %d\n", i, type[i + 1]);

			if (type[i + 1] == 11)
			{
				printf("Minishell: syntax error near unexpected token `%c%c'\n", line[i + 1], line[i + 2]);
				free(type);
				return (1);
			}
			else
			{
				printf("Minishell: syntax error near unexpected token `%c'\n", line[i + 1]);
				free(type);
				return (1);
			}
			return (0);
		}
	}
	// if (type[vars->i] == 11 && type[vars->i + 2] != ' ' || ft_isalpha(line[vars->i + 1])))
	// {
	// 		printf("Minishell: syntax error near unexpected token `<<'\n");
	// 		return (1);
	// 	}
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
