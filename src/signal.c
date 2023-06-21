#include "../inc/minishell.h"

struct termios	t;

void    handle_ctrl_c(int sig)
{
    (void)sig;
    ft_putstr_fd("\n", 1); //writes a new line
    rl_replace_line("", 1); //clears the line
    rl_on_new_line(); //moves the cursor to the beginning of the line and writes Minishell
    //rl_redisplay();
    kill(0, SIGUSR2); //sends a signal to the process
}

void    handle_process_on(int sig)
{
    (void)sig;
    //rl_replace_line("", 0); //clears the line
    rl_on_new_line(); //moves the cursor to the beginning of the line and writes Minishell
    rl_redisplay(); //writes minishell on the desktop
}

void handler_ctrl_d(int sig) 
{
    (void)sig;
    printf("exit\n");
    exit(0);
}

void    set_signal(void)
{
    signal(SIGINT, handle_ctrl_c);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTERM, handler_ctrl_d);  
    signal(SIGUSR2, handle_process_on);
    tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
    //signal(SIGTSTP, SIG_IGN);
}