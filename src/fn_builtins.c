#include "../inc/minishell.h"

int	ft_echo(t_vars *vars)
{
    int i;

    i = 1;
    if (ft_strncmp(vars->cmd_list->cmd[1], "-n", 2) == 0)
        i++;
    while (vars->cmd_list->cmd[i] != NULL)
    {
        printf ("%s", vars->cmd_list->cmd[i]);
        // if (ft_strncmp(vars->cmd_list->cmd[1], "-n", 2) != 0) //(vars->cmd_list->cmd[i + 1] != NULL)// && ft_strncmp(vars->cmd_list->cmd[1], "-n", 2) != 0)
        if (vars->cmd_list->cmd[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (ft_strncmp(vars->cmd_list->cmd[1], "-n", 2) != 0)
        printf("\n");
    return(1);
}

int	ft_cd(t_vars *vars)
{
    printf("cd builtin\n");
    if (chdir(vars->cmd_list->cmd[1]) == 0)
    {
        printf("success\n");
    }
    // printf("TEST\n");
    return(1);
}

int	ft_pwd(t_vars *vars)
{
    int i;

    i = 0;
    printf("pwd builtin\n");
    while (vars->env_var[i] != NULL)
    {
        if (ft_strncmp(vars->env_var[i], "PWD=", 4) == 0)
            printf("%s\n", vars->env_var[i] + 4);
        i++;
    }
    // ft_print_dp(vars->env_var, "ENVVAR");
    return(1);
}

int		ft_export(t_vars *vars)
{
    printf("export builtin\n");
    return(1);
}

int	ft_unset(t_vars *vars)
{
    printf("unset builtin\n");
    return(1);
}
int	ft_env(t_vars *vars)
{
    int i;

    i = 0;
    printf("env builtin\n");
    while (vars->env_var[i] != NULL)
    {
        printf("%s\n", vars->env_var[i++]);
    }
    return(1);
}

int	ft_exit(t_vars *vars)
{
    printf("exit builtin\n");
    return(1);
}