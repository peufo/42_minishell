/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 17:31:49 by jvoisard         ###   ########.fr       */
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
# include "constants.h"

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
typedef struct s_ast	t_ast;
typedef struct s_sh		t_sh;

// INPUT =======================================================================

void	input_read(t_sh *shell);

// LEXER =======================================================================

typedef struct s_token
{
	char		*value;
	char		*type;
}	t_token;

struct s_lexer
{
	int				state;
	int				index;
	char			*cursor;
	char			*varname;
	char			**toks;
	int				nbt;
	size_t			len;
};

typedef void			(*t_lexer_state_handler)(t_sh *);
typedef void			(*t_lexer_transition_handler)(t_sh *);

void	lex(t_sh *shell);
void	lex_free(t_sh *shell);
int		check_string(char *input);
pid_t	get_the_pid(char *process);
int		check_double(t_sh *shell, char c);
void	lexer_add_token(char *type, char *value, t_sh *shell);
void	lexer_skip_whitespace(t_sh *shell);
void	lexer_skip_comment(t_sh *shell);
void	lexer_process_word(t_sh *shell);
void	lexer_process_variable(t_sh *shell);
void	lexer_process_double_quote(t_sh *shell);
void	lexer_process_single_quote(t_sh *shell);
void	lexer_process_status(char *start, t_sh *shell);

// PARSER ====================================================================

typedef enum e_ast_type
{
	AST_SCRIPT,
	AST_COMMAND,
	AST_PIPELINE,
	AST_LOGICAL,
	AST_REDIRECT,
}	t_ast_type;

typedef enum e_ast_op
{
	AST_OP_AND,
	AST_OP_OR,
	AST_OP_GREAT,
	AST_OP_DGREAT,
	AST_OP_LESS,
	AST_OP_DLESS,
	AST_OP_NULL
}	t_ast_op;

struct s_ast
{
	t_lexer			data;
	t_list			*args;
	struct s_ast	*left;
	struct s_ast	*right;
	t_ast_type		type;
	t_ast_op		op;
	int				cursor;
	int				priority;
};

void	parse(t_sh *shell);
void	parse_free(t_sh *shell);
void	look_for_special_commands(t_sh *shell); /*a deplacer in fine dans 
													une section builtin speciale 
													(exemple : exitshell)*/
int		pars_find_next_operator(t_ast *ast, t_sh *shell);
void	pars_context_type(t_ast *ast, t_sh *shell);
void	pars_parse_command(t_ast *ast, t_sh *shell);

int		pars_get_type(int type, t_sh *shell);
int		pars_get_op(char *type, t_sh *shell);
int		pars_get_dir(int type, t_sh *shell);
int		pars_get_position(t_ast *ast, t_list *elements, t_sh *shell);
void	pars_split_lr(t_ast *ast, t_ast *left, t_ast *right, t_sh *shell);

// EXEC ========================================================================

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
	t_lexer		lex;
	t_ast		ast;
	int			debug_fd;
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

t_bfunc	get_builtin(char *cmd);
int		builtin_echo(t_sh *shell);
int		builtin_cd(t_sh *shell);
int		builtin_pwd(t_sh *shell);
int		builtin_export(t_sh *shell);
int		builtin_unset(t_sh *shell);
int		builtin_env(t_sh *shell);
int		builtin_exit(t_sh *shell);

// UTILS  =====================================================================
void	debug(t_sh *shell, char *str);
void	debug_arr(t_sh *shell, char **arr);
void	throw_error(char *error, char *file, int line);
void	debug_tokenisation(t_sh *shell, char *type, char *value);

// LIB PLUS ====================================================================

int		ft_isspace(char c);
char	*ft_cut(char *from, char *to);
void	*ft_lstget_front(t_list *node);
void	ft_lstremove_front(t_list *lst);

#endif
