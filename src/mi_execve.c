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

int ft_check_dir(char *dir, char *cmd, size_t len)
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

char *ft_last_redir(char **redirs, t_vars *vars, int outfile, char *first)
{
    int i = 0;
    int fd;
    while (redirs[i])
    {
        if (outfile == 1)
        {
            fd = open(redirs[i], O_TRUNC | O_CREAT | O_RDWR, 0644);
            if (fd < 0)
            {
                ft_putstr_fd(redirs[i], 2);
                ft_putstr_fd(": Permission denied\n", 2);
                vars->error = 1;
                exit(vars->error);
                // exit(1);
            }
            close(fd);
        }
        if (access(redirs[i], F_OK) == 0 || outfile == 1)
            i++;
        else if (access(redirs[i], F_OK) == -1 && outfile != 1)
        {
            ft_putstr_fd(redirs[i], 2);
            ft_putstr_fd(": No such file or directory\n", 2);
            vars->error = 1;
            exit(vars->error);
            // exit(1);
        }
    }
    return (redirs[i - 1]);
}
int ft_what_is_first(char *line, t_vars *vars)
{
    static int i = -1;
    int *mask;
    mask = ft_mask(line, vars, 0);

    // printf("line is %s \n", line);
    printf("mask is %d \n", mask[0]);
    printf("mask is %d \n", mask[1]);
    printf("mask is %d \n", mask[2]);
    printf("mask is %d \n", mask[3]);
    printf("mask is %d \n", mask[4]);
    while (line[++i])
    {
        if (mask[i] == 11 && mask[i + 1] == 10)
        {
            i++;
            return (11);
        }
        if (mask[i] == 10 && line[i] == '<')
            return (10);
        
    }
    write(1, "tester\n", 7);
    return (0);
}

int ft_dup_file(t_command *cmd, t_vars *vars)
{
    char * test_infile;
    int	fd_infile;
    char *first;
    int first2;
    int *mask;

    
    // if (first[0] == '<')
        // printf("first is %c\n", first[0]);
    // first2 = ft_what_is_first(cmd->str_raw, vars);
    // printf("first2 is %d\n", first2);
    mask = ft_mask(cmd->str_raw, vars, 0);
    int i = -1;
    while (++i < ft_strlen(cmd->str_raw))
    {
        // printf("mask is %d \n", mask[i]);
        if (cmd->appends && mask[i] == 11)
            {
                // printf("I append I go %d\n", i);
                i++;
                fd_infile = open(ft_last_redir(cmd->appends, vars ,1, first), O_APPEND | O_CREAT | O_RDWR, 0664);
                dup2(fd_infile, 1);
                close(fd_infile);
            }
        if (cmd->infiles && mask[i] == 10 && cmd->str_raw[i] == '<')
        {
                // printf("I infile I go %d\n", i);

            test_infile = ft_last_redir(cmd->infiles, vars, 0, first);
            if (!test_infile)
                vars->error = 1;
            if (!test_infile && first[0] == '<')
                return (1);
            fd_infile = open(test_infile, O_RDONLY);
            if (fd_infile < 0)
                vars->error = 1;
            if (fd_infile < 0 && first[0] == '<')
            {
                ft_putstr_fd("check", 1);
                ft_putstr_fd(cmd->infiles[0], 2);
                ft_putstr_fd(": No such file or directory\n", 2);
                vars->error = 1;
                exit(vars->error);
            }
            dup2(fd_infile, 0);
            close(fd_infile);
        }
        if (cmd->outfiles && mask[i] == 10 && cmd->str_raw[i] == '>')
        {
            // close();
            test_infile = ft_last_redir(cmd->outfiles, vars, 1, first);
            if (!test_infile)
                return (1);
            fd_infile = open(ft_last_redir(cmd->outfiles, vars, 1, first), O_TRUNC | O_CREAT | O_RDWR, 0664);
            if (fd_infile < 0)
            {
                ft_putstr_fd(cmd->outfiles[0], 2);
                ft_putstr_fd(": Permission denied\n", 2);
                vars->error = 1;
                if (cmd->infiles)
                {
                    test_infile = ft_last_redir(cmd->infiles, vars, 0, first);
                    if (!test_infile)
                        return (1);
                    fd_infile = open(test_infile, O_RDONLY);
                    dup2(fd_infile, 0);
                    close(fd_infile);
                }
                return (1);
            }
            dup2( fd_infile, 1); //
            close(fd_infile); //
        }
        // first2 = ft_what_is_first(cmd->str_raw, vars);
    }
    return (0);
}
//     // if (cmd->heredocs)
//     // {
//     //     fd_infile = open("./.temp", O_TRUNC | O_CREAT | O_RDWR, 0664);
//     //     while(cmd->heredocs[i])
//     //     {
//     //         write(fd_infile, cmd->heredocs[i], ft_strlen(cmd->heredocs[i]));
//     //         write(fd_infile, "\n", 1);
//     //         i++;
//     //     }
//     //     fd_infile = open("./.temp", O_RDONLY);
//     //     dup2(fd_infile, 0);
//     //     close(fd_infile);
//     // }
//     if (cmd->infiles)
// 	{
// 		fd_infile = open(ft_last_redir(cmd->infiles, vars), O_RDONLY);
// 		// if (fd_infile < 0)
//         // {
//         //     ft_putstr_fd(ft_last_redir(cmd->infiles, vars), 2);
// 		// 	ft_putstr_fd(": No such file or directory\n", 2);
//         //     vars->error = 1;
//         //     exit(1);
//         // }
// 		// perror("fd_infile");
//     	dup2(fd_infile, 0);
//  		close(fd_infile);
// 	}
// }


