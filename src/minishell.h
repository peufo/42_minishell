/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/03 09:27:21 by dyodlm           ###   ########.fr       */
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
# include "global.h"

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
# define INPUT_PIPE 1
# define INPUT_OR 2
# define INPUT_AND 3
# define LINE_IS_COMPLETE 1
# define INPUT_QUOTE 2
# define INPUT_DQUOTE 3
# define INPUT_PARENTHESES 4
# define INPUT_EOF 5
# define INPUT_REDIR 6

# define PROMPT_RED "31"
# define PROMPT_GREEN "32"
# define PROMPT_YELLOW "33"
# define PROMPT_BLUE "36"
# define PROMPT_PURPLE "35"

//	ERROR HANDLING

typedef enum s_errors
{
	SENT_PIPE,
	SENT_LOGICAL,
	SENT_LESS,
	SENT_GREAT,
	SENT_OTHER
}	t_errors;

typedef bool				(*t_sent)(char *, bool);

bool	did_eye_of_sawron(t_sh *shell, bool in_eof);
void	init_error_checker(char **cursor, char **head, t_sh *shell);
bool	did_pipe_sentinel_see(char *line, bool in_eof);
bool	did_less_sentinel_see(char *line, bool in_eof);
bool	did_great_sentinel_see(char *line, bool in_eof);
bool	did_logical_sentinel_see(char *line, bool in_eof);
bool	did_other_sentinel_see(char *line, bool in_eof);
void	error_display(t_sh *shell, char *error);
bool	is_token_valid(char *line, char *token, bool in_eof);
bool	is_eof_token(char *token, bool in_eof);

//	INPUT LOGIC BLOC + HEREDOCS

typedef struct s_input
{
	char	*line;
	char	*stack;
	bool	is_redir;
	char	**redir_input;
	char	*redir_line;
	char	**redir_code;
	int		nb_redir;
	int		state;
	int		last;
}	t_input;

typedef struct s_operator
{
	char	*op;
	int		type;
}	t_operator;

typedef struct s_wild
{
	char		*token;
	char		**sections;
	bool		is_wild_start;
	bool		is_wild_end;
	char		**files;
}	t_wild;

//	SIGNAL
void	handle_signal(int sig);

//	INPUT
int		input_read(t_sh *shell);
int		check_string(char *input);
void	stack_to_history(char *line, t_sh *shell);
int		throw_shell(t_sh *shell, char **error);
bool	apply_redir(t_sh *shell, char *copy);
bool	apply_redir_logic(t_input *input, t_sh *shell);
void	assure_heredoc_line(t_sh *shell);
void	assure_eof_line(t_sh *shell);

//	EOF LEXER
bool	lex_eof(t_sh *shell);
void	input_free(t_input *input);

//	UTILS
int		get_stack_state(t_input *input);
int		get_last_token_type(char *line, t_input *input);
void	stack_to_buffer(char **buffer, char *line);
void	transfer_shell_line(t_sh *shell);
void	safe_init_redir_array(t_sh *shell, t_input *input);
bool	check_redir(char *cursor);
void	check_quotes(char c, bool *dquote, bool *quote);
bool	is_empty_line(char *line);

//	HEREDOCS
bool	treat_redirections(t_input *input, t_sh *shell);
//char	*catch_the_redir_code(char *line);
void	get_safe_readline_inputs(t_sh *shell, t_input *input);
void	get_all_codes(t_input *input, char *cursor);
void	checkout_from_redir(t_sh *shell);
int		count_redir_in_line(t_sh *shell, char *line, bool dquote, bool quote);
void	find_vars_in_line(char **line, char ***vars);
void	expand_vars_in_line(t_sh *shell, char **line, char ***vars);
bool	check_heredoc_code(char *s1, char *s2);
void	simu_heredoc(char *problem, t_sh *shell);

// LEXER =======================================================================

# define CHARSET_META "|&;()<>"
# define CHARSET_SPACE " \t\n"
# define CHARSET_META_SPACE "|&;()<> \t\n"
# define CHARSET_VAR_END "?$=*/.!#%+,-:@[]\\^{}~"

typedef enum e_lexer_state
{
	LEXER_NO_STATE,
	LEXER_DEFAULT,
	LEXER_END_TOKEN,
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
	char				**wilds;
};

typedef struct e_lexer_next_state
{
	t_lexer_state	state;
	char			*charset;
	t_lexer_state	next_state;
}	t_lexer_next_state;

