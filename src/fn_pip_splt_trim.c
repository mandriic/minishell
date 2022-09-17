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
	// char **separ2;
	int start = 0;
	
	separ = malloc(sizeof(char *) * (num_pipes + 2));
	i = 1;
	while(wololoco[i - 1] != '\0')
	{
		if (type[i - 1] == 3)
		{
			separ[i2++] = ft_substr(wololoco, start, i - start - 1);
			start = i;
			// printf("%d\n", i);
		// printf("%s\n", separ[i2 - 1]);
		}
		i++;
		// printf("sep%s\n", separ[i2 - 1]);
		
	}
	separ[i2++] = ft_substr(wololoco, start, i  - start);
	separ[i2] = NULL;
	// int i3;
	// int *sub_type;

	ft_triming(separ, num_pipes, vars, 0);
	// while(--i2 != 0)
	// {
	// 	free(separ[i2]);
	// 	separ[i2] = NULL;
	// }
	// free(separ);
	// for(i= 0; temp[i] != '\0'; i++)
	// 	printf("%s\n", temp[i]);
 	return(separ);
}

void    ft_triming(char **separ, size_t num_pipes, t_vars *vars, int one_comand)
{
	int	i;
	int	i2;
	int	i3;
	char **temp;
	int *sub_type;

	temp = malloc(sizeof(char *) * (num_pipes + 2));
	// printf("sizeof%lu\n", sizeof(separ));
	i = -1;
		while (separ[++i])
		{
			// printf("i%d\n", i);
			// printf("separ%s\n", separ[i]);
			temp[0] = ft_strtrim(separ[i], " ");
			sub_type = ft_mask(temp[0], vars);
			// free(separ[i]);
			i2 = -1;
			i3 = 0;
			while (temp[0][++i2])
			{
				// printf("%d\n",sub_type[i]);
				// printf("check\n");
// 				sleep(1);
				if (temp[0][i2] == ' ' && temp[0][i2 + 1] == ' ' && sub_type[i2] != 5 && sub_type[i2] != 6)
					continue ;
				separ[i][i3] = temp[0][i2];
				i3++;
			}
			free(sub_type);
			free(temp[0]);
			separ[i][i3] = '\0';
	}
	free(temp);
	// int ii = -1;
	// while(++ii != i)
	// 	free(mem[ii]);
	// free(mem[0]);
// 	ft_free_double_arr(mem);
	// temp[i] = NULL;
	// printf("i2%d\n",i);
	if (one_comand)
	{

		vars->split = separ;
	}
		// vars->split = separ;
	
	// return(separ);
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

void	ft_split_args(t_command *data, t_vars *vars)
{
	int		i;
	int		i2;
	int		start;
	int		*type;

	i = -1; //0
	i2 = 0;
	start = 0;
	type = ft_mask(data->arg, vars);
	if (data->arg)
	{
		while (data->arg[++i])
			if (data->arg[i] == ' ')
				i2++;
		data->comando_bonito = malloc (sizeof(char *) * (i2 + 2));     ///free
		i = -1;
		i2 = 0;
		while(data->arg[++i])
		{
			if(data->arg[i] == '-' && data->arg[i + 1] != ' ')
			{
				while(data->arg[i] != ' ' && data->arg[i + 1] != '-')
				{
					i++;
					if (!data->arg[i + 1])
						break;
				}
				data->comando_bonito[i2++] = ft_substr(data->arg, start + 1, i - start); //ft_substr(data->arg, start + 1, i - 1);
				start = i + 1;
			}
			if (data->arg[i] == ' ' && type[i] != 5 && type[i] != 6)
			{
				i++;
				if(data->arg[i] && type[i])
				{
					while ((data->arg[i] != ' ' && data->arg[i] != '\0') || type[i] == 6 || type[i] == 5)
					{
						i++;
						if(!data->arg[i] || !type[i])
							break ;
					}
					data->comando_bonito[i2++] = ft_substr(data->arg, start + 1, i - start); //ft_substr(data->arg, start, i - start + 1)
					start = i + 1;
					i--;
				}
			}
			if (!data->arg[i])
				break ;
		}
		while(i2 != 0)
		{
			free(data->comando_bonito[--i2]); //printf - to free
		}
		free(data->comando_bonito);
	}
	free(type);
}