/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_additional.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:10:25 by mandriic          #+#    #+#             */
/*   Updated: 2023/06/18 18:59:55 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_dup_dp(char **src)
{
	int		i;
	char	**dst;

	i = -1;
	while (src[++i])
		;
	dst = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (src[++i])
		dst[i] = ft_strdup(src[i]);
	dst[i] = NULL;
	ft_free_dob_arr(src);
	return (dst);
}

char	**ft_dupl_dp(char **src)
{
	int		i;
	char	**dst;

	i = -1;
	while (src[++i])
		;
	dst = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (src[++i])
		dst[i] = ft_strdup(src[i]);
	dst[i] = NULL;
	// ft_free_dob_arr(src);
	return (dst);
}

char **ft_append_to_temp_env(t_vars *vars, char *to_append)
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
char *ft_find_in_temp_env(t_vars *vars, char *to_append)
{
	int i = -1;
	char *dst;
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

char **ft_append_to_env(t_vars *vars, char *to_append)
{
	
	int		i;
	char	**dst;
	char	*temp;
	i = -1;
	temp = ft_find_in_temp_env(vars, to_append);
	if (temp == NULL)
		temp = to_append;
	// printf("temp = %s\n", temp);
	if (vars->env_var)
	{
		while (vars->env_var[++i])
			;
		dst = malloc(sizeof(char *) * (i + 2));
		i = -1;
		while (vars->env_var[++i])
			dst[i] = ft_strdup(vars->env_var[i]);
		dst[i++] = ft_strdup(temp);
		// printf("dst[i] = %s\n", dst[i - 1]);
		dst[i] = NULL;
		ft_free_dob_arr(vars->env_var);
		return (dst);
	}
	else
		return (NULL);
}

int	ft_pre_check(t_vars *vars)
{
	int	alpha;

	vars->i = -1;
	alpha = 0;
	while (vars->line[++vars->i])
	{
		if (ft_isalnum(vars->line[vars->i]))
			alpha++;
	}
	if (alpha == 0)
	{
		printf("Minishell: syntax error near unexpected token \n");
		free(vars->line);
		return (1);
	}
	return (0);
}

void	ft_end_of_cicle(t_vars *vars)
{
	ft_my_free(vars->line);
	free(vars->type);
}

void	ft_initint(int *i, int len)
{
	int	cou;

	cou = -1;
	while (++cou != len)
		i[cou] = 0;
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

// void c(char *str)
// {
// 	printf("check %s\n", str);
// }
// void	ft_strcopy(char *dst, const char *src)
// {
// 	size_t	i;
// 	size_t	srclen;

// 	i = 0;
// 	srclen = ft_strlen(src);
// 	if (!src)
// 		return ;
// 	while (src[i] && i < strlen)
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// }