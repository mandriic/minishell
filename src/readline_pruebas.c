#include "../inc/minishell.h"
int	*ft_mask(char *line, t_vars *vars);
int	ft_lastpipe(char *str);
void ft_free_double_arr(char **str)
{
	int i = -1;
	if (str[0])
	{
		while (str[++i] != NULL)
		{
			if(str[i])
				free(str[i]);
		}
		if (str)
			free(str);
	}
}
char	*ft_checkif_var(char *str, t_vars *vars)
{
	char *temp;
	char *temp2;
	char *temp4;
	char *temp3;
	char start;
	// int *type;
	int i;

	i =-1;
	start = 0;
	(void) vars;
	temp3 = NULL;
	// type = ft_mask(str, vars);
	if (str[0] == '"')
	{
		while (str[i] != '\0')
		{

			while (str[i] != '$' && str[i] != '\0')
				i++;
			// printf("%d\n", i);
			// if (str[i] == '\0' && !temp3)
			// 	return (str);
			if ((str[i] == '$' && i != 0) || str[i] == '\0')
			{
				temp = ft_substr(str, start, i );
				printf("substr 1 %s\n", temp);
				start = i + 1;
				while (str[i] != ' ' && str[i] != '\0')
					i++;
				temp2 = ft_substr(str, start, i  - start);
				start = i ;
				printf("sub str 2 %s\n", temp2);
				if (str[i] == ' ')
					temp4 = getenv(temp2);
				else
					temp4 = temp;
				free(temp2);

				printf("getenv %s\n", temp4);
				if (temp3 == NULL)
					temp3 = ft_strjoin(temp, temp4);
				else 
				{
					temp2 = temp3;
					temp3 = ft_strjoin(temp3, temp4);
					free(temp2);
				}
				printf("join %s\n", temp3);
				free(temp);
				// free(temp4);
				// if (str[i] == '\0')
				// 	return (temp3);
			}
			i++;
		}
		return (temp3);

	}
	else if (str[0] == '$')
	{
		temp = getenv(str + 1);
		// free(str);
		return (temp);
	}
	else
		return (str);
}
void	ft_split_args(t_data *data, t_vars *vars)
{
	int i;
	int i2;
	int start;
	int *type;
	char *test;
	size_t len;

	len = ft_strlen(data->arg);
	i = -1;
	i2 = 0;
	start = 0;
	type = ft_mask(data->arg, vars);
	if (data->arg)
	{
		while (data->arg[++i])
			if (data->arg[i] == ' ')
				i2++;
		data->arg_splited = malloc (sizeof(char *) * i2 + 1);     ///free
		i = -1;
		i2 = 0;

		while(data->arg[++i])
		{
			if(data->arg[i] == '-' && data->arg[i + 1] != ' ')
			{
				while(data->arg[i] != ' ' && data->arg[i + 1] != '-')
					i++;
				// data->arg_splited[i2] = malloc (sizeof (char) * i + 1);
				data->arg_splited[i2++] = ft_substr(data->arg, start, i);
				start = i + 1;
				printf("solo flag\t|%s\n", data->arg_splited[i2 - 1]);
				// data->arg_splited[i2++] = '\0';
			}
			// printf("im i%d\n", i);
			// if (data->arg)
			if (data->arg[i] == ' ' )//&& type[i] != 5 && type[i] != 6)
			{
				i++;
				while ((data->arg[i] != ' ' && data->arg[i] != '\0') || type[i] == 6 || type[i] == 5)
					i++;
				data->arg_splited[i2++] = ft_substr(data->arg, start, i - start + 1);
				start = i + 1;
				// data->arg_splited[i2 - 1] = ft_checkif_var(data->arg_splited[i2 - 1], vars);
				test = ft_checkif_var(data->arg_splited[i2 - 1], vars);
				printf("test %s\n", test);
				free(test);
				// printf("arg %d \t\t|%s\n", i2 - 1, data->arg_splited[i2 - 1]);
				i--;
			}
			// printf("first i\t|%c\n", data->arg[i]);
			// printf("first arg\t|%s\n", data->arg_splited[i2]);
		}
	}
	free(type);
}
void	ft_subpars(char *str, t_data *data)
{
	// (void) vars;
	int		i;
	int		start;

	i = -1;   						//antes i = 0; leak was found
	start = 0;
	while (str[++i])
		if (str[i] == ' ' || str[i] == '\0')
			break ;
	data->command = ft_substr(str, start, i);
	if(str[i] != '\0')
	{
		start = i + 1;
		while (str[++i])
			if (str[i] == '\0' || str[i] == '<' || str[i] == '>')
				break ;
		data->arg = ft_substr(str, start, i - start);
		start = i + 1;
		if (str[i] == '<' && str[i + 1] == '<')
		{
			start++;
			data->menos_dob = 1;
		}
		else if(str[i] == '<' )
			data->menos = 1;
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			start++;
			data->mas_dob = 1;
		}
		else if (str[i] == '>')
			data->mas = 1;
		if (str[i] != '\0')
		{
			while (str[++i])
				;
			data->sub_arg = ft_substr(str, start + 1, i - start);
		}
	}
	printf("command\t\t|%s\n", data->command);
	printf("arg\t\t|%s\n", data->arg);
	printf("redir_men\t|%d\n", data->menos);
	printf("redir_men_d\t|%d\n", data->menos_dob);
	printf("redir_mas\t|%d\n", data->mas);
	printf("redir_mas_d\t|%d\n", data->mas_dob);
	printf("sub-arg\t\t|%s\n", data->sub_arg);
	
}
t_data *ft_create_data(char *str, t_list *prev, t_vars *vars)
{
	t_data *data;

	data = calloc(sizeof(t_data), sizeof(t_data));
	*data = (t_data){};
	data->cmd_splited = malloc(sizeof(char *) * 3);
	data->cmd_splited[0] = data->command;
	data->cmd_splited[1] = data->arg;
	data->cmd_splited[2] = NULL;
	if (!str[0])
	{
		while (!str[0])
			str = readline(">");
	}

	data->cmd_arg_full = str;
	ft_subpars(str, data);
	ft_split_args(data, vars);
	data->prev = prev;
	return (data);
}
void ft_lst_cmd(t_vars *vars)
{

	t_list *prev;
	t_list *temp;
	t_data *data;
	int i;

	i = -1;
	prev = NULL;
	vars->list = NULL;
	while (vars->split[++i])
	{
		// data->cmd_arg = vars->split[i];
		// free(vars->split[i]);
		data = ft_create_data(vars->split[i], prev, vars);
		// printf("fitst data %s\n", data->cmd_arg);
		if (vars->list == NULL)
		{
			vars->list = ft_lstnew((t_data *)data);
			data->prev = NULL;
			// printf("lsst_cmd %s\n", ((t_data *)vars->list->content)->cmd_arg);
			temp = vars->list;
		}
		else 
		{
			temp = ft_lstnew(((t_data *)data));
			ft_lstadd_back(&vars->list, temp);
		}
		prev = temp;
		temp = temp->next;

	}
	temp = vars->list;
	while (temp)
	{
		// printf("print puntero from list ->%s\n", ((t_data *)temp->content)->cmd_arg_full);
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
char	**ft_triming(char **separ, size_t num_pipes, t_vars *vars)
{
	int	i;
	int	i2;
	int	i3;
	char **temp;
	char **mem;
	int *sub_type;

	mem = separ;
	temp = malloc(sizeof(char *) * (num_pipes + 2));
	printf("sizeof%lu\n", sizeof(separ));
	i = -1;
		while (separ[++i])
		{
			printf("i%d\n", i);
			printf("separ%s\n", separ[i]);
			temp[0] = ft_strtrim(separ[i], " ");
			sub_type = ft_mask(temp[0], vars);
			// free(separ[i]);
			i2 = -1;
			i3 = 0;
			while (temp[0][++i2])
			{
				// printf("%d\n",sub_type[i]);
				printf("check\n");
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
	return(separ);
}
char **spliting(char *wololoco, int *type, size_t num_pipes, t_vars *vars)
{
	int i = -1;
	int i2 = 0;
	char **separ;
	char **separ2;
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

	separ2 = ft_triming(separ, num_pipes, vars);
	while(i2 != -1)
		free(separ[i2--]);
	free(separ);
	// for(i= 0; temp[i] != '\0'; i++)
	// 	printf("%s\n", temp[i]);
 	return(separ2);
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
	if (line == 0)
		return (0);
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
				type[i] = 6;
			type[i] = 2;
		}
		else if (line[i] == '|'  ) //&& line[i + 1] != '\0' && !ft_lastpipe(line + i + 1)
			type[i] = 3; 
		// else if (ft_lastpipe(line + i + 1))
		// {
		// 	while (line[i])
		// 	{
		// 		if (ft_isalnum(line[i])
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
// void ft_clear_list(t_list *list)
// {
// 	t_list *temp;
//
// 	temp = NULL;
// 	while (list->next != NULL)
// 	{
// 		temp = list->next;
// 		free(list);
// 	}
// 	free(temp);
// }
int main(void)
{
	t_vars vars;

	vars = (t_vars){};

	//int i;
	// char *finline;
	// char **split;
	vars.quotes  = "'";
	while (1)
	{
		vars.line = readline("Minishell $ ");
		// if (ft_strlen(vars.line) == 0)
		// {
		// 	write(1, "exit\n", 5);
		// 	free(vars.line);
		// 	exit (0);
		// }
		if (!ft_strncmp ("exit", vars.line, ft_strlen(vars.line)))
		{
			write(1, "exit\n", 5);
			free(vars.line);
			exit (0);
		}

		add_history(vars.line); //solo añadir si es válido
		// line_cop = ft_strdup(wololo);
		vars.line_len = ft_strlen(vars.line);
		// printf("%zu\n", line_len	);sad
		vars.type = ft_mask(vars.line, &vars); //free
		vars.num_pipes = ft_numpipes(vars.line, vars.type);
		if (vars.num_pipes)
			vars.split = spliting(vars.line, vars.type, vars.num_pipes, &vars);
		// else
		// {
		// 	// vars.split = malloc(sizeof(char *) * 2);
		// 	vars.split = ft_triming(&vars.line, 0, &vars);
		// 	vars.split[1] = NULL;
		// }
		// ft_lst_cmd(&vars);
// 		ft_clear_list(vars.list);
		// free(vars.type);
		printf("\n\n\n ! check !\n\n\n");
		free(vars.line);
		free(vars.type);
// 		system("leaks minishell");


		// ft_test(&vars);

		// printf("%s\n", vars.split[0]);
		// i = -1;
			// printf("%s\n", split[0]);

		// while (split[++i])
		// 	printf("%s\n", split[i]);
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
