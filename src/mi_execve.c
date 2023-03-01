#include "../inc/minishell.h"

void ft_mi_exec(t_vars *vars)
{
    if (ft_strncmp(vars->cmd_list->cmd[0], "ls", 2) == 0)
    {
        if (fork() == 0)
            execve("/bin/ls", vars->cmd_list->cmd, vars->env_var);
        else
            wait(NULL);
        int i = 0;
        while(vars->env_var[i])
        {
            if (ft_strncmp(vars->env_var[i], "PATH", 4) == 0)
            {
                printf("env %s", vars->env_var[i]);
            }
            i++;
        }
    }
        // return;
    // ft_print_dp(vars->cmd_list->cmd, "env_var");
    // int exec = -20;
    // if (!ft_strncmp("cd", vars->cmd_list->cmd[0], ft_strlen(vars->cmd_list->cmd[0])))
    // {
    // // //    exec =  execve("/bin/ls",vars->cmd_list->cmd, vars->env_var);
    // // 	// system("ls");
    // //     // exec = chdir(vars->cmd_list->cmd[1]);
    // // 	// system("ls");
    //     ft_chdir(vars);

    // }
    // // printf("execv %d\n", exec);

    
}