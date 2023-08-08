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
                printf("dir is %s \n", dir);
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

void ft_pipe(void)
{

}

void ft_execuve(char *path, t_command *cmd, t_vars *vars)
{

    int status, pid;
    pipe(cmd->fd);

    pid = fork();
    if (pid == 0)
    {
        if (cmd->next)
        {   
            c("cmd->next"); 
            dup2(cmd->fd[1], 1);
            close(cmd->fd[0]);
            close(cmd->fd[1]);
        }
        if (cmd->prev && cmd->prev->fd[0] != -1)
        {
            dup2(cmd->prev->fd[0], 0);
            close(cmd->prev->fd[0]);
            close(cmd->prev->fd[1]);
        }
        // printf("cmd2 is %s \n", cmd->next->cmd[0]);
        if (ft_check_if_builtins(vars, cmd) == 0)
        {    
            printf("debug %s \n", cmd->cmd[0]);
            if (execve(path, cmd->cmd, vars->env_var) == -1)
            {
                 printf("Minishell: command not found: %s \n", cmd->cmd[0]);
                exit(0);
            }
        }
        exit(0);
    }
    else if (pid < 0)
        printf("Error forking \n");
    else
    {
        // if (cmd->next)
        //     close(cmd->fd[1]);
        if (cmd->prev && cmd->prev->fd[0] != -1)
            close(cmd->prev->fd[0]);
        if (cmd->prev && cmd->prev->fd[1] != -1)
            close(cmd->prev->fd[1]);
        // close(cmd->prev->fd[0]);
        waitpid(pid, &status, 0);
        waitpid(pid, &status, 0);
    }
}
int ft_check_if_builtins_true(t_vars *vars, t_command *cmd)
{
    if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0 && ft_strlen(cmd->cmd[0]) == 4)
        return (1);
    else if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0 && ft_strlen(cmd->cmd[0]) == 2)
        return (1);
    else if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0 && ft_strlen(cmd->cmd[0]) == 3)
        return (1);
    else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0 && ft_strlen(cmd->cmd[0]) == 6)
        return (1);
    else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0 && ft_strlen(cmd->cmd[0]) == 5)
        return (1);
    else if (ft_strncmp(cmd->cmd[0], "env", 3) == 0 && ft_strlen(cmd->cmd[0]) == 3)
        return (1);
    else if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0 && ft_strlen(cmd->cmd[0]) == 4)
        return (1);
    else
        return (0);
}

int ft_check_if_builtins(t_vars *vars, t_command *cmd)
{
    if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0 && ft_strlen(cmd->cmd[0]) == 4)
        return (ft_echo(vars, cmd));
    else if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0 && ft_strlen(cmd->cmd[0]) == 2)
        return (ft_cd(vars, cmd));
    else if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0 && ft_strlen(cmd->cmd[0]) == 3)
        return (ft_pwd(vars, cmd));
    else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0 && ft_strlen(cmd->cmd[0]) == 6)
        return (ft_export(vars, cmd));
    else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0 && ft_strlen(cmd->cmd[0]) == 5)
        return (ft_unset(vars, cmd));
    else if (ft_strncmp(cmd->cmd[0], "env", 3) == 0 && ft_strlen(cmd->cmd[0]) == 3)
        return (ft_env(vars, cmd));
    else if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0 && ft_strlen(cmd->cmd[0]) == 4)
        return (ft_exit(vars, cmd));
    else
        return (0);
}

int ft_check_if_vars(t_vars *vars, t_command *cmd_struct) // Debe ser cambiado no funciona bien
{
    char *temp;
    char **temp2;
    int i = 0;
    while( cmd_struct->cmd[0] != NULL && cmd_struct->cmd[0][i])
        if (cmd_struct->cmd[0][i++] == '=')
        {
            temp = ft_substr(cmd_struct->cmd[0],0, i);
            if (ft_change_env(vars, temp, cmd_struct->cmd[0] + i, ft_strlen(cmd_struct->cmd[0]) - i) == 0)
                vars->temp_env =ft_append_to_temp_env(vars, cmd_struct->cmd[0]);
            free(temp);
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
    //temp_cmd->child_pid = (pid_t *)malloc(sizeof(pid_t) * vars->num_pipes + 1);
    while (temp_cmd != NULL && temp_cmd->cmd && temp_cmd->cmd[0] != NULL)
    {
        printf("temp_cmd->cmd[0] is %s \n", temp_cmd->cmd[0]);
        //signal(SIGUSR2, SIG_IGN);
        if(ft_check_if_vars(vars, temp_cmd))
        {
            if (temp_cmd->next)
                continue ;
            else
                break ;
        }
        if ( ft_check_if_builtins_true(vars, temp_cmd))//Aqui esta comprobando si es un builtin <
                ft_check_if_builtins(vars, temp_cmd);  //si arriba es true, aqui ejecuta el builtin 
        // else if (ft_check_if_builtins(vars, temp_cmd) == 0)
        // {
            printf("cmd CHECK is %s \n", temp_cmd->cmd[0]);
            path = ft_get_val("PATH", vars->env_var); //cogemos el valor de la variable de entorno PATH
            cmd_path = ft_pars_path(path, temp_cmd->cmd[0], 5, vars); //parseo path con comando
            printf("cmd_path is %s \n", cmd_path);
            if (!cmd_path && (temp_cmd->cmd[0][0] == '.' || temp_cmd->cmd[0][0] == '/')) // comprobamos ruta si es relativa o absoluta y binario no esta en PATH //&& (temp_cmd->cmd[0][1] == '/' || temp_cmd->cmd[0][1] == '.'))
                ft_execuve(temp_cmd->cmd[0], temp_cmd, vars); // ATENTION ejecutamos binario

            else if (cmd_path) //si esta en PATH
            {
                temp = cmd_path;
                cmd_path = ft_strjoin(cmd_path, "/"); //creamos ruta completa
                free(temp);
                temp = cmd_path;
                cmd_path = ft_strjoin(cmd_path, temp_cmd->cmd[0]); //creamos ruta completa
                free(temp);
                printf("cmd_path is %s \n", cmd_path);
                ft_execuve(cmd_path, temp_cmd, vars);  // ATENTION execuvamos binario
                free(cmd_path);
            }
            // printf("PATH is %s \n", path);
            // printf("cmd is %s \n", vars->cmd_list->cmd[0]);
            // printf("cmd_path is %s \n", cmd_path);         
            // else
            // {   // ATENTION
            //     printf("Minishell: command not found: %s \n", temp_cmd->cmd[0]);
            // }
        // }
        temp_cmd = temp_cmd->next; //vamos a siguiente comando
    }
}