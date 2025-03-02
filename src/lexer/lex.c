/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/02 13:30:01 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_line(t_ast *node)
{
	while (*(node->lexer.cursor) != '\0')
		node->lexer.cursor++;
}

static bool	next_state_match(t_ast *node, t_lexer_next_state *next)
{
	if (next->state != node->lexer.state)
		return (false);
	if (!ft_include(next->charset, *node->lexer.cursor))
		return (false);
	return (true);
}

static t_lexer_state	get_next_state(t_ast *node)
{
	t_lexer_next_state			*next;
	static t_lexer_next_state	next_states[] = {
	{LEXER_DEFAULT, "\"", LEXER_DQUOTE},
	{LEXER_DEFAULT, "'", LEXER_QUOTE},
	{LEXER_DEFAULT, "$", LEXER_VAR},
	{LEXER_DEFAULT, CHARSET_META, LEXER_META},
	{LEXER_QUOTE, "'", LEXER_DEFAULT},
	{LEXER_DQUOTE, "\"", LEXER_DEFAULT},
	{LEXER_DQUOTE, "$", LEXER_VAR_DQUOTE},
	{LEXER_VAR, "\"", LEXER_DQUOTE},
	{LEXER_VAR, "'", LEXER_QUOTE},
	{LEXER_VAR, CHARSET_META, LEXER_META},
	{LEXER_VAR_DQUOTE, "\"", LEXER_DEFAULT},
	{LEXER_VAR_DQUOTE, CHARSET_META, LEXER_DQUOTE},
	{0, NULL, 0}
	};

	next = next_states;
	while (next->state)
	{
		if (next_state_match(node, next))
			return (next->next_state);
		next++;
	}
	return (LEXER_NO_STATE);
}

void	lex(t_ast *node)
{
	t_lexer_state	next_state;

	node->lexer.state = LEXER_DEFAULT;
	node->lexer.cursor = node->line;
	if (!ft_strlen(node->lexer.cursor))
		shell_exit(node->shell);
	lexer_action_skip_blank(node);
	while (*(node->lexer.cursor))
	{
		next_state = get_next_state(node);
		if (*(node->lexer.cursor) == '#' && next_state <= LEXER_DEFAULT)
			skip_line(node);
		if (node->lexer.state == LEXER_DQUOTE 
			|| node->lexer.state == LEXER_QUOTE
			|| node->lexer.state == LEXER_VAR_DQUOTE)
			node->lexer.entry_state = node->lexer.state;
		if (next_state)
			lexer_action(node, next_state);
		else
			lexer_state(node);
	}
	lexer_action(node, LEXER_META);
	node->tokens = string_array_dup(node->lexer.tokens);
}

void	lex_free(t_lexer *lexer)
{
	string_free(&lexer->token);
	string_free(&lexer->varname);
	string_array_free(&lexer->tokens);
}
