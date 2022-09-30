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
		free(list->cmd_splited);

		if (list->sub_arg)
			ft_my_free(list->sub_arg);
		free(list);
		if(list  == last)
			break ;
		list = temp;
	}
	
}

void	ft_clean_dp(char **arr, t_vars *vars)
{
	int		i;
	char	*temp;
	
	i = -1;
	while(arr[++i])
	{
		temp = ft_cleaning(arr[i], vars);
		ft_my_free(arr[i]);
		arr[i] = ft_strdup(temp);
		ft_my_free(temp);
	}
}

// void	ft_initint(int *i, int len)
// {
// 	int cou;

// 	cou = -1;
// 	while (++cou != len)
// 		i[cou] = 0;
// }
