#include "../inc/minishell.h"

void ft_mi_exec(t_vars *vars)
{
    // ft_print_dp(vars->cmd_list->comando_bonito, "env_var");
    int exec = -20;
    if (!ft_strncmp("cd", vars->cmd_list->comando_bonito[0], ft_strlen(vars->cmd_list->comando_bonito[0])))
    {
    // //    exec =  execve("/bin/ls",vars->cmd_list->comando_bonito, vars->env_var);
    // 	// system("ls");
    //     // exec = chdir(vars->cmd_list->comando_bonito[1]);
    // 	// system("ls");
        ft_chdir(vars);

    }
    // printf("execv %d\n", exec);

    
}