/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/04 23:14:15 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	next_state_match(t_sh *shell, t_lexer_next_state *next)
{
	if (next->state != shell->lexer.state)
		return (false);
	if (!ft_include(next->charset, *shell->lexer.cursor))
		return (false);
	return (true);
}

static t_lexer_state	get_next_state(t_sh *shell)
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
		if (next_state_match(shell, next))
			return (next->next_state);
		next++;
	}
	return (LEXER_NO_STATE);
}

void	lex(t_sh *shell)
{
	t_lexer_state	next_state;

	lex_free(shell);
	shell->lexer.state = LEXER_INIT;
	shell->lexer.cursor = shell->line;
	lexer_action(shell, LEXER_DEFAULT);
	while (*(shell->lexer.cursor))
	{
		next_state = get_next_state(shell);
		if (next_state)
			lexer_action(shell, next_state);
		else
			lexer_state(shell);
	}
	lexer_action(shell, LEXER_DEFAULT);
}

void	lex_free(t_sh *shell)
{
	string_free(&shell->lexer.token);
	string_free(&shell->lexer.varname);
	ft_lstclear(&shell->lexer.tokens, free);
}
