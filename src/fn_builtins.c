#include "../inc/minishell.h"

int	ft_echo(t_vars *vars, t_command *cmd)
{
	int i;

	i = 1;
	// printf("%s\n", cmd->cmd[1]);
	if (ft_strncmp(cmd->cmd[1], "-n", 2) == 0  && ft_strlen(cmd->cmd[1]) == 2)
		i++;
	// {
	//     i++;
	//     printf("tetst\n");
	// }
	while (cmd->cmd[i] != NULL)
	{
		printf ("%s", cmd->cmd[i]);
		// if (ft_strncmp(cmd->cmd[1], "-n", 2) != 0) //(cmd->cmd[i + 1] != NULL)// && ft_strncmp(cmd->cmd[1], "-n", 2) != 0)
		if (cmd->cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (ft_strncmp(cmd->cmd[1], "-n", 2) != 0 || ft_strlen(cmd->cmd[1]) != 2)
		printf("\n");
	vars->last_code = 0;
	return(1);
}
// int ft_check_root(char * root)
// {
//     if ft_strncmp(vars->)
// }
char *ft_get_value(char *str, char **env)
{
	int i = 0;
	if (!str)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
		{
			if (ft_strlen(env[i]) == ft_strlen(str))
				return (env[i] + ft_strlen(str));
			else if (env[i][ft_strlen(str)] == '=')
				return (env[i] + ft_strlen(str) + 1);
		}
		i++;
	}
	return (0);
}

int ft_change_temp_env(t_vars *vars, char *name, char *new_value, int len)
{
	int i;

	i = 0;
	// if (ft_strncmp(new_value, "~", 1) == 0)
	// {
	//     new_value = ft_get_value("HOME", vars->env_var);
	//     printf("new value is %s\n", new_value);
	//     new_value = new_value + 5;
	// }
	while(vars->temp_env[i] != NULL)
	{
		if (ft_strncmp(vars->temp_env[i], name, len) == 0)
		{    
			printf("11111%s \n", vars->temp_env[i]);
			free(vars->temp_env[i]);
			printf("22222%s \n", name);
			vars->temp_env[i] = ft_strjoin(name, new_value);
			printf("VARI %s\n", vars->temp_env[i]);
			return (1);
		}
		i++;
	}
	// ft_print_dp(vars->env_var, "change env test");
	return (0);
}


// int ft_change_temp_env(t_vars *vars, char *name, char *new_value, int len)
// {
//     int i;

//     i = 0;
//     // if (ft_strncmp(new_value, "~", 1) == 0)
//     // {
//     //     new_value = ft_get_value("HOME", vars->env_var);
//     //     printf("new value is %s\n", new_value);
//     //     new_value = new_value + 5;
//     // }
//     while(vars->temp_env[i] != NULL)
//     {
//         if (ft_strncmp(vars->temp_env[i], name, len) == 0)
//         {    
//             printf("11111%s \n", vars->temp_env[i]);
//             free(vars->temp_env[i]);
//             printf("22222%s \n", name);
//             vars->temp_env[i] = ft_strjoin(name, new_value);
//             printf("VARI %s\n", vars->temp_env[i]);
//             return (1);
//         }
//         i++;
//     }
//     // ft_print_dp(vars->env_var, "change env test");
//     return (0);
// }

int ft_change_env(t_vars *vars, char *name, char *new_value, int len)
{
	int i;

	i = 0;
	while(vars->env_var[i] != NULL)
	{
		if (ft_strncmp(vars->env_var[i], name, len) == 0)
		{    
			printf("11111%s \n", vars->env_var[i]);
			free(vars->env_var[i]);
			printf("22222%s \n", name);
			vars->env_var[i] = ft_strjoin(name, new_value);
			printf("VARI %s\n", vars->env_var[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_cd(t_vars *vars, t_command *cmd)
{
	char *cdir;
	printf("cd builtin\n");
	if (chdir(cmd->cmd[1]) == 0)
	{
		cdir = getcwd(NULL, 0);
		ft_change_env(vars, "OLDPWD", ft_get_value("PWD", vars->env_var), 6);
		ft_change_env(vars, "PWD=", cdir, 4);
		free(cdir);
	}
	else if (chdir(cmd->cmd[1]) == -1)
	{
		printf("cd: no such file or directory: %s\n", cmd->cmd[1]);
		vars->last_code = 1;
		return (1);
	}
	vars->last_code = 0;
	return(1);
}

int	ft_pwd(t_vars *vars, t_command *cmd)
{
	int i;

	i = 0;
	printf("pwd builtin\n");
	if (cmd->cmd[1] != NULL)
	{
		printf("pwd: too many arguments\n");
		vars->last_code = 1;
		return(1);
	}
	while (vars->env_var[i] != NULL)
	{
		if (ft_strncmp(vars->env_var[i], "PWD=", 4) == 0)
			printf("%s\n", vars->env_var[i] + 4);
		i++;
	}
	// ft_print_dp(vars->env_var, "ENVVAR");
	vars->last_code = 0;
	return(1);
}

int		ft_export(t_vars *vars, t_command *cmd)
{
	int i;
	int j;
	i = 0;
	char *temp;


	if(cmd->cmd[1] != NULL)
	{
		printf("export builtin%s\n", cmd->cmd[1]);
		if (ft_strchr(cmd->cmd[1], '=') != NULL)
			vars->env_var = ft_append_to_env(vars, cmd->cmd[1]);
		else if (ft_find_in_temp_env(vars, cmd->cmd[1]) != NULL)
		{
			temp = ft_find_in_temp_env(vars, cmd->cmd[1]);
			printf("temp is %s\n", temp);
			vars->env_var = ft_append_to_env(vars, temp);

		}
		// else
		//     vars->env_var = ft_append_to_env(vars, cmd->cmd[1]);
		// printf("export builtin\n");
		// printf("check %d\n", ft_strncmp(cmd->cmd[1], "=", 1));
			// ft_change_env(vars, cmd->cmd[1], char *new_value, int len)
		vars->last_code = 0;
		return(1);
	}

	while(vars->env_var[i])
	{
		j = 0;
		printf("declare -x ");
		while(vars->env_var[i][j] != '=')
		{
			printf("%c", vars->env_var[i][j]);
			j++;
		}
		printf("=\"%s\"\n", vars->env_var[i] + j + 1);
		i++;
	}
	vars->last_code = 0;
	return(1);
}

int	ft_unset(t_vars *vars, t_command *cmd)
{
	if (cmd->cmd[1] != NULL)
	{
		if (ft_get_value(cmd->cmd[1], vars->env_var) != NULL)
		{
			ft_change_env(vars, cmd->cmd[1], "", ft_strlen(cmd->cmd[1]));
			return(1);
		}
		else if (ft_get_value(cmd->cmd[1], vars->temp_env) != NULL)
		{
			ft_change_temp_env(vars, cmd->cmd[1], "", ft_strlen(cmd->cmd[1]));
			return(1);

		}
	}
	vars->last_code = 0;
	return(1);
}
int	ft_env(t_vars *vars, t_command *cmd)
{
	int i;

	i = 0;
	printf("env builtin\n");
	while (vars->env_var[i] != NULL)
	{
		ft_putstr_fd(vars->env_var[i++], 1);
		ft_putstr_fd("\n", 1);
		// printf("%s\n", vars->env_var[i++]);
	}
	vars->last_code = 0;
	return(1);
}

int	ft_exit(t_vars *vars, t_command *cmd)
{
	int temp;

	printf("exit builtin\n");
	temp = ft_atoi(cmd->cmd[1]);
	if (temp >= 256)
		temp = 0 + (temp - 256);
	vars->last_code = temp;
	return(1);
}