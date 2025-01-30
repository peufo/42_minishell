/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 12:20:30 by jvoisard         ###   ########.fr       */
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
typedef struct s_exec	t_exec;
typedef struct s_sh		t_sh;

// INPUT =======================================================================

void	input_read(t_sh *shell);

// LEXER =======================================================================

typedef struct s_token
{
	t_string	value;
	int			type;
}	t_token;

struct s_lexer
{
	int				state;
	int				index;
	char			*cursor;
	t_token			token;
	char			*varname;
	t_list			*tokens;
	t_list			*starters;
	size_t			len;
};

typedef void			(*t_lexer_state_handler)(t_sh *);
typedef void			(*t_lexer_transition_handler)(t_sh *);

void	lex(t_sh *shell);
void	lex_free(t_sh *shell);
int		check_string(char *input);
pid_t	get_the_pid(char *process);
int		check_double(t_lexer *lexer, char c);
void	lexer_add_token(t_lexer *lexer, int type, char *value);
void	lexer_skip_whitespace(t_lexer *lexer);
void	lexer_skip_comment(t_lexer *lexer);
void	lexer_process_word(t_lexer *lexer);
void	lexer_process_variable(t_lexer *lexer);
void	lexer_process_double_quote(t_lexer *lexer);
void	lexer_process_single_quote(t_lexer *lexer);
void	lexer_process_status(t_lexer *lexer, char *start);

// PARSER ====================================================================

typedef enum s_define_a
{
	D_PIPELINE,
	D_SUFFIX,
	D_REDIRECTS,
	D_DGREAT,
	D_DLESS,
	D_GREAT,
	D_LESS,
	D_COMMAND,
	D_WORD,
	D_LOGICAL_EXP,
	D_OR,
	D_AND,
	D_SUBSHELL,
	D_FILE,
	D_UNKNOWN
}	t_define_a;

typedef int				(*t_argdef)(t_sh *);
typedef struct s_define_arg
{
	char		*name;
	t_argdef	function;
}	t_define_arg;

typedef struct s_branch
{
	int		type;
	char	*text;
}	t_branch;

typedef struct s_context
{
	t_branch	left;
	t_branch	right;
}	t_context;

typedef struct s_element
{
	t_context	context;
	t_branch	data;
}	t_element;

typedef struct s_cmd
{
	t_element	element;
	t_list		*elements;
	t_list		*args;
}	t_cmd;

typedef struct s_parser
{
	t_cmd	cmd;
}	t_parser;

void	parse(t_sh *shell);
void	parse_free(t_sh *shell);
void	check_priority(t_sh *shell);
void	check_arguments(t_sh *shell);
void	print_tokens(t_list *tokens);
void	look_for_special_commands(t_sh *shell); /*a deplacer in fine dans 
													une section builtin speciale 
													(exemple : exitshell)*/

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
	t_parser	ast;
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

int		ft_isspace(char c);
int		ft_isalphanum(int c);
char	*ft_strndup(const char *str, size_t n);
void	message(int error, int function);
void	track_origin(int func);
void	init_tracking(char **a, char **b, char **c);
void	track_argument_type(int element);
void	get_macro(char *s);
void	get_fpath(char *buf, size_t len);

#endif
