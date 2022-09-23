#include "../inc/minishell.h"

void	fr_subargs(char *str, char *temp, t_command *data, t_vars *vars)
{
	temp = ft_substr(str, vars->start2, vars->i2 - vars->start2);
	data->arg = ft_checkif_var(temp, vars); 
	free(temp);
	vars->start2 = vars->i2 + 1;
	if (str[vars->i2] == '<' && str[vars->i2 + 1] == '<')
	{
		vars->start2++;
		data->menos_dob = 1;
	}
	else if(str[vars->i2] == '<' )
		data->menos = 1;
	else if (str[vars->i2] == '>' && str[vars->i2 + 1] == '>')
	{
		vars->start2++;
		data->mas_dob = 1;
	}
	else if (str[vars->i2] == '>')
		data->mas = 1;
	if (str[vars->i2] != '\0')
	{
		while (str[++vars->i2])
			;
		data->sub_arg = ft_substr(str, vars->start2 + 1, vars->i2 - vars->start2);
	}
}

void	ft_subpars(char *str, t_command *data, t_vars * vars)
{
	char	*temp;

	temp = NULL;
	vars->i2 = -1;   						//antes i = 0; leak was found
	vars->start2 = 0;
	while (str[++vars->i2])
		if (str[vars->i2] == ' ' || str[vars->i2] == '\0')
			break ;
	data->comando_a_pelo = ft_substr(str, vars->start2, vars->i2);
	if(str[vars->i2] != '\0')
	{
		vars->start2 = vars->i2 + 1;
		while (str[++vars->i2])
			if (str[vars->i2] == '\0' || str[vars->i2] == '<' || str[vars->i2] == '>')
				break ;
		if ((str[vars->i2] == '<' || str [vars->i2] == '>') && str[vars->i2 + 1] == '\0')
		{
			if (vars->cmd_list)
				ft_del_list(vars->cmd_list);
			ft_end_of_cicle(vars);
			ft_submain(vars);
		}
		else
			fr_subargs(str, temp, data, vars);
		printf("command\t\t|%s\n", data->comando_a_pelo);
		data->comando_bonito = ft_split(data->arg, ' ');
		ft_print_dp(data->comando_bonito, "comando bonito");

		printf("arg\t\t|%s\n", data->arg);
		printf("redir_men\t|%d\n", data->menos);
		printf("redir_men_d\t|%d\n", data->menos_dob);
		printf("redir_mas\t|%d\n", data->mas);
		printf("redir_mas_d\t|%d\n", data->mas_dob);
		printf("sub-arg\t\t|%s\n", data->sub_arg);
	}	
}