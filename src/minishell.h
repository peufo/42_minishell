/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 14:12:55 by jvoisard         ###   ########.fr       */
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

typedef union u_pipe
{
	int	in_out[2];
	struct
	{
		int	in;
		int	out;
	};
}	t_pipe;

typedef struct s_cmd
{
	char	*executable;
	t_list	*args;
	t_pipe	pipe;
}	t_cmd;

typedef struct s_sh
{
	char	*name;
	char	*line;
	t_cmd	*cmd;
	char	**env;
	bool	is_running;
	bool	is_interactive;
	t_pipe	pipe;
}	t_sh;

void	shell_init(t_sh *shell, char **env);
void	shell_exec(t_sh *shell);
void	shell_exit(t_sh *shell);

// INPUT =======================================================================

void	input_read(t_sh *shell);

// LEXER =======================================================================

typedef enum e_lexer_state
{
	LEXER_NO_STATE,
	LEXER_INIT,
	LEXER_DEFAULT,
	LEXER_QUOTE,
	LEXER_DQUOTE,
	LEXER_VAR,
	LEXER_VAR_DQUOTE,
}	t_lexer_state;

typedef struct s_lexer
{
	t_lexer_state		state;
	char				*line;
	t_string			token;
	t_string			varname;
	t_list				*tokens;
	t_cmd				*cmd;
}	t_lexer;

typedef void	(*t_lexer_state_handler)(t_lexer *);
typedef void	(*t_lexer_transition_handler)(t_lexer *);

void	lex(t_sh *shell);
void	lexer_state(t_lexer *lexer);
void	lexer_state_var(t_lexer *lexer);
void	lexer_state_var_dquote(t_lexer *lexer);
void	lexer_transition(t_lexer *lexer, t_lexer_state next_state);

// EXEC ========================================================================

int		executor(t_sh *shell, t_cmd *cmd);
void	command_free(t_cmd **cmd);
t_cmd	*command_from(t_list *tokens);

// BUILTINS ====================================================================

typedef int		(*t_bfunc)(t_sh *, t_cmd *cmd);
typedef struct s_builtin
{
	char	*name;
	t_bfunc	function;
}	t_builtin;

t_bfunc	get_builtin(t_cmd *cmd);
int		builtin_echo(t_sh *shell, t_cmd *cmd);
int		builtin_cd(t_sh *shell, t_cmd *cmd);
int		builtin_pwd(t_sh *shell, t_cmd *cmd);
int		builtin_export(t_sh *shell, t_cmd *cmd);
int		builtin_unset(t_sh *shell, t_cmd *cmd);
int		builtin_env(t_sh *shell, t_cmd *cmd);
int		builtin_exit(t_sh *shell, t_cmd *cmd);

#endif
