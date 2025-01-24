/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_transition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:21:54 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 15:33:37 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "minishell.h"

static void	lexer_transition_next_char(t_sh *shell)
{
	shell->lexer.cursor++;
}

static void	lexer_transition_skip_blank(t_sh *shell)
{
	char	**cursor;

	cursor = &shell->lexer.cursor;
	while (**cursor == ' ' || **cursor == '\t' || **cursor == '\n')
		(*cursor)++;
	if (**cursor == '#')
	{
		while (**cursor != '\0')
			(*cursor)++;
	}
}

static void	lexer_transition_preserv_dollar(t_sh *shell)
{
	if (!shell->lexer.varname.value)
		string_push(&shell->lexer.token, '$');
	shell->lexer.cursor++;
}

static void	lexer_transition_end_token(t_sh *shell)
{
	if (!shell->lexer.token.value)
		return ;
	ft_lstadd_back(&shell->lexer.tokens, ft_lstnew(shell->lexer.token.value));
	shell->lexer.token.value = NULL;
	lexer_transition_skip_blank(shell);
}

void	lexer_transition(t_sh *shell)//, t_lexer_state next_state)
{
	t_lexer_transition_handler			handler;
	static t_lexer_transition_handler	handlers[][8] = {
	[L_INIT][L_DEFAULT] = lexer_transition_skip_blank,
	[L_VAR][L_DQUOTE] = lexer_transition_preserv_dollar,
	[L_DEFAULT][L_DEFAULT] = lexer_transition_end_token,
	[L_IGNORE][L_DEFAULT] = lexer_transition_skip_blank
	};

	handler = handlers[shell->lexer.state][next_state];
	if (!handler)
		handler = lexer_transition_next_char;
	handler(shell);
	shell->lexer.state = next_state;
}
*/