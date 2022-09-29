#include "../inc/minishell.h"
void ft_my_free_d(char **arr)
{
	free(arr);
	arr = NULL;
}

void ft_my_free(char *str)
{
	free(str);
	str = NULL;
}

void ft_free_dob_arr(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			ft_my_free(arr[i]);
		ft_my_free_d(arr);
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
		ft_free_dob_arr(list->infiles);
		ft_free_dob_arr(list->outfiles);
		ft_free_dob_arr(list->appends);
		ft_free_dob_arr(list->heredocs);
		ft_free_dob_arr(list->comando_bonito);
		// ft_free_dob_arr(list->pre_comand_bon);

		//ft_my_free(list->comando_a_pelo);
		//ft_my_free(list->vars_resolv);
		free(list->cmd_splited);
		// if (list->heredocs)
		// if (list->pre_comand_bon)
		// 	ft_my_free_d(list->pre_comand_bon);
		// if(list->infiles != NULL)
		// 	ft_my_free_d(list->infiles);
		// if(list->outfiles != NULL)
		// 	ft_my_free_d(list->outfiles);
		// if(list->comando_bonito)
		// 	ft_my_free_d(list->comando_bonito);
		// if(list->appends != NULL)
		// 	ft_my_free_d(list->appends);
		// ft_my_free_d(list->pre_args);
		//ft_my_free(list->infiles);
		//ft_my_free(list->appends);
		//ft_my_free(list->outfiles);
		// if(list->heredocs)
		// 	ft_my_free(list->heredocs);
		// ft_free_dob_arr(list->pre_args);
		// ft_free_dob_arr(list->infiles);
		
		//ft_my_free(((t_data *)list->content)->cmd_list->comando_con_flags);
		if (list->sub_arg)
			ft_my_free(list->sub_arg);
		//ft_my_free(((t_command *)list->content)->cmd_list);
		//ft_my_free(list->content);
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
	// char	**pre_bon;
	// int		num_args;
	int 	*type;

	i = -1;
	i2 = 0;
	start = 0;
	com_bon = malloc(sizeof(char *) * BUFFER_SIZE);
	type = ft_mask(str, vars, 0);
	// int len = ft_strlen(str);
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
					ft_my_free(temp);
					start = i;
				}
				while( str[i] == '<' || str[i] == '>') //str[i] == ' ' ||
					i++;
				temp = ft_substr(str, start, i - start);
				com_bon[i2++] = ft_strtrim(temp, " ");
				ft_my_free(temp);
				start = i;
				// com_bon[i2++] = "<< ";
			}
			else if(type[i] == 10)
			{
				if (i != 0 && str[i - 1] != ' ')
				{
					temp = ft_substr(str, start, i - start);
					com_bon[i2++] = ft_strtrim(temp, " ");
					ft_my_free(temp);
					start = i;
				}
				while(str[i] == '<' || str[i] == '>') //str[i] == ' ' || 
					i++;
				temp = ft_substr(str, start, i - start);
				com_bon[i2++] = ft_strtrim(temp, " ");
					ft_my_free(temp);
				start = i;
			}
			else
			{
				temp = ft_substr(str, start, i - start + 1);
				com_bon[i2++] = ft_strtrim(temp, " ");
				ft_my_free(temp);
				start = i + 1;
			}
			// }
			// printf("combom .%s. \n", com_bon[i2 - 1]);
	
		}
	}
	temp = ft_substr(str, start, i - start + 1);
	com_bon[i2++] = ft_strtrim(temp, " ");
	ft_my_free(temp);
	com_bon[i2] = NULL;
	// printf("combom .%s. \n", com_bon[i2 - 1]);
	// sleep(10);
	free(type);
	return (com_bon);
}
void	ft_merge_comando_args(t_command *data)
{
	int	i;
	// int i2;

	i = -1;
	if (data->pre_args)
	{
		while(data->pre_args[++i])
			;
		data->comando_bonito = malloc(sizeof(char *) * (i + 3));
		// data->comando_bonito[0] = data->comando_a_pelo;
		i = -1;
		while(data->pre_args[++i])
			data->comando_bonito[i] = ft_strdup(data->pre_args[i]);
		data->comando_bonito[i] = NULL;

	}
	else
	{
		// data->comando_bonito = malloc(sizeof(char *) * 2);
		// data->comando_bonito[0] = data->comando_a_pelo;
		data->comando_bonito = NULL;

	}
	ft_free_dob_arr(data->pre_args);

}
void	ft_heredoc(char **arr, t_command *data, int *i)
{
	char	*eofile;
	int		str_cmp;

	// if (i[0] == 0)
	// 	data->comando_a_pelo = arr[3];
	// else
	// 	data->comando_a_pelo = arr[0];
	eofile = arr[i[0] + 1];
	// printf("eofcheck\n");
	// printf("eof %s\n", eofile);
	// printf("len %ld\n",  ft_strlen(eofile));
	str_cmp = 1;
	if(!data->heredocs)
		data->heredocs = malloc(sizeof(char *) * BUFFER_SIZE);
	while(str_cmp)
	{
		data->heredocs[i[1]] = readline(">"); //<---------i'm here // i'm was here
		str_cmp = ft_strncmp(eofile, data->heredocs[i[1]], ft_strlen(eofile));
		i[1]++;
	}
	free(data->heredocs[--i[1]]);
	data->heredocs[i[1]--] = NULL;
	ft_print_dp(data->heredocs, "heredocs");
	i[0]++;
	// printf("ch3%d\n",chk);
	// while(ft_strncmp(eofile, data->heredocs[i3], ft_strlen(eofile)))
}
void	ft_initint(int *i, int len)
{
	int cou;

	cou = -1;
	while (++cou != len)
		i[cou] = 0;
}

