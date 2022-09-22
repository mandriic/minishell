#include "../inc/minishell.h"

void	ft_del_list(t_command *list)
{
	t_command	*last;
	t_command	*temp;

	temp = list;
	last = ft_lstlast_mod(list);
	while(1)
	{
		temp = list->next;
		free(list->comando_a_pelo);
		free(list->vars_resolv);
		free(list->cmd_splited);
		// free(((t_data *)list->content)->cmd_list->comando_con_flags);
		if (list->sub_arg)
			free(list->sub_arg);
		// free(((t_command *)list->content)->cmd_list);
		// free(list->content);
		free(list);
		if(list  == last)
			break ;
		list = temp;
	}
	
}

t_command	*ft_lstnew_mod(t_command *content)
{
	t_command	*new;

	// new = (t_command *)malloc(sizeof(t_command));
	// if (!new)
	// 	return (NULL);
	new = content;
	// new->content = content;
	new->next = NULL;
	return (new);
}



t_command	*ft_lstlast_mod(t_command *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_mod(t_command **lst, t_command *new)
{
	t_command	*old_last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	old_last = ft_lstlast_mod(*lst);
	old_last->next = new;
}

char	**ft_pre_com_bon(char *str, t_vars *vars)
{
	int	i;
	int	start;
	char	*temp;
	char	**com_bon;
	int		num_args;
	int 	*type;

	type = ft_mask(str, vars);
	// ft_print_arrint(type, "type");
	// num_args = 0;
	// i = -1;
	// start = 0;
	// while(str[++i])
	// {
	// 	if (str[i] == ' ')
	// 		num_args++;
	// 	if (type[i] == 1)
	// 	{
	// 		i++;
	// 		while(type[i] != 1)
	// 			i++;
	// 		num_args++;
			
	// 	}
	// 	// {
	// 		// start = i;
	// 		// temp = ft_substr(str, start, i - start);
	// 		// com_bon = 
	// 	// }
	// }
}
t_command *ft_create_data(char *str, t_vars *vars)
{
	t_command *data;

	data = malloc(sizeof(t_command));
	*data = (t_command){};
	// data->cmd_splited = malloc(sizeof(char *) * 3);
	// data->cmd_splited[0] = data->comando_a_pelo;
	// data->cmd_splited[1] = data->arg;
	// data->cmd_splited[2] = NULL;
	// printf("str %c\n", str[0]);
	if (!str[0])
	{
		// printf("chl\n");
		while (str[0] == '\0')
			str = readline(">");
	}

	data->comando_con_flags = str;
	data->vars_resolv = ft_checkif_var(str, vars);
	printf("resolved %s\n", data->vars_resolv);

	data->pre_comand_bon = ft_pre_com_bon(data->vars_resolv, vars);







	// ft_split_args(data,vars);

	// ft_print_dp(data->comando_bonito," com bon");
	// printf("DATAcmdarg_full %s\n", data->comando_con_flags);

	// ft_subpars(str, data, vars);
	// ft_split_args(data, vars);
	// data->prev = prev;
	return (data);
}

void ft_lst_cmd(t_vars *vars)
{

	// t_list *prev;
	t_command *temp;
	t_command *vars_data;
	t_command *data;
	int i;
	i = -1;
	if (vars->cmd_list)
		ft_del_list(vars->cmd_list);
	// prev = NULL;
	vars->cmd_list = NULL;
	while (vars->split[++i])
	{
		// data->cmd_arg = vars->split[i];
		// free(vars->split[i]);
		// vars_data = malloc(sizeof(t_command));
		data = ft_create_data(vars->split[i], vars); //prev,
		vars_data = data;
		// printf("fitst data %s\n", data->cmd_arg);
		if (vars->cmd_list == NULL)
		{
			vars->cmd_list = ft_lstnew_mod((t_command *)vars_data);
			// data->prev = NULL;
			// printf("lsst_cmd %s\n", ((t_data *)vars->cmd_list->content)->cmd_list->comando_con_flags);
			temp = vars->cmd_list;
		}
		else 
		{
			temp = ft_lstnew_mod(((t_command*)vars_data));
			ft_lstadd_back_mod(&vars->cmd_list, temp);
		}
		// prev = temp;
		temp = temp->next;

	}

	temp = vars->cmd_list;
	while (temp)
	{
		 printf("print puntero from list ->%s\n", temp->comando_con_flags);
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