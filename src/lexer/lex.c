/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 14:12:55 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer_state	get_next_state(t_lexer *lexer)
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

	return (next_stats[lexer->state][(int)*(lexer->line)]);
}

static void	input_line_to_tokens(t_lexer *lexer)
{
	t_lexer_state	next_state;

	while (*(lexer->line))
	{
		next_state = get_next_state(lexer);
		if (next_state)
			lexer_transition(lexer, next_state);
		else
			lexer_state(lexer);
	}
	lexer_transition(lexer, LEXER_DEFAULT);
}

void	lex(t_sh *shell)
{
	t_lexer	lexer;

	ft_memset(&lexer, 0, sizeof(lexer));
	lexer.line = shell->line;
	lexer.state = LEXER_INIT;
	lexer_transition(&lexer, LEXER_DEFAULT);
	input_line_to_tokens(&lexer);
	string_free(&lexer.token);
	string_free(&lexer.varname);
	shell->cmd = command_from(lexer.tokens);
}
