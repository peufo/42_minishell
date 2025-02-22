/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/22 23:15:48 by jvoisard         ###   ########.fr       */
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
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <errno.h>
# include "libft.h"
# include "input/get_next_line.h"
# include "utils/string.h"
# include "utils/string_array.h"

typedef union u_pipe
{
	int	fildes[2];
	struct
	{
		int	out;
		int	in;
	};
}	t_pipe;

typedef struct s_child
{
	pid_t	pid;
	int		status;
}	t_child;

typedef struct s_utils
{
	int	i;
	int	j;
	int	k;
	int	x;
}	t_utils;

typedef struct s_lexer		t_lexer;
typedef struct s_ast		t_ast;
typedef struct s_sh			t_sh;

// INPUT =======================================================================

void	input_read(t_sh *shell);

// LEXER =======================================================================

# define CHARSET_META "|&;()<> \t\n"
# define CHARSET_META_VISIBLE "|&;()<>"
# define BASIC_MOD 0
# define BONUS_MOD 1

typedef enum e_lexer_state
{
	LEXER_NO_STATE,
	LEXER_DEFAULT,
	LEXER_META,
	LEXER_QUOTE,
	LEXER_DQUOTE,
	LEXER_VAR,
	LEXER_VAR_DQUOTE,
}	t_lexer_state;

struct s_lexer
{
	t_lexer_state		state;
	char				*cursor;
	t_string			token;
	t_string			varname;
	char				**tokens;
};

typedef struct e_lexer_next_state
{
	t_lexer_state	state;
	char			*charset;
	t_lexer_state	next_state;
}	t_lexer_next_state;

typedef void				(*t_lexer_state_handler)(t_sh *);
typedef void				(*t_lexer_action_handler)(t_sh *);

//	MAIN LEXER
void	lex(t_sh *shell);
void	lex_free(t_sh *shell);
void	lexer_state(t_sh *shell);
void	lexer_action(t_sh *shell, t_lexer_state next_state);
void	lexer_action_end_token(t_sh *shell);
void	lexer_action_expand_var(t_sh *shell);
void	lexer_action_expand_var_end_token(t_sh *shell);
void	lexer_action_skip_blank(t_sh *shell);

//	EOF LEXER
bool	check_token(t_sh *shell);
bool	lex_check_eof(t_sh *shell);
bool	lex_check_var(t_sh *shell, char *line, char **buffer);
bool	lex_check_quotes(t_sh *shell, char *line, char **buffer);

// PARSER ====================================================================

typedef enum e_atype
{
	AST_SCRIPT,
	AST_COMMAND,
	AST_PIPELINE,
	AST_LOGICAL,
	AST_REDIRECT,
	AST_SUBSHELL,
	AST_END,
}	t_atype;

typedef enum e_aop
{
	AST_OP_NULL,
	AST_OP_AND,
	AST_OP_OR,
	AST_OP_GREAT,
	AST_OP_DGREAT,
	AST_OP_LESS,
	AST_OP_DLESS,
}	t_aop;

typedef struct s_ttype
{
	char		*tok;
	t_atype		op;
}	t_ttype;

typedef struct s_otype
{
	char	*tok;
	t_aop	op;
}	t_otype;

struct s_ast
{
	t_sh			*shell;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**args;
	pid_t			pid;
	int				status;
	t_atype			type;
	t_aop			op;
	t_pipe			*pipe_in;
	t_pipe			*pipe_out;
};

void	parse(t_sh *shell);
void	parse_free(t_sh *shell);

/////////// UTILS /////////////

char	**parse_collector(char **toks);
t_ast	*parse_init_ast(t_sh *shell);
char	**parse_word_content(t_sh *shell, char *element);

/////////// CHECKERS /////////////

int		check_for_simple_pars(t_sh *shell, char **toks);

/////////// HANDLERS /////////////

t_ast	*parse_handle_script(char **toks, t_sh *shell);

/////////// GETERS /////////////

t_atype	parse_get_type(char *tok);
t_aop	parse_get_op(char *tok);
int		parse_get_nbops(char **toks, int len);
t_list	*parse_get_typelist(char **toks, int mod, t_sh *shell);

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
	t_ast		*ast;
	int			debug_fd;
};

void	shell_init(t_sh *shell, char **env);
void	shell_exec(t_sh *shell);
void	shell_exit(t_sh *shell);

// BUILTINS ====================================================================

typedef int					(*t_exe)(t_ast *);
typedef struct s_builtin
{
	char	*name;
	t_exe	exe;
}	t_builtin;

t_exe	get_builtin(char *cmd);
int		builtin_echo(t_ast *node);
int		builtin_cd(t_ast *node);
int		builtin_pwd(t_ast *node);
int		builtin_export(t_ast *node);
int		builtin_unset(t_ast *node);
int		builtin_env(t_ast *node);
int		builtin_exit(t_ast *node);

void	env_set(t_sh *shell, char *key, char *value);
char	*env_get(t_sh *shell, char *varname);
void	env_unset(t_sh *shell, char *varname);

// EXEC ========================================================================

int		exec_bin(t_ast *node);
int		exec_ast(t_ast *node);
int		exec_command(t_ast *node);
void	exec_child(t_ast *node, t_exe exe);
void	exec_handle_pipeline(t_ast *node);
void	exec_handle_redirection(t_ast *node);
void	exec_handle_logical(t_ast *node);

// UTILS =======================================================================
void	debug(t_sh *shell, char *str);
void	debug_arr(t_sh *shell, char **arr);
void	throw_error(char *error, char *file, int line);
bool	ft_include(char *str, char c);
bool	ft_startwith(char *str, char *start);
int		ft_isop(char *str);
int		ft_isspace(int c);

// DEBUG =======================================================================
void	debug_input(t_sh *shell);
void	debug_tokens(t_sh *shell);
void	debug_ast(t_sh *shell);
void	debug_new_tokens(t_sh *shell, char **toks);
void	debug_two_lists(t_sh *shell, t_list *l1, t_list *l2);

#endif
