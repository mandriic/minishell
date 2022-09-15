#include "../inc/minishell.h"
int	*ft_mask(char *line, t_vars *vars);
int	ft_lastpipe(char *str);
void	ft_end_of_cicle(t_vars *vars);
void	ft_submain(t_vars * vars);

void	ft_del_list(t_list *list)
{
	t_list	*last;
	t_list	*temp;

	temp = list;
	last = ft_lstlast(list);
	while(1)
	{
		temp = list->next;
		free(((t_data *)list->content)->cmd_list->comando_a_pelo);
		free(((t_data *)list->content)->cmd_list->arg);
		free(((t_data *)list->content)->cmd_list->cmd_splited);
		// free(((t_data *)list->content)->cmd_list->comando_con_flags);
		if (((t_data *)list->content)->cmd_list->sub_arg)
			free(((t_data *)list->content)->cmd_list->sub_arg);
		free(((t_data *)list->content)->cmd_list);
		free(list->content);
		free(list);
		if(list  == last)
			break ;
		list = temp;
	}
	
}

char	*ft_get_env(char *str, int len)
{
	char	var[len];
	char	*valor;
	char	*temp;
	// int 	mem;
	int 	i;
	// int flag;

	// flag = 0;
	i = -1;
	// mem = len;
	if(str[1] == '?')
	{
		var[0] = '$';
		var[1] = '?';
		var[2] = '\0';
	}
	else
	{
		while (++i != len)
		{
			// // if (str[i + 1] == '/')
			// // 	break ;
			// if (flag == 1)
			// 	var[i] = str[i];
			// else
			var[i] = str[i + 1];
			if (str[i + 1] == '\0' || str[i + 1] == '$')
				break ;
			printf("%c\n", var[i]);

		}
		var[i] = '\0';
	}
	// len-=1;
	// while (len + 1 != -1)
	// {
	// 	var[len] = str[len + 1];
	// 	if 
	// 	// printf("var[len] %c str [len--] %c\n", var[len], str[len]);
	// 	len--;
	// }
	printf("VAR %s\n",var);
	printf("STRRRRR %s\n", str);
	valor = getenv(var);
	printf("valor %s\n", valor);
	// printf("str[mem] %c\n", str[mem]);

	if (str[i + 1] == ' ' ) //|| str[i + 1] == '"'
		temp = ft_strjoin(valor, " ");
	else if (str[i + 1] == '/')
		temp = ft_strjoin(valor, "/");
	// else if(str[i + 1] == '/')
	// {
	// 	temp = ft_strjoin(valor, str + i + 1);
	// }
	else
		temp = ft_strdup(valor);
	return (temp);
}

