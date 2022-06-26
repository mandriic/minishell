#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
#include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>

# define EOF             -1
# define ERRCHAR         0
# define INIT_SRC_POS    -2

typedef struct s_input
{
    char    *buffer;
    int     bufsize;
    int     curpos;
}   t_input;

typedef struct s_token
{
    struct s_input  *input;
    int             text_len;
    char            *text;
}   t_token;


char    ft_next_char(t_input *input);
void    ft_unget_char(t_input *input);
char    ft_peek_char(t_input *input);
void    ft_skip_white_spaces(t_input *input);

t_token *ft_tokenize(t_input *src);
void    ft_free_token(t_token *tok);

char	*ft_leelinea(void);

#endif