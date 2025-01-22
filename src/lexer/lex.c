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
	[LEXER_VAR]['\n'] = LEXER_DEFAULT
	};

	return (next_stats[shell->lexer.state][(int)*(shell->lexer.cursor)]);
}

void	lex(t_sh *shell)
{
	t_lexer_state	next_state;

	lex_free(shell);
	shell->lexer.state = LEXER_INIT;
	shell->lexer.cursor = shell->line;
	lexer_transition(shell, LEXER_DEFAULT);
	while (*(shell->lexer.cursor))
	{
		next_state = get_next_state(shell);
		if (next_state)
			lexer_transition(shell, next_state);
		else
			lexer_state(shell);
	}
	lexer_transition(shell, LEXER_DEFAULT);
}

void	lex_free(t_sh *shell)
{
	string_free(&shell->lexer.token);
	string_free(&shell->lexer.varname);
	ft_lstclear(&shell->lexer.tokens, free);
}