void	ft_infile(char **arr, t_command *data, int *i)
{
	if (!data->infiles)
	{
		data->infiles = malloc(sizeof(char *) * BUFFER_SIZE);
		data->infiles[0] = NULL;
	}
	if (i[0] == 0)
		data->comando_a_pelo = arr[3];
	else if (!data->comando_a_pelo)
		data->comando_a_pelo = arr[0];
	data->infiles[i[3]++] = ft_strdup(arr[i[0] + 1]);
	data->infiles[i[3]] = NULL;
	i[0]++;

}

void	ft_appends(char **arr, t_command *data, int *i)
{
	if (!data->appends)
	{
		data->appends = malloc(sizeof(char *) * BUFFER_SIZE);
		// data->infiles[0] = NULL;
	}
	if (i[0] == 0)
		data->comando_a_pelo = arr[3];
	else if (!data->comando_a_pelo)
		data->comando_a_pelo = arr[0];
	data->appends[i[4]++] = ft_strdup(arr[i[0] + 1]);
	data->appends[i[4]] = NULL;
	i[0]++;
}

void	ft_outfiles(char **arr, t_command *data, int *i)
{
	if (!data->outfiles)
	{
		data->outfiles = malloc(sizeof(char *) * BUFFER_SIZE);
		// data->infiles[0] = NULL;
	}
	if (i[0] == 0)
		data->comando_a_pelo = arr[3];
	else if (!data->comando_a_pelo)
		data->comando_a_pelo = arr[0];
	data->outfiles[i[5]++] = ft_strdup(arr[i[0] + 1]);
	data->outfiles[i[5]] = NULL;
	i[0]++;
}

