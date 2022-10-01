/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:13:45 by mandriic          #+#    #+#             */
/*   Updated: 2022/09/30 16:13:49 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	char	**pre_bon;
	int		num_args;
	int 	*type;

	i = -1;
	i2 = 0;
	start = 0;
	com_bon = malloc(sizeof(char *) * BUFFER_SIZE);
	type = ft_mask(str, vars, 0);
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

	i = -1;
	if (data->pre_args)
	{
		while (data->pre_args[++i])
			;
		data->comando_bonito = malloc(sizeof(char *) * (i + 3));
		i = -1;
		while (data->pre_args[++i])
			data->comando_bonito[i] = ft_strdup(data->pre_args[i]);
		data->comando_bonito[i] = NULL;
	}
	else
		data->comando_bonito = NULL;
	ft_free_dob_arr(data->pre_args);
}

int	ft_check_redir(char **arr, t_command *data)
{
	int	i[6];

	i[0] = -1;
	while (arr[++i[0]] != NULL)
	{
		if (arr[i[0]][0] == '<' || arr[i[0]][0] == '>')
		{
			ft_initint(i, 6);
			while (arr[i[0]] != NULL)
			{
				ft_check_redir_create(arr, data, i);
				i[0]++;
			}
			ft_merge_comando_args(data);
			ft_free_dob_arr(arr);
			return (1);
		}
	}
	return (0);
}

void	ft_resolv_com_bon(t_command *data, t_vars *vars)
{
	if (data->infiles || data->comando_bonito || data->appends
		|| data->heredocs || data->outfiles)
	{
		if (data->infiles)
			ft_get_env2(&data->infiles, vars);
		if (data->comando_bonito)
			ft_get_env2(&data->comando_bonito, vars);
		if (data->appends)
			ft_get_env2(&data->appends, vars);
		if (data->heredocs)
			ft_get_env2(&data->heredocs, vars);
		if (data->outfiles)
			ft_get_env2(&data->outfiles, vars);
	}
}

void	ft_add2list(t_vars *vars, t_command *data, t_command **prev,
	t_command **temp)
{
	if (vars->cmd_list == NULL)
	{
		vars->cmd_list = ft_lstnew_mod((t_command *)data);
		data->prev = NULL;
		*temp = vars->cmd_list;
	}
	else
	{
		data->prev = *prev;
		*temp = ft_lstnew_mod(((t_command *)data));
		ft_lstadd_back_mod(&vars->cmd_list, *temp);
	}
}

void	ft_lst_cmd(t_vars *vars)
{
	t_command	*temp;
	t_command	*data;
	t_command	*prev;
	int			i;

	i = -1;
	if (vars->cmd_list)
		ft_del_list(vars->cmd_list);
	prev = NULL;
	temp = NULL;
	vars->cmd_list = NULL;
	while (vars->split[++i])
	{
		data = ft_create_data(vars->split[i], vars);
		ft_add2list(vars, data, &prev, &temp);
		prev = temp;
		temp = temp->next;
	}
	temp = vars->cmd_list;
	while (temp)
	{
		if (temp->comando_bonito)
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
}
