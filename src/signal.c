#include "../inc/minishell.h"

extern int g_e_status;

void	ft_singint_hand(int sig)
{
	struct termios	prompt_conf;

	if (sig == SIGINT)
	{
		g_e_status = 130;
		printf("\n");
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
