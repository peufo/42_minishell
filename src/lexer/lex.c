/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/20 13:18:50 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO use reverse_match.
static t_lexer_state	find_next_state_match(
	t_ast *node,
	t_lexer_next_state *next_states)
{
	t_lexer_next_state	*n;
	t_lexer				*lexer;

	n = next_states;
	lexer = &node->lexer;
	while (n->state)
	{
		if (n->state == lexer->state)
		{
			if (!n->charset)
				return (n->next_state);
			if (ft_include(n->charset, *lexer->cursor))
				return (n->next_state);
		}
		n++;
	}
	return (LEXER_NO_STATE);
}

static t_lexer_state	get_next_state(t_ast *node)
{
	static t_lexer_next_state	next_states[] = {
	{LEXER_DEFAULT, "\"", LEXER_DQUOTE},
	{LEXER_DEFAULT, "'", LEXER_QUOTE},
	{LEXER_DEFAULT, "$", LEXER_VAR},
	{LEXER_DEFAULT, CHARSET_META, LEXER_META},
	{LEXER_DEFAULT, CHARSET_SPACE, LEXER_END_TOKEN},
	{LEXER_QUOTE, "'", LEXER_DEFAULT},
	{LEXER_DQUOTE, "\"", LEXER_DEFAULT},
	{LEXER_DQUOTE, "$", LEXER_VAR_DQUOTE},
	{LEXER_VAR, "\"", LEXER_DQUOTE},
	{LEXER_VAR, "'", LEXER_QUOTE},
	{LEXER_VAR, CHARSET_META, LEXER_META},
	{LEXER_VAR, CHARSET_SPACE, LEXER_END_TOKEN},
	{LEXER_VAR, CHARSET_VAR_END, LEXER_DEFAULT},
	{LEXER_VAR_DQUOTE, "\"", LEXER_DEFAULT},
	{LEXER_VAR_DQUOTE, "'", LEXER_DQUOTE},
	{LEXER_VAR_DQUOTE, CHARSET_META_SPACE, LEXER_DQUOTE},
	{LEXER_VAR_DQUOTE, CHARSET_VAR_END, LEXER_DQUOTE},
	{LEXER_END_TOKEN, NULL, LEXER_DEFAULT},
	{0, NULL, 0}
	};

	return (find_next_state_match(node, next_states));
}

void	lex(t_ast *node, char *line)
{
	t_lexer_state	next_state;

	node->lexer.state = LEXER_DEFAULT;
	node->lexer.cursor = line;
	lexer_action_skip_blank(node);
	while (*(node->lexer.cursor))
	{
		next_state = get_next_state(node);
		if (node->lexer.state == LEXER_DQUOTE
			|| node->lexer.state == LEXER_QUOTE
			|| node->lexer.state == LEXER_VAR_DQUOTE)
			node->lexer.entry_state = node->lexer.state;
		if (next_state)
			lexer_action(node, next_state);
		else
			lexer_state(node);
	}
	lexer_action(node, LEXER_END_TOKEN);
	node->tokens = string_array_dup(node->lexer.tokens);
}

void	lex_free(t_lexer *lexer)
{
	string_free(&lexer->token);
	string_free(&lexer->varname);
	string_array_free(&lexer->tokens);
}
