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

/*void ft_pipe(char *path, t_vars *vars, int i, int *prev_fd)
{
    pid_t pid;

    if (pipe(vars->cmd_list->fd) == -1)
    {
        perror ("Error: ");
        return ;
    }
    pid = fork();
    if (pid == -1)
    {
        perror ("Error: ");
        return ;
    }
    else if ( pid == 0)
    {
        close (vars->cmd_list->fd[0]);
        dup2(vars->cmd_list->fd[1], STDOUT_FILENO);
        close (vars->cmd_list->fd[1]);
        dup2(*prev_fd, STDIN_FILENO);
        close (*prev_fd);
        execve(path, &vars->cmd_list->cmd[i], vars->env_var);
    }
    else
    {
        close (vars->cmd_list->fd[1]);
        close (*prev_fd);
        *prev_fd = vars->cmd_list->fd[0];
    }
}

void ft_last_pipe(char *path, t_vars *vars, int i, int *prev_fd)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror ("Error: ");
        return ;
    }
    else if ( pid == 0)
    {
        dup2(*prev_fd, STDIN_FILENO);
        close (*prev_fd);
        execve(path, &vars->cmd_list->cmd[i], vars->env_var);
    }
    else
    {
        close (*prev_fd);
        waitpid(-1, NULL, 0);
    }  
}*/

/*void ft_execuve(char *path, char **cmd, t_vars *vars)
{
    //pid_t pid;
    //int status;
    int prev_fd;
    int i;

    //prev_fd = 0;
    //if (prev_fd == -1)
    //{
        //perror("Error:");
    //}
    i = 0;
    //printf("num_pipes is %zu \n", vars->num_pipes);
    while (i < vars->num_pipes)
    {
        prev_fd = 0;
        if (pipe(vars->cmd_list->fd) == -1)
        {
            perror ("Error: ");
            return ;
        }

        pid_t pid = fork();
        if (pid == -1)
        {
            perror ("Error: ");
            return ;
        }
        else if (pid == 0)
        {
            //printf("i is %d \n", i);
            if (i > 0)
            {
                if (dup2(prev_fd, STDIN_FILENO) == -1)
                {
                    perror("Duplication failed");
                    exit(EXIT_FAILURE);
                } 
                close(prev_fd); 
            }
            if (dup2(vars->cmd_list->fd[1], STDOUT_FILENO) == -1)
            {
                perror("Duplication failed");
                exit(EXIT_FAILURE);
            }
            close(vars->cmd_list->fd[0]);

            if (execve(path, &vars->cmd_list->cmd[i], vars->env_var) == -1)
            {
                perror("Error: ");
                exit(EXIT_FAILURE);
            }
        }
        else 
        {
            close (vars->cmd_list->fd[1]);
            if (prev_fd != 0)
            {
                close(prev_fd);
            }
                prev_fd = vars->cmd_list->fd[0];
                printf("prev_fd is %d \n", prev_fd);
                //printf("cmd is %d\n", vars->num_cmds);
        }
        i++;
    }
    if (prev_fd != 0)
    {
        close(prev_fd);
    }

    i = 0;
    while (i < vars->num_pipes)
    {
        waitpid(-1, NULL, 0);
        i++;
    }
        
}*/

    /*{
        if (i == vars->num_pipes - 1)
        {
            ft_last_pipe(path, vars, i, &prev_fd);
            printf("last pipe \n");
        }
        else if (i < vars->num_pipes)
        {
            ft_pipe(path, vars, i, &prev_fd);
            printf("pipe \n");
        }
        i++;
    }*/
   
//}

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

void ft_execuve(char *path, char **cmd, t_vars *vars)
{
    pid_t pid;
    int prev_pipe;
    int i;
    int status;

    i = 0;
    prev_pipe = 0;
    while (i < vars->num_pipes + 1)
{
    if(pipe(vars->cmd_list->fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror ("fork");
        exit(EXIT_FAILURE);
    }
    if ( pid == 0)
    {
        dup2(prev_pipe, STDIN_FILENO);
        if (i < vars->num_pipes - 1)
        {
            dup2(vars->cmd_list->fd[1], STDOUT_FILENO);
        }
        close(vars->cmd_list->fd[0]);
        execve(path, cmd, vars->env_var);

        perror ("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        close(vars->cmd_list->fd[1]);
        prev_pipe = vars->cmd_list->fd[0];
        waitpid(-1, &status, WUNTRACED | WNOHANG);
    }
    i++;
}
    /*i = 0;
    while (i < vars->num_pipes)
    {
        
        i++;
    }*/
}


void ft_mi_exec(t_vars *vars)
{
    char *path;
    char *cmd_path;
    char *temp;
    if (ft_check_if_builtins(vars) == 0)
    {
        path = ft_get_val("PATH", vars->env_var);
        // printf("PATH is %s \n", path);
        cmd_path = ft_pars_path(path, vars->cmd_list->cmd[0], 5, vars);  
        // printf("cmd_path is %s \n", cmd_path);
        if (cmd_path)
        {
            temp = cmd_path;
            cmd_path = ft_strjoin(cmd_path, "/");
            free(temp);
            temp = cmd_path;
            cmd_path = ft_strjoin(cmd_path, vars->cmd_list->cmd[0]);
            free(temp);
            printf("cmd_path is %s \n", cmd_path);
            //printf("cmd is %s \n", vars->cmd_list->cmd[0]);
            //printf("cmd is %s \n", vars->cmd_list->cmd[1]);
            //printf("cmd is %s \n", vars->cmd_list->cmd[2]);
            //printf("cmd_splited is %s\n", vars->cmd_list->cmd_splited[0]);
            //printf("cmd_splited is %s\n", vars->cmd_list->cmd_splited[1]);
            printf("num_cmds is %d\n", vars->num_cmds);
            printf("num_pipes is %zu\n", vars->num_pipes);
            //printf("cmd_splited is %c\n", vars->cmd_list->cmd_splited[0][1]);
            ft_execuve(cmd_path, vars->cmd_list->cmd, vars);    // ATENTION
            free(cmd_path);
        }
        else
            printf("Minishell: command not found: %s \n", vars->cmd_list->cmd[0]);
    }
}