/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:49:27 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 14:12:55 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_state_default(t_lexer *lexer)
{
	string_push(&lexer->token, *lexer->line);
	lexer->line++;
}

static void	handle_state_dquote(t_lexer *lexer)
{
	string_push(&lexer->token, *lexer->line);
	lexer->line++;
}

static void	handle_state_quote(t_lexer *lexer)
{
	string_push(&lexer->token, *lexer->line);
	lexer->line++;
}

void	lexer_state(t_lexer *lexer)
{
	t_lexer_state_handler			handler;
	static t_lexer_state_handler	handlers[] = {
	[LEXER_DEFAULT] = handle_state_default,
	[LEXER_QUOTE] = handle_state_quote,
	[LEXER_DQUOTE] = handle_state_dquote,
	[LEXER_VAR] = lexer_state_var,
	[LEXER_VAR_DQUOTE] = lexer_state_var_dquote,
	};

	handler = handlers[lexer->state];
	if (handler)
		handler(lexer);
}
