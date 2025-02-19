/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:49:27 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/19 07:48:38 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	push_char_token(t_sh *shell)
{
	string_push_char(&shell->lexer.token, *shell->lexer.cursor);
	shell->lexer.cursor++;
}

static void	push_char_varname(t_sh *shell)
{
	string_push_char(&shell->lexer.varname, *shell->lexer.cursor);
	shell->lexer.cursor++;
}

static void	handle_meta_chars(t_sh *shell)
{
	lexer_action_skip_blank(shell);
	if (ft_include(CHARSET_META_VISIBLE, *shell->lexer.cursor))
	{
		push_char_token(shell);
		if (ft_include("|&<>", *shell->lexer.cursor))
			push_char_token(shell);
		lexer_action_end_token(shell);
	}
	shell->lexer.state = LEXER_DEFAULT;
}

void	lexer_state(t_sh *shell)
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

	handler = handlers[shell->lexer.state];
	if (handler)
		handler(shell);
}
