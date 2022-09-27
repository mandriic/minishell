#include "../inc/minishell.h"

void	ft_readline(void)
{
	t_vars  vars;

	vars = (t_vars){};
	vars.split = NULL;
	// vars.list = NULL;
	vars.line = NULL;
	vars.quotes  = "'";
	ft_submain(&vars);
}

void	ft_line_exist(t_vars *vars)
{
	vars->num_pipes = ft_numpipes(vars->line, vars->type);
	if (vars->num_pipes)
		vars->split = spliting(vars->line, vars->type, vars->num_pipes, vars);
	else
	{
		free(vars->type);
		vars->type = NULL;
		ft_triming(&vars->line, 0, vars, 1);
	}
	ft_lst_cmd(vars);
}

void	ft_submain(t_vars *vars)
{
	while (1)
	{
		vars->line = readline("Minishell $ ");
		if (!ft_strncmp ("exit", vars->line, ft_strlen(vars->line)))
		{
			write(1, "exit\n", 5);
			system("leaks minishell");
			exit (0);
		}
		if (ft_pre_check(vars))
			continue ;
		add_history(vars->line);
		vars->line_len = ft_strlen(vars->line);
		vars->type = ft_mask(vars->line, vars, 1);
		if (vars->type != NULL)
			ft_line_exist(vars);
		ft_end_of_cicle(vars);
	}
}

void	ft_end_of_cicle(t_vars *vars)
{
	ft_my_free(vars->line);
	free(vars->type);
}

int	ft_pre_check(t_vars *vars)
{
	int alpha;

	vars->i = -1;
	alpha = 0;
	while (vars->line[++vars->i])
	{
		if (ft_isalnum(vars->line[vars->i]))
			alpha++;
	}
	if (alpha == 0)
		return (1);
	return (0);
}

void	ft_subcleaning(char *str, char **clear, char **temp, t_vars *vars, int *type)
{
	if (vars->i2 - vars->start2 != 0)
		{
			if (vars->start2 == 0)
				*temp = ft_substr(str, vars->start2, vars->i2 - vars->start2);
			else
				*temp = ft_substr(str, vars->start2 + 1, vars->i2 - vars->start2 - 1);
			*clear = ft_acumulate(*clear, *temp);
		}
	vars->start2 = vars->i2;
	vars->i2++;
	while (str[vars->i2] != '\0' && type[vars->i2] != 1 && type[vars->i2] != 2) //(str[vars->i2] != '"' && str[vars->i2] != vars->quotes[0]  && str[vars->i2] != '\0')
		vars->i2++;
	*temp = ft_substr(str, vars->start2 + 1, vars->i2 - vars->start2 - 1);
	vars->start2 = vars->i2;

	printf("CHEEECK\n");
	printf("cleaning temp .%s.\n", *temp);
	
	printf("clear befor .%s.\n", *clear);
	*clear = ft_acumulate(*clear, *temp);
	printf("clean desp .%s.\n", *clear);

}

char	*ft_cleaning(char *str, t_vars *vars)
{
	char	*clear;
	char	*temp;
	int		*type;
	vars->i2 = -1;
	clear = NULL;
	temp = NULL;
	type = ft_mask(str, vars, 0);

	vars->start2 = 0;
	while (str[++vars->i2])
	{
		// printf(" str .%c. ", str[vars->i2]);
		// printf(" type %d", type[vars->i2]);
		// printf(" i2 %d \n", vars->i2);
		if (type[vars->i2] == 2 || type[vars->i2] == 1) ///str[vars->i2] == '"' || str[vars->i2] == vars->quotes[0])
		{
			if ((str[vars->i2] == '"' && str[vars->i2 + 1] == '"') || (str[vars->i2] == vars->quotes[0] && str[vars->i2 + 1] == vars->quotes[0]) || str[vars->i2 + 1] == '\0')
			{
				free(type);
				return(NULL);
			}
			ft_subcleaning(str, &clear, &temp, vars, type);
			if (str[vars->i2] == '\0')
				break ;
		}
		if (str[vars->i2] == '\0')
				break ;
	}
	free(type);
	if (vars->start2 !=vars->i2 && clear != NULL)
	{
		temp = ft_substr(str, vars->start2 + 1,vars->i2 - vars->start2 - 1);
		clear = ft_acumulate(clear, temp);	
		// ft_my_free(str);
		return (clear);
	}
	else if (clear == NULL)
		return (ft_strdup(str));
	return (clear);
}