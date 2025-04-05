/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:49:27 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/05 15:06:17 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	push_char_token(t_lexer *lexer)
{
	char	*end_token;

	end_token = string_push_char(&lexer->token, *lexer->cursor);
	if (!end_token)
		shell_exit(lexer->node->shell);
	if (lexer->state == LEXER_DEFAULT && *lexer->cursor == '*')
	{
		string_array_push(&lexer->wilds, end_token - 1);
	}
	lexer->cursor++;
}

static void	push_char_varname(t_lexer *lexer)
{
	string_push_char(&lexer->varname, *lexer->cursor);
	lexer->cursor++;
}

static void	reset_default(t_lexer *lexer)
{
	lexer->state = LEXER_DEFAULT;
}

static void	handle_meta(t_lexer *lexer)
{
	while (ft_include(CHARSET_META, *lexer->cursor))
		push_char_token(lexer);
	reset_default(lexer);
}

void	lexer_state(t_lexer *lexer)
{
	t_lexer_handler			handler;
	static t_lexer_handler	handlers[] = {
	[LEXER_DEFAULT] = push_char_token,
	[LEXER_META] = handle_meta,
	[LEXER_QUOTE] = push_char_token,
	[LEXER_DQUOTE] = push_char_token,
	[LEXER_VAR] = push_char_varname,
	[LEXER_VAR_DQUOTE] = push_char_varname,
	[LEXER_END_TOKEN] = reset_default
	};

	handler = handlers[lexer->state];
	if (handler)
		handler(lexer);
}
