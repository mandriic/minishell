/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:56:36 by josgarci          #+#    #+#             */
/*   Updated: 2022/06/16 20:26:10 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

char	*leelinea(void);

typedef struct s_pipe
{
	struct s_command	*command;
	struct s_pipe		*pipe;
}	t_pipe;

typedef struct s_command
{
	char	*type;
	char	*flags;
	char	*arguments;
	char	*redirections;
}	t_command;

#endif
