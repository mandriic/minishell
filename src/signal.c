#include "../inc/minishell.h"

void    ft_signal(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (sig == SIGQUIT)
    {
        printf("Quit: 3\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void    set_signal(void)
{
    signal(SIGINT, ft_signal);
    signal(SIGQUIT, ft_signal);
}