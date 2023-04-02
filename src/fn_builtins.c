#include "../inc/minishell.h"

int	ft_echo(t_vars *vars)
{
    int i;

    i = 1;
    if (ft_strncmp(vars->cmd_list->cmd[1], "-n", 2) == 0)
        i++;
    while (vars->cmd_list->cmd[i] != NULL)
    {
        printf ("%s", vars->cmd_list->cmd[i++]);
        if (vars->cmd_list->cmd[i + 1] != NULL && ft_strncmp(vars->cmd_list->cmd[1], "-n", 2) != 0)
            write(1, " ", 1);
    }
    if (ft_strncmp(vars->cmd_list->cmd[1], "-n", 2) != 0)
        printf("\n");
    return(1);
}

int	ft_cd(t_vars *vars)
{
    printf("cd builtin\n");
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
    printf("env builtin\n");
    return(1);
}

int	ft_exit(t_vars *vars)
{
    printf("exit builtin\n");
    return(1);
}