// void	ft_dup_outfile(t_command *cmd, t_vars *vars)
// {
// 	int	fd_outfile;

//     // if (cmd->appends)
//     // {
//     //     fd_outfile = open(cmd->appends[0], O_APPEND | O_CREAT | O_RDWR, 0664);
//     //     if (fd_outfile < 0)
//     //         perror("fd_outfile:");
//     //     close(STDOUT_FILENO);
//     //     dup2(fd_outfile, 1);
//     //     close(fd_outfile);
//     // }    
//     // if (cmd->outfiles != NULL)
//     // {
//     //     fd_outfile = open(cmd->outfiles[0], O_TRUNC | O_CREAT | O_RDWR, 0664);
//     //     if (fd_outfile < 0)
//     //         perror("fd_outfile:");
//     //     close(STDOUT_FILENO);
//     //     dup2(fd_outfile, 1);
//     //     close(fd_outfile);
// 	// }
// }

int	ft_redirections(t_command *cmd, t_vars *vars)
{
	/*if (cmd->prev != NULL)
		dup2(cmd->prev->fd[0], 0);
	if (cmd->next != NULL)
		dup2(cmd->fd[1], 1);*/
	if (ft_dup_file(cmd, vars))
        return (1);
    return (0);
	// ft_dup_outfile(cmd, vars);
}

/*char	ft_exit_cmd(int exit, t_command *cmd)
{
    if (cmd->exit_status)
	    free (cmd->exit_status);
    else
    {
        cmd->exit_status = malloc(sizeof(char) * 2);
        //cmd->exit_status[0] = '0';
        //cmd->exit_status[1] = '\0';
        if(!cmd->exit_status)
            return (0);
	    cmd->exit_status = ft_itoa(exit);
        {
            printf("exit_status2 %s \n", cmd->exit_status);
            return(*cmd->exit_status);
        } 
    }
    
    free(cmd->exit_status);
}*/


