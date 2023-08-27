/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:56:06 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/27 19:58:10 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_e_status;

int	ft_export_err_equal(char *cmd)
{
	size_t		temp3;
	int			i;

	i = -1;
	temp3 = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '=')
			temp3++;
	}
	if (temp3 == ft_strlen(cmd))
	{
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_e_status = 1;
		return (1);
	}
	return (0);
}

void	ft_put_err(char *str, char **temp2)
{
	ft_putstr_fd("Minishell: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	ft_free_dob_arr(temp2);
	g_e_status = 1;
}

int	ft_export_err(char *cmd)
{
	char		**temp2;
	size_t		temp3;
	int			i;
	int			j;

	temp2 = ft_split(cmd, '=');
	i = -1;
	while (temp2[++i])
	{
		j = -1;
		temp3 = 0;
		while (temp2[i][++j])
		{
			if (ft_isdigit(temp2[i][j]))
				temp3++;
			if (i == 0 && (!ft_isalnum(temp2[i][j])
				|| temp3 == ft_strlen(temp2[0])))
			{
				ft_put_err(cmd, temp2);
				return (1);
			}
		}
	}
	ft_free_dob_arr(temp2);
	return (0);
}
