#include "../inc/minishell.h"

void	ft_readline(void)
{
	t_vars  vars;

	vars = (t_vars){};
	vars.split = NULL;
	vars.list = NULL;
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
			exit (0);
		}
		if (ft_pre_check(vars))
			continue ;
		add_history(vars->line);
		vars->line_len = ft_strlen(vars->line);
		vars->type = ft_mask(vars->line, vars);
		if (vars->type != NULL)
			ft_line_exist(vars);
		ft_end_of_cicle(vars);
	}
}

void	ft_end_of_cicle(t_vars *vars)
{
	free(vars->line);
	vars->line = NULL;
	free(vars->type);
	vars->type = NULL;
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

void	ft_subcleaning(char *str, int *start, char **clear, char **temp, t_vars *vars)
{
	if (vars->i - *start != 0)
		{
			if (*start == 0)
				*temp = ft_substr(str, *start, vars->i - *start);
			else
				*temp = ft_substr(str, *start + 1, vars->i - *start - 1);
			*clear = ft_acumulate(*clear, *temp);
		}
	*start = vars->i;
	vars->i++;
	while (str[vars->i] != '"' && str[vars->i] != vars->quotes[0]  && str[vars->i] != '\0')
		vars->i++;
	*temp = ft_substr(str, *start + 1, vars->i - *start - 1);
	*start = vars->i;

	printf("CHEEECK\n");
	printf("cleaning temp .%s.\n", *temp);
	
	printf("clear befor .%s.\n", *clear);
	*clear = ft_acumulate(*clear, *temp);
	printf("clean desp .%s.\n", *clear);

}

char	*ft_cleaning(char *str, t_vars *vars)
{
	char	*clear;
	int		start;
	char	*temp;

	vars->i = -1;
	clear = NULL;
	temp = NULL;
	start = 0;
	while (str[++vars->i])
	{
		if (str[vars->i] == '"' || str[vars->i] == vars->quotes[0])
		{
			ft_subcleaning(str, &start, &clear, &temp, vars);
			if (str[vars->i] == '\0')
				break ;
		}
	}
	if (start !=vars->i && clear != NULL)
	{
		temp = ft_substr(str, start + 1,vars->i - start - 1);
		printf("error %s\n", temp);
		clear = ft_acumulate(clear, temp);	
		return (clear);
	}
	else if (clear == NULL)
	{
		free(clear);
		return (ft_strdup(str));
	}
	else
		return (clear);
}