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

void    heredoc(t_command *cmd, int fd_infile)
{
    char *temp;

    fd_infile = open(cmd->infiles[0], O_TRUNC | O_CREAT | O_RDWR, 0664);
    while(1)
    {
        write(1, "heredoc>", 9);
        temp = readline("");//hes to chge for the function get_next_line
        if(!ft_strncmp(temp, cmd->heredocs[0], ft_strlen(cmd->heredocs[0] - 1)))
        {
            free(temp);
            break;
        }
        write(fd_infile, temp, ft_strlen(temp));
        free(temp);
    }
    //free(buf);
    //free(cmd->infiles[0]);
    close(fd_infile);
}

void	ft_dup_infile(t_command *cmd)
{
	int	fd_infile;

	if(cmd->infiles)
	{
		fd_infile = open(cmd->infiles[0], O_RDONLY);
		if (fd_infile < 0)
			perror("fd_infile");
		dup2(fd_infile, 0);
		close(fd_infile);
		close(fd_infile);
        // a function to creat heredocs to do << redirections
	}
    else if (cmd->heredocs)
    {
        fd_infile = -1;
        cmd->infiles[0] = ft_strdup("./.infile.tmp");
        heredoc(cmd, fd_infile);
    }
    //to check if it works correctly
}

void	ft_dup_outfile(t_command *cmd)
{
	int	fd_outfile;

    if (cmd->appends)
    {
        fd_outfile = open(cmd->appends[0], O_APPEND | O_CREAT | O_RDWR, 0664);
        if (fd_outfile < 0)
            perror("fd_outfile:");
        close(STDOUT_FILENO);
        dup2(fd_outfile, 1);
        close(fd_outfile);
    }    
     else if (cmd->outfiles != NULL)
    {
        fd_outfile = open(cmd->outfiles[0], O_TRUNC | O_CREAT | O_RDWR, 0664);
        if (fd_outfile < 0)
            perror("fd_outfile:");
        close(STDOUT_FILENO);
        dup2(fd_outfile, 1);
        close(fd_outfile);
	}
}

void	ft_redirections(t_command *cmd)
{
	/*if (cmd->prev != NULL)
		dup2(cmd->prev->fd[0], 0);
	if (cmd->next != NULL)
		dup2(cmd->fd[1], 1);*/
	ft_dup_infile(cmd);
	ft_dup_outfile(cmd);
}

void ft_execuve(char *path, t_command *cmd, t_vars *vars)
{

    int status, pid;
    pipe(cmd->fd);

    pid = fork();
    if (pid == 0)
    {
        ft_redirections(cmd); //si es echo no lo hace
        if (cmd->next)
        {    
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
        if (execve(path, cmd->cmd, vars->env_var) == -1)
        {
            printf("Minishell: command not found: %s \n", cmd->cmd[0]);
            exit(0);
        }
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
    char *temp;
    int i = 0;
        while(cmd_struct->cmd[0][i])
            if (cmd_struct->cmd[0][i++] == '=')
            {
                temp = ft_substr(cmd_struct->cmd[0],0, i);
                if (ft_change_env(vars, temp, cmd_struct->cmd[0] + i, ft_strlen(cmd_struct->cmd[0]) - i) == 0)
                    vars->env_var = ft_append_to_dobl_arr(vars->env_var, cmd_struct->cmd[0]);
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
    while (temp_cmd != NULL)
    {
        if(ft_check_if_vars(vars, temp_cmd))
        {
            if (temp_cmd->next)
                continue ;
            else
                break ;
        }
        else if (ft_check_if_builtins(vars) == 0)
        {
            path = ft_get_val("PATH", vars->env_var);
            cmd_path = ft_pars_path(path, temp_cmd->cmd[0], 5, vars);
            if (!cmd_path && (temp_cmd->cmd[0][0] == '.' || temp_cmd->cmd[0][0] == '/')) //&& (temp_cmd->cmd[0][1] == '/' || temp_cmd->cmd[0][1] == '.'))
                ft_execuve(temp_cmd->cmd[0], temp_cmd, vars); // ATENTION
            else if (cmd_path)
            {
                temp = cmd_path;
                cmd_path = ft_strjoin(cmd_path, "/");
                free(temp);
                temp = cmd_path;
                cmd_path = ft_strjoin(cmd_path, temp_cmd->cmd[0]);
                free(temp);
                printf("cmd_path is %s \n", cmd_path);
                ft_execuve(cmd_path, temp_cmd, vars);  // ATENTION
                free(cmd_path);
            }
            // printf("PATH is %s \n", path);
            // printf("cmd is %s \n", vars->cmd_list->cmd[0]);
            // printf("cmd_path is %s \n", cmd_path);         
            else
            {   // ATENTION
                printf("Minishell: command not found: %s \n", temp_cmd->cmd[0]);
            }
        }
        temp_cmd = temp_cmd->next;
    }
}
