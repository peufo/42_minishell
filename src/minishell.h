/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/24 15:17:24 by dyodlm           ###   ########.fr       */
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
# define BASIC_MOD 0
# define BONUS_MOD 1
# define CLOSED 1
# define UNCLOSED 0
# define LINE_IS_COMPLETE 1

bool	input_read(t_sh *shell);
int		check_string(char *input);

// LEXER =======================================================================

# define CHARSET_META "|&;()<> \t\n"
# define CHARSET_META_VISIBLE "|&;()<>"

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
	t_lexer_state		entry_state;
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
void	lexer_action_next_char(t_sh *shell);

//	EOF LEXER
void	lex_eof(t_sh *shell, int entry_state);
void	lex_eof_free(t_sh *shellm, t_lexer *lex);

//	UTILS
char	*ft_cut(char *from, char *to);
int		lex_eof_get_last_type(t_sh *shell);
void	sub_last_token(t_sh *shell, t_lexer *lexer);
void	lexer_eof_skip_whitespace(t_sh *shell, t_lexer *lexer);
void	lexer_eof_skip_comment(t_sh *shell, t_lexer *lexer);
bool	check_end_in_line(char *line, int state, int type);
void	stack_to_buffer(char **buffer, char *line);
void	stack_new_input(char **buffer, t_lexer *lex, char *line);
int		parse_get_type(char *tok);

//	PROCESSES
void	lex_eof_process_word(t_sh *shell, t_lexer *lexer);
void	lex_eof_process_parenthesis(t_sh *shell, t_lexer *lexer);
void	lex_eof_process_redirection(t_sh *shell, t_lexer *lexer);
void	lex_eof_process_gate_and_pipe(t_sh *shell, t_lexer *lexer);
void	lex_eof_process_quotes_and_var(t_sh *shell, t_lexer *lexer);
void	lex_eof_process_single_quote(t_sh *shell, t_lexer *lexer);
void	lex_eof_process_double_quote(t_sh *shell, t_lexer *lexer);
void	lex_eof_process_variable(t_sh *shell, t_lexer *lexer);

// PARSER ====================================================================

typedef enum e_atype
{
	AST_NULL,
	AST_SUBSHELL,
	AST_AND,
	AST_OR,
	AST_PIPELINE,
	AST_GREAT,
	AST_DGREAT,
	AST_LESS,
	AST_DLESS,
	AST_COMMAND,
}	t_atype;

typedef struct s_ttype
{
	char		*tok;
	t_atype		op;
}	t_ttype;

struct s_ast
{
	t_sh	*shell;
	t_ast	**children;
	char	**tokens;
	pid_t	pid;
	int		status;
	t_atype	type;
	t_pipe	*pipe_in;
	t_pipe	*pipe_out;
};

t_ast	*ast_create(t_sh *shell, char **tokens);
void	ast_free(t_ast **node);
void	ast_parse(t_ast *node);
int		ast_parse_pipe(t_ast *node);
int		ast_parse_subshell(t_ast *node);
char	**ast_tokens_find(char **tokens, char *token);
void	ast_debug(t_ast *node, int deep);

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

int		exec_ast(t_ast *node);
int		exec_bin(t_ast *node);
void	exec_child(t_ast *node, t_exe exe);
int		exec_command(t_ast *node);
int		exec_subshell(t_ast *node);
int		exec_pipeline(t_ast *node);
int		exec_and(t_ast *node);
int		exec_or(t_ast *node);
int		exec_great(t_ast *node);
int		exec_dgreat(t_ast *node);
int		exec_less(t_ast *node);
int		exec_dless(t_ast *node);
t_exe	get_exe(t_ast *node);

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
void	debug_ast(t_sh *shell);
void	debug_new_tokens(t_sh *shell, char **toks);
void	debug_two_lists(t_sh *shell, t_list *l1, t_list *l2);

#endif