typedef void				(*t_lexer_state_handler)(t_ast *);
typedef void				(*t_lexer_action_handler)(t_ast *);

//	MAIN LEXER
void	lex(t_ast *node, char *line);
void	lex_free(t_lexer *lexer);
void	lexer_state(t_ast *node);
void	lexer_action(t_ast *node, t_lexer_state next_state);
void	lexer_action_end_token(t_ast *node);
void	lexer_action_expand_var(t_ast *node);
void	lexer_action_expand_var_dquote(t_ast *node);
void	lexer_action_expand_var_end_token(t_ast *node);
void	lexer_action_skip_blank(t_ast *node);
void	lexer_action_next_char(t_ast *node);
void	lexer_expand_exit_status(t_ast *node);
void	lexer_expand_wildcard(t_ast *node);
void	lexer_action_var_catch_wild(t_ast *node, int var_len);

// PARSER ====================================================================

typedef enum e_atype
{
	AST_NULL,
	AST_SUBSHELL,
	AST_AND,
	AST_OR,
	AST_PIPELINE,
	AST_COMMAND,
}	t_atype;

typedef enum e_ast_state
{
	AST_STATE_DEFAULT,
	AST_STATE_QUOTE,
	AST_STATE_DQUOTE
}	t_ast_state;

typedef struct s_ttype
{
	char		*tok;
	t_atype		op;
}	t_ttype;

typedef struct s_redir
{
	char	**files_in;
	char	**files_out;
	char	**files_out_append;
	int		fd_in;
	int		fd_out;
	int		fd_std_in;
	int		fd_std_out;
	int		is_last_append;
}	t_redir;

typedef int					(*t_exe)(t_ast *);
struct s_ast
{
	t_sh	*shell;
	t_ast	**children;
	char	*line;
	char	**tokens;
	t_lexer	lexer;
	pid_t	pid;
	bool	is_child_process;
	int		status;
	t_exe	builtin;
	t_atype	type;
	t_pipe	*pipe_in;
	t_pipe	*pipes;
	t_pipe	*pipe_out;
	t_redir	redir;
	t_redir	heredoc;
};

t_ast	*ast_create(t_sh *shell, char *line);
void	ast_parse_command(t_ast *node);
void	ast_free(t_ast **node);
void	ast_parse(t_ast *node);
int		ast_parse_pipe(t_ast *node);
void	ast_parse_heredoc(t_ast *node);
int		ast_parse_subshell(t_ast *node);
void	ast_parse_tilde(t_ast *node);
char	*ast_tokens_find(char *line, char *token);
char	*ast_tokens_find_last(char *line, char *token);
char	*ast_take_word(t_ast *node, char *cursor);

// SHELL =======================================================================

struct s_sh
{
	char		*name;
	char		*line;
	char		*line2;
	char		**env;
	t_string	prompt;
	t_pipe		pipe;
	t_lexer		lexer;
	t_input		input;
	bool		is_running;
	bool		is_interactive;
	t_ast		*ast;
	bool		ast_error;
	int			exit_status;
	int			signal;
	bool		shell_inception;
};

void	shell_init(t_sh *shell, char **env);
void	shell_exec(t_sh *shell);
void	shell_exit(t_sh *shell);
void	shell_free(t_sh *shell);
void	shell_update_prompt(t_sh *shell);

// BUILTINS ====================================================================

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
int		builtin_export_print(t_ast *node);
int		builtin_unset(t_ast *node);
int		builtin_env(t_ast *node);
int		builtin_exit(t_ast *node);

void	env_set(t_sh *shell, char *key, char *env_row);
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
t_exe	get_exe(t_ast *node);
void	exec_update_underscore(t_ast *node);
void	exec_redir_save_std(t_ast *node);
void	exec_redir_restore_std(t_ast *node);
bool	is_env_path_defined(t_ast	*node);
int		exec_bin_try(t_ast *node, char *path);

// UTILS =======================================================================
int		throw(t_ast *node, char **error);
int		waitstatus(pid_t pid);
bool	ft_include(char *str, char c);
int		ft_isop(char *str);
char	*ft_strchrstr(const char *str, char *to_find);
char	*ft_strrchrstr(const char *str, char *to_find);
char	*get_line(int fd);
void	ft_suppress(char *from, char *to, char **line);
void	custom_sprintf(char *buffer, const char *format, const char *str_arg,
			int int_arg);
void	ft_strcpy(char *s1, const char *s2);

#endif
