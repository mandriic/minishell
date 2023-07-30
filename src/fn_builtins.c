#include "../inc/minishell.h"

int	ft_echo(t_vars *vars, t_command *cmd)
{
    int i;

    (void)vars;
    i = 1;
    //printf("%s\n", cmd->cmd[1]);
    // if (cmd->cmd[i] != NULL && strncmp(cmd->cmd[i], "$", 1) == 0) {
    //     ft_putstr_fd("$", 1);
    //     i++;
    // }
    if (ft_strncmp(cmd->cmd[1], "-n", 2) == 0  && ft_strlen(cmd->cmd[1]) == 2)
        i++;

    while (cmd->cmd[i] != NULL)
    {
        if (ft_strncmp(cmd->cmd[i], "$?", 2) == 0) //to get exit status and print it
        {
            //printf("The recent exit status:  %d", vars->error); // have to add as a global varient
            ft_putnbr_fd(vars->error, 1);
        }
    
        else if (ft_strncmp(cmd->cmd[i], "$?", 2) != 0 && ft_strncmp(cmd->cmd[i], "-n", 2) != 0)
            ft_putstr_fd(cmd->cmd[i], 1);
           // printf("the cmd is %s \n", cmd->cmd[i] );
        /*else if (ft_strncmp(cmd->cmd[1], "-n", 2) != 0)
            printf("%s", cmd->cmd[i]);*/

        // if (ft_strncmp(cmd->cmd[1], "-n", 2) != 0) //(cmd->cmd[i + 1] != NULL)// && ft_strncmp(cmd->cmd[1], "-n", 2) != 0)
        //if (cmd->cmd[i + 1] != NULL)
        if(cmd->cmd[i + 1] != NULL)
            ft_putstr_fd(" ", 1);
        //printf("the cmd is %s \n", cmd->cmd[i]);
        i++;
    }
    if (cmd->cmd[1] == NULL || (ft_strncmp(cmd->cmd[1], "-n", 2) != 0 || ft_strlen(cmd->cmd[1]) != 2))
    printf("\n");
    vars->error = 0;
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
            // printf("11111%s \n", vars->temp_env[i]);
            free(vars->temp_env[i]);
            // printf("22222%s \n", name);
            vars->temp_env[i] = ft_strjoin(name, new_value);
            // printf("VARI %s\n", vars->temp_env[i]);
            return (1);
        }
        i++;
    }
    // ft_print_dp(vars->env_var, "change env test");
    return (0);
}

int ft_change_env(t_vars *vars, char *name, char *new_value, int len)
{
    int i;

    i = 0;
    // if (ft_strncmp(new_value, "~", 1) == 0)
    // {
    //     new_value = ft_get_value("HOME", vars->env_var);
    //     printf("new value is %s\n", new_value);
    //     new_value = new_value + 5;
    // }
    while(vars->env_var[i] != NULL)
    {
        if (ft_strncmp(vars->env_var[i], name, len) == 0)
        {    
            free(vars->env_var[i]);
            vars->env_var[i] = ft_strjoin(name, new_value);
            return (1);
        }
        i++;
    }
    // ft_print_dp(vars->env_var, "change env test");
    return (0);
}

int	ft_cd(t_vars *vars, t_command *cmd)
{
    char *cdir;
    // printf("cd builtin\n");
    if (chdir(cmd->cmd[1]) == 0)
    {
        cdir = getcwd(NULL, 0);
        // printf("%s \n",  cdir);
        ft_change_env(vars, "OLDPWD=", ft_get_value("PWD", vars->env_var), 6);
        ft_change_env(vars, "PWD=", cdir, 4);
        free(cdir);
        // ft_print_dp(vars->env_var, "ENVVAR");

        // ft_change_env(vars, "PWD=", cmd->cmd[1], 4);

        // printf("success\n");
        // printf("%s\n", cmd->cmd[1]);
    }
    else if(cmd->cmd[1] == NULL)
    {
        if (chdir(ft_get_value("HOME", vars->env_var)) == 0)
        {
            cdir = getcwd(NULL, 0);
            // printf("%s \n",  cdir);
            ft_change_env(vars, "OLDPWD=", ft_get_value("PWD", vars->env_var), 6);
            ft_change_env(vars, "PWD=", cdir, 4);
            free(cdir);
        }
        // printf("cd builtin\n");
        // printf("success\n");
        // printf("%s\n", cmd->cmd[1]);
        // printf("cd: %s: No such file or directory\n", cmd->cmd[1]);
        // printf("error\n");
    }
    else if (chdir(cmd->cmd[1]) == -1)
    {
        printf("cd: %s: No such file or directory\n", cmd->cmd[1]);
        // printf("error\n");
    }
    // printf("TEST\n");
    return(1);
}

int	ft_pwd(t_vars *vars, t_command *cmd)
{
    int i;

    (void)vars;(void)cmd;
    i = 0;
    // printf("pwd builtin\n");
    while (vars->env_var[i] != NULL)
    {
        if (ft_strncmp(vars->env_var[i], "PWD=", 4) == 0)
            printf("%s\n", vars->env_var[i] + 4);
        i++;
    }
    // ft_print_dp(vars->env_var, "ENVVAR");
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
        // printf("export builtin%s\n", cmd->cmd[1]);
        if (ft_strchr(cmd->cmd[1], '=') != NULL)
            vars->env_var = ft_append_to_env(vars, cmd->cmd[1]);
        else if (ft_find_in_temp_env(vars, cmd->cmd[1]) != NULL)
        {
            temp = ft_find_in_temp_env(vars, cmd->cmd[1]);
            // printf("temp is %s\n", temp);
            vars->env_var = ft_append_to_env(vars, temp);

        }
        // else
        //     vars->env_var = ft_append_to_env(vars, cmd->cmd[1]);
        // printf("export builtin\n");
        // printf("check %d\n", ft_strncmp(cmd->cmd[1], "=", 1));
            // ft_change_env(vars, cmd->cmd[1], char *new_value, int len)
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
    return(1);
}
int	ft_env(t_vars *vars, t_command *cmd)
{
    int i;

    (void)cmd;
    i = 0;
    // printf("env builtin\n");
    while (vars->env_var[i] != NULL)
    {
        ft_putstr_fd(vars->env_var[i++], 1);
        ft_putstr_fd("\n", 1);
        // printf("%s\n", vars->env_var[i++]);
    }
    return(1);
}

int	ft_exit(t_vars *vars, t_command *cmd)
{
    (void)vars;
    int i;
    int j;

    i = 1;
    while (cmd->cmd[i] != NULL)
    {
        j = 0;
        while (cmd->cmd[i][j] != '\0')
        {
            if (ft_isdigit(cmd->cmd[i][j]) == 0)
            {
                printf("minishell: exit: %s: numeric argument required\n", cmd->cmd[i]);
                vars->error = 255;
                // printf("vars->error = %d\n", vars->error);
                // system("leaks minishell");
        		// free(vars->line);
                exit(0); //added by Anush in order to exit the program
                return(1);
            }
            j++;
        }
        i++;
    }
    // printf("exit builtin\n");
    // system("leaks minishell");
    // ft_end_of_cicle(vars);
    // free(vars->line);
    exit(0); //added by Anush in order to exit the program
    return(1);
}
