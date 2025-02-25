/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:21:54 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/04 18:05:03 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_action_next_char(t_ast *node)
{
	node->lexer.cursor++;
}

void	lexer_action_skip_blank(t_ast *node)
{
	char	**cursor;

	cursor = &node->lexer.cursor;
	while (**cursor == ' ' || **cursor == '\t' || **cursor == '\n')
		(*cursor)++;
}

void	lexer_action_end_token(t_ast *node)
{
	if (!node->lexer.token.value)
		return ;
	string_array_push(&node->lexer.tokens, node->lexer.token.value);
	node->lexer.token.value = NULL;
	lexer_action_skip_blank(node);
}

void	lexer_action_ensure_token(t_ast *node)
{
	string_push_str(&node->lexer.token, "");
	node->lexer.cursor++;
}

void	lexer_action(t_ast *node, t_lexer_state next_state)
{
	t_lexer_action_handler			handler;
	static t_lexer_action_handler	handlers[][8] = {
	[LEXER_VAR][LEXER_DQUOTE] = lexer_action_expand_var,
	[LEXER_VAR][LEXER_QUOTE] = lexer_action_expand_var,
	[LEXER_VAR_DQUOTE][LEXER_DQUOTE] = lexer_action_expand_var,
	[LEXER_VAR_DQUOTE][LEXER_DEFAULT] = lexer_action_expand_var,
	[LEXER_DEFAULT][LEXER_QUOTE] = lexer_action_ensure_token,
	[LEXER_DEFAULT][LEXER_DQUOTE] = lexer_action_ensure_token,
	[LEXER_DEFAULT][LEXER_META] = lexer_action_end_token,
	[LEXER_VAR][LEXER_META] = lexer_action_expand_var_end_token,
	};

	handler = handlers[node->lexer.state][next_state];
	if (!handler)
		handler = lexer_action_next_char;
	handler(node);
	node->lexer.state = next_state;
}
