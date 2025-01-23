/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 15:07:39 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static t_lexer_state	get_next_state(t_sh *shell)
{
	static t_lexer_state	next_stats[][256] = {
	[LEXER_DEFAULT]['"'] = LEXER_DQUOTE,
	[LEXER_DEFAULT]['\''] = LEXER_QUOTE,
	[LEXER_DEFAULT]['$'] = LEXER_VAR,
	[LEXER_DEFAULT][' '] = LEXER_DEFAULT,
	[LEXER_DEFAULT]['\t'] = LEXER_DEFAULT,
	[LEXER_DEFAULT]['\n'] = LEXER_DEFAULT,
	[LEXER_QUOTE]['\''] = LEXER_DEFAULT,
	[LEXER_DQUOTE]['"'] = LEXER_DEFAULT,
	[LEXER_DQUOTE]['$'] = LEXER_VAR_DQUOTE,
	[LEXER_VAR_DQUOTE]['"'] = LEXER_DEFAULT,
	[LEXER_VAR_DQUOTE][' '] = LEXER_DQUOTE,
	[LEXER_VAR_DQUOTE]['\t'] = LEXER_DQUOTE,
	[LEXER_VAR]['"'] = LEXER_DQUOTE,
	[LEXER_VAR]['\''] = LEXER_QUOTE,
	[LEXER_VAR][' '] = LEXER_DEFAULT,
	[LEXER_VAR]['\t'] = LEXER_DEFAULT,
	[LEXER_VAR]['\n'] = LEXER_DEFAULT,
	[LEXER_VAR]['#'] = LEXER_IGNORE
	};

	return (next_stats[shell->lexer.state][(int)*(shell->lexer.cursor)]);
}

static void	handle_state_quote(t_sh *shell)
{
	string_push(&shell->lexer.token, *shell->lexer.cursor);
	shell->lexer.cursor++;
}

void	lexer_state(t_sh *shell)
{
	t_lexer_state_handler			handler;
	static t_lexer_state_handler	handlers[] = {
	[L_QUOTE] = handle_state_quote,
	[L_VAR] = lexer_state_var,
	[L_VAR_DQUOTE] = lexer_state_var_dquote,
	};

	handler = handlers[shell->lexer.state];
	if (handler)
		handler(shell);
}

void	lexer_state_var(t_sh *shell)
{
	string_push(&shell->lexer.token, *shell->lexer.cursor);
	shell->lexer.cursor++;
}*/
/*
void	lex(t_sh *shell)
{
	t_lexer_state	next_state;

	lex_free(shell);
	shell->lexer.state = L_INIT;
	shell->lexer.cursor = shell->line;
	lexer_transition(shell, L_DEFAULT);
	while (*(shell->lexer.cursor))
	{
		if (!get_next_state1(shell))
			get_next_state2(shell);
		if (next_state)
			lexer_transition(shell, next_state);
		else
			lexer_state(shell);
	}
	lexer_transition(shell, L_DEFAULT);
}*/

int 	lex(t_sh *shell)
{
	lex_free(shell);
	shell->lexer.state = L_INIT;
	shell->lexer.cursor = shell->line;
	lex_transition(shell, L_DEFAULT);
	while (*(shell->lexer.cursor))
	{
		if (get_next_state1(shell) == -1)
			return (0);
		if (shell->lexer.next_state != BULLSHIT)
			lexer_transition(shell);
		else
			lexer_state(shell);
	}
	lexer_transition(shell);
	return (1);
}

void	lex_free(t_sh *shell)
{
	string_free(&shell->lexer.token);
	string_free(&shell->lexer.varname);
	ft_lstclear(&shell->lexer.tokens, free);
}
