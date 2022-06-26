#include "../inc/minishell.h"

void leakss()
{
	system("leaks minishell");
}

int main()
{
atexit(leakss);
	char	*cmd;

	while (1)
	{
		cmd = readline("minishell: ");

		if (!cmd)
			exit(EXIT_SUCCESS);
		if (cmd[0] == '\0' || ft_strncmp(cmd, "\n", 1) == 0)
		{
			free(cmd);
			continue;
		}
		if (ft_strncmp(cmd, "exit\n", ft_strlen(cmd)) == 0)
		{
			write(1, "exit\n", ft_strlen(cmd) + 1);
			free(cmd);
			break;
		}
		write(1, cmd, ft_strlen(cmd));
		write(1, "\n", 1);
		free(cmd);
		
	} 

	
	return (0);
}


/*    ---- SCANNING INPUT -----    */


char    ft_next_char(t_input *input)
{
	char	c1;

	if (!input || !input->buffer)
	{
		errno = ENODATA;
		return ('\0');
	}
	c1 = 0;
	if (input->curpos == -2) //return de peek_char
		input->curpos = -1;
	else
		c1 = input->buffer[input->curpos];
	if (++input->curpos >= input->bufsize)
	{
		input->curpos = input->bufsize;
		return(-1); //EOF < 0, pues -1
	}
	return (input->buffer[input->bufsize]);
	
}

void    ft_unget_char(t_input *input)
{
	if (input->curpos < 0)
	return ;
	input->curpos--;	
}

char    ft_peek_char(t_input *input)
{
	int	pos;

	if (!input || !input->buffer)
	{
		errno = ENODATA;
		return ('\0');
	}
	pos = input->curpos;
	if (pos == -2)
		pos++;
	pos++;
	if (pos >= input->bufsize)
		return (-1); //EOF
	return (input->buffer[pos]);
}

void    ft_skip_white_spaces(t_input *input)
{
	char	c;

	if (!input || !input->buffer)
		return ;
	c = ft_peek_char(input);
	while (c != -1 && (c == ' ' || c == '\t'))
		ft_next_char(input);	
}


/*    ---- TOKENIZING INPUT -----    */

void	ft_add_to_buf(char c)
{
	char	*tok_buf;
	int		tok_bufsize;
	int		tok_bufindex;
	char	*temp;

	tok_buf = NULL;
	tok_bufindex = -1;
	tok_buf[tok_bufindex++] = c;
	if (tok_bufindex >= tok_bufsize)
	{
		temp = malloc(tok_bufsize * 2); //xq x2?
		if (!temp)
		{
			errno = ENOMEM;
			return ;
		}
	tok_buf = temp;
	tok_bufsize *= 2;
	}
	
}

t_token	*ft_create_token(char *input)
{
	t_token	*tok;
	char	*nstr;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	ft_memset(tok, 0, sizeof(t_token));
	tok->text_len = ft_strlen(input);
	nstr = malloc(tok->text_len + 1);
	if (!nstr)
	{
		free(tok);
		return (NULL);
	}
	ft_strlcpy(nstr, input, tok->text_len + 1); //+1?
	tok->text = nstr;
	return (tok);
}

void free_token(t_token *tok)
{
    if(tok->text)
    {
        free(tok->text);
    }
    free(tok);
}

t_token *ft_tokenize(t_input *input)
{

}

void    ft_free_token(t_token *token)
{

}
