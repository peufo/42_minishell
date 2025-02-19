/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:39 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/19 13:06:01 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_current_meta_state(t_sh *shell)
{
	int	type;

	if (shell->lexer.token.value)
		type = parse_get_type(shell->lexer.token.value);
	//	get additionnal info 
	return (type);
}

static void	bonus_exec(t_sh *shell)
{
	debug_input(shell);
	lex_eof(shell, 0);
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
	entry_state = get_current_meta_state(shell);
	if (entry_state != 0)
		lex_eof(shell, entry_state);
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
