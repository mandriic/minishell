#include "../inc/minishell.h"

void	ft_del_list(t_list *list)
{
	t_list	*last;
	t_list	*temp;

	temp = list;
	last = ft_lstlast(list);
	while(1)
	{
		temp = list->next;
		free(((t_command *)list->content)->comando_a_pelo);
		free(((t_command *)list->content)->arg);
		free(((t_command *)list->content)->cmd_splited);
		// free(((t_data *)list->content)->cmd_list->comando_con_flags);
		if (((t_command *)list->content)->sub_arg)
			free(((t_command *)list->content)->sub_arg);
		// free(((t_command *)list->content)->cmd_list);
		free(list->content);
		free(list);
		if(list  == last)
			break ;
		list = temp;
	}
	
}

t_command *ft_create_data(char *str, t_vars *vars)
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
	// data->prev = prev;
	return (data);
}

void ft_lst_cmd(t_vars *vars)
{

	// t_list *prev;
	t_list *temp;
	t_command *vars_data;
	t_command *data;
	int i;
	i = -1;
	if (vars->list)
		ft_del_list(vars->list);
	// prev = NULL;
	vars->list = NULL;
	while (vars->split[++i])
	{
		// data->cmd_arg = vars->split[i];
		// free(vars->split[i]);
		// vars_data = malloc(sizeof(t_command));
		data = ft_create_data(vars->split[i], vars); //prev,
		vars_data = data;
		// printf("fitst data %s\n", data->cmd_arg);
		if (vars->list == NULL)
		{
			vars->list = ft_lstnew((t_command *)vars_data);
			// data->prev = NULL;
			// printf("lsst_cmd %s\n", ((t_data *)vars->list->content)->cmd_list->comando_con_flags);
			temp = vars->list;
		}
		else 
		{
			temp = ft_lstnew(((t_command*)vars_data));
			ft_lstadd_back(&vars->list, temp);
		}
		// prev = temp;
		temp = temp->next;

	}

	temp = vars->list;
	while (temp)
	{
		 printf("print puntero from list ->%s\n", ((t_command *)temp->content)->comando_con_flags);
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