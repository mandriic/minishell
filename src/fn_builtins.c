#include "../inc/minishell.h"

int	ft_echo(t_vars *vars)
{
    printf("echo builtin %s\n", vars->cmd_list->cmd[0]);
    return(1);
}

int	ft_cd(t_vars *vars)
{
    printf("cd builtin\n");
    return(1);
}

int	ft_pwd(t_vars *vars)
{
    printf("pwd builtin\n");
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