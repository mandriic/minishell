# include "../inc/minishell.h"

void	ft_error_exit(char *err_msg)
{
	printf("%s\n", err_msg);
	perror("");
	exit(EXIT_FAILURE);
}

void leaks ()
{
	system ("leaks -fullContent --list minishell");
}

void	ft_free_nodes(t_command *cmd)
{
	t_command	*aux;

	aux = cmd;
	while (aux)
	{
		free(aux->comando_a_pelo);
		free(aux->comando_con_flags);
		ft_free_array(aux->comando_bonito);
		ft_free_array(aux->infiles);
		ft_free_array(aux->outfiles);
		aux = aux->next;
	}
}

void	ft_close_pipes(t_command *cmd)
{
	t_command	*aux;

	aux = cmd;
	while (aux->next)
	{
		close(aux->fd[0]);
		close(aux->fd[1]);
		aux = aux->next;
	}
	return ;
}

void	ft_dup_infile(t_command *cmd)
{
	int	fd_infile;
	int	i;

	if (cmd->infiles == NULL)
		return ;
	i = 0;
	while(cmd->infiles[i])
	{
		fd_infile = open(cmd->infiles[i], O_RDONLY);
		if (fd_infile < 0)
			perror("fdinfile");//pendiente de mejora
		if (cmd->infiles[i + 1] != NULL)
		{
			dup2(fd_infile, 0);
			close(fd_infile);
		}
		close(fd_infile);
		//gestionar "<<" here-doc
		i++;
	}
}

