#include "../inc/minishell.h"

int     ft_lastpipe(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '|')
			return (0);
	// printf("%c\n", str[i]);
	return (1);
}

char    **spliting(char *wololoco, int *type, size_t num_pipes, t_vars *vars)
{
	int i = -1;
	int i2 = 0;
	char **separ;
	int start = 0;
	
	separ = malloc(sizeof(char *) * (num_pipes + 2));
	i = 1;
	while(wololoco[i - 1] != '\0')
	{
		if (type[i - 1] == 3)
		{
			separ[i2++] = ft_substr(wololoco, start, i - start - 1);
			start = i;
		}
		i++;
	}
	separ[i2++] = ft_substr(wololoco, start, i  - start);
	separ[i2] = NULL;
	ft_triming(separ, num_pipes, vars, 0);
	// printf(" **spliting - separ + 1 %s", separ[0]);
 	return(separ);
}

void	ft_subtrim(char **separ, char **temp, int *i, int *i2, t_vars *vars)
{
	int	*sub_type;
	int	i3;

	i3 = 0;
	sub_type = ft_mask(temp[0], vars);
	while (temp[0][++*i2])
	{
		if (temp[0][*i2] == ' ' && temp[0][*i2 + 1] == ' '\
			&& sub_type[*i2] != 5 && sub_type[*i2] != 6)
			continue ;
		separ[*i][i3] = temp[0][*i2];
		i3++;
	}
	free(sub_type);
	free(temp[0]);
	separ[*i][i3] = '\0';
}

void    ft_triming(char **separ, size_t num_pipes, t_vars *vars, int one_comand)
{
	int	i;
	int	i2;
	char **temp;

	temp = malloc(sizeof(char *) * (num_pipes + 2));
	i = -1;
	while (separ[++i])
	{
		temp[0] = ft_strtrim(separ[i], " ");
		i2 = -1;
		ft_subtrim(separ, temp, &i, &i2, vars);
	}
	free(temp);
	if (one_comand)
		vars->split = separ;
}

size_t  ft_numpipes(char *wololoco, int *type)
{
	int num_pipes;
	int	i;

	i = -1;
	num_pipes = 0;
	while(wololoco[++i])
	{
		if (type[i] == 3)
			num_pipes++;
	}
	return (num_pipes);
}

// void	ft_split_args(t_command *data, t_vars *vars)
// {
// 	int		i;
// 	int		i2;
// 	int		start;
// 	int		*type;

// 	i = -1; //0
// 	i2 = 0;
// 	start = 0;
// 	type = ft_mask(data->vars_resolv, vars);
// 	if (data->vars_resolv)
// 	{
// 		while (data->vars_resolv[++i])
// 			if (data->vars_resolv[i] == ' ')
// 				i2++;
// 		data->comando_bonito = malloc (sizeof(char *) * (i2 + 2));     ///free
// 		i = -1;
// 		i2 = 0;
// 		while(data->vars_resolv[++i])
// 		{
// 			if(data->vars_resolv[i] == '-' && data->vars_resolv[i + 1] != ' ')
// 			{
// 				while(data->vars_resolv[i] != ' ' && data->vars_resolv[i + 1] != '-')
// 				{
// 					i++;
// 					if (!data->vars_resolv[i + 1])
// 						break;
// 				}
// 				data->comando_bonito[i2++] = ft_substr(data->vars_resolv, start + 1, i - start); //ft_substr(data->arg, start + 1, i - 1);
// 				start = i + 1;
// 			}
// 			if (data->vars_resolv[i] == ' ' && type[i] != 5 && type[i] != 6)
// 			{
// 				i++;
// 				if(data->vars_resolv[i] && type[i])
// 				{
// 					while ((data->vars_resolv[i] != ' ' && data->vars_resolv[i] != '\0') || type[i] == 6 || type[i] == 5)
// 					{
// 						i++;
// 						if(!data->vars_resolv[i] || !type[i])
// 							break ;
// 					}
// 					data->comando_bonito[i2++] = ft_substr(data->vars_resolv, start + 1, i - start); //ft_substr(data->arg, start, i - start + 1)
// 					start = i + 1;
// 					i--;
// 				}
// 			}
// 			if (!data->vars_resolv[i])
// 				break ;
// 		}
// 		while(i2 != 0)
// 		{
// 			 printf("com bon %s\n", data->comando_bonito[--i2]); //printf - to free
// 		}
// 		// free(data->comando_bonito);
// 	}
// 	free(type);
// }