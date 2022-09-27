#include "../inc/minishell.h"

char	*ft_checkif_var(char *str, t_vars *vars)
{
	int		*type;
	char	*acum;

	vars->start = 0;
	type = ft_mask(str, vars);
	acum = NULL;
	ft_checkif_var_subfoo(str, &acum, type, vars);
	if (acum == NULL || str[vars->start - 1] == '\0') //  && -> ||
	{
		free(type);
		if (vars->start - 1 > 0 && str[vars->start - 1] == '\0' && acum != NULL) //? 
		{
			//?free type
			// vars->temp2 = ft_cleaning(acum, vars);
			// free(acum);
			return (acum); //<--------//ft_cleaning(str, vars)
		}
		return(str);
		// return(ft_cleaning(str, vars)); //return(ft_strdup(str)); return(ft_cleaning(str));
	}
	// printf("str[i %c \n", str[vars->i -1]);
	vars->temp2 = ft_substr(str, vars->start, vars->i - vars->start + 1); //start - 1
	if (vars->temp2 != NULL) //&& temp[0] != '\0' 
	{
		// printf("check\n");
		// printf("vars->temp2,%s.\n", vars->temp2);
		// printf("acum,%s.\n", acum);
		acum = ft_acumulate(acum, vars->temp2);
		free(type);
		// vars->temp2 = ft_cleaning(acum, vars);
		// free(acum);
		// return (vars->temp2);
		return (acum);
	}
	free(type);
	return(acum);
}

void	ft_pre_getenv(char *str, char **acum, t_vars *vars)
{
	char	lastchar;
	// printf("str [vars->i - 1] %c\n", str [vars->i - 1]);
	// printf("str [vars->i] %c\n",str [vars->i]);
	lastchar = '\0';
	if (vars->i - vars->start > 0 && ( str [vars->i - 1] == ' ' || lastchar == '/' || str[vars->i - 1] != vars->quotes[0]))
	{
		vars->temp = ft_substr(str, vars->start, vars->i - vars->start); //ft_substr(str, vars->start, vars->i - vars->start - 1);
		*acum = ft_acumulate(*acum, vars->temp);
	}
	vars->start = vars->i + 1;
	vars->i++;
	while (str[vars->i] != ' ' && str[vars->i] != '\0'  && str[vars->i] != '/'  && str[vars->i] != '"' && str[vars->i] != '$'  && str[vars->i] != vars->quotes[0])
		vars->i++;
	vars->var = ft_get_env(str + vars->start - 1, vars->i - vars->start);  // +1 
	vars->start = vars->i + 1;
	*acum = ft_acumulate(*acum, vars->var);
	lastchar = str[vars->i];
	if (str[vars->i] == '$' && str[vars->i - 1] != ' ' && str[vars->i - 1] != '"') // ?  && str[vars->i - 1] != ' ' && str[vars->i - 1] != '"'
		vars->i--;
}
void	ft_checkif_var_subfoo(char *str, char **acum, int *type, t_vars *vars)
{
	vars->i = 0;
	while (1) //str[vars->i] != '\0'
	{
		if (str[vars->i] == '$' && (type[vars->i] == 6 \
		|| type[vars->i] == 0) && str[vars->i + 1] != ' ')
			{
				printf("str i %c\n", str[vars->i]);
				ft_pre_getenv(str, acum, vars);
			}
	// printf("str [vars->i - 1] %c\n", str [vars->i - 1]);
	// printf("str [vars->i] %c\n",str [vars->i]);
	// printf("vars->i -  vats->start  %d\n",vars->i - vars->start);

		if (str[vars->i] == '\0')
			break;
		vars->i++;
	}
}

void	ft_sub_get_env(char *str, char *var, int len, int *i)
{
	while (++*i != len)
	{
		var[*i] = str[*i + 1];
		if (str[*i + 1] == '\0' || str[*i + 1] == '$')
			break ;
	}
	var[*i] = '\0';
}
char	*ft_get_env(char *str, int len)
{
	char	var[len];
	char	*valor;
	char	*temp;
	int 	i;

	i = -1;
	if(str[1] == '?')
	{
		var[0] = '$';
		var[1] = '?';
		var[2] = '\0';
	}
	else
		ft_sub_get_env(str, var, len, &i);
	valor = getenv(var);
	if (str[i + 1] == ' ' ) //|| str[i + 1] == '"'
		temp = ft_strjoin(valor, " ");
	else if (str[i + 1] == '/')
		temp = ft_strjoin(valor, "/");
	else
		temp = ft_strdup(valor);
	return (temp);
}
// char *ft_checkif_var2(char *str, t_vars *vars)
// {
// 	int i = -1;
// 	int start = 0;
// 	char *accum;
// 	char *var;
// 	char *res;
// 	while (str[++i])
// 	{
// 		if (str[0] == '"' || str[0] == vars->quotes[0])
// 			start = 1;
// 		if (str[i] == '$' && str[i + 1] != '$')
// 		{
// 			while (str[i] != '\0' && str[i] != '"' && str[i] != vars->quotes[0])
// 				i++;
// 				printf("cjhesadf\n");
// 			var = ft_substr(str, start, i - start);
// 			res = getenv(var);
// 			printf("res%s\n", res);
// 			printf("var%s\n", var);
// 		}
// 	}
// }

void ft_get_env2(char ***arr, t_vars *vars)
{
	int i;
	int i2;
	char *temp;
	
	i = -1;
	while(arr[0][++i] != NULL)
	{
		temp = ft_checkif_var(arr[0][i], vars);
		printf("str .%s.\n", arr[0][i]);
		if(arr[0][i] != temp)
		{
			ft_my_free(arr[0][i]);
			arr[0][i] = ft_strdup(temp);
			ft_my_free(temp);
		}
	}
	// 	printf("arr[i] .%s.\n", arr[i]);
	// }
}