char	*ft_acumulate(char *dest, char *part)
{
	int		lenpart;
	char	*temp;

	lenpart = ft_strlen(part);
	printf("lenpart %d\n", lenpart);
	if (lenpart == 0)
	{
		// printf("lenpart %d\n", lenpart);
		free(part);
		return (dest);
	}
	// printf("part %s\n", part);
	if (!dest)
	{
		// printf("CHARC\n");
		temp = ft_strdup(part);
		free(part);
	}
	else
	{
		// printf("CHARC2\n");
		temp = ft_strjoin(dest, part);
		if(dest != NULL)
		{
			// printf("dest %s\n", dest);
			free(dest);
			dest = NULL;
		}
		// if (part != NULL)
			free(part);
		part = NULL;
	}
	return (temp);
}
void	ft_checkif_var_subfoo(char *str, char **acum, int *type, t_vars *vars)
{
	vars->i = 0;
	char lastchar;

	lastchar = '\0';
	// vars->start = 0;
	printf("str %s\n", str);
	while (str[vars->i] != '\0')
	{
		if (str[vars->i] == '$' && (type[vars->i] == 6 || type[vars->i] == 0) && str[vars->i + 1] != ' ')
		{
				printf("str[vars->i] %c\n", str[vars->i]);
				if (vars->i - vars->start > 1 && (str [vars->i - 1] == ' ' || lastchar == '/' || str[vars->i - 1] != vars->quotes[0]))
				{
					// if (str[vars->i - 1] == '"')
					// 	vars->temp = ft_substr(str, vars->start, vars->i - vars->start - 1);
					// else
						vars->temp = ft_substr(str, vars->start, vars->i - vars->start); //ft_substr(str, vars->start, vars->i - vars->start - 1);
					printf("vars->temp %s\n", vars->temp);
					*acum = ft_acumulate(*acum, vars->temp);
					printf("accumulate1 %s\n", *acum);
					// free(temp);
				}
				vars->start = vars->i + 1;
				vars->i++;
				while (str[vars->i] != ' ' && str[vars->i] != '\0'  && str[vars->i] != '/'  && str[vars->i] != '"' && str[vars->i] != '$' )
					vars->i++;
				// printf("*i%d\n", i);
				// vars->var = ft_get_env(str + vars->start, vars->i - vars->start - 1); 
				vars->var = ft_get_env(str + vars->start - 1, vars->i - vars->start); 
				printf("var %s\n", vars->var);
				vars->start = vars->i + 1;
				*acum = ft_acumulate(*acum, vars->var);
				// if (str [vars->i] == '$')
				// 	vars->i--;
				lastchar = str[vars->i];
				printf("lastchar %c\n", lastchar);
				printf("accumulate %s\n", *acum);
				if (str[vars->i] == '$') // ?  && str[vars->i - 1] != ' ' && str[vars->i - 1] != '"'
					vars->i--;
		}
		// if (str[*i] != '\0')
		if (str[vars->i] == '\0')
			break;

		vars->i++;
	}
}
char *ft_cleaning(char *str)
{
	int i;
	char *cuot;
	// int i2;
	char *clear;
	int start;
	char *temp;

	
	cuot = "'";
	i = -1;
	// while (str[++i])
	// 	if (str[i] == '"' || str[i] == cuot[0])
	// 	{
			// i2 = ft_strlen(str);

			// clear = malloc(sizeof(char) * (i2 + 1));

			clear = NULL;
			start = 0;
			// i = -1;
			while (str[++i])
			{
				if (str[i] == '"' || str[i] == cuot[0])
				{
					if (i - start != 0)
					{
						if (start == 0)
							temp = ft_substr(str, start, i - start);
						else
							temp = ft_substr(str, start + 1, i - start - 1);
						clear = ft_acumulate(clear, temp);
						// free(temp);
					}
					start = i;
					i++;
					// if(clear != NULL)
					// {
					// 	temp = ft_substr(str, start, i - start - 1); // <-
					// 	clear = ft_acumulate(clear, temp);
					// 	start = i + 1;
					// }
					while (str[i] != '"' && str[i] != cuot[0]  && str[i] != '\0')
					{
						
						i++;
					}
					temp = ft_substr(str, start + 1, i - start - 1);
					start = i;
					printf("CHEEECK\n");

					printf("cleaning temp .%s.\n", temp);
					printf("clear befor .%s.\n", clear);
					clear = ft_acumulate(clear, temp);
					printf("clean desp .%s.\n", clear);

					if (str[i] == '\0')
						break ;
				}
			}
			if (start != i && clear != NULL) //start != 0 && 
			{
				// if (str[])
				temp = ft_substr(str, start + 1, i - start - 1); // start + 1
				printf("error %s\n", temp);
				clear = ft_acumulate(clear, temp);	
				// if(temp)
				// 	free(temp);
				
				return (clear);
			}
			else if (clear == NULL)
			{
				free(clear);
				free(clear);
				free(clear);
				free(clear);
				free(clear);
				free(clear);
				printf("!!!!!!!!!!!!chkkkkk\n");
				free(clear);
				free(clear);
				free(clear);
				free(clear);
				return (ft_strdup(str));
			}
			else
			{
				// free(str);
				printf("c_clear\n");
				return (clear);
			}
			// while(str[++i])
			// {
			// 	if (str[i] == '"' || str[i] == cuot)
			// 		i2++;

			// }
		// }
	// return (ft_strdup(str));
}
char	*ft_checkif_var(char *str, t_vars *vars)
{
	int		*type;
	char	*acum;
	char	*temp;

	vars->start = 0;
	type = ft_mask(str, vars);
	acum = NULL;
	// temp = NULL;
	printf("args only %s\n", str);
	ft_checkif_var_subfoo(str, &acum, type, vars);

	if (acum == NULL || str[vars->start - 1] == '\0')
	{
		printf("sstart - i %d \n", vars->start - 1);
			free(type);
			if (vars->start - 1 > 0 && str[vars->start - 1] == '\0' && acum != NULL) //? 
				return (acum);
			
			return(ft_cleaning(str)); //return(ft_strdup(str)); return(ft_cleaning(str));
	}
	// printf("char %c\n", str[vars->start - 1]);
	temp = ft_substr(str, vars->start, vars->i - vars->start); //start - 1
	printf("temp %s\n", temp); // <----------
	printf("accum %s\n", acum);
	// printf("char %c\n", str[start] );
	if (temp != NULL) //&& temp[0] != '\0'
		{
			acum = ft_acumulate(acum, temp);
			printf("accum222 %s\n", acum);

			free(type);
			temp = ft_cleaning(acum);
			free(acum);
			return (temp);
			// free(temp);
		}
	// else
		// free(temp);
	free(type);
	// printf("accumulate2 %s\n", acum);
	return(acum);
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
void	ft_subpars(char *str, t_command *data, t_vars * vars)
{
	// (void) vars;
	int		i;
	int		start;
	char	*temp;

	i = -1;   						//antes i = 0; leak was found
	start = 0;
	while (str[++i])
		if (str[i] == ' ' || str[i] == '\0')
			break ;
	data->comando_a_pelo = ft_substr(str, start, i);
	if(str[i] != '\0')
	{
		start = i + 1;
		while (str[++i])
			if (str[i] == '\0' || str[i] == '<' || str[i] == '>')
				break ;
		if ((str[i] == '<' || str [i] == '>') && str[i + 1] == '\0')
		{
			printf("bash: syntax error near unexpected token 'newline'\n");
			if (vars->list)
				ft_del_list(vars->list);
			ft_end_of_cicle(vars);
			ft_submain(vars);
		}
		else
		{
			temp = ft_substr(str, start, i - start);
			printf("temp!!!!!! %s\n", temp);
			data->arg = ft_checkif_var(temp, vars);
			// printf("data->arg %s\n", data->arg);
			free(temp);
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
		printf("command\t\t|%s\n", data->comando_a_pelo);
		printf("arg\t\t|%s\n", data->arg);
		printf("redir_men\t|%d\n", data->menos);
		printf("redir_men_d\t|%d\n", data->menos_dob);
		printf("redir_mas\t|%d\n", data->mas);
		printf("redir_mas_d\t|%d\n", data->mas_dob);
		printf("sub-arg\t\t|%s\n", data->sub_arg);
	}	
}
t_command *ft_create_data(char *str, t_list *prev, t_vars *vars)
{
	t_command *data;

	data = malloc(sizeof(t_command));
	*data = (t_command){};
	data->cmd_splited = malloc(sizeof(char *) * 3);
	data->cmd_splited[0] = data->comando_a_pelo;
	data->cmd_splited[1] = data->arg;
	data->cmd_splited[2] = NULL;
	// printf("str %c\n", str[0]);
	if (!str[0])
	{
		// printf("chl\n");
		while (str[0] == '\0')
			str = readline(">");
	}

	data->comando_con_flags = str;
	printf("DATAcmdarg_full %s\n", data->comando_con_flags);
	ft_subpars(str, data, vars);
	// ft_split_args(data, vars);
	data->prev = prev;
	return (data);
}
void ft_lst_cmd(t_vars *vars)
{

	t_list *prev;
	t_list *temp;
	t_data *vars_data;
	t_command *data;
	int i;
	i = -1;
	if (vars->list)
		ft_del_list(vars->list);
	prev = NULL;
	vars->list = NULL;
	while (vars->split[++i])
	{
		// data->cmd_arg = vars->split[i];
		// free(vars->split[i]);
		vars_data = malloc(sizeof(t_data));
		data = ft_create_data(vars->split[i], prev, vars);
		vars_data->cmd_list = data;
		// printf("fitst data %s\n", data->cmd_arg);
		if (vars->list == NULL)
		{
			vars->list = ft_lstnew((t_data *)vars_data);
			data->prev = NULL;
			// printf("lsst_cmd %s\n", ((t_data *)vars->list->content)->cmd_list->comando_con_flags);
			temp = vars->list;
		}
		else 
		{
			temp = ft_lstnew(((t_data *)vars_data));
			ft_lstadd_back(&vars->list, temp);
		}
		prev = temp;
		temp = temp->next;

	}

	temp = vars->list;
	while (temp)
	{
		 printf("print puntero from list ->%s\n", ((t_data *)temp->content)->cmd_list->comando_con_flags);
		temp = temp->next;
	}
	// printf("I%d",i);
	if (i != 1)
	{
		while (i != -1) // -1
			free(vars->split[i--]); //i--
		free(vars->split);
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
void	ft_triming(char **separ, size_t num_pipes, t_vars *vars, int one_comand)
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
char **spliting(char *wololoco, int *type, size_t num_pipes, t_vars *vars)
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
int	ft_lastpipe(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '|')
			return (0);
	// printf("%c\n", str[i]);
	return (1);
}
int	*ft_mask(char *line, t_vars *vars)
{
	int i;
	int len;
	int *type;
	i = -1;
	type = NULL;
	len = ft_strlen(line);
	if (len == 0)
		return(type);
	// printf("len %d", len);
	type = malloc(sizeof(int) * len);

	while (line[++i] != '\0')
	{
		if(line[i] == vars->quotes[0])
		{
			type[i] = 1;
			while (line[++i] != vars->quotes[0] && line[i] != '\0')
				type[i] = 5;
			if (line[i] == '\0')
				{
					printf("Not interpret unclosed quotes \n");
					free(type);
					if(vars->list)
						ft_del_list(vars->list);
					return(NULL);
				}
			type[i] = 1;
		}
		else if (line[i] == '"')
		{
			type[i] = 2;
			while (line[++i] != '"' && line[i] != '\0')
				type[i] = 6;
			if (line[i] == '\0')
				{
					printf("Not interpret unclosed quotes \n");
					free(type);
					if(vars->list)
						ft_del_list(vars->list);
					return(NULL);
				}
			else
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
void ft_end_of_cicle(t_vars *vars)
{

		
		free(vars->line);
		vars->line = NULL;
		free(vars->type);
		// free(vars.split);
		vars->type = NULL;
		// free(vars->temp);
		// vars->temp = NULL;

}
int	ft_pre_check(t_vars *vars)
{
	int	alpha;
	vars->i = -1;
	alpha = 0;
	while(vars->line[++vars->i])
	{
		if (ft_isalnum(vars->line[vars->i]))
			alpha++;
	}
	if (alpha == 0)
		return(1);
	return (0);
}
void ft_submain(t_vars *vars)
{
	while (1)
	{
		vars->line = readline("Minishell $ ");
		// if (ft_strlen(vars.line) == 0)
		// {
		// 	write(1, "exit\n", 5);
		// 	free(vars.line);
		// 	exit (0);
		// }
		if (!ft_strncmp ("exit", vars->line, ft_strlen(vars->line)))
		{
			write(1, "exit\n", 5);
			free(vars->type);
			free(vars->line);
			exit (0);
		}
		if (ft_pre_check(vars))
			continue ;
		add_history(vars->line); //solo añadir si es válido
		// line_cop = ft_strdup(wololo);
		vars->line_len = ft_strlen(vars->line);
		// printf("%zu\n", line_len	);sad
		vars->type = ft_mask(vars->line, vars); //free
		if (vars->type != NULL)
		{
			vars->num_pipes = ft_numpipes(vars->line, vars->type);
			if (vars->num_pipes)
				vars->split = spliting(vars->line, vars->type, vars->num_pipes, vars);
			else
			{
				free(vars->type);
				vars->type = NULL;
				ft_triming(&vars->line, 0, vars, 1);
				// vars->split[1] = NULL;
			}
			ft_lst_cmd(vars);
		}
		ft_end_of_cicle(vars);
	}
}
int main(void)
{
	t_vars vars;

	vars = (t_vars){};
	vars.split = NULL;
	vars.list = NULL;
	vars.line = NULL;
	vars.quotes  = "'";
	ft_submain(&vars);
// 		system("leaks minishell");
	return (0);
}
