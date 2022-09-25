#include "../inc/minishell.h"
void ft_free_dob_arr(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
}
void	ft_del_list(t_command *list)
{
	t_command	*last;
	t_command	*temp;

	temp = list;
	last = ft_lstlast_mod(list);
	while(1)
	{
		temp = list->next;
		// free(list->comando_a_pelo);
		// free(list->vars_resolv);
		free(list->cmd_splited);
		// if (list->heredocs)
		ft_free_dob_arr(list->heredocs);
		ft_free_dob_arr(list->pre_comand_bon);
		free(list->comando_bonito);
		free(list->pre_args);
		free(list->infiles);
		// ft_free_dob_arr(list->pre_args);
		// ft_free_dob_arr(list->infiles);
		
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
	int i2;
	int	start;
	char	*temp;
	char	**com_bon;
	char	**pre_bon;
	int		num_args;
	int 	*type;

	i = -1;
	i2 = 0;
	start = 0;
	com_bon = malloc(sizeof(char *) * 10000);
	type = ft_mask(str, vars);
	int len = ft_strlen(str);
	// while(++i != len)
	// 	printf("type[%d] - %d\n", i, type[i]);
	i = -1;
	// ft_print_arrint(type, "type");
	// printf("string %s\n", str);
	while (str[++i] != '\0')
	{
		if ((str[i] == ' ' && type[i] != 5 && type[i] != 6 ) || type[i] == 11 || type[i] == 10)
		{
			if (type[i] == 11)
			{
				if (i != 0 && str[i - 1] != ' ')
				{
					temp = ft_substr(str, start, i - start);
					com_bon[i2++] = ft_strtrim(temp, " ");
					free(temp);
					start = i;
				}
				while( str[i] == '<' || str[i] == '>') //str[i] == ' ' ||
					i++;
				temp = ft_substr(str, start, i - start);
				com_bon[i2++] = ft_strtrim(temp, " ");
				free(temp);
				start = i;
				// com_bon[i2++] = "<< ";
			}
			else if(type[i] == 10)
			{
				if (i != 0 && str[i - 1] != ' ')
				{
					temp = ft_substr(str, start, i - start);
					com_bon[i2++] = ft_strtrim(temp, " ");
					free(temp);
					start = i;
				}
				while(str[i] == '<' || str[i] == '>') //str[i] == ' ' || 
					i++;
				temp = ft_substr(str, start, i - start);
				com_bon[i2++] = ft_strtrim(temp, " ");
					free(temp);
				start = i;
			}
			else
			{
				temp = ft_substr(str, start, i - start + 1);
				com_bon[i2++] = ft_strtrim(temp, " ");
				free(temp);
				start = i + 1;
			}
			// }
			// printf("combom .%s. \n", com_bon[i2 - 1]);
	
		}
	}
	temp = ft_substr(str, start, i - start + 1);
	com_bon[i2++] = ft_strtrim(temp, " ");
	free(temp);
	com_bon[i2] = NULL;
	// printf("combom .%s. \n", com_bon[i2 - 1]);
	// sleep(10);
	free(type);
	return (com_bon);
}
void	ft_merge_comando_args(t_command *data)
{
	int	i;
	int i2;

	i = -1;
	if (data->pre_args)
	{
		while(data->pre_args[++i])
			;
		data->comando_bonito = malloc(sizeof(char *) * (i + 3));
		data->comando_bonito[0] = data->comando_a_pelo;
		i = -1;
		while(data->pre_args[++i])
			data->comando_bonito[i + 1] = data->pre_args[i];
		data->comando_bonito[i + 1] = NULL;

	}
	else
		data->comando_bonito[0] = data->comando_a_pelo;

}

int ft_check_redir(char **arr, t_command *data)
{
	int i;
	int i2;
	int i3;
	int i4;
	int i5;
	char *eofile;
	int ret = 0;

	i = -1;
	while(arr[++i] != NULL)
	{
		i2 = 0;
		if(arr[i][0] == '<' || arr[i][0] == '>')
		{
			i = 0;
			i4 = 0;
			i5 = 0;
			while(arr[i] != NULL)
			{
				i3 = -1;
				if (arr[i][i2] == '<' && arr[i][i2 + 1] == '<')
				{

					if (i == 0)
						data->comando_a_pelo = arr[3];
					else
						data->comando_a_pelo = arr[0];
					eofile = arr[i + 1];
					// printf("eofcheck\n");
					printf("eof %s\n", eofile);
					// printf("len %ld\n",  ft_strlen(eofile));
					int str_cmp = 1;
					data->heredocs = malloc(sizeof(char *) * 10000);
					while(str_cmp)
					{
						data->heredocs[++i3] = readline(">"); //<---------i'm here
						str_cmp = ft_strncmp(eofile, data->heredocs[i3], ft_strlen(eofile));
					}
					data->heredocs[i3] = NULL;
					ft_print_dp(data->heredocs, "heredocs");
					// printf("ch3%d\n",chk);
					// while(ft_strncmp(eofile, data->heredocs[i3], ft_strlen(eofile)))
				}
				else if (arr[i][0] == '<')
				{
					if (!data->infiles)
					{
						data->infiles = malloc(sizeof(char *) * 10000);
						data->infiles[0] = NULL;
					}
					if (i == 0)
						data->comando_a_pelo = arr[3];

					else if (!data->comando_a_pelo)
						data->comando_a_pelo = arr[0];
					data->infiles[i5++] = arr[i + 1];
					data->infiles[i5] = NULL;
				}

				else if (arr[i][0] == '-')
				{
					if (!data->pre_args)
					{
						data->pre_args = malloc(sizeof(char *) * 10000);
						// data->pre_args[0] = NULL;
					}
					data->pre_args[i4++] = arr[i];
					data->pre_args[i4] = NULL;
				}
								
				// printf("arr - ? .%c.\n", arr[i][0]);

				i++;
			}
			if (data->pre_args && data->pre_args[0] != NULL)
				ft_print_dp(data->pre_args, "args");
			if (data->infiles && data->infiles[0] != NULL)	
				ft_print_dp(data->infiles, "infiles");
			printf("comando a pelo .%s.\n", data->comando_a_pelo);
			ft_merge_comando_args(data);
			return(1);
		}

	}
	return (0);
}

// void ft_files(t_command *data)
// {

// 	while(arr[++i] != NULL)
// 	{
// 		i2 = -1;
// 		while(arr[i][++i2] != '\0')
// 			if(arr[i][i2] == '<' || arr[i][i2] == '>')
// 				return (i + 1);
// 	}
// 	whi
// 	if (data->pre_comand_bon[0][0] == '<')
// 	{
// 		if (data->pre_comand_bon[0][1] == '<')
// 		{
// 			data->heredocs[0] = "herodocs";
// 		}
// 		data->infiles[o]
// 	}
// }
t_command *ft_create_data(char *str, t_vars *vars)
{
	t_command *data;

	data = malloc(sizeof(t_command));
	*data = (t_command){};
	if (!str[0])
	{
		// printf("chl\n");
		while (str[0] == '\0')
			str = readline(">");
	}
	data->pre_comand_bon = ft_pre_com_bon(str, vars);
	ft_print_dp(data->pre_comand_bon, "data->pre_comand_bon");
	if(!ft_check_redir(data->pre_comand_bon, data))
	{
		data->comando_bonito = data->pre_comand_bon;
		data->comando_a_pelo = data->pre_comand_bon[0];
	}
	ft_print_dp(data->comando_bonito, "COMANDO BONITO FIN");

	// else
	// {
	// 	ft_files(data);
	// }
	// data->vars_resolv = ft_checkif_var(str, vars);
	// printf("resolved %s\n", data->vars_resolv);

	// data->pre_comand_bon = ft_pre_com_bon(data->vars_resolv, vars);







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
		// ft_print_dp(temp->comando_bonito, "comando bonito list");
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