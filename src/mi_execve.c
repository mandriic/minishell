#include "../inc/minishell.h"

void ft_mi_exec(t_vars *vars)
{
    int execv;
    char const *p = "ls";
    p = malloc(sizeof(char) * 6);
    printf("comando_bonito %s\n", vars->cmd_list->comando_bonito[0]);
    printf("comando_bonito %s\n", vars->env_var[0]);
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // this is the child process
        char *args[] = {"ls", "-l", NULL};
        execve("/bin/ls", args, NULL);

        // if execve returns, there was an error
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        // this is the parent process
        printf("Child process ID: %d\n", pid);
        wait(NULL); // wait for the child process to finish
        printf("Child process finished\n");
        exit(EXIT_SUCCESS);
    }
    execv = execve("/bin/ls", vars->cmd_list->comando_bonito, vars->env_var);
    printf("execv %d\n", execv);






    // ft_print_dp(vars->cmd_list->comando_bonito, "env_var");
    // int exec = -20;
    // if (!ft_strncmp("cd", vars->cmd_list->comando_bonito[0], ft_strlen(vars->cmd_list->comando_bonito[0])))
    // {
    // // //    exec =  execve("/bin/ls",vars->cmd_list->comando_bonito, vars->env_var);
    // // 	// system("ls");
    // //     // exec = chdir(vars->cmd_list->comando_bonito[1]);
    // // 	// system("ls");
    //     ft_chdir(vars);

    // }
    // printf("execv %d\n", exec);

    
}