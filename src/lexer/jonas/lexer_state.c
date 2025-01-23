/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:49:27 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 14:48:25 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	handle_state_default(t_sh *shell)
{
	string_push(&shell->lexer.token, *shell->lexer.cursor);
	shell->lexer.cursor++;
}

static void	handle_state_dquote(t_sh *shell)
{
	string_push(&shell->lexer.token, *shell->lexer.cursor);
	shell->lexer.cursor++;
}

static void	handle_state_quote(t_sh *shell)
{
	string_push(&shell->lexer.token, *shell->lexer.cursor);
	shell->lexer.cursor++;
}

void	lexer_state(t_sh *shell)
{
	t_lexer_state_handler			handler;
	static t_lexer_state_handler	handlers[] = {
	[L_DEFAULT] = handle_state_default,
	[L_QUOTE] = handle_state_quote,
	[L_DQUOTE] = handle_state_dquote,
	[L_VAR] = lexer_state_var,
	[L_VAR_DQUOTE] = lexer_state_var_dquote,
	};

	handler = handlers[shell->lexer.state];
	if (handler)
		handler(shell);
}*/
