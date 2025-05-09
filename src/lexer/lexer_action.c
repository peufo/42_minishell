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

void	lexer_action_next_char(t_lexer *lexer)
{
	if (*(lexer->cursor))
		lexer->cursor++;
}

void	lexer_action_skip_blank(t_lexer *lexer)
{
	char	**cursor;

	cursor = &lexer->cursor;
	while (**cursor == ' ' || **cursor == '\t' || **cursor == '\n')
		(*cursor)++;
}

void	lexer_action_end_token(t_lexer *lexer)
{
	if (!lexer->token.value)
		return ;
	lexer_expand_wildcard(lexer);
	if (!lexer->token.value)
		return ;
	string_array_push(&lexer->tokens, lexer->token.value);
	lexer->token.value = NULL;
}

void	lexer_action_ensure_token(t_lexer *lexer)
{
	string_push_str(&lexer->token, "");
	lexer->cursor++;
}

void	lexer_action(t_lexer *lexer, t_lexer_state next_state)
{
	t_lexer_handler			handler;
	static t_lexer_handler	handlers[][8] = {
	[LEXER_DEFAULT][LEXER_QUOTE] = lexer_action_ensure_token,
	[LEXER_DEFAULT][LEXER_DQUOTE] = lexer_action_ensure_token,
	[LEXER_DEFAULT][LEXER_META] = lexer_action_end_token,
	[LEXER_DEFAULT][LEXER_END_TOKEN] = lexer_action_end_token,
	[LEXER_VAR][LEXER_DEFAULT] = lexer_action_expand_var,
	[LEXER_VAR][LEXER_QUOTE] = lexer_action_expand_var,
	[LEXER_VAR][LEXER_DQUOTE] = lexer_action_expand_var,
	[LEXER_VAR][LEXER_META] = lexer_action_expand_var_end_token,
	[LEXER_VAR][LEXER_END_TOKEN] = lexer_action_expand_var_end_token,
	[LEXER_VAR_DQUOTE][LEXER_DQUOTE] = lexer_action_expand_var_dquote,
	[LEXER_VAR_DQUOTE][LEXER_DEFAULT] = lexer_action_expand_var_dquote,
	[LEXER_END_TOKEN][LEXER_DEFAULT] = lexer_action_skip_blank,
	};

	handler = handlers[lexer->state][next_state];
	if (!handler)
		handler = lexer_action_next_char;
	handler(lexer);
	lexer->state = next_state;
}
