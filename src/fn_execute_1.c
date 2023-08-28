/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_execute_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:58:08 by mandriic          #+#    #+#             */
/*   Updated: 2023/08/28 11:21:23 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_e_status;

int	ft_check_dir(char *dir, char *cmd, size_t len)
{
	DIR				*d;
	struct dirent	*dirr;

	d = opendir(dir);
	if (d)
	{
		dirr = readdir(d);
		while (dirr != NULL)
		{
			if (ft_strncmp(dirr->d_name, cmd, len) == 0
				&& ft_strlen(dirr->d_name) == len)
			{
				closedir(d);
				return (1);
			}
			dirr = readdir(d);
		}
		closedir(d);
	}
	return (0);
}

char	*ft_sub_pars(char *path, char *ifhome, char *cmd, int *i)
{
	char	*dir;

	dir = malloc(sizeof(char) * (i[1] - i[0] + 1));
	ft_strlcpy(dir, path + i[0], i[1] - i[0] + 1);
	i[0] = i[1] + 1;
	if (ifhome)
	{
		if (dir)
			free(dir);
		dir = ft_strjoin(ifhome, dir);
	}
	if (ft_check_dir(dir, cmd, ft_strlen(cmd)) == 1)
		return (dir);
	free(dir);
	return (NULL);
}

char	*ft_pars_path(char *path, char *cmd, int len, t_vars *vars)
{
	int		i[2];
	char	*dir;
	char	*ifhome;

	ifhome = NULL;
	i[0] = len;
	i[1] = len + 1;
	while (path && path[i[1]])
	{
		if (path[i[1]] == '~')
		{
			ifhome = ft_get_val("HOME", vars->env_var);
			ifhome = ifhome + 5;
			i[1]++;
			i[0]++;
		}
		if (path[i[1]] == ':')
		{
			dir = ft_sub_pars(path, ifhome, cmd, i);
			if (dir)
				return (dir);
		}
		i[1]++;
	}
	return (0);
}

void	ft_print_err(t_vars *vars, char *err_str, int err, int io_err)
{
	(void)vars;
	ft_putstr_fd(err_str, io_err);
	if (err != -1)
	{
		g_e_status = err;
		exit(g_e_status);
	}
}

void	ft_check_if_exists(char *str, t_vars *vars)
{
	int	fd;

	fd = open(str, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd < 0)
	{
		ft_print_err(vars, "Minishel: ", -1, 2);
		ft_print_err(vars, str, -1, 2);
		ft_print_err(vars, ": Permission denied\n", 1, 2);
	}
	close(fd);
}
