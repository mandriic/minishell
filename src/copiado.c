#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// just count number of commands
int count(char ***cmd) {
  int i;
  i = 0;
  while (cmd[i]) i++;
  return i;
}

void pipeline(char ***cmd) {
  int i, j = 0;
  pid_t pid;
  int cmd_len = count(cmd);
  int fd[2 * cmd_len];

  // pipe(2) for cmd_len times
  for (i = 0; i < cmd_len; i++) {
    if (pipe(fd + i * 2) < 0) {
      perror("couldn't pipe");
      exit(EXIT_FAILURE);
    }
  }
  while (*cmd != NULL) {
    if ((pid = fork()) == -1) {
      perror("fork");
      exit(1);
    } else if (pid == 0) {
      // if there is next
      if (*(cmd + 1) != NULL) {
        if (dup2(fd[j + 1], 1) < 0) {
          perror("dup2");
          exit(EXIT_FAILURE);
        }
      }
      // if there is previous
      if (j != 0) {
        if (dup2(fd[j - 2], 0) < 0) {
          perror("dup2");
          exit(EXIT_FAILURE);
        }
      }

      for (i = 0; i < 2 * cmd_len; i++) {
        close(fd[i]);
      }

      if (execvp((*cmd)[0], *cmd) < 0) {
        perror((*cmd)[0]);
        exit(EXIT_FAILURE);
      }
    } else if (pid < 0) {
      perror("error");
      exit(EXIT_FAILURE);
    }

    // no wait in each process,
    // because I want children to exec without waiting for each other
    // as bash does.
    cmd++;
    j += 2;
  }
  // close fds in parent process
  for (i = 0; i < 2 * cmd_len; i++) {
    close(fd[i]);
  }
  // wait for children
  for (i = 0; i < cmd_len; i++) wait(NULL);
}

int main(int argc, char *argv[]) {
  char *ls[] = {"ls", "-l", NULL};
  char *rev[] = {"rev", NULL};
  char *nl[] = {"nl", NULL};
  char *cat[] = {"cat", NULL};
  char *wc[] = {"wc", "-l", NULL};
  char *head[] = {"head", "-c", "1000", NULL};
  char *time[] = {"time", "sleep", "3", NULL};
  char *echo[] = {"echo", "toto", NULL};


  //char **cmd[] = {ls, rev,  cat, nl, wc, NULL};
  char **cmd[] = {ls, nl, wc, NULL};

  pipeline(cmd);
  return (0);
}

/* por si acaso 

void	ft_multiple_pipes()
{
	t_command	*cmd1 = NULL;
	t_command	*cmd2 = NULL;
	t_command	*cmd3 = NULL;
	// t_command	*cmd4 = NULL;
	t_command	*aux;

	char	*path_to_execve;
	int		id;
	int		status;

	dar_datos_a_los_cmd();
	aux = cmd1;

	while (aux->next)
	{
		if (pipe(aux->fd))
			perror("pipe");//mejorar esto
		aux = aux->next;
	}
	aux = cmd1;
	while (aux)
	{
		path_to_execve = ft_get_path_to_execve(g_data.envp_copy, aux->comando_a_pelo);
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
			ft_execute(path_to_execve, aux->cmd, g_data.envp_copy);
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
	ft_free_array(g_data.envp_copy);
	ft_free_nodes(cmd1);
	aux = cmd1;

	free(cmd1);
	free(cmd2);
	free(cmd3);
	// free(cmd4);
}
*/