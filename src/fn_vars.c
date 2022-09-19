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
			return (acum);
		return(ft_cleaning(str, vars)); //return(ft_strdup(str)); return(ft_cleaning(str));
	}
	vars->temp2 = ft_substr(str, vars->start, vars->i - vars->start); //start - 1
	if (vars->temp2 != NULL) //&& temp[0] != '\0'
	{
		acum = ft_acumulate(acum, vars->temp2);
		free(type);
		vars->temp2 = ft_cleaning(acum, vars);
		free(acum);
		return (vars->temp2);
	}
	free(type);
	return(acum);
}

void	ft_pre_getenv(char *str, char **acum, t_vars *vars)
{
	char	lastchar;
	
	lastchar = '\0';
	if (vars->i - vars->start > 1 && (str [vars->i - 1] == ' ' || lastchar == '/' || str[vars->i - 1] != vars->quotes[0]))
	{
		vars->temp = ft_substr(str, vars->start, vars->i - vars->start); //ft_substr(str, vars->start, vars->i - vars->start - 1);
		*acum = ft_acumulate(*acum, vars->temp);
	}
	vars->start = vars->i + 1;
	vars->i++;
	while (str[vars->i] != ' ' && str[vars->i] != '\0'  && str[vars->i] != '/'  && str[vars->i] != '"' && str[vars->i] != '$' )
		vars->i++;
	vars->var = ft_get_env(str + vars->start - 1, vars->i - vars->start); 
	vars->start = vars->i + 1;
	*acum = ft_acumulate(*acum, vars->var);
	lastchar = str[vars->i];
	if (str[vars->i] == '$') // ?  && str[vars->i - 1] != ' ' && str[vars->i - 1] != '"'
		vars->i--;
}
void	ft_checkif_var_subfoo(char *str, char **acum, int *type, t_vars *vars)
{
	vars->i = 0;
	while (str[vars->i] != '\0')
	{
		if (str[vars->i] == '$' && (type[vars->i] == 6 \
		|| type[vars->i] == 0) && str[vars->i + 1] != ' ')
			ft_pre_getenv(str, acum, vars);
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