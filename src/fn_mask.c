#include "../inc/minishell.h"

int	ft_singquot(char *line, int *type, t_vars *vars, int check)
{
	type[vars->i] = 1;
	while (line[++vars->i] != vars->quotes[0] && line[vars->i] != '\0' )
		type[vars->i] = 5;
	if (line[vars->i] == '\0' && check)
		{
			printf("Not interpret unclosed quotes \n");
			free(type);
			if(vars->cmd_list)
				ft_del_list(vars->cmd_list);
			return(1);
		}
	type[vars->i] = 1;

	return (0);
}

int	ft_dobquot(char *line, int *type, t_vars *vars, int check)
{
	type[vars->i] = 2;
	while (line[++vars->i] != '"' && line[vars->i] != '\0')
		type[vars->i] = 6;
	if (line[vars->i] == '\0' && check)
		{
			printf("Not interpret unclosed quotes \n");
			free(type);
			if(vars->cmd_list)
				ft_del_list(vars->cmd_list);
			return(1);
		}
	else if (line[vars->i] == '\0' && !check)
	{
		type[vars->i - 1] = 0;
		return (0);

	}
	else
		type[vars->i] = 2;
	return(0);
}
int	*ft_mask(char *line, t_vars *vars, int check)
{
	int len;
	int *type;

	vars->i = -1;
	type = NULL;
	len = ft_strlen(line);
	if (len == 0)
		return(type);
	type = malloc(sizeof(int) * len + 2);
	while (line[++vars->i] != '\0')
	{
		if(line[vars->i] == vars->quotes[0] && ft_singquot(line, type, vars, check))
			return (NULL);
		else if (line[vars->i] == '"' && ft_dobquot(line, type, vars, check))
			return (NULL);
		else if (line[vars->i] == '|')
			type[vars->i] = 3; 
		else if (line[vars->i] == '|' && line[vars->i + 1] == '\0')
			type[vars->i] = 4;
		else if ((line[vars->i] == '<' && line[vars->i + 1] == '<') || (line[vars->i] == '>' &&  line[vars->i + 1] == '>'))
			type[vars->i] = 11;
		else if (line[vars->i] == '<' || line[vars->i] == '>')
			type[vars->i] = 10;
		else if (line[vars->i] != '"' && line[vars->i] != vars->quotes[0] && line[vars->i] != '\0')
			type[vars->i] = 0;
		if (line[vars->i] == '\0')
			break ;
	}
	return (type);
}

char	*ft_acumulate(char *dest, char *part)
{
	int		lenpart;
	char	*temp;

	lenpart = ft_strlen(part);
	printf("lenpart %d\n", lenpart);
	if (lenpart == 0)
	{
		// printf("lenpart %d\n", lenpart);
		ft_my_free(part);
		return (dest);
	}
	// printf("part %s\n", part);
	if (!dest)
	{
		// printf("CHARC\n");
		temp = ft_strdup(part);
		ft_my_free(part);
	}
	else
	{
		// printf("CHARC2\n");
		temp = ft_strjoin(dest, part);
		if(dest != NULL)
		{
			// printf("dest %s\n", dest);
			ft_my_free(dest);
			dest = NULL;
		}
		// if (part != NULL)
			ft_my_free(part);
		part = NULL;
	}
	return (temp);
}