void	ft_dup_outfile(t_command *cmd)
{
	int	fd_outfile;
	int	i;

	if (cmd->outfiles == NULL)
		return ;
	i = 0;
	while(cmd->outfiles[i])
	{
		fd_outfile = open(cmd->outfiles[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (fd_outfile < 0)
			perror("fd_outfile:");//pendiente de mejora
		if (cmd->outfiles[i + 1] == NULL)
		{
			close(STDOUT_FILENO);
			dup(fd_outfile);
		}
		close(fd_outfile);
		//gestionar ">>" appends
		i++;
	}
}

void	ft_redirections(t_command *cmd)
{
	if (cmd->prev != NULL)
		dup2(cmd->prev->fd[0], 0);
	if (cmd->next != NULL)
		dup2(cmd->fd[1], 1);
	ft_dup_infile(cmd);
	ft_dup_outfile(cmd);
}

void	dar_datos_a_los_cmd(t_command **cmd1, t_command **cmd2, t_command **cmd3)
{
	*cmd1 = malloc(sizeof(t_command));
	*cmd2 = malloc(sizeof(t_command));
	*cmd3 = malloc(sizeof(t_command));
	// *cmd4 = malloc(sizeof(t_command));
	

	(*cmd1)->comando_a_pelo = ft_strdup("ls");
	(*cmd1)->comando_con_flags = ft_strdup("ls -la");
	(*cmd1)->comando_bonito = ft_split("ls -la", ' ');
	(*cmd1)->infiles = NULL;
	(*cmd1)->outfiles = NULL;
	(*cmd1)->next = *cmd2;
	(*cmd1)->prev = NULL;

	(*cmd2)->comando_a_pelo = ft_strdup("nl");
	(*cmd2)->comando_con_flags = ft_strdup("nl");
	(*cmd2)->comando_bonito = ft_split("nl", ' ');
	(*cmd2)->infiles = NULL;
	(*cmd2)->outfiles = NULL;
	(*cmd2)->next = *cmd3;
	(*cmd2)->prev = *cmd1;

	(*cmd3)->comando_a_pelo = ft_strdup("wc");
	(*cmd3)->comando_con_flags = ft_strdup("wc -l");
	(*cmd3)->comando_bonito = ft_split("wc -l", ' ');
	(*cmd3)->infiles = NULL;
	(*cmd3)->outfiles = NULL;
	(*cmd3)->next = NULL;
	(*cmd3)->prev = *cmd2;

/* 
	(*cmd1)->comando_a_pelo = ft_strdup("cat");
	(*cmd1)->comando_con_flags = ft_strdup("cat");
	(*cmd1)->comando_bonito = ft_split("cat", ' ');
	(*cmd1)->infiles = ft_split("lotr.txt", ' ');
	(*cmd1)->outfiles = NULL;
	(*cmd1)->next = *cmd2;
	(*cmd1)->prev = NULL;

	(*cmd2)->comando_a_pelo = ft_strdup("grep");
	(*cmd2)->comando_con_flags = ft_strdup("grep Moria");
	(*cmd2)->comando_bonito = ft_split("grep Moria", ' ');
	(*cmd2)->infiles = NULL;
	(*cmd2)->outfiles = NULL;
	(*cmd2)->next = *cmd3;
	(*cmd2)->prev = *cmd1;

	(*cmd3)->comando_a_pelo = ft_strdup("grep");
	(*cmd3)->comando_con_flags = ft_strdup("grep -n mines");
	(*cmd3)->comando_bonito = ft_split("grep -n mines", ' ');
	(*cmd3)->infiles = NULL;
	(*cmd3)->outfiles = NULL;
	(*cmd3)->next = *cmd4;
	(*cmd3)->prev = *cmd2;

	(*cmd4)->comando_a_pelo = ft_strdup("nl");
	(*cmd4)->comando_con_flags = ft_strdup("nl");
	(*cmd4)->comando_bonito = ft_split("nl", ' ');
	(*cmd4)->infiles = NULL;
	(*cmd4)->outfiles = ft_split("wololo.txt", ' ');
	(*cmd4)->next = NULL;
	(*cmd4)->prev = *cmd3;
 */
/* 
	(*cmd1)->comando_a_pelo = ft_strdup("cat");
	(*cmd1)->comando_con_flags = ft_strdup("cat");
	(*cmd1)->comando_bonito = ft_split("cat", ' ');
	(*cmd1)->infiles = NULL;
	(*cmd1)->outfiles = NULL;
	(*cmd1)->next = *cmd2;
	(*cmd1)->prev = NULL;

	(*cmd2)->comando_a_pelo = ft_strdup("cat");
	(*cmd2)->comando_con_flags = ft_strdup("cat");
	(*cmd2)->comando_bonito = ft_split("cat", ' ');
	(*cmd2)->infiles = NULL;
	(*cmd2)->outfiles = NULL;
	(*cmd2)->next = *cmd3;
	(*cmd2)->prev = *cmd1;

	(*cmd3)->comando_a_pelo = ft_strdup("cat");
	(*cmd3)->comando_con_flags = ft_strdup("cat");
	(*cmd3)->comando_bonito = ft_split("cat", ' ');
	(*cmd3)->infiles = NULL;
	(*cmd3)->outfiles = NULL;
	(*cmd3)->next = *cmd4;
	(*cmd3)->prev = *cmd2;

	(*cmd4)->comando_a_pelo = ft_strdup("cat");
	(*cmd4)->comando_con_flags = ft_strdup("cat");
	(*cmd4)->comando_bonito = ft_split("cat", ' ');
	(*cmd4)->infiles = NULL;
	(*cmd4)->outfiles = NULL;
	(*cmd4)->next = NULL;
	(*cmd4)->prev = *cmd3;
 */
}

int main(int argc, char *argv[], char *envp[])
{

	// atexit(leaks);
	(void)argc;
	(void)argv;
	int		id;
	int		status;
	// int		fd_in;
	// int		fd_out;

	char	**envp_copy;
	char	*path_to_execve;

	t_command	*cmd1 = NULL;
	t_command	*cmd2 = NULL;
	t_command	*cmd3 = NULL;
	// t_command	*cmd4 = NULL;
	t_command	*aux;

	envp_copy = ft_copy_enviroment_vars_into_matrix(envp);	
	dar_datos_a_los_cmd(&cmd1, &cmd2, &cmd3);
	aux = cmd1;

	/* Esto crea los pipes y los hijos, en los hijos hace las redirecciones necesarias
	cierra los extremos de los pipes y ejecuta los comandos
	No hay gestión de errores
	No hay gestión de << ni >>, solo < y >
	No hay control de buildins
	 */
	while (aux->next)
	{
		if (pipe(aux->fd))
			perror("pipe");//mejorar esto
		aux = aux->next;
	}
	aux = cmd1;
	while (aux)
	{
		path_to_execve = ft_get_path_to_execve(envp_copy, aux->comando_a_pelo);
		id = fork();
		if (id < 0)
		{
			perror("fork");//mejorar esto
			exit(EXIT_FAILURE);
		}
		if (id == 0)
		{
			ft_redirections(aux);
			ft_close_pipes(cmd1);
			ft_execute(path_to_execve, aux->comando_bonito, envp_copy);
		}
		free(path_to_execve);
		aux = aux->next;
	}
	ft_close_pipes(cmd1);
	aux = cmd1;
	while (aux)
	{
		wait(&status);
		ft_putnbr_fd(status, 2);
		ft_putstr_fd("\n", 2);
		aux = aux->next;
	}
	ft_free_array(envp_copy);
	ft_free_nodes(cmd1);
	aux = cmd1;

	free(cmd1);
	free(cmd2);
	free(cmd3);
	// free(cmd4);
	return (0);
}



/* 
	char *cmd1[] = {
		"ls",
		"-la",
		// "/Users/JoseGF/Desktop",
		// "/home/josgarci/minishell",
		"/Users/josgarci/Desktop",
		NULL
	};
	char *cmd2[] = {
		"wc",
		NULL
	};

	int	id;
	int	id2;
	int	fd1[2]; //0 leer, 1 escribir
	int	fd2;

	path_to_execve = ft_get_path_to_execve(envp_copy, cmd1[0]);

	if (pipe(fd1) == -1)
		ft_error_exit("Error pipe");
	id = fork();
	if (id == -1)
		ft_error_exit("Error fork");
	if (id == 0)
	{

		if (close(fd1[0]) == -1)
			ft_error_exit("Error close");
		if (dup2(fd1[1], STDOUT_FILENO) == -1)
			ft_error_exit("Error dup");
		if (close(fd1[1]) == -1)
			ft_error_exit("Error close");
		ft_execute(path_to_execve, cmd1, envp_copy);
		// if (execve("/bin/ls", cmd1, envp) == -1)
			// ft_error_exit("Error comando ejecución");
	}
	else
	{
		free(path_to_execve);
		close(fd1[1]);
		// close(fd1[0]);
		path_to_execve = ft_get_path_to_execve(envp_copy, cmd2[0]);

		id2 = fork();
		if (id2 == 0)
		{

			//if hay redirección
			fd2 = open(outfile, O_WRONLY | O_CREAT, 0744);
			dup2(fd1[0], STDIN_FILENO);
			close(fd1[0]);
			dup2(fd2, STDOUT_FILENO);
			close(fd2);
			//end if
			ft_execute(path_to_execve, cmd2, envp_copy);
			// if (execve("/usr/bin/wc", cmd2, envp) == -1)
			// 	write(2, "Oh oh\n", 6);
		}
	close(fd1[0]);
	wait(NULL);
	wait(NULL);
	free(path_to_execve);
	ft_free_array(envp_copy);

	}
 */
