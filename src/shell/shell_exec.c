/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:39 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/24 15:43:26 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	shell_check_cursor(t_sh *shell)
{
	int	last_type;

	last_type = lex_eof_get_last_type(shell);
	if (last_type != AST_COMMAND && last_type != AST_NULL)
	{
		shell->lexer.entry_state = last_type;
		return (BONUS_MOD);
	}
	return (BASIC_MOD);
}

static void	bonus_exec(t_sh *shell)
{
	debug_input(shell);
	lex(shell);
	if (!shell->lexer.token.value && !shell->lexer.tokens)
		shell->lexer.entry_state = 1;
	lex_eof(shell, shell->lexer.entry_state);
	shell->ast = ast_create(
			shell,
			string_array_dup(shell->lexer.tokens)
			);
	ast_debug(shell->ast, 0);
	exec_ast(shell->ast);
	lex_free(shell);
	ast_free(&shell->ast);
}

static void	basic_exec(t_sh *shell)
{
	debug_input(shell);
	lex(shell);
	if (shell_check_cursor(shell))
		lex_eof(shell, shell->lexer.entry_state);
	shell->ast = ast_create(
			shell,
			string_array_dup(shell->lexer.tokens)
			);
	ast_debug(shell->ast, 0);
	exec_ast(shell->ast);
	lex_free(shell);
	ast_free(&shell->ast);
}

void	shell_exec(t_sh *shell)
{
	int	exec;

	shell->is_interactive = isatty(shell->pipe.in);
	errno = false;
	shell->is_running = true;
	debug(shell, "INIT SHELL AT : ");
	debug(shell, __TIME__);
	debug(shell, "\n\n");
	while (shell->is_running)
	{
		exec = input_read(shell);
		if (!shell->line)
			break ;
		if (exec == BASIC_MOD)
			basic_exec(shell);
		else
			bonus_exec(shell);
	}
	shell_exit(shell);
}
