/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:11:50 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/19 18:38:56 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static __int128_t	ft_putnbr(const char *str, int i)
{
	__int128_t	num;

	num = 0;
	while (str[i] <= '9' && str[i] >= '0')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

__int128_t	ft_atoll(const char *str)
{
	int			i;
	__int128_t	nb;
	__int128_t	num;

	num = 0;
	nb = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			nb = nb * -1;
			i++;
		}
		else
			i++;
	}
	num = ft_putnbr(str, i);
	return (num * nb);
}
