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

int ft_check_dir(char *dir, char *cmd, int len)
{
    DIR *d;
    struct dirent *dirr;
    d = opendir(dir);
    if (!d)
        return (0);
    // dirr = readdir(d);
    if (d)
    {
        while ((dirr = readdir(d)) != NULL)
        {
            // printf("dirr->d_name %s \n", dirr->d_name);
            if (ft_strncmp(dirr->d_name, cmd, len) == 0 && ft_strlen(dirr->d_name) == len)
            {   
                closedir(d);
                return (1);
            }
        }
        closedir(d);
    }
    return (0);
}

char *ft_pars_path(char *path, char *cmd, int len, t_vars *vars) //char *
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
            // printf("ifhome is %s \n", ifhome);
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
            // printf("dir is %s \n", dir);
            if (ifhome)
            {
                if(dir)
                    free(dir);
                dir = ft_strjoin(ifhome, dir);
                // printf("dir is %s \n", dir);
            }
            if (ft_check_dir(dir, cmd, ft_strlen(cmd)) == 1)
            {
                // printf("command in => %s \n", dir);
                return (dir);
            }

            free(dir);
            // break;
        }
        i++;
    }
    return (0);
}

void ft_execuve(char *path, char **cmd, t_vars *vars)
{
    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0)
    {
        if (execve(path, cmd, vars->env_var) == -1)
        {
            printf("Minishell: command not found: %s \n", cmd[0]);
            exit(0);
        }
    }
    else if (pid < 0)
        printf("Error forking \n");
    else
        waitpid(pid, &status, 0);
}

int ft_check_if_builtins(t_vars *vars)
{
    if (ft_strncmp(vars->cmd_list->cmd[0], "echo", 4) == 0 && ft_strlen(vars->cmd_list->cmd[0]) == 4)
        return (ft_echo(vars));
    else if (ft_strncmp(vars->cmd_list->cmd[0], "cd", 2) == 0 && ft_strlen(vars->cmd_list->cmd[0]) == 2)
        return (ft_cd(vars));
    else if (ft_strncmp(vars->cmd_list->cmd[0], "pwd", 3) == 0 && ft_strlen(vars->cmd_list->cmd[0]) == 3)
        return (ft_pwd(vars));
    else if (ft_strncmp(vars->cmd_list->cmd[0], "export", 6) == 0 && ft_strlen(vars->cmd_list->cmd[0]) == 6)
        return (ft_export(vars));
    else if (ft_strncmp(vars->cmd_list->cmd[0], "unset", 5) == 0 && ft_strlen(vars->cmd_list->cmd[0]) == 5)
        return (ft_unset(vars));
    else if (ft_strncmp(vars->cmd_list->cmd[0], "env", 3) == 0 && ft_strlen(vars->cmd_list->cmd[0]) == 3)
        return (ft_env(vars));
    else if (ft_strncmp(vars->cmd_list->cmd[0], "exit", 4) == 0 && ft_strlen(vars->cmd_list->cmd[0]) == 4)
        return (ft_exit(vars));
    else
        return (0);
}

int ft_check_if_vars(t_vars *vars, t_command *cmd_struct)
{
    int i = 0;

        while(cmd_struct->cmd[0][i])
            if (cmd_struct->cmd[0][i++] == '=')
            {
                vars->env_var = ft_append_to_dobl_arr(vars->env_var, cmd_struct->cmd[0]);
                return (1);
            }
    return (0);
}


void ft_mi_exec(t_vars *vars)
{
    char *path;
    char *cmd_path;
    char *temp;
    t_command *temp_cmd;
    temp_cmd = vars->cmd_list;
    while (temp_cmd != NULL)
    {
        if(ft_check_if_vars(vars, temp_cmd))
        {
            temp_cmd = temp_cmd->next;
            continue ;
        }
        else if (ft_check_if_builtins(vars) == 0)
        {
            path = ft_get_val("PATH", vars->env_var);
            // printf("PATH is %s \n", path);
            // printf("cmd is %s \n", vars->cmd_list->cmd[0]);
            cmd_path = ft_pars_path(path, temp_cmd->cmd[0], 5, vars);  
            // printf("cmd_path is %s \n", cmd_path);
            if (cmd_path)
            {
                temp = cmd_path;
                cmd_path = ft_strjoin(cmd_path, "/");
                free(temp);
                temp = cmd_path;
                cmd_path = ft_strjoin(cmd_path, temp_cmd->cmd[0]);
                free(temp);
                printf("cmd_path is %s \n", cmd_path);
                ft_execuve(cmd_path, temp_cmd->cmd, vars);    // ATENTION
                free(cmd_path);
            }
            else if ((temp_cmd->cmd[0][0] == '.' && (temp_cmd->cmd[0][1] == '/' || temp_cmd->cmd[0][1] == '.')) || temp_cmd->cmd[0][0] == '/')
                ft_execuve(temp_cmd->cmd[0], temp_cmd->cmd, vars);
            else
            {   // ATENTION
                printf("Minishell: command not found: %s \n", temp_cmd->cmd[0]);
            }
        }
        temp_cmd = temp_cmd->next;
    }
}