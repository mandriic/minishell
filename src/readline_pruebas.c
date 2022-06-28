#include "../inc/minishell.h"
t_data *ft_create_data(char *str, t_list *prev)
{
	t_data *data;

	data = malloc(sizeof(t_data));
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
char **spliting(char *wololoco, int *type, size_t num_pipes)
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
	while (separ[++i])
		temp[i] = ft_strtrim(separ[i], " ");
	temp[i] = NULL;
	// for(i= 0; temp[i] != '\0'; i++)
	// 	printf("%s\n", temp[i]);
 	return(temp);
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
		vars.line = readline(">> ");
		add_history(vars.line);
		// line_cop = ft_strdup(wololo);
		vars.line_len = ft_strlen(vars.line);
		// printf("%zu\n", line_len	);
		vars.type = malloc(sizeof(int) * vars.line_len);
		i = -1;
		while (vars.line[++i] != '\0')
		{
			if(vars.line[i] == vars.quotes[0])
			{
				vars.type[i] = 1;
				while (vars.line[++i] != vars.quotes[0])
					vars.type[i] = 0;
				vars.type[i] = 1;
			}
			else if (vars.line[i] == '"')
			{
				vars.type[i] = 2;
				while (vars.line[++i] != '"')
					vars.type[i] = 0;
				vars.type[i] = 2;
			}
			else if (vars.line[i] == '|' && vars.line[i + 1] != '\0')
				vars.type[i] = 3;
			else if (vars.line[i] == '|' && vars.line[i + 1] == '\0')
				vars.type[i] = 4;
			else
				vars.type[i] = 0;
		}
		vars.num_pipes = ft_numpipes(vars.line, vars.type);
		if (vars.num_pipes)
			vars.split = spliting(vars.line, vars.type, vars.num_pipes);
		else
		{
			vars.split = malloc(sizeof(char *) * 2);
			vars.split[0] = vars.line;
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