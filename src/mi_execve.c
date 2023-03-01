#include "../inc/minishell.h"
char *ft_get_val(char *str, char **env)
{
    int i = 0;
    if (!str)
        return (NULL);
    while (env[i])
    {
        if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
            return (env[i]);
        i++;
    }
    return (0);
}

int ft_check_dir(char *dir, char *cmd)
{
    DIR *d;
    struct dirent *dirr;
    d = opendir(dir);
    if (!d)
        return (0);
    dirr = readdir(d);
    if (d)
    {
        while ((dirr = readdir(d)) != NULL)
        {
            printf("dirr->d_name %s \n", dirr->d_name);
            if (ft_strncmp(dirr->d_name, cmd, ft_strlen(cmd)) == 0)
            {
                closedir(d);
                return (1);
            }
        }
        closedir(d);
    }
    return (0);
}

void ft_pars_path(char *path, char *cmd, int len, t_vars *vars) //char *
{
    int i = len + 1;
    int start = len;
    char *dir;
    char *ifhome = NULL;
    while (path[i])
    {
        if (path[i] == '~')
        {
            ifhome = ft_get_val("HOME", vars->env_var);
            ifhome = ifhome + 5;
            printf("ifhome is %s \n", ifhome);
            i++;
            start++;
            // ft_pars_path(ifhome, cmd, i);
            // break;
        }
        if (path[i] == ':')
        {
            dir = malloc(sizeof(char) * (i - start + 1));
            ft_strlcpy(dir, path + start, i - start + 1);
            start = i + 1;
            printf("dir is %s \n", dir);
            if (ifhome)
            {
                if(dir)
                    free(dir);
                dir = ft_strjoin(ifhome, dir);
                printf("dir is %s \n", dir);
            }
            printf(" %d \n", ft_check_dir(dir, cmd));
            free(dir);
            // break;
        }
        i++;
    }    
}
void ft_mi_exec(t_vars *vars)
{
    char *path;
    path = ft_get_val("PATH", vars->env_var);
    printf("PATH is %s \n", path);
    ft_pars_path(path, vars->cmd_list->cmd[0], 5, vars);
    // printf("PATH is %s \n", ft_get_val(vars->cmd_list->cmd[0], vars->env_var));  
    // if (ft_strncmp(vars->cmd_list->cmd[0], "ls", 2) == 0)
    // {
    //     if (fork() == 0)
    //         execve("/bin/ls", vars->cmd_list->cmd, vars->env_var);
    //     else
    //         wait(NULL);

             

        // while(vars->env_var[i])
        // {
        //     if (ft_strncmp(vars->env_var[i], "PATH", 4) == 0)
        //     {
        //         printf("env %s", vars->env_var[i]);
        //     }
        //     i++;
        // }
    // }
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