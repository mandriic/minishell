#include "../inc/minishell.h"
int	*ft_mask(char *line, t_vars *vars);
int	ft_lastpipe(char *str);

t_data *ft_create_data(char *str, t_list *prev)
{
	t_data *data;
	int	i;

	i = -1;
	data = calloc(sizeof(t_data), sizeof(t_data));
	// if (ft_lastpipe (str))
	// {
	// 	// readline(">");
	// 	sleep (2);
	// }
	// printf("createD %s\n", str);
	if (!str[0])
	{
		while (!str[0])
		{
			str = readline(">");
			// printf("data |%s|\n", data->cmd_arg);
			// if (data->cmd_arg == "" || data->cmd_arg == NULL)
			// 	free(data->cmd_arg);
		}

	}
	// while (str[++i])
	// {
	// 	if (str[i] == '|')
	// 		readline (">");
	// }

	data->cmd_arg = str;
	data->prev = prev;
}
void ft_lst_cmd(t_vars *vars)
{
	t_list *lst_cmd;
	t_list *prev;
	t_list *temp;
	t_data *data;

	int i;

	i = -1;
	lst_cmd = NULL;
	while (vars->split[++i])
	{
		// data.cmd_arg = vars->split[i];
		// free(vars->split[i]);
		data = ft_create_data(vars->split[i], prev);
		// printf("fitst data %s\n", data->cmd_arg);
		if (lst_cmd == NULL)
		{
			data->prev = NULL;
			lst_cmd = ft_lstnew((t_data *)data);
			// printf("lsst_cmd %s\n", ((t_data *)lst_cmd->content)->cmd_arg);
			temp = lst_cmd;
		}
		else 
		{
			temp = ft_lstnew(((t_data *)data));
			ft_lstadd_back(&lst_cmd, temp);
		}
		prev = temp;
		temp = temp->next;

	}
	temp = lst_cmd;
	while (temp)
	{
		printf("print puntero from list ->%s\n", ((t_data *)temp->content)->cmd_arg);
		temp = temp->next;
	}

}
size_t ft_numpipes(char *wololoco, int *type)
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
char **spliting(char *wololoco, int *type, size_t num_pipes, t_vars *vars)
{
	int i = -1;
	int i2 = 0;
	char **separ;
	char **temp;
	int start = 0;
	
	separ = malloc(sizeof(char *) * num_pipes + 2);
	temp = malloc(sizeof(char *) * num_pipes + 2);
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
	}
	separ[i2++] = ft_substr(wololoco, start, i  - start);
	i = -1;
	separ[i2] = NULL;
	int i3;
	int i4;
	int *sub_type;
	while (separ[++i])
	{
		temp[i] = ft_strtrim(separ[i], " ");
		sub_type = ft_mask(temp[i], vars);

		// free(separ[i]);
		i2 = -1;
		i3 = 0;
		while (temp[i][++i2])
		{
			// printf("%d\n",sub_type[i]);

			if (temp[i][i2] == ' ' && temp[i][i2 + 1] == ' ' && sub_type[i2] != 5)
				continue ;
			separ[i][i3] = temp[i][i2];
			i3++;
		}
		free(sub_type);
		separ[i][i3] = '\0';
	}
	temp[i] = NULL;
	// for(i= 0; temp[i] != '\0'; i++)
	// 	printf("%s\n", temp[i]);
 	return(separ);
}
int	ft_lastpipe(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '|')
			return (0);
	printf("%c\n", str[i]);
	return (1);
}
int	*ft_mask(char *line, t_vars *vars)
{
	int i;
	int len;
	int *type;

	i = -1;
	len = ft_strlen(line);
	type = malloc(sizeof(int) * len);

	while (line[++i] != '\0')
	{
		if(line[i] == vars->quotes[0])
		{
			type[i] = 1;
			while (line[++i] != vars->quotes[0])
				type[i] = 5;
			type[i] = 1;
		}
		else if (line[i] == '"')
		{
			type[i] = 2;
			while (line[++i] != '"')
				type[i] = 5;
			type[i] = 2;
		}
		else if (line[i] == '|'  ) //&& line[i + 1] != '\0' && !ft_lastpipe(line + i + 1)
			type[i] = 3;
		// else if (ft_lastpipe(line + i + 1))
		// {
		// 	while (line[i])
		// 	{
		// 		if (ft_isalnum(line[i]))

		// 	}
		// }
		else if (line[i] == '|' && line[i + 1] == '\0')
			type[i] = 4;
		else
			type[i] = 0;
		// printf("type %d\n", type[i]);
	}
	return (type);
}
int main(void)
{
	t_vars vars;
	vars = (t_vars){};

	int i;
	// char *finline;
	// char **split;
	vars.quotes  = "'";
	while (1)
	{
		vars.line = readline("$ ");
		if (!ft_strncmp ("exit", vars.line, ft_strlen(vars.line)))
		{
			write(1, "exit\n", 5);
			free(vars.line);
			exit (0);
		}

		//add_history(vars.line); //solo añadir si es válido
		// line_cop = ft_strdup(wololo);
		vars.line_len = ft_strlen(vars.line);
		// printf("%zu\n", line_len	);
		vars.type = ft_mask(vars.line, &vars);
		vars.num_pipes = ft_numpipes(vars.line, vars.type);
		if (vars.num_pipes)
			vars.split = spliting(vars.line, vars.type, vars.num_pipes, &vars);
		else
		{
			vars.split = malloc(sizeof(char *) * 2);
			vars.split[0] = vars.line;
			vars.split[1] = '\0';
		}
		ft_lst_cmd(&vars);

		// printf("%s\n", vars.split[0]);
		// i = -1;
			// printf("%s\n", split[0]);

		// while (split[++i])
		// 	printf("%s\n", split[i]);\
		//-----------------------------------
		// i = 0;
		// finline = malloc(sizeof(char) * line_len + 1);
		// int i2 = 0;
		// while (wololo[i])
		// {
		// 	if (type[i] == 1 || type[i] == 2)
		// 	{
		// 		i++;
		// 		continue ;
		// 	}
		// 	finline[i2] = wololo[i];
		// 	i++;
		// 	i2++;
		// }
		// finline[i2] = '\0';
		//----------------------------------

		// printf("%s\n", finline);
		 // printf("%s\n", line_cop);
		// for(i = 0; i < line_len; i++)
		// 	printf("%d\n", type[i]);
		// i = -1;
		// while (split[++i] != NULL)
		// 	free(split[i]);
		// free(split);
	}

		return (0);
}