void	ft_check_redir_create(char **arr, t_command *data, int *i)
{
	if (arr[i[0]][0] == '<' && arr[i[0]][1] == '<')
		ft_heredoc(arr, data, i);
	else if (arr[i[0]][0] == '<')
		ft_infile(arr, data, i);
	else if (arr[i[0]][0] == '>' && arr[i[0]][1] == '>')
		ft_appends(arr, data, i);
	else if (arr[i[0]][0] == '>')
		ft_outfiles(arr, data, i);
	else //(arr[i][0] != '<' && arr[i][0] != '>')
	{
		if (!data->pre_args)
			data->pre_args = malloc(sizeof(char *) * BUFFER_SIZE);
		data->pre_args[i[2]++] = ft_strdup(arr[i[0]]);
		data->pre_args[i[2]] = NULL;
	}
}
int ft_check_redir(char **arr, t_command *data)
{
	int i[6];

	i[0] = -1;
	while(arr[++i[0]] != NULL)
	{
		if(arr[i[0]][0] == '<' || arr[i[0]][0] == '>')
		{
			ft_initint(i, 6);
			while(arr[i[0]] != NULL)
			{
				ft_check_redir_create(arr, data, i);
				i[0]++;
			}
			ft_merge_comando_args(data);
			ft_free_dob_arr(arr);
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
// void ft_send_dp(char **arr)
// {
// 	int i;
// 	char *temp;
// 	i = -1;
// 	while(arr[++i])
// 	{
// 		temp = ft_get_env(arr[i], ft_strlen(arr[i]));
// 		ft_my_free(arr[i]);
// 		arr[i] = temp;
// 	}
// }
void	ft_clean_dp(char **arr, t_vars *vars)
{
	int i = -1;
	// int i2 = -1;
	char *temp;
	
	while(arr[++i])
	{
		temp = ft_cleaning(arr[i], vars);
		ft_my_free(arr[i]);
		arr[i] = ft_strdup(temp);
		ft_my_free(temp);
	}
}
void	ft_resolv_com_bon(t_command *data, t_vars *vars)
{
	if (data->infiles || data->comando_bonito || data->appends\
		|| data->heredocs || data->outfiles)
	{
		if (data->infiles)
			ft_get_env2(&data->infiles, vars);
		if (data && data->comando_bonito)
			{
			
				ft_get_env2(&data->comando_bonito, vars);
			}
		if (data->appends)
			ft_get_env2(&data->appends, vars);
		if (data->heredocs)
			ft_get_env2(&data->heredocs, vars);
		if (data->outfiles)
			ft_get_env2(&data->outfiles, vars);
	}
}

char	**ft_dup_dp(char **src)
{
	int i = -1;
	char	**dst;

	while(src[++i])
		;
	dst = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (src[++i])
		dst[i] = ft_strdup(src[i]);
	dst[i] = NULL;
	ft_free_dob_arr(src);
	return (dst);
	
}

t_command *ft_create_data(char *str, t_vars *vars)
{
	t_command *data;

	data = malloc(sizeof(t_command));
	*data = (t_command){};
	if (!str[0])
	{
		while (str[0] == '\0')
			str = readline(">");
	}
	data->pre_comand_bon = ft_pre_com_bon(str, vars);
	if(!ft_check_redir(data->pre_comand_bon, data))
	{
		data->comando_bonito = ft_dup_dp(data->pre_comand_bon);        ////////////////// duplicarft_dup_dp(
		data->comando_a_pelo = data->comando_bonito[0];
	}
	ft_resolv_com_bon(data, vars);
	return (data);
}

void ft_lst_cmd(t_vars *vars)
{
	t_command *temp;
	// t_command *vars_data;
	t_command *data;
	t_command *prev;

	int i;
	i = -1;
	if (vars->cmd_list)
		ft_del_list(vars->cmd_list);
	prev = NULL;
	vars->cmd_list = NULL;
	while (vars->split[++i])
	{
		data = ft_create_data(vars->split[i], vars); //prev,
		// vars_data = data;
		if (vars->cmd_list == NULL)
		{
			vars->cmd_list = ft_lstnew_mod((t_command *)data); //vars_data
			data->prev = NULL;
			temp = vars->cmd_list;
		}
		else 
		{
			data->prev = prev;
			temp = ft_lstnew_mod(((t_command*)data)); //vars_data
			ft_lstadd_back_mod(&vars->cmd_list, temp);
		}
		prev = temp;
		temp = temp->next;
	}
	temp = vars->cmd_list;
	while (temp)
	{
		if(temp->comando_bonito)
			ft_print_dp(temp->comando_bonito, "!comando bonito!");
		if (temp->prev)
			ft_print_dp(temp->prev->comando_bonito, "prev ");
		if (temp->infiles)
			ft_print_dp(temp->infiles, "infiles");
		if (temp->outfiles)
			ft_print_dp(temp->outfiles, "outfiles");
		if (temp->appends)
			ft_print_dp(temp->appends, "appends");
		if (temp->heredocs)
			ft_print_dp(temp->heredocs, "heredocs");
		printf("end\n");
		temp = temp->next;
	}
	if (i != 1)
		ft_free_dob_arr(vars->split);
		// while (i != -1) // -1
		// 	ft_my_free(vars->split[i--]); //i--
		// ft_my_free_d(vars->split);
}