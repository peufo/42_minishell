/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/17 14:10:43 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <errno.h>
# include "libft.h"
# include "input/get_next_line.h"
# include "utils/string.h"

typedef union u_pipe
{
	int	in_out[2];
	struct
	{
		int	in;
		int	out;
	};
}	t_pipe;

typedef struct s_sh
{
	char	*name;
	char	*line;
	t_list	*tokens;
	t_list	*commands;
	bool	is_running;
	bool	is_interactive;
	t_pipe	pipe;
}	t_sh;

typedef struct s_command
{
	char	*executable;
	t_list	*args;
	t_pipe	pipe;
}	t_command;

void	shell_init(t_sh *shell);
void	shell_exec(t_sh *shell);
void	shell_exit(t_sh *shell);
void	input_read(t_sh *shell);

// ================= INPUT_PARSE ========================

typedef enum e_parser_state
{
	PARSE_NO_STATE,
	PARSE_INIT,
	PARSE_DEFAULT,
	PARSE_QUOTE,
	PARSE_DQUOTE,
	PARSE_VAR,
	PARSE_VAR_DQUOTE,
}	t_parser_state;

typedef struct s_parser
{
	t_parser_state		state;
	char				*line;
	t_string			token;
	t_string			varname;
	t_list				*tokens;
	t_list				*commands;
}	t_parser;

typedef void	(*t_state_handler)(t_parser *);
typedef void	(*t_transition_handler)(t_parser *);

void	input_parse(t_sh *shell);
void	handle_state(t_parser *parser);
void	handle_state_var(t_parser *parser);
void	handle_state_var_dquote(t_parser *parser);
void	handle_transition(t_parser *parser, t_parser_state next_state);

// ================= EXECUTOR ========================

int		executor(t_command *cmd);

#endif