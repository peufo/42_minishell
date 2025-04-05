/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/05 15:15:33 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer_state	find_next_state_match(
	t_lexer	*lexer,
	t_lexer_next_state *next_states)
{
	t_lexer_next_state	*n;

	n = next_states;
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

static t_lexer_state	get_next_state(t_lexer *lexer)
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

	return (find_next_state_match(lexer, next_states));
}

static void	lexer_free(t_lexer *lexer)
{
	string_free(&lexer->token);
	string_free(&lexer->varname);
	if (lexer->wilds)
	{
		free(lexer->wilds);
		lexer->wilds = NULL;
	}
}

char	**lexer(t_ast *node, char *line)
{
	t_lexer			lexer;
	t_lexer_state	next_state;

	ft_bzero(&lexer, sizeof(lexer));
	lexer.node = node;
	lexer.state = LEXER_DEFAULT;
	lexer.cursor = line;
	lexer_action_skip_blank(&lexer);
	while (*(lexer.cursor))
	{
		next_state = get_next_state(&lexer);
		if (next_state)
			lexer_action(&lexer, next_state);
		else
			lexer_state(&lexer);
	}
	lexer_action(&lexer, LEXER_END_TOKEN);
	lexer_free(&lexer);
	return (lexer.tokens);
}
