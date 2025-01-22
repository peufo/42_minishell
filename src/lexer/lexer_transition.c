/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_transition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:21:54 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 14:12:42 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer_transition_next_char(t_lexer *lexer)
{
	lexer->line++;
}

static void	lexer_transition_skip_blank(t_lexer *p)
{
	while (*p->line == ' ' || *p->line == '\t' || *p->line == '\n')
		p->line++;
}

static void	lexer_transition_preserv_dollar(t_lexer *lexer)
{
	if (!lexer->varname.value)
		string_push(&lexer->token, '$');
	lexer->line++;
}

static void	lexer_transition_end_token(t_lexer *lexer)
{
	if (!lexer->token.value)
		return ;
	ft_lstadd_back(&lexer->tokens, ft_lstnew(lexer->token.value));
	lexer->token.value = NULL;
	lexer_transition_skip_blank(lexer);
}

void	lexer_transition(t_lexer *lexer, t_lexer_state next_state)
{
	t_lexer_transition_handler			handler;
	static t_lexer_transition_handler	handlers[][8] = {
	[LEXER_INIT][LEXER_DEFAULT] = lexer_transition_skip_blank,
	[LEXER_VAR][LEXER_DQUOTE] = lexer_transition_preserv_dollar,
	[LEXER_DEFAULT][LEXER_DEFAULT] = lexer_transition_end_token
	};

	handler = handlers[lexer->state][next_state];
	if (!handler)
		handler = lexer_transition_next_char;
	handler(lexer);
	lexer->state = next_state;
}
