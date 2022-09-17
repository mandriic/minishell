#include "../inc/minishell.h"

int	*ft_mask(char *line, t_vars *vars)
{
	int i;
	int len;
	int *type;
	i = -1;
	type = NULL;
	len = ft_strlen(line);
	if (len == 0)
		return(type);
	// printf("len %d", len);
	type = malloc(sizeof(int) * len);

	while (line[++i] != '\0')
	{
		if(line[i] == vars->quotes[0])
		{
			type[i] = 1;
			while (line[++i] != vars->quotes[0] && line[i] != '\0')
				type[i] = 5;
			if (line[i] == '\0')
				{
					printf("Not interpret unclosed quotes \n");
					free(type);
					if(vars->list)
						ft_del_list(vars->list);
					return(NULL);
				}
			type[i] = 1;
		}
		else if (line[i] == '"')
		{
			type[i] = 2;
			while (line[++i] != '"' && line[i] != '\0')
				type[i] = 6;
			if (line[i] == '\0')
				{
					printf("Not interpret unclosed quotes \n");
					free(type);
					if(vars->list)
						ft_del_list(vars->list);
					return(NULL);
				}
			else
				type[i] = 2;
		}
		else if (line[i] == '|'  ) //&& line[i + 1] != '\0' && !ft_lastpipe(line + i + 1)
			type[i] = 3; 
		// else if (ft_lastpipe(line + i + 1))
		// {
		// 	while (line[i])
		// 	{
		// 		if (ft_isalnum(line[i])
		// 	}
		// }
		else if (line[i] == '|' && line[i + 1] == '\0')
			type[i] = 4;
		else
			type[i] = 0;
		// printf("type %d\n", type[i]);
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
		free(part);
		return (dest);
	}
	// printf("part %s\n", part);
	if (!dest)
	{
		// printf("CHARC\n");
		temp = ft_strdup(part);
		free(part);
	}
	else
	{
		// printf("CHARC2\n");
		temp = ft_strjoin(dest, part);
		if(dest != NULL)
		{
			// printf("dest %s\n", dest);
			free(dest);
			dest = NULL;
		}
		// if (part != NULL)
			free(part);
		part = NULL;
	}
	return (temp);
}