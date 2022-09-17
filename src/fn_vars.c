#include "../inc/minishell.h"

char	*ft_checkif_var(char *str, t_vars *vars)
{
	int		*type;
	char	*acum;
	char	*temp;

	vars->start = 0;
	type = ft_mask(str, vars);
	acum = NULL;
	// temp = NULL;
	printf("args only %s\n", str);
	ft_checkif_var_subfoo(str, &acum, type, vars);

	if (acum == NULL && str[vars->start - 1] == '\0') //  && -> ||
	{
		printf("sstart - i %d \n", vars->start - 1);
			free(type);
			if (vars->start - 1 > 0 && str[vars->start - 1] == '\0' && acum != NULL) //? 
				return (acum);
			
			return(ft_cleaning(str)); //return(ft_strdup(str)); return(ft_cleaning(str));
	}
	// printf("char %c\n", str[vars->start - 1]);
	temp = ft_substr(str, vars->start, vars->i - vars->start); //start - 1
	printf("temp %s\n", temp); // <----------
	printf("accum %s\n", acum);
	// printf("char %c\n", str[start] );
	if (temp != NULL) //&& temp[0] != '\0'
		{
			acum = ft_acumulate(acum, temp);
			printf("accum222 %s\n", acum);

			free(type);
			temp = ft_cleaning(acum);
			free(acum);
			return (temp);
			// free(temp);
		}
	// else
		// free(temp);
	free(type);
	// printf("accumulate2 %s\n", acum);
	return(acum);
}

void	ft_checkif_var_subfoo(char *str, char **acum, int *type, t_vars *vars)
{
	vars->i = 0;
	char lastchar;

	lastchar = '\0';
	// vars->start = 0;
	printf("str %s\n", str);
	while (str[vars->i] != '\0')
	{
		if (str[vars->i] == '$' && (type[vars->i] == 6 || type[vars->i] == 0) && str[vars->i + 1] != ' ')
		{
				printf("str[vars->i] %c\n", str[vars->i]);
				if (vars->i - vars->start > 1 && (str [vars->i - 1] == ' ' || lastchar == '/' || str[vars->i - 1] != vars->quotes[0]))
				{
					// if (str[vars->i - 1] == '"')
					// 	vars->temp = ft_substr(str, vars->start, vars->i - vars->start - 1);
					// else
						vars->temp = ft_substr(str, vars->start, vars->i - vars->start); //ft_substr(str, vars->start, vars->i - vars->start - 1);
					printf("vars->temp %s\n", vars->temp);
					*acum = ft_acumulate(*acum, vars->temp);
					printf("accumulate1 %s\n", *acum);
					// free(temp);
				}
				vars->start = vars->i + 1;
				vars->i++;
				while (str[vars->i] != ' ' && str[vars->i] != '\0'  && str[vars->i] != '/'  && str[vars->i] != '"' && str[vars->i] != '$' )
					vars->i++;
				// printf("*i%d\n", i);
				// vars->var = ft_get_env(str + vars->start, vars->i - vars->start - 1); 
				vars->var = ft_get_env(str + vars->start - 1, vars->i - vars->start); 
				printf("var %s\n", vars->var);
				vars->start = vars->i + 1;
				*acum = ft_acumulate(*acum, vars->var);
				// if (str [vars->i] == '$')
				// 	vars->i--;
				lastchar = str[vars->i];
				printf("lastchar %c\n", lastchar);
				printf("accumulate %s\n", *acum);
				if (str[vars->i] == '$') // ?  && str[vars->i - 1] != ' ' && str[vars->i - 1] != '"'
					vars->i--;
		}
		// if (str[*i] != '\0')
		if (str[vars->i] == '\0')
			break;

		vars->i++;
	}
}

char	*ft_get_env(char *str, int len)
{
	char	var[len];
	char	*valor;
	char	*temp;
	// int 	mem;
	int 	i;
	// int flag;

	// flag = 0;
	i = -1;
	// mem = len;
	if(str[1] == '?')
	{
		var[0] = '$';
		var[1] = '?';
		var[2] = '\0';
	}
	else
	{
		while (++i != len)
		{
			// // if (str[i + 1] == '/')
			// // 	break ;
			// if (flag == 1)
			// 	var[i] = str[i];
			// else
			var[i] = str[i + 1];
			if (str[i + 1] == '\0' || str[i + 1] == '$')
				break ;
			printf("%c\n", var[i]);

		}
		var[i] = '\0';
	}
	// len-=1;
	// while (len + 1 != -1)
	// {
	// 	var[len] = str[len + 1];
	// 	if 
	// 	// printf("var[len] %c str [len--] %c\n", var[len], str[len]);
	// 	len--;
	// }
	printf("VAR %s\n",var);
	printf("STRRRRR %s\n", str);
	valor = getenv(var);
	printf("valor %s\n", valor);
	// printf("str[mem] %c\n", str[mem]);

	if (str[i + 1] == ' ' ) //|| str[i + 1] == '"'
		temp = ft_strjoin(valor, " ");
	else if (str[i + 1] == '/')
		temp = ft_strjoin(valor, "/");
	// else if(str[i + 1] == '/')
	// {
	// 	temp = ft_strjoin(valor, str + i + 1);
	// }
	else
		temp = ft_strdup(valor);
	return (temp);
}