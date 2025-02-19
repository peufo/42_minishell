/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:39 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/19 13:00:45 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	last_token_is_eof(t_sh *shell)
{
	int	i;

	i = 0;
	if (shell->lexer.tokens)
		while (shell->lexer.tokens[i++] != NULL)
			continue ;
	if (parse_get_type(shell->lexer.tokens[i - 1]) != AST_COMMAND)
		return (true);
	return (false);
}

static void	bonus_exec(t_sh *shell)
{
	debug_input(shell);
	lex_eof(shell);
	debug_tokens(shell);
	parse(shell);
	lex_free(shell);
	parse_free(shell);
}

static void	basic_exec(t_sh *shell)
{
	int	entry_state;

	debug_input(shell);
	lex(shell);
	debug_tokens(shell);
	entry_state = last_token_is_eof(shell);
	if (entry_state != 0)
		lex_eof(shell);
	parse(shell);
	executor(shell);
	lex_free(shell);
	parse_free(shell);
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
