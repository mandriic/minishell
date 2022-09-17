#include "../inc/minishell.h"

void    ft_readline(void)
{
	t_vars vars;

	vars = (t_vars){};
	vars.split = NULL;
	vars.list = NULL;
	vars.line = NULL;
	vars.quotes  = "'";
	ft_submain(&vars);
// 		system("leaks minishell");
}

void    ft_submain(t_vars *vars)
{
	while (1)
	{
		vars->line = readline("Minishell $ ");
		// if (ft_strlen(vars.line) == 0)
		// {
		// 	write(1, "exit\n", 5);
		// 	free(vars.line);
		// 	exit (0);
		// }
		if (!ft_strncmp ("exit", vars->line, ft_strlen(vars->line)))
		{
			write(1, "exit\n", 5);
			free(vars->type);
			free(vars->line);
			exit (0);
		}
		if (ft_pre_check(vars))
			continue ;
		add_history(vars->line); //solo añadir si es válido
		// line_cop = ft_strdup(wololo);
		vars->line_len = ft_strlen(vars->line);
		// printf("%zu\n", line_len	);sad
		vars->type = ft_mask(vars->line, vars); //free
		if (vars->type != NULL)
		{
			vars->num_pipes = ft_numpipes(vars->line, vars->type);
			if (vars->num_pipes)
				vars->split = spliting(vars->line, vars->type, vars->num_pipes, vars);
			else
			{
				free(vars->type);
				vars->type = NULL;
				ft_triming(&vars->line, 0, vars, 1);
				// vars->split[1] = NULL;
			}
			ft_lst_cmd(vars);
		}
		ft_end_of_cicle(vars);
	}
}

void    ft_end_of_cicle(t_vars *vars)
{

		
		free(vars->line);
		vars->line = NULL;
		free(vars->type);
		// free(vars.split);
		vars->type = NULL;
		// free(vars->temp);
		// vars->temp = NULL;

}

int ft_pre_check(t_vars *vars)
{
	int	alpha;
	vars->i = -1;
	alpha = 0;
	while(vars->line[++vars->i])
	{
		if (ft_isalnum(vars->line[vars->i]))
			alpha++;
	}
	if (alpha == 0)
		return(1);
	return (0);
}

char    *ft_cleaning(char *str)
{
	int i;
	char *cuot;
	// int i2;
	char *clear;
	int start;
	char *temp;

	
	cuot = "'";
	i = -1;
	// while (str[++i])
	// 	if (str[i] == '"' || str[i] == cuot[0])
	// 	{
			// i2 = ft_strlen(str);

			// clear = malloc(sizeof(char) * (i2 + 1));

			clear = NULL;
			start = 0;
			// i = -1;
			while (str[++i])
			{
				if (str[i] == '"' || str[i] == cuot[0])
				{
					if (i - start != 0)
					{
						if (start == 0)
							temp = ft_substr(str, start, i - start);
						else
							temp = ft_substr(str, start + 1, i - start - 1);
						clear = ft_acumulate(clear, temp);
						// free(temp);
					}
					start = i;
					i++;
					// if(clear != NULL)
					// {
					// 	temp = ft_substr(str, start, i - start - 1); // <-
					// 	clear = ft_acumulate(clear, temp);
					// 	start = i + 1;
					// }
					while (str[i] != '"' && str[i] != cuot[0]  && str[i] != '\0')
					{
						
						i++;
					}
					temp = ft_substr(str, start + 1, i - start - 1);
					start = i;
					printf("CHEEECK\n");

					printf("cleaning temp .%s.\n", temp);
					printf("clear befor .%s.\n", clear);
					clear = ft_acumulate(clear, temp);
					printf("clean desp .%s.\n", clear);

					if (str[i] == '\0')
						break ;
				}
			}
			if (start != i && clear != NULL) //start != 0 && 
			{
				// if (str[])
				temp = ft_substr(str, start + 1, i - start - 1); // start + 1
				printf("error %s\n", temp);
				clear = ft_acumulate(clear, temp);	
				// if(temp)
				// 	free(temp);
				
				return (clear);
			}
			else if (clear == NULL)
			{
				free(clear);
				free(clear);
				free(clear);
				free(clear);
				free(clear);
				free(clear);
				printf("!!!!!!!!!!!!chkkkkk\n");
				free(clear);
				free(clear);
				free(clear);
				free(clear);
				return (ft_strdup(str));
			}
			else
			{
				// free(str);
				printf("c_clear\n");
				return (clear);
			}
			// while(str[++i])
			// {
			// 	if (str[i] == '"' || str[i] == cuot)
			// 		i2++;

			// }
		// }
	// return (ft_strdup(str));
}