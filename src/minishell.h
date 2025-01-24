/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 15:24:21 by jvoisard         ###   ########.fr       */
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
# include "utils/string_array.h"
# include "macros.h"

typedef union u_pipe
{
	int	in_out[2];
	struct
	{
		int	in;
		int	out;
	};
}	t_pipe;

typedef struct s_lexer	t_lexer;
typedef struct s_parser	t_parser;
typedef struct s_exec	t_exec;
typedef struct s_sh		t_sh;

// INPUT =======================================================================

void	input_read(t_sh *shell);

// LEXER =======================================================================

//////////////////////////////////
//	==> look in MACROS_H <==	//
//////////////////////////////////

/*
typedef enum e_lexer_state
{
	L_NO_STATE,
	L_INIT,
	L_DEFAULT,
	L_QUOTE,
	L_DQUOTE,
	L_VAR,
	L_VAR_DQUOTE,
	L_IGNORE,
	L_PAR_OPEN,		//	TODO
	L_PAR_CLOSED,	//	TODO
	L_PROCESS_GATE,	//	TODO
	L_AND_GATE,		//	TODO
	L_OR_GATE,		//	TODO
	L_PIPE,			//	TODO
	L_FLAG,			//	TODO
	L_LEFT_DIR,		//	TODO
	L_RIGHT_DIR,	//	TODO
	L_LEFT_REDIR,	//	TODO
	L_RIGHT_REDIR	//	TODO
}	t_lexer_state;
*/

typedef struct s_token
{
	t_string 	value;
	int 		type;
}	t_token;

struct s_lexer
{
	int					next_state;
	t_list				*state;
	char				*cursor;
	t_token				token;
	t_string			varname;
	t_list				*tokens;
};

typedef void			(*t_lexer_state_handler)(t_sh *);
typedef void			(*t_lexer_transition_handler)(t_sh *);

int		lex(t_sh *shell);
void	lex_free(t_sh *shell);
void 	string_push_and_go(t_sh *shell, t_token *token);
void 	add_to_list(t_sh *shell, t_token *token, int c);
void 	tokenise_parenthesis(t_sh *shell);
void 	tokenise_quotes(t_sh *shell);
void 	tokenise_gates(t_sh *shell);
void 	tokenise_variable(t_sh *shell);
void	tokenise_redirection(t_sh *shell);

// PARSER ====================================================================

typedef struct s_redir
{
	char 	*file;
}	t_redir;

typedef struct s_cmd
{
	t_list		*args;
	t_pipe		pipe;
	t_list 		*c2ex;
	int 	 	op;
	t_redir 	*redir;
}	t_cmd;

typedef struct s_pars
{
	t_cmd 	*cmd;
}	t_pars;

void	parse(t_sh *shell);
void	parse_free(t_sh *shell);

void 	check_priority(t_sh *shell);
void 	check_arguments(t_sh *shell);
void 	check_pipes(t_sh *shell);

// EXEC ========================================================================

struct s_exec
{
	t_cmd	cmd;
};

int		executor(t_sh *shell);

// SHELL =======================================================================

struct s_sh
{
	char		*name;
	char		*line;
	char		**env;
	t_pipe		pipe;
	bool		is_running;
	bool		is_interactive;
	t_lexer		lexer;
	t_pars		parser;
	t_exec		exec;
};

void	shell_init(t_sh *shell, char **env);
void	shell_exec(t_sh *shell);
void	shell_exit(t_sh *shell);

// BUILTINS ====================================================================

typedef int				(*t_bfunc)(t_sh *);
typedef struct s_builtin
{
	char	*name;
	t_bfunc	function;
}	t_builtin;

t_bfunc	get_builtin(t_cmd *cmd);
int		builtin_echo(t_sh *shell);
int		builtin_cd(t_sh *shell);
int		builtin_pwd(t_sh *shell);
int		builtin_export(t_sh *shell);
int		builtin_unset(t_sh *shell);
int		builtin_env(t_sh *shell);
int		builtin_exit(t_sh *shell);

// DIVERS 8===================================================================D

int 	ft_isalphanum(int c);

#endif
