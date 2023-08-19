#include "../inc/minishell.h"

void    handle_ctrl_c(int sig)
{
	(void)sig;
	rl_replace_line("", 0); //clears the line
	rl_on_new_line(); //moves the cursor to the beginning of the line and writes Minishell
	kill(0, SIGUSR2); //sends a signal to the process

	ft_putstr_fd("\n", 0); //writes a new line
	rl_on_new_line(); //moves the cursor to the beginning of the line and writes Minishell
	rl_redisplay(); //writes minishell on the desktop
}

void    handle_process_on(int sig)
{
	(void)sig;
	rl_replace_line("", 0); //clears the line
	rl_redisplay(); //writes minishell on the desktop

}

void handler_ctrl_d(int sig) 
{
	(void)sig;
	printf("mi exit\n");
	exit(0);//no esta fiuncionando
}

void    set_signal(void)
{
	struct termios	t;

	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN); //ignores the signal
	signal(SIGUSR2, handle_process_on);
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

