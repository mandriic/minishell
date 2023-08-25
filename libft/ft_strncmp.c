/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:24:45 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/24 11:46:00 by pepealkalin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s2 || !s1)
		return (-1);
	while (((*s1 || *s2) && n) != 0)
	{
		n--;
		if (*s1++ != *s2++)
			return ((unsigned char)*--s1 - (unsigned char)*--s2);
	}
	return (0);
}
