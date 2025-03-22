/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:49:27 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/20 12:14:53 by jvoisard         ###   ########.fr       */
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

static void	reset_default(t_ast *node)
{
	node->lexer.state = LEXER_DEFAULT;
}

static void	handle_meta(t_ast *node)
{
	while (ft_include(CHARSET_META, *node->lexer.cursor))
		push_char_token(node);
	reset_default(node);
}

void	lexer_state(t_ast *node)
{
	t_lexer_state_handler			handler;
	static t_lexer_state_handler	handlers[] = {
	[LEXER_DEFAULT] = push_char_token,
	[LEXER_META] = handle_meta,
	[LEXER_QUOTE] = push_char_token,
	[LEXER_DQUOTE] = push_char_token,
	[LEXER_VAR] = push_char_varname,
	[LEXER_VAR_DQUOTE] = push_char_varname,
	[LEXER_END_TOKEN] = reset_default
	};

	handler = handlers[node->lexer.state];
	if (handler)
		handler(node);
}
