# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>	


int main ()
{
    char *line;
    rl_replace_line("", 1);
    line = readline("prompt> ");
    return (0);
}