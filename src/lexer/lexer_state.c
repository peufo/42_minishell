/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:49:27 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/25 17:56:03 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	push_char_token(t_ast *node)
{
	string_push_char(&node->lexer.token, *node->lexer.cursor);
	node->lexer.cursor++;
}

static void	push_char_varname(t_ast *node)
{
	string_push_char(&node->lexer.varname, *node->lexer.cursor);
	node->lexer.cursor++;
}

static void	handle_meta_chars(t_ast *node)
{
	lexer_action_skip_blank(node);
	if (ft_include(CHARSET_META_VISIBLE, *node->lexer.cursor))
	{
		push_char_token(node);
		if (ft_include("|&<>", *node->lexer.cursor))
			push_char_token(node);
		lexer_action_end_token(node);
	}
	node->lexer.state = LEXER_DEFAULT;
}

void	lexer_state(t_ast *node)
{
	t_lexer_state_handler			handler;
	static t_lexer_state_handler	handlers[] = {
	[LEXER_DEFAULT] = push_char_token,
	[LEXER_QUOTE] = push_char_token,
	[LEXER_DQUOTE] = push_char_token,
	[LEXER_VAR] = push_char_varname,
	[LEXER_VAR_DQUOTE] = push_char_varname,
	[LEXER_META] = handle_meta_chars
	};

	handler = handlers[node->lexer.state];
	if (handler)
		handler(node);
}