void ft_execuve(char *path, t_command *cmd, t_vars *vars)
{

    int status, pid;
    // if (ft_strncmp("exit", cmd->cmd[0], 4) == 0)
    //     exit(0);
    pipe(cmd->fd);
    //pid_t* child_pid;

    //child_pid = (pid_t *)malloc(sizeof(pid_t) * vars->num_pipes + 1);
   
    pid = fork();
    
    
    if (pid == 0)
    {
        signal(SIGUSR2, handle_process_on); //signal to catch
        if (cmd->next || cmd->outfiles)
        {  
            close(cmd->fd[0]);
            dup2(cmd->fd[1], 1);
            // ft_redirections(cmd, vars);
            close(cmd->fd[1]);
        }
        // if (cmd->prev && cmd->prev->outfiles)
        // 	close(cmd->prev->fd[1]);
        if (cmd->prev && cmd->prev->fd[0] != -1)
        {
            close(cmd->prev->fd[1]);
            dup2(cmd->prev->fd[0], 0);
            // ft_redirections(cmd, vars);
            close(cmd->prev->fd[0]);
        }
        if (ft_redirections(cmd, vars))
            exit(vars->error);
        if (ft_check_if_builtins(vars, cmd) == 0)
        {
        
            //printf("debug %s \n", cmd->cmd[0]);
            if (execve(path, cmd->cmd, vars->env_var) == -1)
            {
                printf("Minishell: command not found: %s \n", cmd->cmd[0]);
                exit(1);
            }
            
            // else
            // {
            //     ft_redirections(cmd, vars);
        
            // }
        }
        else
            exit(vars->error);
                

          /*if (cmd->next && cmd->fd[1] != 1)
            exit(1);
      else */
      //if (cmd->next ==  NULL)
         //exit(1);
        //else 

        exit(0);
            //ft_execuve(path, cmd->next, vars);
    }
    else if (pid < 0)
        printf("Error forking \n");
    else if (pid > 0)
    {
        signal(SIGUSR2, SIG_IGN); //signal to ignore
        rl_set_prompt("");
        // if (cmd->next)
        //     close(cmd->fd[1]);
        //cmd->child_pid[i] = pid;
        if (cmd->prev && cmd->prev->fd[0] != -1)
        {
            close(cmd->prev->fd[0]);
            close (cmd->prev->fd[1]);//added after to heck the signals
        }
        if (cmd->prev && cmd->prev->fd[1] != -1)
        {
            close(cmd->prev->fd[1]);
            close (cmd->prev->fd[0]);//added after to check the signals
        }

        // close(cmd->prev->fd[0]);

        // if (cmd->next == NULL) // it prints only the last command
        // {
            // if (vars->error == 0)
                // {
                    // if (ft_strncmp("cat", cmd->cmd[0], 3))
                    //     waitpid(pid, &status, WNOWAIT);
                    // else
                    //     waitpid(pid, &status, 0);
                    //     // printf("error %d\n", WEXITSTATUS(status));
                    // vars->error = WEXITSTATUS(status);
            if (ft_strncmp("cat", cmd->cmd[0], 3) == 0 && cmd->next != NULL)
            {
                waitpid(pid, &status, WNOWAIT);

                    // perror("waitpid() failed");

                    vars->error = 0;

            }
            else
            {
                if(waitpid(pid, &status, 0) == -1)
                {
                    perror("waitpid() failed");
                    exit(EXIT_FAILURE);
                }    
                if ( WIFEXITED(status) )
                {
                    vars->error = WEXITSTATUS(status);
                    // printf("Exit status was %d\n", vars->error);
                }
            }

        // }
                // }
            // else if (vars->error != 0 && !cmd->infiles)
                // kill(pid, 9);
            //printf("exit %d\n", WEXITSTATUS(status));
            // vars->error = 0;
          
        // }  
    }
             //free(child_pid);
}
int ft_check_if_builtins_true(t_vars *vars, t_command *cmd)
{
    (void)vars;
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

int ft_check_if_vars(t_vars *vars, t_command *cmd_struct)
{
    char *temp;
    // char **temp2;
    int i = 0;
    while(cmd_struct->cmd[0][i])
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

int   ft_get_dollar(t_vars *vars, t_command *temp_cmd)
{
    (void)vars;
      int i = 1;

      while (temp_cmd->cmd[i])
      {
          if (ft_strncmp(temp_cmd->cmd[i], "$?", 2) == 0)
          {
              free(temp_cmd->cmd[i]);
              temp_cmd->cmd[i] = ft_itoa(vars->error);
          }
          i++;
      }
      return(0);
}

// int ft_check_redir_open(t_vars *vars, t_command *command)
// {
//     int fd;
//     int i;

//     i = -1;
//     if (command->infiles)
//     {
//         while(command->infiles[++i])
//         {
//             fd = open(command->infiles[i], O_RDONLY);
//             if (fd < 0)
//             {
//                 ft_putstr_fd("minishell: ", 2);
//                 ft_putstr_fd(command->infiles[i], 2);
//                 ft_putstr_fd(": No such file or directory\n", 2);
//                 vars->error = 1;
//                 if (!command->next)
//                     return(1);
//             }
//             else
//                 close(fd);        
//         }
//     }
//     return (0);
// }

void ft_mi_exec(t_vars *vars)
{
    char *path;
    char *cmd_path;
    char *temp;
    t_command   *temp_cmd;
    //int i = 0;

    temp_cmd = vars->cmd_list;
    //temp_cmd->child_pid = (pid_t *)malloc(sizeof(pid_t) * vars->num_pipes + 1);
    while (temp_cmd != NULL && temp_cmd->cmd)
    {
        // printf("temp_cmd->cmd[0] is %s \n", temp_cmd->cmd[0]);
        //signal(SIGUSR2, SIG_IGN);
        if(ft_check_if_vars(vars, temp_cmd))
        {
            if (temp_cmd->next)
                continue ;
            else
                break ;
        }
        // if (ft_check_redir_open(vars, temp_cmd) == 1)
        // {
        //     continue;
        // }
            // break ;
        
        if (ft_check_if_builtins_true(vars, temp_cmd))
        {
            // if (temp_cmd->next != NULL)
                ft_execuve(NULL, temp_cmd, vars); // ATENTION
            // else
            // {
            //     //printf("vars->error is %d \n", vars->error);
            //     ft_check_if_builtins(vars, temp_cmd);
            // }
        }
        else
        {
            // printf("cmd CHECK is %s \n", temp_cmd->cmd[0]);
            path = ft_get_val("PATH", vars->env_var);
            cmd_path = ft_pars_path(path, temp_cmd->cmd[0], 5, vars);
            // printf("cmd_path is %s \n", cmd_path);
            if (!cmd_path && (temp_cmd->cmd[0][0] == '.' || temp_cmd->cmd[0][0] == '/')) //&& (temp_cmd->cmd[0][1] == '/' || temp_cmd->cmd[0][1] == '.'))
                ft_execuve(temp_cmd->cmd[0], temp_cmd, vars); // ATENTION

            else if (cmd_path)
            {
                //signal(SIGUSR2, SIG_IGN);
                temp = cmd_path;
                cmd_path = ft_strjoin(cmd_path, "/");
                free(temp);
                temp = cmd_path;
                cmd_path = ft_strjoin(cmd_path, temp_cmd->cmd[0]);
                free(temp);
                // printf("cmd_path is %s \n", cmd_path);
                ft_get_dollar(vars, temp_cmd);
    
                ft_execuve(cmd_path, temp_cmd, vars);  // ATENTION
                free(cmd_path);
            }
            else
            {
                printf("Minishell: command not found: %s \n", temp_cmd->cmd[0]);
                vars->error = 127;
            }

            // printf("PATH is %s \n", path);
            // printf("cmd is %s \n", vars->cmd_list->cmd[0]);
            // printf("cmd_path is %s \n", cmd_path);         
            // else
            // {   // ATENTION
            //     printf("Minishell: command not found: %s \n", temp_cmd->cmd[0]);
            // }
        }
       /* else 
        {
            printf("Minishell: command not found: %s \n", temp_cmd->cmd[0]);
        }*/

        // if (temp_cmd->fd[1] >= 0)
        //     close(temp_cmd->fd[1]);
        temp_cmd = temp_cmd->next;
        //printf("i is %d \n", i);
        //i++;
    }
}
