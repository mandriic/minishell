#include "../inc/minishell.h"

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